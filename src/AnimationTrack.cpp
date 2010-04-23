#include <iostream>
#include "AnimationTrack.hpp"
#include "KeyframeSequence.hpp"
#include "AnimationController.hpp"
#include "Exception.hpp"
using namespace std;
using namespace m3g;

static
bool is_property_has_valid_component (int property, int component_count)
{
  switch (property) {
  case AnimationTrack:: ALPHA:         return (component_count == 1) ? true : false;
  case AnimationTrack:: AMBIENT_COLOR: return (component_count == 3) ? true : false;
  case AnimationTrack:: COLOR:         return (component_count == 3) ? true : false;
  case AnimationTrack:: CROP:          return (component_count == 2 || component_count == 4) ? true : false;
  case AnimationTrack:: DENSITY:       return (component_count == 1) ? true : false;
  case AnimationTrack:: DIFFUSE_COLOR: return (component_count == 3) ? true : false;
  case AnimationTrack:: EMISSIVE_COLOR:return (component_count == 3) ? true : false;
  case AnimationTrack:: FAR_DISTANCE:  return (component_count == 1) ? true : false;
  case AnimationTrack:: FIELD_OF_VIEW: return (component_count == 1) ? true : false;
  case AnimationTrack:: INTENSITY:     return (component_count == 1) ? true : false;
  case AnimationTrack:: MORPH_WEIGHTS: return (component_count == 1) ? true : false;
  case AnimationTrack:: NEAR_DISTANCE: return (component_count == 1) ? true : false;
  case AnimationTrack:: ORIENTATION:   return (component_count == 4) ? true : false;
  case AnimationTrack:: PICKABILITY:   return (component_count == 1) ? true : false;
  case AnimationTrack:: SCALE:         return (component_count == 1 || component_count == 3) ? true : false;
  case AnimationTrack:: SHININESS:     return (component_count == 1) ? true : false;
  case AnimationTrack:: SPECULAR_COLOR:return (component_count == 3) ? true : false;
  case AnimationTrack:: SPOT_ANGLE:    return (component_count == 1) ? true : false;
  case AnimationTrack:: SPOT_EXPONENT: return (component_count == 1) ? true : false;
  case AnimationTrack:: TRANSLATION:   return (component_count == 3) ? true : false;
  case AnimationTrack:: VISIBILITY:    return (component_count == 1) ? true : false;
  default: throw InternalException (__FILE__, __func__, "Unknown property, property=%d", property);
  }
}


AnimationTrack:: AnimationTrack (KeyframeSequence* sequence_, int property_) :
  property(0), keyframe_sequence(0), animation_controller(0)
{
  setObjectType (OBJTYPE_ANIMATION_TRACK);
  if (sequence_ == NULL) {
    throw NullPointException (__FILE__, __func__, "KeyframeSequence is NULL.");
  }
  if (property_ < ALPHA || property_ > VISIBILITY) {
    throw IllegalArgumentException (__FILE__, __func__, "Property is unkwon, property=%d", property_);
  }
  if (!is_property_has_valid_component (property_, sequence_->getComponentCount())) {
    throw IllegalArgumentException (__FILE__, __func__, "Component count of KeyframeSequence is invalid for this property, count=%d, property=%d", sequence_->getComponentCount(), property_);
  }


  keyframe_sequence = sequence_;
  property          = property_;
}

AnimationTrack:: ~AnimationTrack ()
{
}

AnimationTrack* AnimationTrack:: duplicate () const
{
  return new AnimationTrack (*this);
}

AnimationController* AnimationTrack:: getController () const
{
    return animation_controller;
}

KeyframeSequence* AnimationTrack:: getKeyframeSequence () const
{
  // null is ok.
  return keyframe_sequence;
}

int AnimationTrack:: getTargetProperty () const
{
    return property;
}

void AnimationTrack:: setController (AnimationController* controller)
{
  // null is ok.
  animation_controller = controller;
}

static
const char* property_to_string (int property)
{
  switch (property) {
  case AnimationTrack::ALPHA:          return "ALPHA";
  case AnimationTrack::AMBIENT_COLOR:  return "AMBIENT_COLOR";
  case AnimationTrack::COLOR:          return "COLOR";
  case AnimationTrack::CROP:           return "CROP";
  case AnimationTrack::DENSITY:        return "DENSITY";
  case AnimationTrack::DIFFUSE_COLOR:  return "DIFFUSE_COLOR";
  case AnimationTrack::EMISSIVE_COLOR: return "EMISSIVE_COLOR";
  case AnimationTrack::FAR_DISTANCE:   return "FAR_DISTANCE";
  case AnimationTrack::FIELD_OF_VIEW:  return "FIELD_OF_VIEW";
  case AnimationTrack::INTENSITY:      return "INTENSITY";
  case AnimationTrack::MORPH_WEIGHTS:  return "MORPH_WEIGHTS";
  case AnimationTrack::NEAR_DISTANCE:  return "NEAR_DISTANCE";
  case AnimationTrack::ORIENTATION:    return "ORIENTATION";
  case AnimationTrack::PICKABILITY:    return "PICKABILITY";
  case AnimationTrack::SCALE:          return "SCALE";
  case AnimationTrack::SHININESS:      return "SHININESS";
  case AnimationTrack::SPECULAR_COLOR: return "SPECULAR_COLOR";
  case AnimationTrack::SPOT_ANGLE:     return "SPOT_ANGLE";
  case AnimationTrack::SPOT_EXPONENT:  return "SPOT_EXPONENT";
  case AnimationTrack::TRANSLATION:    return "TRANSLATION";
  case AnimationTrack::VISIBILITY:     return "VISIBILITY";
  default: return "Unknwon";
  }
}

std::ostream& AnimationTrack:: print (std::ostream& out) const
{
  out << "AnimationTrack: ";
  out << "  property=" << property_to_string(property);
  out << ", keyframe_sequence=[";
  for (int i = 0;  i < keyframe_sequence->getKeyframeCount(); i++) {
    out << i << ":" << keyframe_sequence->getKeyframe (i, 0) << ",";
  }
  out << "]";
  if (animation_controller)
    out << ", animation_controller=0x" << hex << animation_controller << dec;
  else
    out << ", animation_controller=0";
  return out;
}

std::ostream& operator<< (std::ostream& out, const AnimationTrack& track)
{
  return track.print(out);
}
