#include "Node.hpp"
#include "Exception.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include "RenderState.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

const int Node:: NONE;
const int Node:: ORIGIN;
const int Node:: X_AXIS;
const int Node:: Y_AXIS;
const int Node:: Z_AXIS;

Node:: Node () : 
  parent(0), rendering_enable(true), picking_enable(true),
  alpha_factor(1), scope(-1),
  z_alignment(NONE, 0), y_alignment(NONE, 0)
{
}

Node:: ~Node ()
{
}

Node* Node:: duplicate () const
{
  // 注意：Nodeクラスを継承する全てのクラスはduplicate()する時に
  // この関数を呼ばなければならない。
  Node* node = new Node (*this);
  node->parent = NULL;
  return node;
}

void Node:: addAnimationTrack (AnimationTrack* animation_track)
{
   if (animation_track == NULL) {
     throw NullPointException (__FILE__, __func__, "Animation track is NULL.");
  }
   int property = animation_track->getTargetProperty();
  if (property != AnimationTrack::ALPHA       &&
      property != AnimationTrack::PICKABILITY &&
      property != AnimationTrack::VISIBILITY  &&
      property != AnimationTrack::ORIENTATION &&
      property != AnimationTrack::SCALE       &&
      property != AnimationTrack::TRANSLATION &&
      property != AnimationTrack::MORPH_WEIGHTS ) {
    throw IllegalArgumentException (__FILE__, __func__, "Annimation target is invlid for this Node, property=%d.", property);
  }

  Object3D:: addAnimationTrack (animation_track);
}

void Node:: align (Node* reference)
{
  if (reference == 0) {
    throw NullPointException (__FILE__, __func__, "Reference is NULL.");
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

  bool  is_alpha_modefied            = false;
  bool  is_picking_enable_modefied   = false;
  bool  is_rendering_enable_modefied = false;
  float new_alpha            = 0;
  bool  new_picking_enable   = false;
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
      new_alpha += value[0] * weight;
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
    alpha_factor = clamp (0, 1, new_alpha);
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
  case Z_AXIS: return z_alignment.reference;
  case Y_AXIS: return y_alignment.reference;
  default: throw IllegalArgumentException (__FILE__, __func__, "Axis is invalid, axis=%d.", axis);
  }
}

int Node:: getAlignmentTarget (int axis) const
{
  switch (axis) {
  case Z_AXIS: return z_alignment.target;
  case Y_AXIS: return y_alignment.target;
  default: throw IllegalArgumentException (__FILE__, __func__, "Axis is invalid, axis=%d.", axis);
  }
}

float Node:: getAlphaFactor () const
{
    return alpha_factor;
}

Matrix Node:: getGlobalPose () const
{
  const Node* node = this;
  Matrix global_pose;
  do {
    Transform trans;
    node->getCompositeTransform (&trans);
    float m[16];
    trans.get (m);
    global_pose = Matrix(m) * global_pose;
  } while ((node = node->getParent()));

  return global_pose;
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
  if (target == NULL) {
    throw NullPointException (__FILE__, __func__, "Target is NULL.");
  }
  if (transform == NULL) {
    throw NullPointException (__FILE__, __func__, "Transform is NULL.");
  }

  const Node *root_a, *root_b, *node;
  
  node = this;
  do {
    root_a = node;
  } while ((node = node->parent));

  node = target;
  do {
    root_b = node;
  } while ((node = node->parent));

  if (root_a != root_b) {
    return false;
  }

  Matrix global_pose_a = this->getGlobalPose ();
  Matrix global_pose_b = target->getGlobalPose ();

  Matrix transform_matrix = global_pose_b.invert() * global_pose_a;
  transform->set (transform_matrix.m);

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
  if (alpha < 0 || alpha > 1.0) {
    throw IllegalArgumentException (__FILE__, __func__, "Alpha is invalid, alph=%f.", alpha);
  }

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
void Node:: render (RenderState& state) const
{
  Transformable::render (state);
  
  float alpha = 1;
  const Node* node  = this;
  do {
    alpha *= node->getAlphaFactor();
  } while ((node = node->getParent()) != 0);

  state.alpha = alpha;
}

std::ostream& Node:: print (std::ostream& out) const
{
  out << "Node: ";
  out << "  scope=" << scope;
  out << ", rendering_enable=" << rendering_enable;
  out << ", picking_enable=" << picking_enable;
  out << ", alpha_factor=" << alpha_factor;
  return out;
}

std::ostream& operator<< (std::ostream& out, const Node& node)
{
  return node.print(out);
}
