#include <new>
#include "ruby.h"
#include "CompositingMode.hpp"
using namespace m3g;

VALUE ruby_CompositingMode_free (CompositingMode* ptr)
{
    ptr->~CompositingMode ();
    ruby_xfree (ptr);
}

VALUE ruby_CompositingMode_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(CompositingMode));
    return Data_Wrap_Struct (self, NULL, ruby_CompositingMode_free, p);
}

VALUE ruby_CompositingMode_initialize (VALUE self)
{
    CompositingMode* p;
    Data_Get_Struct (self, CompositingMode, p);
    new (p) CompositingMode;
    return Qnil;
}

VALUE ruby_CompositingMode_get_alpha_threshold (VALUE self)
{
    return Qnil;
}

VALUE ruby_CompositingMode_get_blending (VALUE self)
{
    return Qnil;
}

VALUE ruby_CompositingMode_get_depth_offset_factor (VALUE self)
{
    return Qnil;
}

VALUE ruby_CompositingMode_get_depth_offset_units (VALUE self)
{
    return Qnil;
}

VALUE ruby_CompositingMode_is_alpha_write_enabled (VALUE self)
{
    return Qnil;
}

VALUE ruby_CompositingMode_is_color_write_enabled (VALUE self)
{
    return Qnil;
}

VALUE ruby_CompositingMode_is_depth_test_enabled (VALUE self)
{
    return Qnil;
}

VALUE ruby_CompositingMode_is_depth_write_enabled (VALUE self)
{
    return Qnil;
}

VALUE ruby_CompositingMode_set_alpha_threshold (VALUE self, VALUE val_threshold)
{
    return Qnil;
}

VALUE ruby_CompositingMode_set_alpha_write_enable (VALUE self, VALUE val_enable)
{
    return Qnil;
}

VALUE ruby_CompositingMode_set_blending (VALUE self, VALUE val_mode)
{
    return Qnil;
}

VALUE ruby_CompositingMode_set_color_write_enable (VALUE self, VALUE val_enable)
{
    return Qnil;
}

VALUE ruby_CompositingMode_set_depth_offset (VALUE self, VALUE val_factor_and_units)
{
    return Qnil;
}

VALUE ruby_CompositingMode_set_depth_test_enable (VALUE self, VALUE val_enable)
{
    return Qnil;
}

VALUE ruby_CompositingMode_set_depth_write_enable (VALUE self, VALUE val_enable)
{
    return Qnil;
}


void register_CompositingMode (VALUE rb_cCompositingMode)
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
     rb_define_method (rb_cCompositingMode, "depth_offset_factor", (VALUE(*)(...))ruby_CompositingMode_get_depth_offset_factor, 0);
     rb_define_method (rb_cCompositingMode, "alpha_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_alpha_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "color_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_color_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "depth_test_enabled?",  (VALUE(*)(...))ruby_CompositingMode_is_depth_test_enabled,  0);
     rb_define_method (rb_cCompositingMode, "depth_write_enabled?", (VALUE(*)(...))ruby_CompositingMode_is_depth_write_enabled, 0);
     rb_define_method (rb_cCompositingMode, "alpha_threashold=",    (VALUE(*)(...))ruby_CompositingMode_set_alpha_threshold,    1);
     rb_define_method (rb_cCompositingMode, "alpha_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_alpha_write_enable, 1);
     rb_define_method (rb_cCompositingMode, "blending=",            (VALUE(*)(...))ruby_CompositingMode_set_blending,           1);
     rb_define_method (rb_cCompositingMode, "color_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_color_write_enable, 1);
     rb_define_method (rb_cCompositingMode, "depth_offset=",        (VALUE(*)(...))ruby_CompositingMode_set_depth_offset,       1);
     rb_define_method (rb_cCompositingMode, "depth_test_enable=",   (VALUE(*)(...))ruby_CompositingMode_set_depth_test_enable,  1);
     rb_define_method (rb_cCompositingMode, "depth_write_enable=",  (VALUE(*)(...))ruby_CompositingMode_set_depth_write_enable, 1);

}
