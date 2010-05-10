#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  struct ValidRangeAccessor {
    KeyframeSequence* keyframe_sequence;
  };
  struct KeyframeAccessor {
    KeyframeSequence* keyframe_sequence;
  };
  VALUE rb_cKeyframeSequence_ValidRangeAccessor;
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
  return Data_Wrap_Struct (self, 0, ruby_KeyframeSequence_free, p);
}

VALUE ruby_KeyframeSequence_initialize (VALUE self, VALUE val_num_keyframes, VALUE val_num_components, int val_interpolation)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  int num_keyframes  = NUM2INT(val_num_keyframes);
  int num_components = NUM2INT(val_num_components);
  int interpolation  = NUM2INT(val_interpolation);
  new (p) KeyframeSequence (num_keyframes, num_components, interpolation);
  p->setExportedEntity ((void*)self);
  return self;
}

VALUE ruby_KeyframeSequence_get_component_count (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  int component_count = p->getComponentCount();
  return INT2NUM(component_count);
}

VALUE ruby_KeyframeSequence_get_duration (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  int duration = p->getDuration();
  return INT2NUM(duration);
}

VALUE ruby_KeyframeSequence_get_interpolation_type (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  int type = p->getInterpolationType();
  return INT2NUM(type);
}

VALUE ruby_KeyframeSequence_get_keyframe (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  KeyframeAccessor* accessor;
  VALUE val_accessor = Data_Make_Struct (rb_cKeyframeSequence_KeyframeAccessor, KeyframeAccessor, 0, -1, accessor);
  accessor->keyframe_sequence = p;

  return val_accessor;
}

VALUE ruby_KeyframeSequence_get_keyframe_count (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  int keyframe_count = p->getKeyframeCount();
  return INT2NUM(keyframe_count);
}

VALUE ruby_KeyframeSequence_get_repeat_mode (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  int repeat = p->getRepeatMode();
  return INT2NUM(repeat);
}

VALUE ruby_KeyframeSequence_get_valid_range (VALUE self)
{
  KeyframeSequence* p;
  Data_Get_Struct (self, KeyframeSequence, p);
  ValidRangeAccessor* accessor;
  VALUE val_accessor = Data_Make_Struct (rb_cKeyframeSequence_ValidRangeAccessor, ValidRangeAccessor, 0, -1, accessor);
  accessor->keyframe_sequence = p;
  return val_accessor;
}


/**
 * KeyframeSequence_ValidRangeAccessor
 */

VALUE ruby_KeyframeSequence_ValidRangeAccessor_get_first (VALUE self)
{
  ValidRangeAccessor* p;
  Data_Get_Struct (self, ValidRangeAccessor, p);
  int first = p->keyframe_sequence->getValidRangeFirst();
  return INT2NUM(first);
}

VALUE ruby_KeyframeSequence_ValidRangeAccessor_get_last (VALUE self)
{
  ValidRangeAccessor* p;
  Data_Get_Struct (self, ValidRangeAccessor, p);
  int last = p->keyframe_sequence->getValidRangeLast();
  return INT2NUM(last);
}

/**
 * KeyframeSequence_KeyframeAccessor
 */

VALUE ruby_KeyframeSequence_KeyframeAccessor_get_keyframe (VALUE self, VALUE val_index)
{
  int index = NUM2INT(val_index);
  KeyframeAccessor* p;
  Data_Get_Struct (self, KeyframeAccessor, p);
  int component_count = p->keyframe_sequence->getComponentCount();
  
  float* values = (float*)ruby_xmalloc(sizeof(float)*component_count);

  int time = p->keyframe_sequence->getKeyframe (index, values);
  
  VALUE val_time   = INT2NUM(time);
  VALUE val_values = rb_ary_new();
  for (int i = 0; i < component_count; i++) {
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
  int   index      = NUM2INT(val_index);
  VALUE val_time   = rb_ary_entry(val_keyframe, 0);
  VALUE val_values = rb_ary_entry(val_keyframe, 1);
  KeyframeAccessor* p;
  Data_Get_Struct (self, KeyframeAccessor, p);
  int component_count = p->keyframe_sequence->getComponentCount();

  int    time   = NUM2INT (val_time);
  float* values = (float*)ruby_xmalloc(sizeof(float)*component_count);
  for (int i = 0; i < component_count; i++) {
    values[i] = NUM2DBL (rb_ary_entry(val_values, i));
  }

  p->keyframe_sequence->setKeyframe (index, time, values);
  ruby_xfree (values);
  
  return Qnil;
}


void register_KeyframeSequence ()
{
  // KeyframeSequence
    rb_cKeyframeSequence    = rb_define_class_under (rb_mM3G, "KeyframeSequence",    rb_cObject3D);


     rb_define_const (rb_cKeyframeSequence, "CONSTANT", INT2NUM(KeyframeSequence::CONSTANT));
     rb_define_const (rb_cKeyframeSequence, "LOOP",     INT2NUM(KeyframeSequence::LOOP));
     rb_define_const (rb_cKeyframeSequence, "LINEAR",   INT2NUM(KeyframeSequence::LINEAR));
     rb_define_const (rb_cKeyframeSequence, "SLERP",    INT2NUM(KeyframeSequence::SLERP));
     rb_define_const (rb_cKeyframeSequence, "SPLINE",   INT2NUM(KeyframeSequence::SPLINE));
     rb_define_const (rb_cKeyframeSequence, "SQUAD",    INT2NUM(KeyframeSequence::SQUAD));
     rb_define_const (rb_cKeyframeSequence, "STEP",     INT2NUM(KeyframeSequence::STEP));


     rb_define_alloc_func (rb_cKeyframeSequence, ruby_KeyframeSequence_allocate);
     rb_define_private_method (rb_cKeyframeSequence, "initialize", (VALUE(*)(...))ruby_KeyframeSequence_initialize, 3);

     rb_define_method (rb_cKeyframeSequence, "component_count",     (VALUE(*)(...))ruby_KeyframeSequence_get_component_count,    0);
     rb_define_method (rb_cKeyframeSequence, "duration",            (VALUE(*)(...))ruby_KeyframeSequence_get_duration,           0);
     rb_define_method (rb_cKeyframeSequence, "interpolation_type",  (VALUE(*)(...))ruby_KeyframeSequence_get_interpolation_type, 0);
     rb_define_method (rb_cKeyframeSequence, "keyframe",            (VALUE(*)(...))ruby_KeyframeSequence_get_keyframe,           0);
     rb_define_method (rb_cKeyframeSequence, "keyframe_count",      (VALUE(*)(...))ruby_KeyframeSequence_get_keyframe_count,     0);
     rb_define_method (rb_cKeyframeSequence, "repeat_mode",         (VALUE(*)(...))ruby_KeyframeSequence_get_repeat_mode,        0);
     rb_define_method (rb_cKeyframeSequence, "valid_range",         (VALUE(*)(...))ruby_KeyframeSequence_get_valid_range,        0);

     // KeyframeSequence_ValidRangeAccessor
    rb_cKeyframeSequence_ValidRangeAccessor    = rb_define_class_under (rb_cKeyframeSequence, "ValidRangeAccessor",    rb_cObject3D);

     rb_define_method (rb_cKeyframeSequence_ValidRangeAccessor, "first",       (VALUE(*)(...))ruby_KeyframeSequence_ValidRangeAccessor_get_first, 0);
     rb_define_method (rb_cKeyframeSequence_ValidRangeAccessor, "last",       (VALUE(*)(...))ruby_KeyframeSequence_ValidRangeAccessor_get_last,   0);

     // KeyframeSequence_KeyframeAccessor
    rb_cKeyframeSequence_KeyframeAccessor    = rb_define_class_under (rb_cKeyframeSequence, "KeyframeAccessor",    rb_cObject3D);

     rb_define_method (rb_cKeyframeSequence_KeyframeAccessor, "[]",       (VALUE(*)(...))ruby_KeyframeSequence_KeyframeAccessor_get_keyframe,    1);
     rb_define_method (rb_cKeyframeSequence_KeyframeAccessor, "[]=",       (VALUE(*)(...))ruby_KeyframeSequence_KeyframeAccessor_set_keyframe,   2);
}

