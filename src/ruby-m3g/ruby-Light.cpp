#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  struct AttenuationAccessor {
    Light* light;
  };
  struct SpotAccessor {
    Light* light;
  };
  VALUE rb_cLight_AttenuationAccessor;
  VALUE rb_cLight_SpotAccessor;
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
    Data_Get_Struct (self, Light, p);
    AttenuationAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cLight_AttenuationAccessor, AttenuationAccessor, 0, -1, accessor);
    accessor->light = p;
    return val_accessor;
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
    SpotAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cLight_SpotAccessor, SpotAccessor, 0, -1, accessor);
    accessor->light = p;
    return val_accessor;
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
  VALUE val_angle    = rb_ary_entry(val_spot, 0);
  VALUE val_exponent = rb_ary_entry(val_exponent, 0);
  Light* p;
  Data_Get_Struct (self, Light, p);
  float angle    = NUMERIC2FLOAT(val_angle);
  float exponent = NUMERIC2FLOAT(val_exponent);

  p->setSpotAngle (angle);
  p->setSpotExponent (exponent);

  return Qnil;
}

/**
 * Light::AttenuationAccessor
 */

VALUE ruby_Light_AttenuationAccessor_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(AttenuationAccessor));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Light_AttenuationAccessor_initialize (VALUE self)
{
  AttenuationAccessor* p;
  Data_Get_Struct (self, AttenuationAccessor, p);
  return self;
}

VALUE ruby_Light_AttenuationAccessor_get_constant (VALUE self)
{
  AttenuationAccessor* p;
  Data_Get_Struct (self, AttenuationAccessor, p);
  float constant = p->light->getConstantAttenuation();
  return rb_float_new (constant);
}

VALUE ruby_Light_AttenuationAccessor_get_linear (VALUE self)
{
  AttenuationAccessor* p;
  Data_Get_Struct (self, AttenuationAccessor, p);
  float linear = p->light->getLinearAttenuation();
  return rb_float_new (linear);
}

VALUE ruby_Light_AttenuationAccessor_get_quadratic (VALUE self)
{
  AttenuationAccessor* p;
  Data_Get_Struct (self, AttenuationAccessor, p);
  float quadratic = p->light->getQuadraticAttenuation();
  return rb_float_new (quadratic);
}

/**
 * Light_SpotAccessor
 */

VALUE ruby_Light_SpotAccessor_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(SpotAccessor));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Light_SpotAccessor_initialize (VALUE self)
{
  SpotAccessor* p;
  Data_Get_Struct (self, SpotAccessor, p);
  return self;
}

VALUE ruby_Light_SpotAccessor_get_angle (VALUE self)
{
  SpotAccessor* p;
  Data_Get_Struct (self, SpotAccessor, p);
  float angle = p->light->getSpotAngle();
  return rb_float_new (angle);
}

VALUE ruby_Light_SpotAccessor_get_exponent (VALUE self)
{
  SpotAccessor* p;
  Data_Get_Struct (self, SpotAccessor, p);
  float exponent = p->light->getSpotExponent();
  return rb_float_new (exponent);
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

     // Light_AttenuationAccessor
     rb_cLight_AttenuationAccessor  = rb_define_class_under (rb_cLight, "AttenuationAccessor", rb_cObject);

     rb_define_alloc_func (rb_cLight_AttenuationAccessor, ruby_Light_AttenuationAccessor_allocate);
     rb_define_private_method (rb_cLight_AttenuationAccessor, "initialize", (VALUE(*)(...))ruby_Light_AttenuationAccessor_initialize, 0);

     rb_define_method (rb_cLight_AttenuationAccessor, "constant",           (VALUE(*)(...))ruby_Light_AttenuationAccessor_get_constant, 0);
     rb_define_method (rb_cLight_AttenuationAccessor, "linear",             (VALUE(*)(...))ruby_Light_AttenuationAccessor_get_linear, 0);
     rb_define_method (rb_cLight_AttenuationAccessor, "quadratic",          (VALUE(*)(...))ruby_Light_AttenuationAccessor_get_quadratic, 0);

     // Light_SpotAccessor
     rb_cLight_SpotAccessor  = rb_define_class_under (rb_cLight, "SpotAccessor", rb_cObject);

     rb_define_alloc_func (rb_cLight_SpotAccessor, ruby_Light_SpotAccessor_allocate);
     rb_define_private_method (rb_cLight_SpotAccessor, "initialize", (VALUE(*)(...))ruby_Light_SpotAccessor_initialize, 0);

     rb_define_method (rb_cLight_SpotAccessor, "angle",         (VALUE(*)(...))ruby_Light_SpotAccessor_get_angle, 0);
     rb_define_method (rb_cLight_SpotAccessor, "exponent",      (VALUE(*)(...))ruby_Light_SpotAccessor_get_exponent, 0);
}
