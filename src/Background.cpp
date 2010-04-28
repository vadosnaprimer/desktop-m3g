#include <iostream>
#include <cmath>
#include "Background.hpp"
#include "Image2D.hpp"
#include "Exception.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include "RenderState.hpp"
using namespace std;
using namespace m3g;


Background:: Background () :
  color_clear_enable(true), depth_clear_enable(true), background_color(0x00000000), 
  background_image(0), image_mode(BORDER,BORDER), crop_rectangle(0,0,0,0),
  texobj(0)
{
  setObjectType (OBJTYPE_BACKGROUND);
}

Background:: ~Background ()
{
}

Background* Background:: duplicate () const
{
  return new Background (*this);
}

void Background:: addAnimationTrack (AnimationTrack* animation_track)
{
  if (animation_track == NULL) {
    throw NullPointException (__FILE__, __func__, "Animation track is NULL.");
  }
  int property = animation_track->getTargetProperty();
  if (property != AnimationTrack::ALPHA &&
      property != AnimationTrack::COLOR &&
      property != AnimationTrack::CROP) {
    throw IllegalArgumentException (__FILE__, __func__, "Animation track target is invalid for this Background, property=%d", property);
  }

  Object3D:: addAnimationTrack (animation_track);
}

int Background:: animate (int world_time)
{
  //cout << "Background: animate time=" << world_time << "\n";

  Object3D:: animate (world_time);

  bool     is_color_modefied = false;
  bool     is_alpha_modefied = false;
  bool     is_crop_modefied  = false;
  float    new_color[] = {0,0,0};
  float    new_alpha   = 0;
  CropRect new_crop    = CropRect(0,0,0,0);
    
  for (int i = 0; i < getAnimationTrackCount(); i++) {
    AnimationTrack*      track      = getAnimationTrack (i);
    KeyframeSequence*    keyframe   = track->getKeyframeSequence();
    AnimationController* controller = track->getController();
    if (controller == NULL) {
      //cout << "Background: missing controller, this animation track should be ignored.\n";
      continue;
    }
    if (world_time < controller->getActiveIntervalStart() || world_time >= controller->getActiveIntervalEnd()) {
      continue;
    }
    float weight     = controller->getWeight ();
    float local_time = controller->getPosition (world_time);
    
    switch (track->getTargetProperty()) {
    case AnimationTrack:: ALPHA: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_alpha += value[0] * weight;
      is_alpha_modefied = true;
      //cout << "Background: alpha --> " << new_alpha << "\n";
      break;
    }
    case AnimationTrack:: CROP: {
      float value[4] = {0,0,0,0};
      keyframe->getFrame (local_time, value);
      if (keyframe->getComponentCount() == 4) {
	new_crop.x      += value[0] * weight;
	new_crop.y      += value[1] * weight;
	new_crop.width  += value[2] * weight;
	new_crop.height += value[3] * weight;
      } else {
	new_crop.x      += value[0] * weight;
	new_crop.y      += value[1] * weight;
	new_crop.width  += crop_rectangle.width * weight;
	new_crop.height += crop_rectangle.height * weight;
	
      }
      is_crop_modefied = true;
      //cout << "Background: crop --> " << crop.x << ", " << crop.y << ", " << crop.width << ", " << crop.height << "\n";
    }
    case AnimationTrack:: COLOR: {
      float value[3] = {1,1,1};
      keyframe->getFrame (local_time, value);
      new_color[0] += value[0] * weight;
      new_color[1] += value[1] * weight;
      new_color[2] += value[2] * weight;
      is_color_modefied = true;
      //cout << "Background: color --> " << new_color[0] << ", " << new_color[1] << ", " << new_color[2]  << "\n";
      break;
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class (of Derived class) retrieve it.
    }
    }
  }

  if (is_crop_modefied) {
    new_crop.width  = max(0.f, new_crop.width);
    new_crop.height = max(0.f, new_crop.height);
    crop_rectangle  = CropRect(new_crop.x, new_crop.y, new_crop.width, new_crop.height);
  }
  if (is_color_modefied) {
    unsigned char r  = clamp(0, 1, new_color[0]) * 255;
    unsigned char g  = clamp(0, 1, new_color[1]) * 255;
    unsigned char b  = clamp(0, 1, new_color[2]) * 255;
    background_color = (background_color & 0xff000000) | (r << 16) | (g << 8) | (b << 0);
  }
  if (is_alpha_modefied) {
    unsigned char a  = clamp(0, 1, new_alpha) * 255;
    background_color = (background_color & 0x00ffffff) | (a << 24);
  }
  
  return 0;

}

int Background:: getColor () const
{
    return background_color;
}

int Background:: getCropHeight () const
{
    return crop_rectangle.height;
}

int Background:: getCropWidth () const
{
    return crop_rectangle.width;
}
    
int Background:: getCropX () const
{
    return crop_rectangle.x;
}

int Background:: getCropY () const
{
  return crop_rectangle.y;
}

Image2D* Background:: getImage () const
{
  return background_image;
}

int Background:: getImageModeX () const
{
    return image_mode.x;
}

int Background:: getImageModeY () const
{
    return image_mode.y;
}

bool Background:: isColorClearEnabled () const
{
    return color_clear_enable;
}


bool Background:: isDepthClearEnabled () const
{
    return depth_clear_enable;
}

void Background:: setColor (int argb)
{
  background_color = argb;
}

void Background:: setColorClearEnable (bool enable)
{
  color_clear_enable = enable;
}

void Background:: setCrop (int crop_x, int crop_y, int width, int height)
{
  crop_rectangle = CropRect(crop_x, crop_y, width, height);
}

void Background:: setDepthClearEnable (bool enable)
{
  depth_clear_enable = enable;
}

void Background:: setImage (Image2D* image)
{
  background_image  = image;
  background_width  = image->getWidth ();
  background_height = image->getHeight ();
  crop_rectangle = CropRect (0,0,background_width,background_height);

  int format = image->getOpenGLFormat ();
  void* data = image->getOpenGLData ();

  glGenTextures   (1, &texobj);
  glBindTexture   (GL_TEXTURE_2D, texobj);
  glPixelStorei   (GL_UNPACK_ALIGNMENT, 1);

  //glTexImage2D    (GL_TEXTURE_2D, 0, format, background_width, background_height, 0, format, GL_UNSIGNED_BYTE, data);
  gluBuild2DMipmaps (GL_TEXTURE_2D, format, background_width, background_height, format, GL_UNSIGNED_BYTE, data);

}

void Background:: setImageMode (int mode_x, int mode_y)
{
  if ((mode_x != REPEAT && mode_x != BORDER) ||
      (mode_y != REPEAT && mode_y != BORDER)) {
    throw IllegalArgumentException (__FILE__, __func__, "Mode is invalid, x=%d, y=%d.\n", mode_x, mode_y);
  }

  image_mode = ImageMode(mode_x, mode_y);
}



/**
 * Note: Background should be rendered only at 0th rendering pass(pass=0).
 * In other cases, do nothing.
 */
void Background:: render (RenderState& state) const
{
  if (state.pass != 0) {
    return;
  }

  //cout << "Background: render\n";

  float r = ((background_color & 0x00ff0000) >> 16) / 255.f;
  float g = ((background_color & 0x0000ff00) >>  8) / 255.f;
  float b = ((background_color & 0x000000ff) >>  0) / 255.f;
  float a = ((background_color & 0xff000000) >> 24) / 255.f;
  float rgba[4] = {r,g,b,a};

  glClearColor (r,g,b,a);
  glClearDepth (1.f);

  if (color_clear_enable) {
    //cout << "Background: glClear (GL_COLOR_BUFFER_BIT)\n";
    glClear (GL_COLOR_BUFFER_BIT);
  }
  if (depth_clear_enable) {
    //cout << "Background: glClear (GL_DEPTH_BUFFER_BIT)\n";
    glClear (GL_DEPTH_BUFFER_BIT);
  }
  if (background_image) {
    //cout << "Background: render image, texobj = " << texobj << "\n";
    glBindTexture    (GL_TEXTURE_2D, texobj);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvi        (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    if (image_mode.x == BORDER) {
      glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
      glTexParameterfv (GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (GLfloat*)&rgba);
    } else {
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    }
    if (image_mode.y == BORDER) {
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
      glTexParameterfv (GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, (GLfloat*)&rgba);
    } else {
      glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glMatrixMode   (GL_PROJECTION);
    glPushMatrix   ();
    glLoadIdentity ();
    glMatrixMode   (GL_MODELVIEW);
    glPushMatrix   ();
    glLoadIdentity ();

    float s0 = crop_rectangle.x / background_width;
    float t0 = (background_height - crop_rectangle.y) / background_height;
    float s1 = (crop_rectangle.x + crop_rectangle.width) / background_width;
    float t1 = (background_height - (crop_rectangle.y + crop_rectangle.height)) / background_height;
    glBegin      (GL_TRIANGLE_STRIP);
    glTexCoord2f (s1, t1);
    glVertex3f   (1, -1, 0.99999);
    glTexCoord2f (s1, t0);
    glVertex3f   (1, 1,  0.99999);
    glTexCoord2f (s0, t1);
    glVertex3f   (-1, -1, 0.99999);
    glTexCoord2f (s0, t0);
    glVertex3f   (-1, 1,  0.99999);
    glEnd        ();

    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();
    glMatrixMode (GL_MODELVIEW);
    glPopMatrix ();

    glEnable (GL_TEXTURE_2D);

  }
}

static
const char* mode_to_string (int mode)
{
  switch (mode) {
  case Background::BORDER: return "BORDER";
  case Background::REPEAT: return "REPEAT";
  default: return "Unknown";
  }
}

std::ostream& Background:: print (std::ostream& out) const
{
  out << "Background: ";
  out << "  color clear="        << color_clear_enable;
  out << ", depth clear="        << depth_clear_enable;
  out << ", background color=0x" << hex << background_color << dec;
  out << ", background image="   << background_image;
  out << ", image mode="         << mode_to_string(image_mode.x);
  out << ","                     << mode_to_string(image_mode.y);
  out << ", crop rectangle="     << crop_rectangle.x;
  out << ","                     << crop_rectangle.y;
  out << ","                     << crop_rectangle.width;
  out << ","                     << crop_rectangle.height;
  return out;
}

std::ostream& operator<< (std::ostream& out, const Background& bg)
{
  return bg.print (out);
}
