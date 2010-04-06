#include "Sprite3D.hpp"
#include <iostream>
#include <cmath>
#include "Appearance.hpp"
#include "Image2D.hpp"
#include "Exception.hpp"
#include "Graphics3D.hpp"
#include "Vector.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


Sprite3D:: Sprite3D (bool scaled_, Image2D* image_, Appearance* appearance_) :
  scaled(false), image(0), appearance(0), crop(0,0,0,0),
  texobj(0)
{
  setObjectType (OBJTYPE_SPRITE3D);

  if (image_ == NULL) {
    throw NullPointException (__FILE__, __func__, "Image is NULL.");
  }

  scaled      = scaled_;
  image       = image_;
  appearance  = appearance_;
  crop.x      = 0;
  crop.y      = 0;
  crop.width  = image->getWidth();
  crop.height = image->getHeight();

  int format = image->getOpenGLFormat ();
  void* data = image->getOpenGLData ();

  glGenTextures   (1, &texobj);
  glBindTexture   (GL_TEXTURE_2D, texobj);
  glPixelStorei   (GL_UNPACK_ALIGNMENT, 1);

  //glTexImage2D    (GL_TEXTURE_2D, 0, format, background_width, background_height, 0, format, GL_UNSIGNED_BYTE, data);
  gluBuild2DMipmaps (GL_TEXTURE_2D, GL_RGBA, image->getWidth(), image->getHeight(), format, GL_UNSIGNED_BYTE, data);

}

Sprite3D:: ~Sprite3D ()
{
}

void Sprite3D:: addAnimationTrack (AnimationTrack* animation_track)
{
  if (animation_track == NULL) {
    throw NullPointException (__FILE__, __func__, "Animation track is NULL.");
  }
  int property = animation_track->getTargetProperty();
  if (property != AnimationTrack::CROP        &&
      property != AnimationTrack::ALPHA       &&
      property != AnimationTrack::PICKABILITY &&
      property != AnimationTrack::VISIBILITY  &&
      property != AnimationTrack::ORIENTATION &&
      property != AnimationTrack::SCALE       &&
      property != AnimationTrack::TRANSLATION) {
    throw IllegalArgumentException (__FILE__, __func__, "Animation target is invalid for this Sprite3D, property=%d.", property);
  }
 
  Object3D:: addAnimationTrack (animation_track);
}

int Sprite3D:: animate (int world_time)
{
  Object3D:: animate (world_time);

  //cout << "Sprite3D: animte, time=" << world_time << "\n";

  bool  is_crop_modefied = false;
  CropRect new_crop = CropRect(0,0,0,0);
    
  for (int i = 0; i < getAnimationTrackCount(); i++) {
    AnimationTrack*      track      = getAnimationTrack (i);
    KeyframeSequence*    keyframe   = track->getKeyframeSequence();
    AnimationController* controller = track->getController();
    if (controller == NULL) {
      //cout << "Sprite3D: missing controller, this animation track is ignored.\n";
      continue;
    }
    if (!controller->isActiveInterval(world_time)) {
      continue;
    }
    float weight     = controller->getWeight ();
    float local_time = controller->getPosition (world_time);
    
    switch (track->getTargetProperty()) {
    case AnimationTrack:: CROP: {
      float value[4] = {0,0,0,0};
      keyframe->getFrame (local_time, value);
      if (keyframe->getComponentCount() == 4) {
	new_crop.x      += value[0] * weight;
	new_crop.y      += value[1] * weight;
	new_crop.width  += value[2] * weight;
	new_crop.height += value[3] * weight;
      }
      else {
	new_crop.x      += value[0] * weight;
	new_crop.y      += value[1] * weight;
	new_crop.width  += crop.width * weight;
	new_crop.height += crop.height * weight;
	
      }
      is_crop_modefied = true;
      //cout << "Sprite3D: crop --> " << crop.x << ", " << crop.y << ", " << crop.width << ", " << crop.height << "\n";
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class (of Derived class) retrieve it.
    }
    }
  }

  if (is_crop_modefied) {
    crop = new_crop;
  }
  
  return 0;
}

Appearance* Sprite3D:: getAppearance () const
{
  return appearance;
}

int Sprite3D:: getCropHeight () const
{
  return crop.height;
}

int Sprite3D:: getCropWidth () const
{
  return crop.width;
}

int Sprite3D:: getCropX () const
{
  return crop.x;
}

int Sprite3D:: getCropY () const
{
  return crop.y;
}

Image2D* Sprite3D:: getImage () const
{
  return image;
}

bool Sprite3D:: isScaled () const
{
  return scaled;
}

void Sprite3D:: setAppearance (Appearance* appearance_)
{
  appearance = appearance_;
}

void Sprite3D:: setCrop (int crop_x, int crop_y, int width, int height)
{
  crop.x      = crop_x;
  crop.y      = crop_y;
  crop.width  = width;
  crop.height = height;
}



void Sprite3D:: setImage (Image2D* image_)
{
  if (image_ == NULL) {
    throw NullPointException (__FILE__, __func__, "Image is NULL.");
  }

  image       = image_;
  crop.x      = 0;
  crop.y      = 0;
  crop.width  = image->getWidth();
  crop.height = image->getHeight();
  
}

/**
 * Note: Sprite3D should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Sprite3D:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  if (appearance) {
    //cout << "Sprite3D: render, layer=" << appearance->getLayer() <<  "\n";
  }
  else {
    //cout << "Sprite3D: render, layer=0\n";
  }

  Node:: render (pass, index);
  if (appearance) {
    appearance->render(pass, index);
  }

  Matrix model_view;
  Matrix projection;
  Matrix model_view_projection;
  GLfloat m[16];
  glGetFloatv (GL_MODELVIEW_MATRIX, m);
  model_view.set (m);
  model_view.transpose ();
  glGetFloatv (GL_PROJECTION_MATRIX, m);
  projection.set (m);
  projection.transpose ();
  model_view_projection = projection * model_view;
  //cout << model_view_projection << "\n";
  float tx = model_view_projection.m[0][3]/model_view_projection.m[3][3];
  float ty = model_view_projection.m[1][3]/model_view_projection.m[3][3];
  float tz = model_view_projection.m[2][3]/model_view_projection.m[3][3];

  Graphics3D* g3d = Graphics3D::getInstance();
  float viewport_width  = g3d->getViewportWidth();
  float viewport_height = g3d->getViewportHeight();
  //cout << "Sprite3D: viewport width = " << viewport_width << "\n";
  //cout << "Sprite3D: viewport height = " << viewport_height << "\n";
  //cout << "Sprite3D: crop width = " << crop.width << "\n";
  //cout << "Sprite3D: crop height = " << crop.height << "\n";

  GLfloat rgba[4] = {1,1,1,0};
  glEnable (GL_TEXTURE_2D);
  glEnable (GL_ALPHA_TEST);
  glBindTexture    (GL_TEXTURE_2D, texobj);
  glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri  (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexParameterfv (GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, rgba);
  glTexEnvi        (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glAlphaFunc      (GL_GREATER, 0);

  float x = (crop.width  >= 0) ? crop.x : (-crop.width + crop.x);
  float y = (crop.height >= 0) ? crop.y : (-crop.height + crop.y);
  float s0 = x / image->getWidth();
  float t0 = (image->getHeight() - y) / image->getHeight();
  float s1 = (x + crop.width) / image->getWidth();
  float t1 = (image->getHeight() - (y + crop.height)) / image->getHeight();
  //cout << "s = (" << s0 << ", " << s1 << ")\n";
  //cout << "t = (" << t0 << ", " << t1 << ")\n";

  if (scaled) {
    Vector o  = model_view * Vector(0,0,0);
    Vector px = model_view * Vector(1,0,0);
    Vector py = model_view * Vector(0,1,0);
    //cout << "o  = " << o << "\n";
    //cout << "px = " << px << "\n";
    //cout << "py = " << py << "\n";
    float  dx = fabsf(px.x - o.x);
    float  dy = fabsf(py.y - o.y);
    //cout << "dx = " << dx << "\n";
    //cout << "dy = " << dy << "\n";
    Vector oo  = projection * o;
    Vector ppx = projection * (o + Vector(dx,0,0,0));
    Vector ppy = projection * (o + Vector(0,dy,0,0));
    //cout << "oo  = " << oo << "\n";
    //cout << "ppx = " << ppx << "\n";
    //cout << "ppy = " << ppy << "\n";
    float  width  = fabsf(ppx.x/ppx.w - oo.x/oo.w);
    float  height = fabsf(ppy.y/ppy.w - oo.y/oo.w);

    //cout << "Sprite3D: scaled (clip-coord) width = " << width << "\n";
    //cout << "Sprite3D: scaled (clip-coord) height = " << height << "\n";

    glMatrixMode   (GL_PROJECTION);
    glPushMatrix   ();
    glLoadIdentity ();
    glMatrixMode   (GL_MODELVIEW);
    glPushMatrix   ();
    glLoadIdentity ();

    glBegin      (GL_TRIANGLE_STRIP);
    glColor4f    (1,1,1,1);
    glTexCoord2f (s1, t1);
    glVertex3f   (tx+width/2.f, ty-height/2.f, tz);
    glTexCoord2f (s1, t0);
    glVertex3f   (tx+width/2.f, ty+height/2.f, tz);
    glTexCoord2f (s0, t1);
    glVertex3f   (tx-width/2.f, ty-height/2.f, tz);
    glTexCoord2f (s0, t0);
    glVertex3f   (tx-width/2.f, ty+height/2.f, tz);
    glEnd        ();

    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();
    glMatrixMode (GL_MODELVIEW);
    glPopMatrix ();

  } else {
    
    float width  = 2*image->getWidth()/viewport_width;
    float height = 2*image->getHeight()/viewport_height;
    //cout << "Sprite3D: unscaled (clip-coord) width = " << width << "\n";
    //cout << "Sprite3D: unscaled (clip-coord) height = " << height << "\n";

    glMatrixMode   (GL_PROJECTION);
    glPushMatrix   ();
    glLoadIdentity ();
    glMatrixMode   (GL_MODELVIEW);
    glPushMatrix   ();
    glLoadIdentity ();

    glBegin      (GL_TRIANGLE_STRIP);
    glColor4f    (1,1,1,1);
    glTexCoord2f (s1, t1);
    glVertex3f   (tx+width/2.f, ty-height/2.f, tz);
    glTexCoord2f (s1, t0);
    glVertex3f   (tx+width/2.f, ty+height/2.f, tz);
    glTexCoord2f (s0, t1);
    glVertex3f   (tx-width/2.f, ty-height/2.f, tz);
    glTexCoord2f (s0, t0);
    glVertex3f   (tx-width/2.f, ty+height/2.f, tz);
    glEnd        ();

    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();
    glMatrixMode (GL_MODELVIEW);
    glPopMatrix ();

  }
}

int Sprite3D:: getLayer () const
{
  if (appearance) {
    return appearance->getLayer();
  } else {
    return 0;
  }
}


bool Sprite3D:: sort_by_layer (const Sprite3D* lhs, const Sprite3D* rhs)
{
  return lhs->getLayer() < rhs->getLayer();
}


std::ostream& Sprite3D:: print (std::ostream& out) const
{
  int width  = image ? image->getWidth() : 0;
  int height = image ? image->getHeight() : 0;
  out << "Sprite3D: ";
  out << "  scaled=" << scaled;
  out << ", image=0x" << image << "(" << width << "x" << height << ")";
  out << ", appearance=0x" << appearance;
  out << ", crop=" << crop.x << "," << crop.y << "," << crop.width << "," << crop.height;
  return out << "\n";;
}

std::ostream& operator<< (std::ostream& out, const Sprite3D& spr)
{
  return spr.print(out);
}


