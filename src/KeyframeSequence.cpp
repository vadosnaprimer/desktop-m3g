#include "m3g/KeyframeSequence.hpp"
#include "m3g/Exception.hpp"
#include "m3g/Quaternion.hpp"
#include <iostream>
#include <cstring>
using namespace std;
using namespace m3g;

const int KeyframeSequence:: CONSTANT;
const int KeyframeSequence:: LOOP;
const int KeyframeSequence:: LINEAR;
const int KeyframeSequence:: SLERP;
const int KeyframeSequence:: SPLINE;
const int KeyframeSequence:: SQUAD;
const int KeyframeSequence:: STEP;

KeyframeSequence:: KeyframeSequence (int num_keyframes, int num_components, int interpolation) :
    repeat_mode(CONSTANT), interp_type(LINEAR), duration(0), valid_range(-1,-1),
    component_count(0), keyframe_count(0)
{
    if (num_keyframes < 1) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of keyframes is invalid, num=%d.", num_keyframes);
    }
    if (num_components < 1) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of components is invalid, conponent=%d.", num_components);
    }
    if (interpolation != LINEAR && interpolation != SLERP && interpolation != SPLINE && interpolation != SQUAD && interpolation != STEP) {
        throw IllegalArgumentException (__FILE__, __func__, "Interpolation type is invalid, type=%d.", interpolation);
    }

    keyframe_count    = num_keyframes;
    component_count   = num_components;
    interp_type       = interpolation;
    valid_range.first = 0;
    valid_range.last  = num_keyframes-1;

    keyframes.reserve (keyframe_count);
    for (int i = 0; i < keyframe_count; i++) {
        int    time  = 0;
        float* value = new float[component_count] ();
        keyframes.push_back (Keyframe(time, value));
    }
}

KeyframeSequence:: ~KeyframeSequence ()
{
    for (int i = 0; i < (int)keyframes.size(); i++) {
        delete [] keyframes[i].value;
    }
}

KeyframeSequence* KeyframeSequence:: duplicate () const
{
    return duplicate_xxx (NULL);
}

KeyframeSequence* KeyframeSequence:: duplicate_xxx (Object3D* obj) const
{
    KeyframeSequence* key_seq = dynamic_cast<KeyframeSequence*>(obj);
    if (key_seq == NULL) {
        key_seq = new KeyframeSequence (keyframe_count, component_count, interp_type);
    }
    Object3D:: duplicate_xxx (key_seq);

    key_seq->repeat_mode     = repeat_mode;
    key_seq->duration        = duration;
    key_seq->valid_range     = valid_range;
    for (int i = 0; i < keyframe_count; i++) {
        key_seq->keyframes[i].time = keyframes[i].time;
        memcpy (key_seq->keyframes[i].value,
                keyframes[i].value,
                sizeof(float)*component_count);
    }

    return key_seq;
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
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d.", index);
    }

    if (value) {
        memcpy (value, keyframes[index].value, sizeof(float)*component_count);
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
    if (new_duration <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Duration is invalid, duration=%d.", duration);
    }

    duration = new_duration;
}

void KeyframeSequence:: setKeyframe (int index, int time, float* value)
{
    if (index < 0 || index >= keyframe_count) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d, keyframe_count=%d.", index, keyframe_count);
    }
    if (time < 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Time is Invalid, time=%d.", time);
    }
    if (value == NULL) {
        throw NullPointerException (__FILE__, __func__, "Value is NULL.");
    }

    keyframes[index].time  = time;
    memcpy (keyframes[index].value,
            value,
            sizeof(float)*component_count);
}

void KeyframeSequence:: setRepeatMode (int mode)
{
    if (mode != CONSTANT && mode != LOOP) {
        throw IllegalArgumentException (__FILE__, __func__, "Repeat mode is invalid, mode=%d.", mode);
    }
    repeat_mode = mode;
}

void KeyframeSequence:: setValidRange (int first, int last)
{
    if (first < 0 || first >= keyframe_count) {
        throw IllegalArgumentException (__FILE__, __func__, "First of valid range is invalid, first=%d, keyframe_count=%d.", first, keyframe_count);
    }
    if (last < 0 || last >= keyframe_count) {
        throw IllegalArgumentException (__FILE__, __func__, "Last of valid range is invalid, last=%d, keyframe_count=%d.", last, keyframe_count);
    }
    if (first > last) {
        throw NotImplementedException (__FILE__, __func__, "Sorry, valid_range.(frist > last) is not yet implemented, first=%d, last=%d.", first, last);
    }

    valid_range = ValidRange (first, last);
}

void KeyframeSequence:: sample (int sequence_time, float* value) const
{
    if (value == NULL) {
        throw NullPointerException (__FILE__, __func__, "Value is NULL.");
    }
    if (valid_range.first > valid_range.last) {
        throw NotImplementedException (__FILE__, __func__, "Sorry, valid_range.(first > last) is not yet implemented, first=%d, last=%d.", valid_range.first, valid_range.last);
    }
    if (duration <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Duraion is invalid, duration=%d.", duration);
    }

    int first = valid_range.first;
    int last  = valid_range.last;


    if (repeat_mode == LOOP) {
        sequence_time %= duration;
    }

    if (sequence_time <= keyframes[first].time) {
        for (int i = 0; i < component_count; i++) {
            value[i] = keyframes[first].value[i];
        }
        return;
    }
    if (sequence_time >= keyframes[last].time) {
        for (int i = 0; i < component_count; i++) {
            value[i] = keyframes[last].value[i];
        }
        return;
    }


    int left  = -1;
    int right = -1;

    for (int i = first; i <= last; i++) {
        if (keyframes[i].time > sequence_time) {
            left  = i-1;
            right = i;
            break;
        }
    }

    float           s  = (sequence_time - keyframes[left].time) / (float)(keyframes[right].time - keyframes[left].time);
    const Keyframe& k0 = (left == first && repeat_mode == LOOP)     ? Keyframe(-1,0) : 
                         (left == first && repeat_mode == CONSTANT) ? Keyframe(-1,0) :
                         keyframes[left-1];
    const Keyframe& k1 = keyframes[left];
    const Keyframe& k2 = keyframes[right];
    const Keyframe& k3 = (right == last && repeat_mode == LOOP)     ? Keyframe(-1,0) :
                         (right == last && repeat_mode == CONSTANT) ? Keyframe(-1,0) :
                         keyframes[right+1];

    switch (interp_type) {
    case STEP:
        step (s, k1, k2, component_count, value);
        return;
    case LINEAR:
        linear (s, k1, k2, component_count, value);
        return;
    case SLERP:
        slerp (s, k1, k2, component_count, value);
        return;
    case SPLINE:
        spline (s, k0, k1, k2, k3, component_count, value);
        return;
    case SQUAD:
        squad  (s, k0, k1, k2, k3, component_count, value);
        return;
    default:
        throw InternalException (__FILE__, __func__, "Interpolation type is unknown, type=%d.", interp_type);
    }
}

static
const char* repeat_mode_to_string (int mode)
{
    switch (mode) {
    case KeyframeSequence::CONSTANT: return "CONSTANT";
    case KeyframeSequence::LOOP    : return "LOOP"    ;
    default: return "Unknown";
    }
}
static
const char* interp_type_to_string (int interp)
{
    switch (interp) {
    case KeyframeSequence::LINEAR: return "LINEAR";
    case KeyframeSequence::SLERP:  return "SLERP" ;
    case KeyframeSequence::SPLINE: return "SPLINE";
    case KeyframeSequence::SQUAD:  return "SQUAD" ;
    case KeyframeSequence::STEP:   return "STEP"  ;
    default: return "Unknown";
    }
}

std::ostream& KeyframeSequence:: print (std::ostream& out) const
{
    out << "KeyframeSequence: ";
    out << "  keyframe_count="  << keyframe_count;
    out << ", component_count=" << component_count;
    out << ", valid_range="     << valid_range.first << "," << valid_range.last;
    out << ", duration="        << duration;
    out << ", repeat_mode="     << repeat_mode_to_string(repeat_mode);
    out << ", interp_type="     << interp_type_to_string(interp_type);
    out << ", keyframes=[";
    for (int i = 0; i < keyframe_count; i++) {
        out << i << ":(" << keyframes[i].time << ")=[";
        if (keyframes[i].value) {
            for (int j = 0; j < component_count; j++) {
                out << keyframes[i].value[j];
                if (j < component_count-1)
                    out << ",";
                else
                    out << "] ";
            }
        }
    }
    out << "]";
    return out;
}

std::ostream& operator<< (std::ostream& out, const KeyframeSequence& keys)
{
    return keys.print(out);
}


