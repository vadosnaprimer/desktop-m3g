#include "Texture2D.hpp"
#include "m3gdef.hpp"
#include <iostream>
#include "Image2D.hpp"
#include "Exception.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;
//#include <cstdlib>

Texture2D:: Texture2D (Image2D* img) :
  image(0), wrapping(WRAP_REPEAT, WRAP_REPEAT),
  filter(FILTER_BASE_LEVEL, FILTER_NEAREST),
  blending_mode(FUNC_MODULATE), blend_color(0x00000000),
  texobj(0)
{
  setObjectType (OBJTYPE_TEXTURE2D);

  if (img == NULL) {
    throw NullPointException (__FILE__, __func__, "Image is NULL.");
  }

  image = img;

  int format = image->getOpenGLFormat();
  int width  = image->getWidth();
  int height = image->getHeight();
  void* data = image->getOpenGLData();

  glGenTextures (1, &texobj);
  glBindTexture (GL_TEXTURE_2D, texobj);
  glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
  //glTexImage2D (GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
  gluBuild2DMipmaps (GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
  
  //cout << "AAA: gluBuild2DMipmaps, texobj = " << texobj << "\n";
}

Texture2D:: ~Texture2D ()
{
}

void Texture2D:: addAnimationTrack (AnimationTrack* animation_track)
{
  if (animation_track == NULL) {
    throw NullPointException (__FILE__, __func__, "Animation track is NULL.");
  }
  int property = animation_track->getTargetProperty();
  if (property != AnimationTrack::COLOR       &&
      property != AnimationTrack::ORIENTATION &&
      property != AnimationTrack::SCALE       &&
      property != AnimationTrack::TRANSLATION) {
    throw IllegalArgumentException (__FILE__, __func__, "Animation target is invalid for this VertexBuffer, property=%d.", property);
  }
 
  Object3D:: addAnimationTrack (animation_track);
}

int Texture2D:: animate (int world_time)
{
  Object3D:: animate (world_time);

  //cout << "Texture2D: animate, track=" << getAnimationTrackCount() << "\n";
  
  bool  is_color_modefied = false;
  float rgb[]  = {0,0,0};

  for (int i = 0; i < getAnimationTrackCount(); i++) {
    AnimationTrack*      track      = getAnimationTrack (i);
    KeyframeSequence*    keyframe   = track->getKeyframeSequence();
    AnimationController* controller = track->getController();
    if (controller == NULL) {
      //cout << "Texture2D: missing controller, this animation track is ignored.\n";
      continue;
    }
    if (!controller->isActiveInterval(world_time)) {
      continue;
    }
    float weight     = controller->getWeight ();
    float local_time = controller->getPosition (world_time);
    
    switch (track->getTargetProperty()) {
    case AnimationTrack::COLOR: {
      float value[3] = {1,1,1};
      keyframe->getFrame (local_time, value);
      rgb[0] += value[0] * weight;
      rgb[1] += value[1] * weight;
      rgb[2] += value[2] * weight;
      is_color_modefied = true;
      //cout << "Texture2D: default color --> " << rgb[0] << ", " << rgb[1] << ", " << rgb[2] << "\n";
      break;
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class (of Derived class) retrieve it.
    }
    }
  }

  if (is_color_modefied) {
    unsigned char r = clamp (0, 1, rgb[0]) * 255;
    unsigned char g = clamp (0, 1, rgb[1]) * 255;
    unsigned char b = clamp (0, 1, rgb[2]) * 255;
    //cout << "VertexBuffer: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
    blend_color = (blend_color & 0xff000000) | (r << 16) | (g << 8) | (b << 0);
  }

  //cout << hex << "Texture2D: blend color = 0x" << blend_color << dec << "\n";

  return 0;

}


int Texture2D:: getBlendColor () const
{
    return blend_color;
}

int Texture2D:: getBlending () const
{
    return blending_mode;
}

Image2D* Texture2D:: getImage () const
{
    return image;
}

int Texture2D:: getImageFilter () const
{
  return filter.image;
}

int Texture2D:: getLevelFilter () const
{
    return filter.level;
}

int Texture2D:: getWrappingS () const
{
    return wrapping.s;
}

int Texture2D:: getWrappingT () const
{
    return wrapping.t;
}

void Texture2D:: setBlendColor (int rgb)
{
  blend_color = rgb & 0x00ffffff;
}

void Texture2D:: setBlending (int func)
{
  if (func != FUNC_ADD && func != FUNC_BLEND && func != FUNC_DECAL &&
      func != FUNC_MODULATE && func != FUNC_REPLACE) {
    throw IllegalArgumentException (__FILE__, __func__, "Blending function is invalid, func=%d.", func);
  }

  blending_mode = func;
}

void Texture2D:: setFiltering (int level_filter, int image_filter)
{
  if (level_filter != FILTER_BASE_LEVEL && level_filter != FILTER_LINEAR && level_filter != FILTER_NEAREST ) {
    throw IllegalArgumentException (__FILE__, __func__, "Level filter is invalid, level_filter=%d.", level_filter);
  }
  if (image_filter != FILTER_LINEAR && image_filter != FILTER_NEAREST) {
    throw IllegalArgumentException (__FILE__, __func__, "Image filter is invalid, image_filter=%d.", image_filter);
  }

  filter.level = level_filter;
  filter.image = image_filter;
}

void Texture2D:: setImage (Image2D* img)
{
  image = img;
}

void Texture2D:: setWrapping (int wrap_s, int wrap_t)
{
  if (wrap_s != WRAP_CLAMP && wrap_s != WRAP_REPEAT) {
    throw IllegalArgumentException (__FILE__, __func__, "Wrap mode of S is invalid, wrap_s=%d.", wrap_s);
  }
  if (wrap_t != WRAP_CLAMP && wrap_t != WRAP_REPEAT) {
    throw IllegalArgumentException (__FILE__, __func__, "Wrap mode of T is invalid, wrap_t=%d.", wrap_t);
  }

  wrapping.s = wrap_s;
  wrapping.t = wrap_t;
}

/**
 * Note: Texture2D should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Texture2D:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  //cout << "Texture2D: render\n";

  glActiveTexture (GL_TEXTURE0+index);
  glBindTexture   (GL_TEXTURE_2D, texobj);

  switch (blending_mode) {
  case FUNC_ADD     : glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD); break;
  case FUNC_BLEND   : glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND); break;
  case FUNC_DECAL   : glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); break;
  case FUNC_MODULATE: glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); break;
  case FUNC_REPLACE : glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); break;
  default: throw IllegalStateException (__FILE__, __func__, "Blending mode is invalid, mode=%d.", blending_mode);
  }

  switch (filter.image) {
  case FILTER_BASE_LEVEL:
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    break;
  case FILTER_LINEAR:
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    break;
  case FILTER_NEAREST:
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    break;
  default:
    throw IllegalStateException (__FILE__, __func__, "Level filter is invalid.");
  }

  // filter.levelは？

  switch (wrapping.s) {
  case WRAP_CLAMP :  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); break;
  case WRAP_REPEAT:  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); break;
  default: throw IllegalStateException (__FILE__, __func__, "Wraping mode S is invalid, mode=%d.", wrapping.s);
  }

  switch (wrapping.t) {
  case WRAP_CLAMP :  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); break;
  case WRAP_REPEAT:  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); break;
  default: throw IllegalStateException (__FILE__, __func__, "Wraping mode T is invalid, mode=%d.", wrapping.t);
  }

  glEnable        (GL_TEXTURE_2D);
  //cout << "Texture2D: enabled = " << index << "\n";
  //cout << "Texture2D: error = " << glGetError() << "\n";
}

void Texture2D:: findByObjectType (int type, std::vector<Object3D*>& objs) const
{
  if (image) {
    image->findByObjectType (type, objs);
  }

  if (getObjectType() == type) {
    objs.push_back (const_cast<Texture2D*>(this));
  }
}

static 
const char* wrap_to_string (int wrap)
{
  switch (wrap) {
  case Texture2D::WRAP_CLAMP : return "CLAMP";
  case Texture2D::WRAP_REPEAT: return "REPEAT";
  default: return "Unknown";
  }
}

static 
const char* filter_to_string (int filter)
{
  switch (filter) {
  case Texture2D::FILTER_BASE_LEVEL: return "BASE_LEVEL";
  case Texture2D::FILTER_LINEAR    : return "FILTER_LINEAR";
  case Texture2D::FILTER_NEAREST   : return "FILTER_NEAREST";
  default: return "Unknown";
  }
}

static
const char* blending_to_string (int blending)
{
  switch (blending) {
  case Texture2D::FUNC_ADD     : return "ADD";
  case Texture2D::FUNC_BLEND   : return "BLEND";
  case Texture2D::FUNC_DECAL   : return "DECAL";
  case Texture2D::FUNC_MODULATE: return "MODULATE";
  case Texture2D::FUNC_REPLACE : return "REPLACE";
  default: return "Unknown";
  }
}

std::ostream& Texture2D:: print (std::ostream& out) const
{
  out << "Texture2D: ";
  out << "  wrapping=" << wrap_to_string(wrapping.s) << "," << wrap_to_string(wrapping.t);
  out << ", filter="   << filter_to_string(filter.level) << "," << filter_to_string(filter.image);
  out << ", blending=" << blending_to_string(blending_mode);
  out << ", blend_color=0x" << hex << blend_color << dec;
  return out << "\n";
}

std::ostream& operator<< (std::ostream& out, const Texture2D& tex)
{
  return tex.print(out);
}
