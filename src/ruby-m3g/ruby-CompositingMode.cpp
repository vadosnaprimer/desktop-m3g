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
    __TRY__;
    ptr->~CompositingMode ();
    __CATCH__;
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
    __TRY__;
    new (p) CompositingMode;
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_CompositingMode_get_alpha_threshold (VALUE self)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    float alpha;
    __TRY__;
    alpha = p->getAlphaThreshold ();
    __CATCH__;
    return rb_float_new (alpha);
}

VALUE ruby_CompositingMode_get_blending (VALUE self)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    int mode;
    __TRY__;
    mode = p->getBlending ();
    __CATCH__;
    return INT2NUM(mode);
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
    Data_Get_Struct (self, CompositingMode, p);
    bool enabled;
    __TRY__;
    enabled = p->isAlphaWriteEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_CompositingMode_is_color_write_enabled (VALUE self)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    bool enabled;
    __TRY__;
    enabled = p->isColorWriteEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_CompositingMode_is_depth_test_enabled (VALUE self)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    bool enabled;
    __TRY__;
    enabled = p->isDepthTestEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_CompositingMode_is_depth_write_enabled (VALUE self)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    bool enabled;
    __TRY__;
    enabled = p->isDepthWriteEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_CompositingMode_set_alpha_threshold (VALUE self, VALUE val_threshold)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    float threshold = NUM2DBL(val_threshold);
    __TRY__;
    p->setAlphaThreshold (threshold);
    __CATCH__;
    return Qnil;
}

VALUE ruby_CompositingMode_set_alpha_write_enable (VALUE self, VALUE val_enable)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setAlphaWriteEnable (enable);
    __CATCH__;
    return Qnil;
}

VALUE ruby_CompositingMode_set_blending (VALUE self, VALUE val_mode)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    int mode = NUM2INT (val_mode);
    __TRY__;
    p->setBlending (mode);
    __CATCH__;
    return Qnil;
}

VALUE ruby_CompositingMode_set_color_write_enable (VALUE self, VALUE val_enable)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setColorWriteEnable (enable);
    __CATCH__;
    return Qnil;
}

VALUE ruby_CompositingMode_set_depth_offset (VALUE self, VALUE val_depth_offset)
{
    VALUE val_factor = rb_ary_entry(val_depth_offset, 0);
    VALUE val_units  = rb_ary_entry(val_depth_offset, 1);
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    float factor = NUM2DBL(val_factor);
    float units  = NUM2DBL(val_units);
    __TRY__;
    p->setDepthOffset (factor, units);
    __CATCH__;
    return Qnil;
}

VALUE ruby_CompositingMode_set_depth_test_enable (VALUE self, VALUE val_enable)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setDepthTestEnable (enable);
    __CATCH__;
    return Qnil;
}

VALUE ruby_CompositingMode_set_depth_write_enable (VALUE self, VALUE val_enable)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setDepthWriteEnable (enable);
    __CATCH__;
    return Qnil;
}

/**
 * CompositingMode:: DepthOffsetAccessor
 */

VALUE ruby_CompositingMode_DepthOffsetAccessor_get_factor (VALUE self)
{
    DepthOffsetAccessor* p;
    Data_Get_Struct (self, DepthOffsetAccessor, p);
    float factor;
    __TRY__;
    factor = p->compositing_mode->getDepthOffsetFactor ();
    __CATCH__;
    return rb_float_new (factor);
}

VALUE ruby_CompositingMode_DepthOffsetAccessor_get_units (VALUE self)
{
    DepthOffsetAccessor* p;
    Data_Get_Struct (self, DepthOffsetAccessor, p);
    float units;
    __TRY__;
    units = p->compositing_mode->getDepthOffsetUnits ();
    __CATCH__;
    return rb_float_new (units);
}

void register_CompositingMode ()
{
    // CompositingMode
    rb_cCompositingMode     = rb_define_class_under (rb_mM3G, "CompositingMode",     rb_cObject3D);

    rb_define_const (rb_cCompositingMode, "ALPHA",       INT2NUM(CompositingMode::ALPHA));
    rb_define_const (rb_cCompositingMode, "ALPHA_ADD",   INT2NUM(CompositingMode::ALPHA_ADD));
    rb_define_const (rb_cCompositingMode, "MODULATE",    INT2NUM(CompositingMode::MODULATE));
    rb_define_const (rb_cCompositingMode, "MODULATE_X2", INT2NUM(CompositingMode::MODULATE_X2));
    rb_define_const (rb_cCompositingMode, "REPLACE",     INT2NUM(CompositingMode::REPLACE));

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
