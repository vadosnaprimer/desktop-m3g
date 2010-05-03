#include <new>
#include "ruby.h"
#include "Light.hpp"
using namespace m3g;

VALUE ruby_Light_free (Light* ptr)
{
    ptr->~Light ();
    ruby_xfree (ptr);
}

VALUE ruby_Light_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Light));
    return Data_Wrap_Struct (self, NULL, ruby_Light_free, p);
}

VALUE ruby_Light_initialize (VALUE self)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    new (p) Light;
    return Qnil;
}

VALUE ruby_Light_get_color (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_get_constant_attenuation (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_get_intensity (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_get_linear_attenuation (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_get_mode (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_get_quadratic_attenuation (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_get_spot_angle (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_get_spot_exponent (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_get_attenuation (VALUE self)
{
    return Qnil;
}

VALUE ruby_Light_set_color (VALUE self, VALUE val_rgb)
{
    return Qnil;
}

VALUE ruby_Light_set_intensity (VALUE self, VALUE val_intensity)
{
    return Qnil;
}

VALUE ruby_Light_set_mode (VALUE self, VALUE val_mode)
{
    return Qnil;
}

VALUE ruby_Light_set_spot_angle (VALUE self, VALUE val_angle)
{
    return Qnil;
}

VALUE ruby_Light_set_spot_exponent (VALUE self, VALUE val_exponent)
{
    return Qnil;
}

void register_Light (VALUE rb_cLight)
{
     // Light
     rb_define_const (rb_cLight, "AMBIENT",     INT2FIX(Light::AMBIENT));
     rb_define_const (rb_cLight, "DIRECTIONAL", INT2FIX(Light::DIRECTIONAL));
     rb_define_const (rb_cLight, "OMNI",        INT2FIX(Light::OMNI));
     rb_define_const (rb_cLight, "SPOT",        INT2FIX(Light::SPOT));

     rb_define_alloc_func (rb_cLight, ruby_Light_allocate);
     rb_define_private_method (rb_cLight, "initialize", (VALUE(*)(...))ruby_Light_initialize, 0);

     rb_define_method (rb_cLight, "color",                (VALUE(*)(...))ruby_Light_get_color, 0);
     rb_define_method (rb_cLight, "constant_attenuation", (VALUE(*)(...))ruby_Light_get_constant_attenuation, 0);
     rb_define_method (rb_cLight, "intensity",            (VALUE(*)(...))ruby_Light_get_intensity, 0);
     rb_define_method (rb_cLight, "linear_attenuation",   (VALUE(*)(...))ruby_Light_get_linear_attenuation, 0);
     rb_define_method (rb_cLight, "mode",                 (VALUE(*)(...))ruby_Light_get_mode, 0);
     rb_define_method (rb_cLight, "quadratic_attenuation",(VALUE(*)(...))ruby_Light_get_quadratic_attenuation, 0);
     rb_define_method (rb_cLight, "spot_angle",           (VALUE(*)(...))ruby_Light_get_spot_angle, 0);
     rb_define_method (rb_cLight, "spot_exponent",        (VALUE(*)(...))ruby_Light_get_spot_exponent, 0);
     rb_define_method (rb_cLight, "attenuation",          (VALUE(*)(...))ruby_Light_get_attenuation, 3);
     rb_define_method (rb_cLight, "color=",                (VALUE(*)(...))ruby_Light_set_color, 1);
     rb_define_method (rb_cLight, "intensity=",            (VALUE(*)(...))ruby_Light_set_intensity, 1);
     rb_define_method (rb_cLight, "mode=",                 (VALUE(*)(...))ruby_Light_set_mode, 1);
     rb_define_method (rb_cLight, "spot_angle=",           (VALUE(*)(...))ruby_Light_set_spot_angle, 1);
     rb_define_method (rb_cLight, "spot_exponent=",        (VALUE(*)(...))ruby_Light_set_spot_exponent, 1);


}
