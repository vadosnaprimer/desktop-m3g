#include <iostream>
#include "Transformable.hpp"
#include "Transform.hpp"
#include "m3gexcept.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;

Transformable:: Transformable () :
  scaling(1,1,1), translation(0,0,0), orientation(0,0,0,1)
{
  setObjectType(OBJTYPE_TRANSFORMABLE);
}

Transformable:: ~Transformable ()
{
}

void Transformable:: addAnimationTrack (AnimationTrack* animation_track)
{
   if (animation_track == NULL) {
    throw null_point_error ("Added animation_track is NULL.");
  }
  if (animation_track->getTargetProperty() != AnimationTrack::ORIENTATION &&
      animation_track->getTargetProperty() != AnimationTrack::SCALE &&
      animation_track->getTargetProperty() != AnimationTrack::TRANSLATION) {
    throw invalid_argument ("Invalid animation track target for this Transformable.");
  }
 
  Object3D:: addAnimationTrack (animation_track);
}

int Transformable:: animate (int world_time)
{
  //cout << "Transformable: animate, time=" << world_time << "\n";

  Object3D:: animate (world_time);

  bool  is_orientation_modefied = false;
  bool  is_scaling_modefied     = false;
  bool  is_translation_modefied = false;
  Quaternion  new_orientation = Quaternion();
  new_orientation.set (0,0,0,0);
  Scale       new_scaling     = Scale(0,0,0);
  Translation new_translation = Translation(0,0,0);

  
  
  for (int i = 0; i < getAnimationTrackCount(); i++) {
    AnimationTrack*      track      = getAnimationTrack (i);
    KeyframeSequence*    keyframe   = track->getKeyframeSequence();
    AnimationController* controller = track->getController();
    if (controller == NULL) {
      //cout << "Node: missing controller, this animation track is ignored.\n";
      continue;
    }
    if (!controller->isActiveInterval(world_time)) {
      continue;
    }
    float weight     = controller->getWeight ();
    float local_time = controller->getPosition (world_time);
    
    switch (track->getTargetProperty()) {
    case AnimationTrack:: ORIENTATION: {
      float value[4] = {0,0,0,0};  // Quaternion(x,y,z,w)
      keyframe->getFrame (local_time, value);
      Quaternion q;
      q.set (value[0], value[1], value[2], value[3]);
      new_orientation = new_orientation + q * weight;
      is_orientation_modefied = true;
      //cout << "Transformable: orientation --> " << new_orientation << "\n";
      break;
    }
    case AnimationTrack:: SCALE: {
      float value[3] = {0,0,0};
      keyframe->getFrame (local_time, value);
      if (keyframe->getComponentCount() == 3) {
	new_scaling = Scale(value[0]*weight, value[1]*weight, value[2]*weight);
      }
      else {
	new_scaling = Scale(value[0]*weight, value[0]*weight, value[0]*weight);	
      }
      is_scaling_modefied = true;
      //cout << "Transformable: scale --> " << new_scaling.x << ", " << new_scaling.y << ", " << new_scaling.z << "\n";
      break;
    }
    case AnimationTrack:: TRANSLATION: {
      float value[3] = {0,0,0};
      keyframe->getFrame (local_time, value);
      new_translation = Translation (value[0]*weight, value[1]*weight, value[2]*weight);
      is_translation_modefied = true;
      cout << "Transformable: translation --> " << new_translation.x << ", " << new_translation.y << ", " << new_translation.z << "\n";
      break;
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class (of Derived class) retrieve it.
    }
    }
  }

  if (is_orientation_modefied) {
    // メモ
    // 正規化必要？
    orientation = new_orientation;
  }
  if (is_scaling_modefied) {
    scaling = new_scaling;
  }
  if (is_translation_modefied) {
    translation = new_translation;
  }

  //cout << *this << "\n";
  
  return 0;
}

void Transformable:: getCompositeTransform (Transform* ctransform) const
{
  if (ctransform == NULL) {
    throw null_point_error ("Tranform is NULL.");
  }

  ctransform->setIdentity ();
  ctransform->postTranslate (translation.x, translation.y, translation.z);
  ctransform->postRotateQuat (orientation.x, orientation.y, orientation.z, orientation.w);
  ctransform->postScale (scaling.x, scaling.y, scaling.z);
  ctransform->postMultiply (transform);
}

void Transformable:: getOrientation (float* angle_axis) const
{
  if (angle_axis == NULL) {
    throw null_point_error ("Angle_axis is NULL.");
  }
  
  orientation.getAngleAxis (angle_axis);
}

void Transformable:: getScale (float* xyz) const
{
  if (xyz == NULL) {
    throw null_point_error ("Scaling xyz is NULL.");
  }

  xyz[0] = scaling.x;
  xyz[1] = scaling.y;
  xyz[2] = scaling.z;
}

void Transformable:: getTransform (Transform* out_transform) const
{
  if (out_transform == NULL) {
    throw null_point_error ("Transform is NULL.");
  }

  out_transform->set (transform);
}

void Transformable:: getTranslation (float* xyz) const
{
  if (xyz == NULL) {
    throw null_point_error ("Translation xyz is NULL.");
  }

  xyz[0] = translation.x;
  xyz[1] = translation.y;
  xyz[2] = translation.z;
}

void Transformable:: postRotate (float angle, float ax, float ay, float az)
{
    orientation = orientation * Quaternion (angle, ax,ay,az);
}

void Transformable:: preRotate (float angle, float ax, float ay, float az)
{
    orientation = Quaternion (angle, ax,ay,az) * orientation;
}

void Transformable:: scale (float sx, float sy, float sz)
{
  scaling.x *= sx;
  scaling.y *= sy;
  scaling.z *= sz;
}

void Transformable:: setOrientation (float angle, float ax, float ay, float az)
{
  orientation = Quaternion (angle, ax, ay, az);
}

void Transformable:: setScale (float sx, float sy, float sz)
{
  scaling.x = sx;
  scaling.y = sy;
  scaling.z = sz;
}

void Transformable:: setTransform (const Transform& in_transform)
{
  transform.set (in_transform);
}

void Transformable:: setTranslation (float tx, float ty, float tz)
{
  translation.x = tx;
  translation.y = ty;
  translation.z = tz;
}

void Transformable:: translate (float tx, float ty, float tz)
{
  translation.x += tx;
  translation.y += ty;
  translation.z += tz;
}

void Transformable:: render (int pass, int index) const
{
  Transform trans;
  getCompositeTransform(&trans);
  trans.transpose();

  float m[16];
  trans.get (m);
  glMultMatrixf ((GLfloat*)&m);

}

std::ostream& Transformable:: print (std::ostream& out) const
{
  out << "Transformable: ";
  out << " translation=" << translation.x << "," << translation.y << "," << translation.z;
  out << ", scale=" << scaling.x << "," << scaling.y << "," << scaling.z;
  out << ", orientation=" << orientation.x << "," << orientation.y << "," << orientation.z;
  out << ", transform=" << transform;
  return out << "\n";
}

std::ostream& operator<< (std::ostream& out, const Transformable& t)
{
  return t.print(out);
}
