#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
	struct DepthOffsetAccessor {
		CompositingMode* compositing_mode;
	};
	VALUE rb_cCompositingMode_DepthOffsetAccessor;
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
  Data_Get_Struct (self, CompositingMode, p);
  DepthOffsetAccessor* accessor;
  VALUE val_accessor = Data_Make_Struct (rb_cCompositingMode_DepthOffsetAccessor, DepthOffsetAccessor, 0, -1, accessor);
  accessor->compositing_mode = p;
  return val_accessor;
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
  threshold = NUMERIC2FLOAT(val_threshold);

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

VALUE ruby_CompositingMode_set_depth_offset (VALUE self, VALUE val_depth_offset)
{
  VALUE val_factor = rb_ary_entry(val_depth_offset, 0);
  VALUE val_units  = rb_ary_entry(val_depth_offset, 1);
  CompositingMode* p;
  Data_Get_Struct (self, CompositingMode, p);
  float factor = NUMERIC2FLOAT(val_factor);
  float units  = NUMERIC2FLOAT(val_units);
  
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
 * CompositingMode:: DepthOffsetAccessor
 */

VALUE ruby_CompositingMode_DepthOffsetAccessor_get_factor (VALUE self)
{
  DepthOffsetAccessor* p;
  Data_Get_Struct (self, DepthOffsetAccessor, p);
  float factor = p->compositing_mode->getDepthOffsetFactor ();
  return rb_float_new (factor);
}

VALUE ruby_CompositingMode_DepthOffsetAccessor_get_units (VALUE self)
{
  DepthOffsetAccessor* p;
  Data_Get_Struct (self, DepthOffsetAccessor, p);
  float units = p->compositing_mode->getDepthOffsetUnits ();
  return rb_float_new (units);
}

void register_CompositingMode ()
{
    // CompositingMode
    rb_cCompositingMode     = rb_define_class_under (rb_mM3G, "CompositingMode",     rb_cObject3D);

    rb_define_const (rb_cCompositingMode, "ALPHA",       INT2FIX(CompositingMode::ALPHA));
    rb_define_const (rb_cCompositingMode, "ALPHA_ADD",   INT2FIX(CompositingMode::ALPHA_ADD));
    rb_define_const (rb_cCompositingMode, "MODULATE",    INT2FIX(CompositingMode::MODULATE));
    rb_define_const (rb_cCompositingMode, "MODULATE_X2", INT2FIX(CompositingMode::MODULATE_X2));
    rb_define_const (rb_cCompositingMode, "REPLACE",     INT2FIX(CompositingMode::REPLACE));

     rb_define_alloc_func (rb_cCompositingMode, ruby_CompositingMode_allocate);
     rb_define_private_method (rb_cCompositingMode, "initialize", (VALUE(*)(...))ruby_CompositingMode_initialize, 0);

     rb_define_method (rb_cCompositingMode, "alpha_threshold",      (VALUE(*)(...))ruby_CompositingMode_get_alpha_threshold,    0);
     rb_define_method (rb_cCompositingMode, "blending",             (VALUE(*)(...))ruby_CompositingMode_get_blending,           0);
     rb_define_method (rb_cCompositingMode, "depth_offset",         (VALUE(*)(...))ruby_CompositingMode_get_depth_offset,       0);
     rb_define_method (rb_cCompositingMode, "alpha_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_alpha_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "color_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_color_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "depth_test_enabled?",  (VALUE(*)(...))ruby_CompositingMode_is_depth_test_enabled,  0);
     rb_define_method (rb_cCompositingMode, "depth_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_depth_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "alpha_threshold=",     (VALUE(*)(...))ruby_CompositingMode_set_alpha_threshold,    1);
     rb_define_method (rb_cCompositingMode, "alpha_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_alpha_write_enable, 1);
     rb_define_method (rb_cCompositingMode, "blending=",            (VALUE(*)(...))ruby_CompositingMode_set_blending,           1);
     rb_define_method (rb_cCompositingMode, "color_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_color_write_enable, 1);
     rb_define_method (rb_cCompositingMode, "depth_offset=",        (VALUE(*)(...))ruby_CompositingMode_set_depth_offset,       1);
     rb_define_method (rb_cCompositingMode, "depth_test_enable=",   (VALUE(*)(...))ruby_CompositingMode_set_depth_test_enable,  1);
     rb_define_method (rb_cCompositingMode, "depth_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_depth_write_enable, 1);


    // CompositingMode:: DepthOffsetAccessor
     rb_cCompositingMode_DepthOffsetAccessor = rb_define_class_under (rb_cCompositingMode, "DepthOffsetAccessor", rb_cObject);

    rb_define_method (rb_cCompositingMode_DepthOffsetAccessor, "factor",     (VALUE(*)(...))ruby_CompositingMode_DepthOffsetAccessor_get_factor, 0);
    rb_define_method (rb_cCompositingMode_DepthOffsetAccessor, "units",      (VALUE(*)(...))ruby_CompositingMode_DepthOffsetAccessor_get_units,  0);

}
