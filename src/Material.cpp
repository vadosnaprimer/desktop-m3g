#include <iostream>
#include "Material.hpp"
#include "Exception.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


Material:: Material () : 
  vertex_color_tracking(false), 
  ambient_color(0x00333333), diffuse_color(0xffcccccc), 
  emissive_color(0), specular_color(0), 
  shininess(0)
{
  setObjectType (OBJTYPE_MATERIAL);
}

Material:: ~Material ()
{
}


void Material:: addAnimationTrack (AnimationTrack* animation_track)
{
  if (animation_track == NULL) {
    throw NullPointException (__FILE__, __func__, "Animation_track is NULL.");
  }
  int property = animation_track->getTargetProperty();
  if (property != AnimationTrack::ALPHA &&
      property != AnimationTrack::AMBIENT_COLOR &&
      property != AnimationTrack::DIFFUSE_COLOR &&
      property != AnimationTrack::EMISSIVE_COLOR &&
      property != AnimationTrack::SHININESS && 
      property != AnimationTrack::SPECULAR_COLOR) {
    throw IllegalArgumentException (__FILE__, __func__, "Animation target is invalid for this Material, property=%d.", property);
  }
 
  Object3D:: addAnimationTrack (animation_track);
}

int Material:: animate (int world_time)
{
  //cout << "Material: animate, track=" << getAnimationTrackCount() << "\n";

  Object3D:: animate (world_time);
  
  bool  is_alpha_modefied = false;
  bool  is_ambient_color_modefied = false;
  bool  is_diffuse_color_modefied = false;
  bool  is_emissive_color_modefied = false;
  bool  is_shininess_modefied = false;
  bool  is_specular_color_modefied = false;
  float ambient_rgb[] = {0,0,0};
  float diffuse_rgb[] = {0,0,0};
  float emissive_rgb[] = {0,0,0};
  float specular_rgb[] = {0,0,0};
  float alpha  = 0;
  float new_shininess = 0;

  for (int i = 0; i < getAnimationTrackCount(); i++) {
    AnimationTrack*      track      = getAnimationTrack (i);
    KeyframeSequence*    keyframe   = track->getKeyframeSequence();
    AnimationController* controller = track->getController();
    if (controller == NULL) {
      //cout << "Material: missing controller, this animation track is ignored.\n";
      continue;
    }
    if (!controller->isActiveInterval(world_time)) {
      continue;
    }
    float weight     = controller->getWeight ();
    float local_time = controller->getPosition (world_time);
    
    switch (track->getTargetProperty()) {
    case AnimationTrack::ALPHA: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      alpha += value[0] * weight;
      is_alpha_modefied = true;
      //cout << "Material: alpha --> " << alpha << "\n";
      break;
    }
    case AnimationTrack::AMBIENT_COLOR: {
      float value[3] = {1,1,1};
      keyframe->getFrame (local_time, value);
      ambient_rgb[0] += value[0] * weight;
      ambient_rgb[1] += value[1] * weight;
      ambient_rgb[2] += value[2] * weight;
      is_ambient_color_modefied = true;
      //cout << "Material: ambient color --> " << ambient_rgb[0] << ", " << ambient_rgb[1] << ", " << ambient_rgb[2] << "\n";
      break;
    }
    case AnimationTrack::DIFFUSE_COLOR: {
      float value[3] = {1,1,1};
      keyframe->getFrame (local_time, value);
      diffuse_rgb[0] += value[0] * weight;
      diffuse_rgb[1] += value[1] * weight;
      diffuse_rgb[2] += value[2] * weight;
      is_diffuse_color_modefied = true;
      //cout << "Material: diffuse color --> " << diffuse_rgb[0] << ", " << ambient_rgb[1] << ", " << ambient_rgb[2] << "\n";
      break;
    }
    case AnimationTrack::EMISSIVE_COLOR: {
      float value[3] = {1,1,1};
      keyframe->getFrame (local_time, value);
      emissive_rgb[0] += value[0] * weight;
      emissive_rgb[1] += value[1] * weight;
      emissive_rgb[2] += value[2] * weight;
      is_emissive_color_modefied = true;
      //cout << "Material: emissive color --> " << emissive_rgb[0] << ", " << ambient_rgb[1] << ", " << ambient_rgb[2] << "\n";
      break;
    }
    case AnimationTrack::SHININESS: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      shininess += value[0] * weight;
      is_shininess_modefied = true;
      //cout << "Material: shininess --> " << shininess << "\n";
      break;
    }
    case AnimationTrack::SPECULAR_COLOR: {
      float value[3] = {1,1,1};
      keyframe->getFrame (local_time, value);
      specular_rgb[0] += value[0] * weight;
      specular_rgb[1] += value[1] * weight;
      specular_rgb[2] += value[2] * weight;
      is_specular_color_modefied = true;
      //cout << "Material: specular color --> " << specular_rgb[0] << ", " << ambient_rgb[1] << ", " << ambient_rgb[2] << "\n";
      break;
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class (of Derived class) retrieve it.
    }
    }
  }

  if (is_ambient_color_modefied) {
      unsigned char r = (ambient_rgb[0] <= 0) ? 0 : 
	(ambient_rgb[0] >= 1) ? 255 :
	ambient_rgb[0]*255;
      unsigned char g = (ambient_rgb[1] <= 0) ? 0 : 
	(ambient_rgb[1] >= 1) ? 255 : 
	ambient_rgb[1]*255;
      unsigned char b = (ambient_rgb[2] <= 0) ? 0 : 
	(ambient_rgb[2] >= 1) ? 255 : 
	ambient_rgb[2]*255;
      //cout << "Material: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
      ambient_color &= 0xff000000;
      ambient_color |= (r << 16) | (g << 8) | (b << 0);
  }
  if (is_diffuse_color_modefied) {
      unsigned char r = (diffuse_rgb[0] <= 0) ? 0 : 
	(diffuse_rgb[0] >= 1) ? 255 :
	diffuse_rgb[0]*255;
      unsigned char g = (diffuse_rgb[1] <= 0) ? 0 : 
	(diffuse_rgb[1] >= 1) ? 255 : 
	diffuse_rgb[1]*255;
      unsigned char b = (diffuse_rgb[2] <= 0) ? 0 : 
	(diffuse_rgb[2] >= 1) ? 255 : 
	diffuse_rgb[2]*255;
      //cout << "Material: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
      diffuse_color &= 0xff000000;
      diffuse_color |= (r << 16) | (g << 8) | (b << 0);
  }
  if (is_emissive_color_modefied) {
      unsigned char r = (emissive_rgb[0] <= 0) ? 0 : 
	(emissive_rgb[0] >= 1) ? 255 :
	emissive_rgb[0]*255;
      unsigned char g = (emissive_rgb[1] <= 0) ? 0 : 
	(emissive_rgb[1] >= 1) ? 255 : 
	emissive_rgb[1]*255;
      unsigned char b = (emissive_rgb[2] <= 0) ? 0 : 
	(emissive_rgb[2] >= 1) ? 255 : 
	emissive_rgb[2]*255;
      //cout << "Material: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
      emissive_color &= 0xff000000;
      emissive_color |= (r << 16) | (g << 8) | (b << 0);
  }
  if (is_alpha_modefied) {
      unsigned char a = (alpha <= 0) ? 0 :
	(alpha >= 1) ? 255 :
	(unsigned char)(alpha*255);
      diffuse_color &= 0x00ffffff;
      diffuse_color |= (a << 24);
  }
  if (is_shininess_modefied) {
    new_shininess = (new_shininess < 0) ? 0 :
      (new_shininess > 128) ? 128 :
      new_shininess;
    shininess = new_shininess;
  }
  if (is_specular_color_modefied) {
      unsigned char r = (specular_rgb[0] <= 0) ? 0 : 
	(specular_rgb[0] >= 1) ? 255 :
	specular_rgb[0]*255;
      unsigned char g = (specular_rgb[1] <= 0) ? 0 : 
	(specular_rgb[1] >= 1) ? 255 : 
	specular_rgb[1]*255;
      unsigned char b = (specular_rgb[2] <= 0) ? 0 : 
	(specular_rgb[2] >= 1) ? 255 : 
	specular_rgb[2]*255;
      //cout << "Material: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
      specular_color &= 0xff000000;
      specular_color |= (r << 16) | (g << 8) | (b << 0);
  }


  //cout << hex << "Material: ambient_color = 0x" << ambient_color << dec << "\n";
  //cout << hex << "Material: diffuse_color = 0x" << diffuse_color << dec << "\n";
  //cout << "Material: alpha = " << alpha << "\n";
  //cout << "Material: shininess = " << shininess << "\n";
  //cout << hex << "Material: specular_color = 0x" << specular_color << dec << "\n";

  return 0;
}

int Material:: getColor (int target) const
{
  switch (target) {
  case AMBIENT: {
    return ambient_color;
  }
  case DIFFUSE: {
    return diffuse_color;
  }
  case EMISSIVE: {
    return emissive_color;
  }
  case SPECULAR: {
    return specular_color;
  }
  default: {
    throw IllegalArgumentException (__FILE__, __func__, "Unknown target of getColor is specified.");
  }
  }
}

float Material:: getShininess () const
{
    return shininess;
}

bool Material:: isVertexColorTrackingEnabled () const
{
    return vertex_color_tracking;
}

void Material:: setColor (int target, int argb)
{
  switch (target) {
  case AMBIENT: {
    ambient_color = argb & 0x00ffffff;
    return;
  }
  case DIFFUSE: {
    diffuse_color = argb;
    return;
  }
  case EMISSIVE: {
    emissive_color = argb & 0x00ffffff;
    return;
  }
  case SPECULAR: {
     specular_color = argb & 0x00ffffff;
     return;
  }
  default: {
    throw IllegalArgumentException (__FILE__, __func__, "Target of setColor is invalid, target=%d.", target);
  }
  }
  
}

void Material:: setShininess (float value)
{
  shininess = value;
}

void Material:: setVertexColorTrackingEnable (bool enable)
{
  vertex_color_tracking = enable;
}

/**
 * Note: Material should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Material:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  //cout << "Material: render\n";
  Object3D::render (pass, index);

  GLfloat argb[4] = {0,0,0,0};

  argb[3] = ((ambient_color & 0xff000000) >> 24) / 255.f;
  argb[0] = ((ambient_color & 0x00ff0000) >> 16) / 255.f;
  argb[1] = ((ambient_color & 0x0000ff00) >> 8) / 255.f;
  argb[2] = ((ambient_color & 0x000000ff) >> 0) / 255.f;
  glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT,  argb);

  argb[3] = ((diffuse_color & 0xff000000) >> 24) / 255.f;
  argb[0] = ((diffuse_color & 0x00ff0000) >> 16) / 255.f;
  argb[1] = ((diffuse_color & 0x0000ff00) >> 8) / 255.f;
  argb[2] = ((diffuse_color & 0x000000ff) >> 0) / 255.f;
  glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE,  argb);
  
  // In no light, diffuse color of material shoud be used.
  glColor4f (argb[0], argb[1], argb[2], argb[3]);

  argb[3] = ((specular_color & 0xff000000) >> 24) / 255.f;
  argb[0] = ((specular_color & 0x00ff0000) >> 16) / 255.f;
  argb[1] = ((specular_color & 0x0000ff00) >> 8) / 255.f;
  argb[2] = ((specular_color & 0x000000ff) >> 0) / 255.f;
  glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, argb);

  argb[3] = ((emissive_color & 0xff000000) >> 24) / 255.f;
  argb[0] = ((emissive_color & 0x00ff0000) >> 16) / 255.f;
  argb[1] = ((emissive_color & 0x0000ff00) >> 8) / 255.f;
  argb[2] = ((emissive_color & 0x000000ff) >> 0) / 255.f;
  glMaterialfv (GL_FRONT_AND_BACK, GL_EMISSION, argb);

  //cout << *this;
}


 std::ostream& Material:: print (std::ostream& out) const
 {
   out << "Material: ambient=" << hex << ambient_color << ", diffuse=0x" << diffuse_color;
   out << ", emissive=0x" << emissive_color << ", specular=0x" << specular_color << dec;
   out << ", shininess=" << shininess << ", vertex_color_tracking=" << vertex_color_tracking << "\n";
   return out;
 }



std::ostream& operator<< (std::ostream& out, const Material& mat)
{
  return mat.print(out);
}
