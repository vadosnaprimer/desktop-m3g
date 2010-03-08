#include <new>
#include "ruby.h"
#include "PolygonMode.hpp"
using namespace m3g;

VALUE ruby_PolygonMode_free (PolygonMode* ptr)
{
    ptr->~PolygonMode ();
    ruby_xfree (ptr);
}

VALUE ruby_PolygonMode_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(PolygonMode));
    return Data_Wrap_Struct (self, NULL, ruby_PolygonMode_free, p);
}

VALUE ruby_PolygonMode_initialize (VALUE self)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    new (p) PolygonMode;
    return Qnil;
}

VALUE ruby_PolygonMode_get_culling (VALUE sefl)
{
    return Qnil;
}
VALUE ruby_PolygonMode_get_shading (VALUE sefl)
{
    return Qnil;
}
VALUE ruby_PolygonMode_get_winding (VALUE sefl)
{
    return Qnil;
}
VALUE ruby_PolygonMode_is_local_camera_lighting_enabled (VALUE sefl)
{
    return Qnil;
}
VALUE ruby_PolygonMode_is_perspective_correction_enabled (VALUE sefl)
{
    return Qnil;
}
VALUE ruby_PolygonMode_is_two_sided_lighting_enabled (VALUE sefl)
{
    return Qnil;
}
VALUE ruby_PolygonMode_set_culling (VALUE sefl, VALUE val_mode)
{
    return Qnil;
}
VALUE ruby_PolygonMode_set_local_camera_lighting_enable (VALUE sefl, VALUE val_enable)
{
    return Qnil;
}
VALUE ruby_PolygonMode_set_perspective_correction_enable (VALUE sefl, VALUE val_enable)
{
    return Qnil;
}
VALUE ruby_PolygonMode_set_shading (VALUE sefl, VALUE val_mode)
{
    return Qnil;
}
VALUE ruby_PolygonMode_set_two_sided_lighting_enable (VALUE sefl, VALUE val_enablec)
{
    return Qnil;
}
VALUE ruby_PolygonMode_set_winding (VALUE sefl, VALUE val_mode)
{
    return Qnil;
}


void register_PolygonMode (VALUE rb_cPolygonMode)
{
     // PolygonMode
     rb_define_const (rb_cPolygonMode, "CULL_BACK",    INT2FIX(PolygonMode::CULL_BACK));
     rb_define_const (rb_cPolygonMode, "CULL_FRONT",   INT2FIX(PolygonMode::CULL_FRONT));
     rb_define_const (rb_cPolygonMode, "CULL_NONE",    INT2FIX(PolygonMode::CULL_NONE));
     rb_define_const (rb_cPolygonMode, "CULL_FLAT",    INT2FIX(PolygonMode::CULL_FLAT));
     rb_define_const (rb_cPolygonMode, "SHADE_FLAT",   INT2FIX(PolygonMode::SHADE_FLAT));
     rb_define_const (rb_cPolygonMode, "SHADE_SMOOTH", INT2FIX(PolygonMode::SHADE_SMOOTH));
     rb_define_const (rb_cPolygonMode, "WINDING_CCW",  INT2FIX(PolygonMode::WINDING_CCW));
     rb_define_const (rb_cPolygonMode, "WINDING_CW",   INT2FIX(PolygonMode::WINDING_CW));
     
     rb_define_alloc_func (rb_cPolygonMode, ruby_PolygonMode_allocate);
     rb_define_private_method (rb_cPolygonMode, "initialize", (VALUE(*)(...))ruby_PolygonMode_initialize,0);

     rb_define_method (rb_cPolygonMode, "culling", (VALUE(*)(...))ruby_PolygonMode_get_culling, 0);
     rb_define_method (rb_cPolygonMode, "shading", (VALUE(*)(...))ruby_PolygonMode_get_shading, 0);
     rb_define_method (rb_cPolygonMode, "winding", (VALUE(*)(...))ruby_PolygonMode_get_winding, 0);
     rb_define_method (rb_cPolygonMode, "local_camera_lighting_enabled?",  (VALUE(*)(...))ruby_PolygonMode_is_local_camera_lighting_enabled, 0);
     rb_define_method (rb_cPolygonMode, "perspective_correction_enabled?", (VALUE(*)(...))ruby_PolygonMode_is_perspective_correction_enabled, 0);
     rb_define_method (rb_cPolygonMode, "two_sided_lighting_enabled?",     (VALUE(*)(...))ruby_PolygonMode_is_two_sided_lighting_enabled, 0);
     rb_define_method (rb_cPolygonMode, "culling=",                        (VALUE(*)(...))ruby_PolygonMode_set_culling, 1);
     rb_define_method (rb_cPolygonMode, "local_camera_lighting_enable=",   (VALUE(*)(...))ruby_PolygonMode_set_local_camera_lighting_enable, 1);
     rb_define_method (rb_cPolygonMode, "perspective_correction_enable=",    (VALUE(*)(...))ruby_PolygonMode_set_perspective_correction_enable, 1);
     rb_define_method (rb_cPolygonMode, "shading=",                        (VALUE(*)(...))ruby_PolygonMode_set_shading, 1);
     rb_define_method (rb_cPolygonMode, "two_sided_lighting_enable=",       (VALUE(*)(...))ruby_PolygonMode_set_two_sided_lighting_enable, 1);
     rb_define_method (rb_cPolygonMode, "winding=",                        (VALUE(*)(...))ruby_PolygonMode_set_winding, 1);



}
