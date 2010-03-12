#include "Node.hpp"
#include "m3gexcept.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

Node:: Node () : 
  parent(0), rendering_enable(true), picking_enable(true),
  alpha_factor(1), scope(-1),
  z_alignment(NONE, 0), y_alignment(NONE, 0)
{
  setObjectType (OBJTYPE_NODE);
}

Node:: ~Node ()
{
}

void Node:: addAnimationTrack (AnimationTrack* animation_track)
{
   if (animation_track == NULL) {
    throw null_point_error ("Added animation_track is NULL.");
  }
  if (animation_track->getTargetProperty() != AnimationTrack::ALPHA       &&
      animation_track->getTargetProperty() != AnimationTrack::PICKABILITY &&
      animation_track->getTargetProperty() != AnimationTrack::VISIBILITY  &&
      animation_track->getTargetProperty() != AnimationTrack::ORIENTATION &&
      animation_track->getTargetProperty() != AnimationTrack::SCALE       &&
      animation_track->getTargetProperty() != AnimationTrack::TRANSLATION) {
    throw invalid_argument ("Invalid animation track target for Node.");
  }
 
  Object3D:: addAnimationTrack (animation_track);

}

void Node:: align (Node* reference)
{
  if (reference == 0) {
    throw null_point_error ("Reference is NULL.");
  }
  z_alignment.target    = ORIGIN;
  z_alignment.reference = reference;
  y_alignment.target    = ORIGIN;
  y_alignment.reference = reference;
}

int Node:: animate (int world_time)
{
  //cout << "Node: animate, time=" << world_time << "\n";

  Transformable:: animate (world_time);

  bool  is_alpha_modefied = false;
  bool  is_picking_enable_modefied = false;
  bool  is_rendering_enable_modefied = false;
  float alpha = 0;
  bool  new_picking_enable = false;
  bool  new_rendering_enable = false;
  
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
    case AnimationTrack:: ALPHA: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      alpha += value[0] * weight;
      is_alpha_modefied = true;
      //cout << "Node: alpha --> " << alpha << "\n";
      break;
    }
    case AnimationTrack:: PICKABILITY: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_picking_enable = new_picking_enable || ((value[0] != 0) ? true : false);
      is_picking_enable_modefied = true;
      //cout << "Node: picking_enable --> " << new_picking_enable << "\n";
      break;
    }
    case AnimationTrack:: VISIBILITY: {
      float value[1] = {1};
      keyframe->getFrame (local_time, value);
      new_rendering_enable = new_rendering_enable || ((value[0] != 0) ? true : false);
      is_rendering_enable_modefied = true;
      //cout << "Node: rendering_enable --> " << new_rendering_enable << "\n";
      break;
    }
    default: {
      // Unknwon target should be ignored.
      // animate() of Base class (of Derived class) retrieve it.
    }
    }
  }

  if (is_alpha_modefied) {
    alpha = (alpha < 0) ? 0 : 
      (alpha > 1) ? 1 : 
      alpha;
    alpha_factor = alpha;
  }
  if (is_picking_enable_modefied) {
    picking_enable = new_picking_enable;
  }
  if (is_rendering_enable_modefied) {
    rendering_enable = new_rendering_enable;
  }

  //cout << *this << "\n";

  return 0;
}

Node* Node:: getAlignmentReference (int axis) const
{
  switch (axis) {
  case Z_AXIS: {
    return z_alignment.reference;
  }
  case Y_AXIS: {
    return y_alignment.reference;
  }
  default: {
    throw invalid_argument ("Unknown axis is specified.");
  }
  }
}

int Node:: getAlignmentTarget (int axis) const
{
  switch (axis) {
  case Z_AXIS: {
    return z_alignment.target;
  }
  case Y_AXIS: {
    return y_alignment.target;
  }
  default: {
    throw invalid_argument ("Unknown axis is specified.");
  }
  }
}

float Node:: getAlphaFactor () const
{
    return alpha_factor;
}

Node* Node:: getParent () const
{
    return parent;
}

int Node:: getScope () const
{
    return scope;
}

bool Node:: getTransformTo (Node* target, Transform* transform) const
{
  std::vector<const Node*> v0, v1;
  const Node* node;

  node = this;
  while ((node = node->parent) != 0) {
    v0.push_back (node);
  }
  node = target;
  while ((node = node->parent) != 0) {
    v1.push_back (node);
  }

  const Node* root = 0;
  for (int i = 0; i < (int)v0.size(); i++) {
    for (int j = 0; j < (int)v1.size(); j++) {
      if (v0[i] == v1[j]) {
        root = v0[i];
        break;
      }
    }
  }

  if (root == 0) {
    return false;
  }

  Transform t0;
  node->getTransform (&t0);

  node = this;
  while ((node = node->parent) != root) {
    Transform t;
    node->getTransform (&t);
    t.postMultiply (t0);
    t0 = t;
  }

  Transform t1;
  node->getTransform (&t1);

  node = this;
  while ((node = node->parent) != root) {
    Transform t;
    node->getTransform (&t);
    t.postMultiply (t1);
    t1 = t;
  }

  t1.invert ();
  t1.postMultiply (t0);
  
  *transform = t1;
  return true;
}

bool Node:: isPickingEnabled () const
{
    return picking_enable;
}

bool Node:: isRenderingEnabled () const
{
    return rendering_enable;
}


void Node:: setAlignment (Node* z_ref, int z_target, Node* y_ref, int y_target)
{
  if (z_target == ORIGIN) {
    z_alignment.target = ORIGIN;
    z_alignment.reference = z_ref;
  }
  if (y_target == ORIGIN) {
    y_alignment.target = ORIGIN;
    y_alignment.reference = y_ref;
  }
  
}


void Node:: setAlphaFactor (float alpha)
{
  alpha_factor = alpha;
}


void Node:: setPickingEnable (bool enable)
{
  picking_enable = enable;
}

void Node:: setRenderingEnable (bool enable)
{
  rendering_enable = enable;
}

void Node:: setScope (int s)
{
  scope = s;
}

void Node:: setParent (Node* node)
{
  parent = node;
}

/**
 * Note: Node should be rendered via all rendering pass.
 */
void Node:: render (int pass, int index) const
{
  Transformable::render (pass, index);
}

std::ostream& Node:: print (std::ostream& out) const
{
  out << "Node: ";
  out << " scope=" << scope;
  out << ", rendering_enable=" << rendering_enable;
  out << ", picking_enable=" << picking_enable;
  out << ", alpha_factor=" << alpha_factor;
  return out << "\n";
}

std::ostream& operator<< (std::ostream& out, const Node& node)
{
  return node.print(out);
}
