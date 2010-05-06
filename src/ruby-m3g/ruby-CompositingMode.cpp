#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  VALUE rb_cCompositingMode_DepthOffset;
}

VALUE ruby_CompositingMode_free (CompositingMode* ptr)
{
    ptr->~CompositingMode ();
    ruby_xfree (ptr);
}

VALUE ruby_CompositingMode_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(CompositingMode));
    return Data_Wrap_Struct (self, 0, ruby_CompositingMode_free, p);
}

VALUE ruby_CompositingMode_initialize (VALUE self)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    new (p) CompositingMode;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_CompositingMode_get_alpha_threshold (VALUE self)
{
  CompositingMode* p;
  float alpha;

  Data_Get_Struct (self, CompositingMode, p);

  alpha = p->getAlphaThreshold ();

  return rb_float_new (alpha);
}

VALUE ruby_CompositingMode_get_blending (VALUE self)
{
  CompositingMode* p;
  int mode;

  Data_Get_Struct (self, CompositingMode, p);

  mode = p->getBlending ();

  return INT2FIX(mode);
}

VALUE ruby_CompositingMode_get_depth_offset (VALUE self)
{
  CompositingMode* p;
  CompositingMode::DepthOffset* depth_offset;
  VALUE val_depth_offset;

  Data_Get_Struct (self, CompositingMode, p);
  val_depth_offset = Data_Make_Struct (rb_cCompositingMode_DepthOffset, CompositingMode::DepthOffset, 0, -1, depth_offset);

  depth_offset->factor = p->getDepthOffsetFactor ();
  depth_offset->units  = p->getDepthOffsetUnits ();

  return val_depth_offset;
}


VALUE ruby_CompositingMode_is_alpha_write_enabled (VALUE self)
{
  CompositingMode* p;
  bool enabled;

  Data_Get_Struct (self, CompositingMode, p);

  enabled = p->isAlphaWriteEnabled ();

  if (enabled)
    return Qtrue;
  else
    return Qfalse;
}

VALUE ruby_CompositingMode_is_color_write_enabled (VALUE self)
{
  CompositingMode* p;
  bool enabled;

  Data_Get_Struct (self, CompositingMode, p);

  enabled = p->isColorWriteEnabled ();

  if (enabled)
    return Qtrue;
  else
    return Qfalse;
}

VALUE ruby_CompositingMode_is_depth_test_enabled (VALUE self)
{
  CompositingMode* p;
  bool enabled;

  Data_Get_Struct (self, CompositingMode, p);

  enabled = p->isDepthTestEnabled ();

  if (enabled)
    return Qtrue;
  else
    return Qfalse;

}

VALUE ruby_CompositingMode_is_depth_write_enabled (VALUE self)
{
  CompositingMode* p;
  bool enabled;

  Data_Get_Struct (self, CompositingMode, p);

  enabled = p->isDepthWriteEnabled ();

  if (enabled)
    return Qtrue;
  else
    return Qfalse;
}

VALUE ruby_CompositingMode_set_alpha_threshold (VALUE self, VALUE val_threshold)
{
  CompositingMode* p;
  float threshold;

  Data_Get_Struct (self, CompositingMode, p);
  threshold = RFLOAT_VALUE(val_threshold);

  p->setAlphaThreshold (threshold);

  return Qnil;
}

VALUE ruby_CompositingMode_set_alpha_write_enable (VALUE self, VALUE val_enable)
{
  CompositingMode* p;
  bool enable;

  Data_Get_Struct (self, CompositingMode, p);
  enable = (val_enable == Qtrue) ? true : false;

  p->setAlphaWriteEnable (enable);

  return Qnil;
}

VALUE ruby_CompositingMode_set_blending (VALUE self, VALUE val_mode)
{
  CompositingMode* p;
  int mode;

  Data_Get_Struct (self, CompositingMode, p);
  mode = FIX2INT (val_mode);

  p->setBlending (mode);

  return Qnil;
}

VALUE ruby_CompositingMode_set_color_write_enable (VALUE self, VALUE val_enable)
{
  CompositingMode* p;
  bool enable;

  Data_Get_Struct (self, CompositingMode, p);
  enable = (val_enable == Qtrue) ? true : false;

  p->setColorWriteEnable (enable);

  return Qnil;
}

VALUE ruby_CompositingMode_set_depth_offset (VALUE self, VALUE val_factor, VALUE val_units)
{
  CompositingMode* p;
  float factor;
  float units;

  Data_Get_Struct (self, CompositingMode, p);
  factor = RFLOAT_VALUE (val_factor);
  units = RFLOAT_VALUE (val_units);
  
  p->setDepthOffset (factor, units);

  return Qnil;
}

VALUE ruby_CompositingMode_set_depth_test_enable (VALUE self, VALUE val_enable)
{
  CompositingMode* p;
  bool enable;

  Data_Get_Struct (self, CompositingMode, p);
  enable = (val_enable == Qtrue) ? true : false;

  p->setDepthTestEnable (enable);

  return Qnil;
}

VALUE ruby_CompositingMode_set_depth_write_enable (VALUE self, VALUE val_enable)
{
  CompositingMode* p;
  bool enable;

  Data_Get_Struct (self, CompositingMode, p);
  enable = (val_enable == Qtrue) ? true : false;

  p->setDepthWriteEnable (enable);

  return Qnil;
}

/**
 * CompositingMode:: DepthOffset
 */

VALUE ruby_CompositingMode_DepthOffset_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(CompositingMode::DepthOffset));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_CompositingMode_DepthOffset_initialize (VALUE self)
{
  CompositingMode:: DepthOffset* p;
  Data_Get_Struct (self, CompositingMode::DepthOffset, p);
  return self;
}

VALUE ruby_CompositingMode_DepthOffset_get_factor (VALUE self)
{
  CompositingMode::DepthOffset* p;
  Data_Get_Struct (self, CompositingMode::DepthOffset, p);
  return rb_float_new (p->factor);
}

VALUE ruby_CompositingMode_DepthOffset_get_units (VALUE self)
{
  CompositingMode::DepthOffset* p;
  Data_Get_Struct (self, CompositingMode::DepthOffset, p);
  return rb_float_new (p->units);
}

void register_CompositingMode ()
{
    // CompositingMode
    rb_define_const (rb_cCompositingMode, "ALPHA",       INT2FIX(CompositingMode::ALPHA));
    rb_define_const (rb_cCompositingMode, "ALPHA_ADD",   INT2FIX(CompositingMode::ALPHA_ADD));
    rb_define_const (rb_cCompositingMode, "MODULATE",    INT2FIX(CompositingMode::MODULATE));
    rb_define_const (rb_cCompositingMode, "MODULATE_X2", INT2FIX(CompositingMode::MODULATE_X2));
    rb_define_const (rb_cCompositingMode, "REPLACE",     INT2FIX(CompositingMode::REPLACE));

     rb_define_alloc_func (rb_cCompositingMode, ruby_CompositingMode_allocate);
     rb_define_private_method (rb_cCompositingMode, "initialize", (VALUE(*)(...))ruby_CompositingMode_initialize, 0);

     rb_define_method (rb_cCompositingMode, "alpha_threshold",     (VALUE(*)(...))ruby_CompositingMode_get_alpha_threshold,     0);
     rb_define_method (rb_cCompositingMode, "blending",            (VALUE(*)(...))ruby_CompositingMode_get_blending,            0);
     rb_define_method (rb_cCompositingMode, "depth_offset", (VALUE(*)(...))ruby_CompositingMode_get_depth_offset, 0);
     rb_define_method (rb_cCompositingMode, "alpha_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_alpha_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "color_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_color_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "depth_test_enabled?",  (VALUE(*)(...))ruby_CompositingMode_is_depth_test_enabled,  0);
     rb_define_method (rb_cCompositingMode, "depth_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_depth_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "alpha_threashold=",    (VALUE(*)(...))ruby_CompositingMode_set_alpha_threshold,    1);
     rb_define_method (rb_cCompositingMode, "alpha_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_alpha_write_enable, 1);
     rb_define_method (rb_cCompositingMode, "blending=",            (VALUE(*)(...))ruby_CompositingMode_set_blending,           1);
     rb_define_method (rb_cCompositingMode, "color_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_color_write_enable, 1);
     rb_define_method (rb_cCompositingMode, "depth_offset=",        (VALUE(*)(...))ruby_CompositingMode_set_depth_offset,       2);
     rb_define_method (rb_cCompositingMode, "depth_test_enable=",   (VALUE(*)(...))ruby_CompositingMode_set_depth_test_enable,  1);
     rb_define_method (rb_cCompositingMode, "depth_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_depth_write_enable, 1);


    // CompositingMode:: DepthOffset
    rb_define_alloc_func (rb_cCompositingMode_DepthOffset, ruby_CompositingMode_DepthOffset_allocate);
    rb_define_private_method (rb_cCompositingMode_DepthOffset, "initialize", (VALUE(*)(...))ruby_CompositingMode_DepthOffset_initialize, 0);

    rb_define_method (rb_cCompositingMode_DepthOffset, "x",          (VALUE(*)(...))ruby_CompositingMode_DepthOffset_get_factor, 0);
    rb_define_method (rb_cCompositingMode_DepthOffset, "y",          (VALUE(*)(...))ruby_CompositingMode_DepthOffset_get_units, 0);

}
