#include <iostream>
#include <cmath>
#include "Camera.hpp"
#include "Vector.hpp"
#include "Transform.hpp"
#include "m3gexcept.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


Camera:: Camera () :
type(GENERIC), fovy(0), aspect_ratio(0), near(0), far(0)
{
  setObjectType (OBJTYPE_CAMERA);
}

Camera:: ~Camera ()
{
}

void Camera:: addAnimationTrack (AnimationTrack* animation_track)
{
   if (animation_track == NULL) {
    throw null_point_error ("Added animation_track is NULL.");
  }
  if (animation_track->getTargetProperty() != AnimationTrack::FAR_DISTANCE  &&
      animation_track->getTargetProperty() != AnimationTrack::FIELD_OF_VIEW &&
      animation_track->getTargetProperty() != AnimationTrack::NEAR_DISTANCE &&
      animation_track->getTargetProperty() != AnimationTrack::ALPHA         &&
      animation_track->getTargetProperty() != AnimationTrack::PICKABILITY   &&
      animation_track->getTargetProperty() != AnimationTrack::VISIBILITY    &&
      animation_track->getTargetProperty() != AnimationTrack::ORIENTATION   &&
      animation_track->getTargetProperty() != AnimationTrack::SCALE         &&
      animation_track->getTargetProperty() != AnimationTrack::TRANSLATION) {
    throw invalid_argument ("Invalid animation track target for this Camera.");
  }
 
  Object3D:: addAnimationTrack (animation_track);
}

int Camera:: animate (int world_time)
{
  //cout << "Camera: animate, time=" << world_time << "\n";

  Object3D:: animate (world_time);

  bool  is_far_modefied  = false;
  bool  is_fovy_modefied = false;
  bool  is_near_modefied  = false;
  float new_far  = 0;
  float new_fovy = 0;
  float new_near  = 0;
  
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
    case AnimationTrack:: FAR_DISTANCE: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_far += value[0] * weight;
      is_far_modefied = true;
      //cout << "Camera: far --> " << new_far << "\n";
      break;
    }
    case AnimationTrack::FIELD_OF_VIEW: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_fovy += value[0] * weight;
      is_fovy_modefied = true;
      //cout << "Fog: fovy --> " << new_fovy << "\n";
      break;
    }
    case AnimationTrack:: NEAR_DISTANCE: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_near += value[0] * weight;
      is_near_modefied = true;
      //cout << "Camera: near --> " << new_near << "\n";
      break;
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class (of Derived class) retrieve it.
    }
    }
  }

  if (is_far_modefied) {
    if (type == PARALLEL) {
      new_far = (new_far < M3G_EPSILON) ? M3G_EPSILON : 0;
    }
    far = new_far;
  }
  if (is_fovy_modefied) {
    if (type == PERSPECTIVE) {
      new_fovy = clamp (0, 180, new_fovy);
    }
    else {
      new_fovy = (new_fovy < M3G_EPSILON) ? M3G_EPSILON : 0;
    }
    fovy = new_fovy;
  }
  if (is_near_modefied) {
    if (type == PERSPECTIVE) {
      new_near = (new_near < M3G_EPSILON) ? M3G_EPSILON : 0;
    }
    near = new_near;
  }

  
  return 0;
}


int Camera:: getProjection (float* params) const
{
  if (params) {
    params[0] = fovy;
    params[1] = aspect_ratio;
    params[2] = near;
    params[3] = far;
  }
  return type;
}

int Camera:: getProjection (Transform* transform) const
{
  if (transform) {
    transform->set (proj_trans);
  }
  return type;
}

void Camera:: setGeneric (const Transform& transform)
{
  type = GENERIC;
  proj_trans.set (transform);
}

void Camera:: setParallel (float fovy_, float aspect_ratio_, float near_, float far_)
{
  type         = PARALLEL;
  fovy         = fovy_;
  aspect_ratio = aspect_ratio_;
  near         = near_;
  far          = far_;
}

void Camera:: setPerspective (float fovy_, float aspect_ratio_, float near_, float far_)
{
  type         = PERSPECTIVE;
  fovy         = fovy_;
  aspect_ratio = aspect_ratio_;
  near         = near_;
  far          = far_;
}

/**
 * Note: Camera should be rendered only at 0th rendering pass(pass=0).
 * In other cases, do nothing.
 */
void Camera:: render (int pass, int index) const
{
  if (pass != 0) {
    return;
  }

  //cout << "Camera: render, " << *this << "\n";

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (type == PERSPECTIVE) {
      gluPerspective (fovy, aspect_ratio, near, far);
      //gluPerspective (45, 1.3333, 1, 100);
    }
    else if (type == PARALLEL) {
      float left   = -fovy*aspect_ratio/2.f;
      float right  =  fovy*aspect_ratio/2.f;
      float bottom = -fovy/2.f;
      float top    =  fovy/2.f;
      glOrtho (left, right, bottom, top, near, far);
    }
    else if (type == GENERIC) {
      float m[16];
      proj_trans.get (m);
      glMultMatrixf (m);
    }
    else {
      throw domain_error ("Projection type of Camera is unknown.");
    }

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();

    Transform trns;
    getCompositeTransform (&trns);
    trns.invert ();
    trns.transpose ();

    float m[16];
    trns.get (m);
    glMultMatrixf (m);

    //    gluLookAt (0, 0, 5, // from
    //	0, 0, 0, // to
    //	0, 1, 0);  // up

}

void Camera:: lookAt  (float from_x, float from_y, float from_z,
                       float to_x, float to_y, float to_z, 
                       float up_x, float up_y, float up_z)
{
  Vector from (from_x, from_y, from_z);
  Vector view (to_x-from_x, to_y-from_y, to_z-from_z);
  Vector up   (up_x, up_y, up_z);

  view.normalize();
  up.normalize();
  Vector right = cross(view, up);
  up = cross(right, view);

  float m[16] = { right.x, up.x, -view.x, from.x,
                  right.y, up.y, -view.y, from.y,
                  right.z, up.z, -view.z, from.z,
                        0,    0,       0,      1 };
  Transform trans;
  trans.set (m);   

  setTransform (trans);
}


std::ostream& Camera:: print (std::ostream& out) const
{
  out << "Camera: ";
  if (type == PERSPECTIVE) {
    out << "type=\"PERSPECTIVE\", fovy=" << fovy << ", aspect_ratio=" << aspect_ratio << ", near=" << near << ", far=" << far;
  }
  else if (type == PARALLEL) {
    out << "type=\"PARALLEL\", fovy=" << fovy << ", aspect_ratio=" << aspect_ratio << ", near=" << near << ", far=" << far;
  }
  else {
    Transform trns;
    getTransform (&trns);
    out << "type=\"GENERIC\" matrix=" << trns;
  }
  out << "\n";
  return out;
}


std::ostream& operator<< (std::ostream& out, const Camera& cam)
{
  return cam.print(out);
}
