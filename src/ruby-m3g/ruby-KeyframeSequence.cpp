#include <new>
#include "ruby.h"
#include "KeyframeSequence.hpp"
using namespace m3g;

VALUE ruby_KeyframeSequence_free (KeyframeSequence* ptr)
{
    ptr->~KeyframeSequence ();
    ruby_xfree (ptr);
}

VALUE ruby_KeyframeSequence_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(KeyframeSequence));
    return Data_Wrap_Struct (self, NULL, ruby_KeyframeSequence_free, p);
}

VALUE ruby_KeyframeSequence_initialize (VALUE self, VALUE val_numKeyframes, VALUE val_num_components, VALUE val_interpolation)
{
    KeyframeSequence* p;
    Data_Get_Struct (self, KeyframeSequence, p);
    new (p) KeyframeSequence (0,0,0);
    return Qnil;
}

VALUE ruby_KeyframeSequence_get_component_count (VALUE self)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_get_duration (VALUE self)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_get_interpolation_type (VALUE self)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_get_keyframe (VALUE self, VALUE val_index)
{
    // timeとvalueは戻り値(Keyframe)で。
    return Qnil;
}

VALUE ruby_KeyframeSequence_get_keyframe_count (VALUE self)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_get_repeat_mode (VALUE self)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_get_valid_range (VALUE self)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_set_duration (VALUE self, VALUE val_duration)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_set_keyframe (VALUE self, VALUE val_index, VALUE val_time, VALUE val_value)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_set_repeat_mode (VALUE self, VALUE val_mode)
{
    return Qnil;
}

VALUE ruby_KeyframeSequence_set_valid_range (VALUE self, VALUE val_first, VALUE val_last)
{
    return Qnil;
}


VALUE ruby_Keyframe_allocate (VALUE self)
{
    return Qnil;
}

VALUE ruby_Keyframe_initialize (VALUE self)
{
    return Qnil;
}

VALUE ruby_Keyframe_get_time (VALUE self)
{
    return Qnil;
}

VALUE ruby_Keyframe_get_value (VALUE self)
{
    return Qnil;
}


void register_KeyframeSequence (VALUE rb_cKeyframeSequence)
{
     // KeyframeSequence
     rb_define_const (rb_cKeyframeSequence, "CONSTANT", INT2FIX(KeyframeSequence::CONSTANT));
     rb_define_const (rb_cKeyframeSequence, "LINEAR",   INT2FIX(KeyframeSequence::LINEAR));
     rb_define_const (rb_cKeyframeSequence, "LOOP",     INT2FIX(KeyframeSequence::LOOP));
     rb_define_const (rb_cKeyframeSequence, "SLERP",    INT2FIX(KeyframeSequence::SLERP));
     rb_define_const (rb_cKeyframeSequence, "SPLINE",   INT2FIX(KeyframeSequence::SPLINE));
     rb_define_const (rb_cKeyframeSequence, "SQUAD",    INT2FIX(KeyframeSequence::SQUAD));
     rb_define_const (rb_cKeyframeSequence, "STEP",     INT2FIX(KeyframeSequence::STEP));

     rb_define_alloc_func (rb_cKeyframeSequence, ruby_KeyframeSequence_allocate);
     rb_define_private_method (rb_cKeyframeSequence, "initialize", (VALUE(*)(...))ruby_KeyframeSequence_initialize, 3);

     rb_define_method (rb_cKeyframeSequence, "component_count",    (VALUE(*)(...))ruby_KeyframeSequence_get_component_count, 0);
     rb_define_method (rb_cKeyframeSequence, "duration",           (VALUE(*)(...))ruby_KeyframeSequence_get_duration, 0);
     rb_define_method (rb_cKeyframeSequence, "interpolation_type", (VALUE(*)(...))ruby_KeyframeSequence_get_interpolation_type, 0);
     rb_define_method (rb_cKeyframeSequence, "keyframe",           (VALUE(*)(...))ruby_KeyframeSequence_get_keyframe, 1);
     rb_define_method (rb_cKeyframeSequence, "keyframe_count",     (VALUE(*)(...))ruby_KeyframeSequence_get_keyframe_count, 0);
     rb_define_method (rb_cKeyframeSequence, "repeat_mode",        (VALUE(*)(...))ruby_KeyframeSequence_get_repeat_mode, 0);
     rb_define_method (rb_cKeyframeSequence, "valid_range",        (VALUE(*)(...))ruby_KeyframeSequence_get_valid_range, 0);
     rb_define_method (rb_cKeyframeSequence, "duration=",           (VALUE(*)(...))ruby_KeyframeSequence_set_duration, 1);
     rb_define_method (rb_cKeyframeSequence, "keyframe=",           (VALUE(*)(...))ruby_KeyframeSequence_set_keyframe, 3);
     rb_define_method (rb_cKeyframeSequence, "repeat_mode=",        (VALUE(*)(...))ruby_KeyframeSequence_set_repeat_mode, 1);
     rb_define_method (rb_cKeyframeSequence, "valid_range=",        (VALUE(*)(...))ruby_KeyframeSequence_set_valid_range, 2);

     // Keyframe
     VALUE rb_cKeyframe = rb_define_class_under (rb_cKeyframeSequence, "Keyframe", rb_cObject);
     rb_define_alloc_func (rb_cKeyframe, ruby_Keyframe_allocate);
     rb_define_private_method (rb_cKeyframe, "initialize", (VALUE(*)(...))ruby_Keyframe_initialize, 0);

     rb_define_method (rb_cKeyframe, "time", (VALUE(*)(...))ruby_Keyframe_get_time, 0);
     rb_define_method (rb_cKeyframe, "value", (VALUE(*)(...))ruby_Keyframe_get_value, 0);
     
}
