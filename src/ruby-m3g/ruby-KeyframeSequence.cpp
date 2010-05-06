#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  struct KeyframeAccessor {
    KeyframeSequence* keyframe_sequence;
  };
  VALUE rb_cKeyframeSequence_ValidRange;
  VALUE rb_cKeyframeSequence_KeyframeAccessor;
}

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

VALUE ruby_KeyframeSequence_initialize (VALUE self, VALUE val_num_keyframes, VALUE val_num_components, VALUE val_interpolation)
{
    KeyframeSequence* p;
    Data_Get_Struct (self, KeyframeSequence, p);

    int num_keyframes  = FIX2INT (val_num_keyframes);
    int num_components = FIX2INT (val_num_components);
    int interpolation  = FIX2INT (val_interpolation);

    new (p) KeyframeSequence (num_keyframes, num_components, interpolation);
    
    return self;
}

VALUE ruby_KeyframeSequence_get_component_count (VALUE self)
{
  KeyframeSequence* p;
  int count;

  Data_Get_Struct (self, KeyframeSequence, p);

  count = p->getComponentCount ();

  return INT2FIX(count);
}

VALUE ruby_KeyframeSequence_get_duration (VALUE self)
{
  KeyframeSequence* p;
  int duration;

  Data_Get_Struct (self, KeyframeSequence, p);

  duration = p->getDuration ();

  return INT2FIX(duration);
}

VALUE ruby_KeyframeSequence_get_interpolation_type (VALUE self)
{
  KeyframeSequence* p;
  int interpolation;

  Data_Get_Struct (self, KeyframeSequence, p);

  interpolation = p->getInterpolationType ();

  return INT2FIX(interpolation);
}

VALUE ruby_KeyframeSequence_get_keyframe (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);

  KeyframeAccessor* accessor;
  VALUE      val_accessor = Data_Make_Struct (rb_cKeyframeSequence_KeyframeAccessor, KeyframeAccessor, 0, -1, accessor);
  accessor->keyframe_sequence = p;

  return val_accessor;
}

VALUE ruby_KeyframeSequence_get_keyframe_count (VALUE self)
{
  KeyframeSequence* p;
  int count;

  Data_Get_Struct (self, KeyframeSequence, p);
  
  count = p->getKeyframeCount();

  return INT2FIX(count);
}

VALUE ruby_KeyframeSequence_get_repeat_mode (VALUE self)
{
  KeyframeSequence* p;
  int mode;

  Data_Get_Struct (self, KeyframeSequence, p);
  
  mode = p->getRepeatMode();

  return INT2FIX(mode);
}

VALUE ruby_KeyframeSequence_get_valid_range (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  KeyframeSequence::ValidRange* valid_range;
  VALUE val_valid_range = Data_Make_Struct (rb_cKeyframeSequence_ValidRange, KeyframeSequence::ValidRange, 0, -1, valid_range);

  return val_valid_range;
}

VALUE ruby_KeyframeSequence_set_duration (VALUE self, VALUE val_duration)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  int duration = FIX2INT (val_duration);

  p->setDuration (duration);

  return Qnil;
}



VALUE ruby_KeyframeSequence_set_repeat_mode (VALUE self, VALUE val_mode)
{
  KeyframeSequence* p;
  int mode;

  Data_Get_Struct (self, KeyframeSequence, p);
  mode = FIX2INT (val_mode);

  p->setRepeatMode (mode);

  return Qnil;
}

VALUE ruby_KeyframeSequence_set_valid_range (VALUE self, VALUE val_valid_range)
{
  VALUE val_first = rb_ary_entry(val_valid_range, 0);
  VALUE val_last  = rb_ary_entry(val_valid_range, 1);
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  int first = FIX2INT (val_first);
  int last  = FIX2INT (val_last);

  p->setValidRange (first, last);

  return Qnil;
}



/**
 * KeyframeSequence_ValidRange
 */
VALUE ruby_KeyframeSequence_ValidRange_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(KeyframeSequence::ValidRange));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_KeyframeSequence_ValidRange_initialize (VALUE self)
{
  KeyframeSequence::ValidRange* p;
  Data_Get_Struct (self, KeyframeSequence::ValidRange, p);
  return self;
}

VALUE ruby_KeyframeSequence_ValidRange_get_first (VALUE self)
{
  KeyframeSequence::ValidRange* p;
  Data_Get_Struct (self, KeyframeSequence::ValidRange, p);
  return INT2FIX (p->first);
}

VALUE ruby_KeyframeSequence_ValidRange_get_last (VALUE self)
{
  KeyframeSequence::ValidRange* p;
  Data_Get_Struct (self, KeyframeSequence::ValidRange, p);
  return INT2FIX (p->last);
}


/**
 * KeyframeSequence_KeyframeAccessor
 */

VALUE ruby_KeyframeSequence_KeyframeAccessor_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(KeyframeAccessor));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_KeyframeSequence_KeyframeAccessor_initialize (VALUE self)
{
    KeyframeAccessor* p;
    Data_Get_Struct (self, KeyframeAccessor, p);
    return self;
}

VALUE ruby_KeyframeSequence_KeyframeAccessor_get_keyframe (VALUE self, VALUE val_index)
{
  KeyframeAccessor* p;
  Data_Get_Struct (self, KeyframeAccessor, p);
  int    index  = FIX2INT (val_index);
  int    count  = p->keyframe_sequence->getComponentCount ();
  float* values = (float*)ruby_xmalloc (sizeof(float)*count);
  int    time;

  time = p->keyframe_sequence->getKeyframe (index, values);

  VALUE val_time   = INT2FIX(time);
  VALUE val_values = rb_ary_new ();
  for (int i = 0; count; i++) {
    rb_ary_push (val_values, rb_float_new(values[i]));
  }
  ruby_xfree (values);

  VALUE val_keyframe = rb_ary_new ();
  rb_ary_push (val_keyframe, val_time);
  rb_ary_push (val_keyframe, val_values);

  return val_keyframe;
}

VALUE ruby_KeyframeSequence_KeyframeAccessor_set_keyframe (VALUE self, VALUE val_index, VALUE val_keyframe)
{
  int   val_time  = rb_ary_entry(val_keyframe, 0);
  int   val_values  = rb_ary_entry(val_keyframe, 1);
  KeyframeAccessor* p;
  Data_Get_Struct (self, KeyframeAccessor, p);
  int   index = FIX2INT (val_index);
  int   time  = FIX2INT(val_time);
  int   num   = RARRAY(val_keyframe)->len;
  float* values = (float*)ruby_xmalloc(sizeof(float)*num);
  for (int i = 0; i < num; i++) {
    values[i] = RFLOAT_VALUE(rb_ary_entry(val_values, i));
  }

  // TODO: numとcomponent\countをチェックして異なればエラーとする

  p->keyframe_sequence->setKeyframe (index, time, values);

  return Qnil;
}



void register_KeyframeSequence ()
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
     rb_define_method (rb_cKeyframeSequence, "repeat_mode=",        (VALUE(*)(...))ruby_KeyframeSequence_set_repeat_mode, 1);
     rb_define_method (rb_cKeyframeSequence, "valid_range=",        (VALUE(*)(...))ruby_KeyframeSequence_set_valid_range, 2);

     // KeyframeSequence_ValidRange
     VALUE rb_cKeyframeSequence_ValidRange = rb_define_class_under (rb_cKeyframeSequence, "ValidRange", rb_cObject);
     rb_define_alloc_func (rb_cKeyframeSequence_ValidRange, ruby_KeyframeSequence_ValidRange_allocate);
     rb_define_private_method (rb_cKeyframeSequence_ValidRange, "initialize", (VALUE(*)(...))ruby_KeyframeSequence_ValidRange_initialize, 0);

    rb_define_method (rb_cKeyframeSequence_ValidRange, "first",     (VALUE(*)(...))ruby_KeyframeSequence_ValidRange_get_first, 1);
    rb_define_method (rb_cKeyframeSequence_ValidRange, "last",     (VALUE(*)(...))ruby_KeyframeSequence_ValidRange_get_last, 1);


     // KeyframeSequence_KeyframeAccessor
     VALUE rb_cKeyframeSequence_KeyframeAccessor = rb_define_class_under (rb_cKeyframeSequence, "KeyframeAccessor", rb_cObject);
     rb_define_alloc_func (rb_cKeyframeSequence_KeyframeAccessor, ruby_KeyframeSequence_KeyframeAccessor_allocate);
     rb_define_private_method (rb_cKeyframeSequence_KeyframeAccessor, "initialize", (VALUE(*)(...))ruby_KeyframeSequence_KeyframeAccessor_initialize, 0);

    rb_define_method (rb_cKeyframeSequence_KeyframeAccessor, "[]",     (VALUE(*)(...))ruby_KeyframeSequence_KeyframeAccessor_get_keyframe, 1); 
    rb_define_method (rb_cKeyframeSequence_KeyframeAccessor, "[]=",     (VALUE(*)(...))ruby_KeyframeSequence_KeyframeAccessor_set_keyframe, 2); 

    
}
