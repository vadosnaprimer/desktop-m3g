#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  VALUE rb_cLight_Attenuation;
  VALUE rb_cLight_Spot;
};

VALUE ruby_Light_free (Light* ptr)
{
    ptr->~Light ();
    ruby_xfree (ptr);
}

VALUE ruby_Light_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Light));
    return Data_Wrap_Struct (self, 0, ruby_Light_free, p);
}

VALUE ruby_Light_initialize (VALUE self)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    new (p) Light;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Light_get_color (VALUE self)
{
    Light* p;
    int rgb;
    Data_Get_Struct (self, Light, p);

    rgb = p->getColor ();

    return INT2FIX(rgb);
}

VALUE ruby_Light_get_attenuation (VALUE self)
{
    Light* p;
    Light::Attenuation* attenuation;
    VALUE val_attenuation;

    Data_Get_Struct (self, Light, p);
    val_attenuation = Data_Make_Struct (val_attenuation, Light::Attenuation, 0, -1, attenuation);

    attenuation->constant  = p->getConstantAttenuation ();
    attenuation->linear    = p->getLinearAttenuation ();
    attenuation->quadratic = p->getQuadraticAttenuation ();
    
    return val_attenuation;
}

VALUE ruby_Light_get_intensity (VALUE self)
{
    Light* p;
    float intensity;

    Data_Get_Struct (self, Light, p);

    intensity = p->getIntensity ();

    return rb_float_new(intensity);
}

VALUE ruby_Light_get_mode (VALUE self)
{
    Light* p;
    int mode;

    Data_Get_Struct (self, Light, p);

    mode = p->getMode();

    return INT2FIX(mode);
}


VALUE ruby_Light_get_spot (VALUE self)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    Light::Spot* spot;
    VALUE val_spot = Data_Make_Struct (rb_cLight_Spot, Light::Spot, 0, -1, spot);
    spot->angle    = p->getSpotAngle ();
    spot->exponent = p->getSpotExponent ();
    return val_spot;
}

VALUE ruby_Light_set_attenuation (VALUE self, VALUE val_args)
{
  VALUE val_constant  = rb_ary_entry(val_args, 0);
  VALUE val_linear    = rb_ary_entry(val_args, 1);
  VALUE val_quadratic = rb_ary_entry(val_args, 2);
  Light* p;
  Data_Get_Struct (self, Light, p);
  float constant  = RFLOAT_VALUE(val_constant);
  float linear    = RFLOAT_VALUE(val_linear);
  float quadratic = RFLOAT_VALUE(val_quadratic);

  p->setAttenuation (constant, linear, quadratic);

  return Qnil;
}


VALUE ruby_Light_set_color (VALUE self, VALUE val_rgb)
{
    Light* p;
    int rgb;

    Data_Get_Struct (self, Light, p);
    rgb = FIX2INT (rgb);

    p->setColor (rgb);

    return Qnil;
}

VALUE ruby_Light_set_intensity (VALUE self, VALUE val_intensity)
{
    Light* p;
    float intensity;

    Data_Get_Struct (self, Light, p);
    intensity = RFLOAT_VALUE(val_intensity);

    p->setIntensity (intensity);

    return Qnil;
}

VALUE ruby_Light_set_mode (VALUE self, VALUE val_mode)
{
    Light* p;
    int mode;

    Data_Get_Struct (self, Light, p);
    mode = FIX2INT (val_mode);

    p->setMode (mode);

    return Qnil;
}

VALUE ruby_Light_set_spot (VALUE self, VALUE val_spot)
{
    Light* p;
    Light::Spot* spot;

    Data_Get_Struct (self, Light, p);
    Data_Get_Struct (val_spot, Light::Spot, spot);

    p->setSpotAngle (spot->angle);
    p->setSpotExponent (spot->exponent);

    return Qnil;
}

/**
 * Light::Attenuation
 */

VALUE ruby_Light_Attenuation_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(Light::Attenuation));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Light_Attenuation_initialize (VALUE self, VALUE val_constant, VALUE val_linear, VALUE val_quadratic)
{
  Light::Attenuation* p;
    Data_Get_Struct (self, Light::Attenuation, p);
    p->constant  = RFLOAT_VALUE (val_constant);
    p->linear    = RFLOAT_VALUE (val_linear);
    p->quadratic = RFLOAT_VALUE (val_quadratic);

    return self;
}

VALUE ruby_Light_Attenuation_get_constant (VALUE self)
{
  Light::Attenuation* p;
  Data_Get_Struct (self, Light::Attenuation, p);

  return rb_float_new (p->constant);
}

VALUE ruby_Light_Attenuation_get_linear (VALUE self)
{
  Light::Attenuation* p;
  Data_Get_Struct (self, Light::Attenuation, p);

  return rb_float_new (p->linear);
}

VALUE ruby_Light_Attenuation_get_quadratic (VALUE self)
{
  Light::Attenuation* p;
  Data_Get_Struct (self, Light::Attenuation, p);

  return rb_float_new (p->quadratic);
}

/**
 * Light::Spot
 */
VALUE ruby_Light_Spot_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(Light::Spot));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Light_Spot_initialize (VALUE self, VALUE val_angle, VALUE val_exponent)
{
  Light::Spot* p;
    Data_Get_Struct (self, Light::Spot, p);
    p->angle     = RFLOAT_VALUE (val_angle);
    p->exponent  = RFLOAT_VALUE (val_exponent);
    return self;
}

VALUE ruby_Light_Spot_get_angle (VALUE self)
{
  Light::Spot* p;
  Data_Get_Struct (self, Light::Spot, p);

  return rb_float_new (p->angle);
}

VALUE ruby_Light_Spot_get_exponent (VALUE self)
{
  Light::Spot* p;
  Data_Get_Struct (self, Light::Spot, p);

  return rb_float_new (p->exponent);
}



void register_Light ()
{
     // Light
     rb_define_const (rb_cLight, "AMBIENT",     INT2FIX(Light::AMBIENT));
     rb_define_const (rb_cLight, "DIRECTIONAL", INT2FIX(Light::DIRECTIONAL));
     rb_define_const (rb_cLight, "OMNI",        INT2FIX(Light::OMNI));
     rb_define_const (rb_cLight, "SPOT",        INT2FIX(Light::SPOT));

     rb_define_alloc_func (rb_cLight, ruby_Light_allocate);
     rb_define_private_method (rb_cLight, "initialize", (VALUE(*)(...))ruby_Light_initialize, 0);

     rb_define_method (rb_cLight, "color",                (VALUE(*)(...))ruby_Light_get_color, 0);
     rb_define_method (rb_cLight, "attenuation", (VALUE(*)(...))ruby_Light_get_attenuation, 0);
     rb_define_method (rb_cLight, "intensity",            (VALUE(*)(...))ruby_Light_get_intensity, 0);
     rb_define_method (rb_cLight, "mode",                 (VALUE(*)(...))ruby_Light_get_mode, 0);
     rb_define_method (rb_cLight, "spot",           (VALUE(*)(...))ruby_Light_get_spot, 0);
     rb_define_method (rb_cLight, "attenuation=",          (VALUE(*)(...))ruby_Light_set_attenuation, 1);
     rb_define_method (rb_cLight, "color=",                (VALUE(*)(...))ruby_Light_set_color, 1);
     rb_define_method (rb_cLight, "intensity=",            (VALUE(*)(...))ruby_Light_set_intensity, 1);
     rb_define_method (rb_cLight, "mode=",                 (VALUE(*)(...))ruby_Light_set_mode, 1);
     rb_define_method (rb_cLight, "spot=",           (VALUE(*)(...))ruby_Light_set_spot, 1);

     // Light::Attenuation
     rb_define_alloc_func (rb_cLight_Attenuation, ruby_Light_Attenuation_allocate);
     rb_define_private_method (rb_cLight_Attenuation, "initialize", (VALUE(*)(...))ruby_Light_Attenuation_initialize, 3);

     rb_define_method (rb_cLight_Attenuation, "constant",                (VALUE(*)(...))ruby_Light_Attenuation_get_constant, 0);
     rb_define_method (rb_cLight_Attenuation, "linear",                (VALUE(*)(...))ruby_Light_Attenuation_get_linear, 0);
     rb_define_method (rb_cLight_Attenuation, "quadratic",                (VALUE(*)(...))ruby_Light_Attenuation_get_quadratic, 0);

     // Light::Spot
     rb_define_alloc_func (rb_cLight_Spot, ruby_Light_Spot_allocate);
     rb_define_private_method (rb_cLight_Spot, "initialize", (VALUE(*)(...))ruby_Light_Spot_initialize, 2);

     rb_define_method (rb_cLight_Spot, "angle",         (VALUE(*)(...))ruby_Light_Spot_get_angle, 0);
     rb_define_method (rb_cLight_Spot, "exponent",      (VALUE(*)(...))ruby_Light_Spot_get_exponent, 0);

}
