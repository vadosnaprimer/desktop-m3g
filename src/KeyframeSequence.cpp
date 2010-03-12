#include "KeyframeSequence.hpp"
#include <iostream>
#include <cstring>
#include "m3gexcept.hpp"
#include "Quaternion.hpp"
using namespace std;
using namespace m3g;


KeyframeSequence:: KeyframeSequence (int num_keyframes, int num_components, int interpolation) :
  repeat_mode(CONSTANT), interp_type(LINEAR), duration(0), valid_range(0,0),
  component_count(0), keyframe_count(0)
{
  setObjectType (OBJTYPE_KEYFRAME_SEQUENCE);
  
  if (num_keyframes < 1) {
    throw invalid_argument ("Invalid Number of keyframs is specified.");
  }
  if (num_components < 1) {
    throw invalid_argument ("Invalid Number of components is specified.");
  }
  if (interpolation != LINEAR && interpolation != SLERP && interpolation != SPLINE && interpolation != SQUAD && interpolation != STEP) {
    throw invalid_argument ("Invalid interpolation type is specified.");
  }

  keyframe_count    = num_keyframes;
  component_count   = num_components;
  interp_type       = interpolation;
  valid_range.first = 0;
  valid_range.last  = num_keyframes-1;

  keyframes.reserve (keyframe_count);
  for (int i = 0; i < keyframe_count; i++) {
    keyframes.push_back (Keyframe(-1,0));
  }
}

KeyframeSequence:: ~KeyframeSequence ()
{
}

int KeyframeSequence:: getComponentCount () const
{
    return component_count;
}

int KeyframeSequence:: getDuration () const
{
    return duration;
}

int KeyframeSequence:: getInterpolationType () const
{
    return interp_type;
}

int KeyframeSequence:: getKeyframe (int index, float* value) const
{
  if (index < 0 || index >= keyframe_count) {
    throw invalid_argument ("Invalid index is specified.");
  }

  if (value) {
    for (int i = 0; i < component_count; i++) {
      *value++ = keyframes[index].value[i];
    }
  }
  return keyframes[index].time;
}

int KeyframeSequence:: getKeyframeCount () const
{
    return keyframe_count;
}

int KeyframeSequence:: getRepeatMode () const
{
    return repeat_mode;
}

int KeyframeSequence:: getValidRangeFirst () const
{
    return valid_range.first;
}

int KeyframeSequence:: getValidRangeLast () const
{
    return valid_range.last;
}

void KeyframeSequence:: setDuration (int new_duration)
{
  duration = new_duration;
}

void KeyframeSequence:: setKeyframe (int index, int time, float* value)
{
  if (index < 0 || index >= keyframe_count) {
    throw invalid_argument ("Invalid index is specified.");
  }
  if (time < 0) {
    throw invalid_argument ("Invalid time is specified.");
  }
  if (value == NULL) {
    throw null_point_error ("value is null.");
  }

  keyframes[index].time = time;
  keyframes[index].value = new float[component_count];
  for (int i = 0; i < component_count; i++) {
    keyframes[index].value[i] = value[i];
  }
}

void KeyframeSequence:: setRepeatMode (int mode)
{
  if (mode != CONSTANT && mode != LOOP) {
    throw invalid_argument ("Specified repeat mode is unknown.");
  }
  repeat_mode = mode;
}

void KeyframeSequence:: setValidRange (int first, int last)
{
  if (first < 0 || first >= keyframe_count) {
    throw invalid_argument ("First of valid range is invalid.");
  }
  if (last < 0 || last >= keyframe_count) {
    throw invalid_argument ("Last of valid range is invalid.");
  }
  if (first >= last) {
    throw not_implemented_error ("Sorry, frist>last(inverse animation) is not yet implemented.");
  }

  valid_range = ValidRange (first, last);
}

void KeyframeSequence:: getFrame (int local_time, float* value) const
{
  if (value == NULL) {
    throw null_point_error ("Specified value is NULL.");
  }
  if (valid_range.first == valid_range.last) {
    throw invalid_argument ("Valid range is not setted.");
  }
  if (valid_range.first > valid_range.last) {
    throw not_implemented_error ("Sorry, frist>last(inverse animation) is not yet implemented.");
  }

  int first = valid_range.first;
  int last  = valid_range.last;
  /*
  if (repeat_mode == LOOP) {
    while (local_time < keyframes[first].time) {
      local_time += keyframes[last].time - keyframes[first].time;
    }
    while (local_time > keyframes[last].time) {
      local_time -= keyframes[last].time - keyframes[first].time;
    }
  }
  */
  //cout << "duration = " << duration << "\n";

  if (repeat_mode == LOOP) {
    while (local_time < 0) {
      local_time += duration;
    }
    while (local_time > duration) {
      local_time -= duration;
    }
  }

  if (local_time <= keyframes[first].time) {
    for (int i = 0; i < component_count; i++) {
      value[i] = keyframes[first].value[i];
    }
    return;
  }
  if (local_time >= keyframes[last].time) {
    for (int i = 0; i < component_count; i++) {
      value[i] = keyframes[last].value[i];
    }
    return;
  }


  int left  = -1;
  int right = -1;

  for (int i = first; i <= last; i++) {
    if (keyframes[i].time > local_time) {
      left  = i-1;
      right = i;
      break;
    }
  }

  float     s  = (local_time - keyframes[left].time) / (float)(keyframes[right].time - keyframes[left].time);
  const Keyframe& k0 = (left == first && repeat_mode == LOOP) ? Keyframe(-1,0) : 
                       (left == first && repeat_mode == CONSTANT) ? Keyframe(-1,0) :
                       keyframes[left-1];
  const Keyframe& k1 = keyframes[left];
  const Keyframe& k2 = keyframes[right];
  const Keyframe& k3 = (right == last && repeat_mode == LOOP) ? Keyframe(-1,0) :
                       (right == last && repeat_mode == CONSTANT) ? Keyframe(-1,0) :
                       keyframes[right+1];

  switch (interp_type) {
  case STEP: {
    step (s, k1, k2, component_count, value);
    return;
  }
  case LINEAR: {
    linear (s, k1, k2, component_count, value);
    return;
  }
  case SLERP: {
    slerp (s, k1, k2, component_count, value);
    return;
  }
  case SPLINE: {
    cout << "interp: " << k0 << ", " << k1 << ", " << k2 << ", " << k3 << "\n";
    spline (s, k0, k1, k2, k3, component_count, value);
    return;
  }
  case SQUAD: {
    // fall throgh
  }
  default: {
    throw not_implemented_error ("This Interpolated type is unimplemented.");
  }
  }
}

static
const char* repeat_mode_to_string (int mode)
{
  switch (mode) {
  case KeyframeSequence::CONSTANT: return "CONSTANT";
  case KeyframeSequence::LOOP: return "LOOP";
  default: return "Unknown";
  }
}
static
const char* interp_type_to_string (int interp)
{
  switch (interp) {
  case KeyframeSequence::LINEAR: return "LINEAR";
  case KeyframeSequence::SLERP:  return "SLERP";
  case KeyframeSequence::SPLINE: return "SPLINE";
  case KeyframeSequence::SQUAD:  return "SQUAD";
  case KeyframeSequence::STEP:   return "STEP";
  default: return "Unknwon";
  }
}

std::ostream& KeyframeSequence:: print (std::ostream& out) const
{
  out << "KeyframeSequence: ";
  out << " keyframe_count=" << keyframe_count;
  out << " component_count=" << component_count;
  out << " valid_range=" << valid_range.first << "," << valid_range.last;
  out << " duration=" << duration;
  out << " repeat_mode=" << repeat_mode_to_string(repeat_mode);
  out << " interp_type=" << interp_type_to_string(interp_type);
  out << " keyframes=[";
  for (int i = 0; i < keyframe_count; i++) {
    out << i << ":(" << keyframes[i].time << ")=[";
    for (int j = 0; j < component_count; j++) {
      out << keyframes[i].value[j];
      if (j < component_count-1)
	out << ",";
      else
	out << "] ";
    }
  }
  return out << "]\n";
}

std::ostream& operator<< (std::ostream& out, const KeyframeSequence& keys)
{
  return keys.print(out);
}


