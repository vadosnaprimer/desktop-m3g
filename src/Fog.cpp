#include "Fog.hpp"
#include <iostream>
#include <algorithm>
#include "Exception.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include "RenderState.hpp"
using namespace std;
using namespace m3g;

const int Fog:: EXPONENTIAL;
const int Fog:: LINEAR;

Fog:: Fog () : 
  mode(LINEAR), density(1), color(0), distance(0,1)
{
  setObjectType (OBJTYPE_FOG);
}

Fog:: ~Fog ()
{
}

Fog* Fog:: duplicate () const
{
  return new Fog (*this);
}

void Fog:: addAnimationTrack (AnimationTrack* animation_track)
{
  if (animation_track == NULL) {
    throw NullPointException (__FILE__, __func__, "Animation track is NULL.");
  }
  int property = animation_track->getTargetProperty();
  if (property != AnimationTrack::COLOR         &&
      property != AnimationTrack::DENSITY       &&
      property != AnimationTrack::FAR_DISTANCE  &&
      property != AnimationTrack::NEAR_DISTANCE &&
      property != AnimationTrack::ALPHA         &&
      property != AnimationTrack::PICKABILITY   &&
      property != AnimationTrack::VISIBILITY    &&
      property != AnimationTrack::ORIENTATION   &&
      property != AnimationTrack::SCALE         &&
      property != AnimationTrack::TRANSLATION) {
    throw IllegalArgumentException (__FILE__, __func__, "Animation track target is invalid for this Fog, property=%d.", property);
  }
 
  Object3D:: addAnimationTrack (animation_track);
}


int Fog :: animate (int world_time)
{
  Object3D:: animate (world_time);

  //cout << "Fog: animate, track=" << getAnimationTrackCount() << "\n";
  
  bool  is_color_modefied   = false;
  bool  is_density_modefied = false;
  bool  is_far_modefied     = false;
  bool  is_near_modefied    = false;
  float rgb[]       = {0,0,0};
  float new_density = 0;
  float new_far     = 0;
  float new_near    = 0;

  for (int i = 0; i < getAnimationTrackCount(); i++) {
    AnimationTrack*      track      = getAnimationTrack (i);
    KeyframeSequence*    keyframe   = track->getKeyframeSequence();
    AnimationController* controller = track->getController();
    if (controller == NULL) {
      //cout << "VertexBuffer: missing controller, this animation track is ignored.\n";
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
      //cout << "Fog: color --> " << rgb[0] << ", " << rgb[1] << ", " << rgb[2] << "\n";
      break;
    }
    case AnimationTrack::DENSITY: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_density += value[0] * weight;
      is_density_modefied = true;
      //cout << "Fog: density --> " << new_density << "\n";
      break;
    }
    case AnimationTrack::FAR_DISTANCE: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_far += value[0] * weight;
      is_far_modefied = true;
      //cout << "Fog: far --> " << new_far << "\n";
      break;
    }
    case AnimationTrack::NEAR_DISTANCE: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_near += value[0] * weight;
      is_near_modefied = true;
      //cout << "Fog: near --> " << new_near << "\n";
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
    unsigned char b = clamp (0, 1, rgb[1]) * 255;
    //cout << "Fog: r,g,b = " << (int)r << ", " << (int)g << ", " << (int)b << "\n";
    color = (r << 16) | (g << 8) | (b << 0);
  }
  if (is_density_modefied) {
    density = max (0.f, new_density);
  }
  if (is_far_modefied) {
    distance.far = new_far;
  }
  if (is_near_modefied) {
    distance.near = new_near;
  }

  //this->print (cout);

  return 0;
}

int Fog:: getColor () const
{
    return color;
}

float Fog:: getDensity () const
{
    return density;
}

float Fog:: getFarDistance () const
{
    return distance.far;
}

int Fog:: getMode () const
{
    return mode;
}

float Fog:: getNearDistance () const
{
    return distance.near;
}

void Fog:: setColor (int rgb)
{
  color = rgb & 0x00ffffff;
}

void Fog:: setDensity (float dens)
{
  if (dens < 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Density is invalid, dens=%f.", dens);
  }

  density = dens;
}

void Fog:: setLinear (float near, float far)
{
  if (near == far) {
    // M3Gでは定義されてないが将来的に確実に0割を発生するため
    // ここでエラーとする
    throw IllegalArgumentException (__FILE__, __func__, "Near and far are invalid, n=%f, n=%f.", near, far);
  }

  distance.near = near;
  distance.far  = far;
}

void Fog:: setMode (int mode_)
{
  if (mode_ != LINEAR && mode_ != EXPONENTIAL) {
    throw IllegalArgumentException (__FILE__, __func__, "Mode is invalid, mode=%d, \n", mode_);
  }

  mode = mode_;
}


/**
 * Note: Fog should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Fog:: render (RenderState& state) const
{
  if (state.pass != 2) {
    return;
  }

  //cout << "Fog: render\n";

  glEnable (GL_FOG);

  GLfloat rgb[3] = {((color & 0x00ff0000) >> 16) / 255.f,
                    ((color & 0x0000ff00) >> 8 ) / 255.f,
                    ((color & 0x000000ff) >> 0 ) / 255.f};

  switch (mode) {
  case EXPONENTIAL:
    glFogi  (GL_FOG_MODE   , GL_EXP);
    glFogf  (GL_FOG_DENSITY, density);
    glFogfv (GL_FOG_COLOR  , rgb);
    break;
  case LINEAR:
    glFogi  (GL_FOG_MODE , GL_LINEAR);
    glFogf  (GL_FOG_START, distance.near);
    glFogf  (GL_FOG_END  , distance.far);
    glFogfv (GL_FOG_COLOR, rgb);
    break;
  default:
    throw InternalException (__FILE__, __func__, "Fog mode is unknwon, mode=%d.", mode);
  }

}


void Fog:: renderX ()
{
  glDisable (GL_FOG);
}

static
const char* mode_to_string (int mode)
{
  switch (mode) {
  case Fog::LINEAR     : return "LINEAR";
  case Fog::EXPONENTIAL: return "EXPONENTIAL";
  default: return "Unknwon";
  }
}

std::ostream& Fog:: print (std::ostream& out) const
{
  out << "Fog: ";
  out << "  mode=" << mode_to_string(mode);
  out << ", density=" << density;
  out << ", near=" << distance.near;
  out << ", far=" << distance.far;
  out << ", color=0x" << hex << color << dec; 
  return out;
}

 std::ostream& operator<< (std::ostream& out, const Fog& fog)
{
  return fog.print(out);
}



