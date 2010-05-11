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
    __TRY__;
    ptr->~Light ();
    __CATCH__;
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
    __TRY__;
    new (p) Light;
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Light_get_color (VALUE self)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    int rgb;
    __TRY__;
    rgb = p->getColor ();
    __CATCH__;
    return INT2NUM(rgb);
}

VALUE ruby_Light_get_attenuation (VALUE self)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    AttenuationAccessor* accessor;
    VALUE            val_accessor = Data_Make_Struct (rb_cLight_AttenuationAccessor, AttenuationAccessor, 0, -1, accessor);
    accessor->light = p;
    return val_accessor;
}

VALUE ruby_Light_get_intensity (VALUE self)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    float intensity;
    __TRY__;
    intensity = p->getIntensity ();
    __CATCH__;
    return rb_float_new(intensity);
}

VALUE ruby_Light_get_mode (VALUE self)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    int mode;
    __TRY__;
    mode = p->getMode();
    __CATCH__;
    return INT2NUM(mode);
}


VALUE ruby_Light_get_spot (VALUE self)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    SpotAccessor* accessor;
    VALUE     val_accessor = Data_Make_Struct (rb_cLight_SpotAccessor, SpotAccessor, 0, -1, accessor);
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
    float constant  = NUM2DBL(val_constant);
    float linear    = NUM2DBL(val_linear);
    float quadratic = NUM2DBL(val_quadratic);
    __TRY__;
    p->setAttenuation (constant, linear, quadratic);
    __CATCH__;
    return Qnil;
}


VALUE ruby_Light_set_color (VALUE self, VALUE val_rgb)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    int rgb = NUM2INT (rgb);
    __TRY__;
    p->setColor (rgb);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Light_set_intensity (VALUE self, VALUE val_intensity)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    float intensity = NUM2DBL(val_intensity);
    __TRY__;
    p->setIntensity (intensity);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Light_set_mode (VALUE self, VALUE val_mode)
{
    Light* p;
    Data_Get_Struct (self, Light, p);
    int mode = NUM2INT (val_mode);
    __TRY__;
    p->setMode (mode);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Light_set_spot (VALUE self, VALUE val_spot)
{
    VALUE val_angle    = rb_ary_entry(val_spot, 0);
    VALUE val_exponent = rb_ary_entry(val_spot, 1);
    Light* p;
    Data_Get_Struct (self, Light, p);
    float angle    = NUM2DBL(val_angle);
    float exponent = NUM2DBL(val_exponent);
    __TRY__;
    p->setSpotAngle (angle);
    p->setSpotExponent (exponent);
    __CATCH__;
    return Qnil;
}

/**
 * Light::AttenuationAccessor
 */

VALUE ruby_Light_AttenuationAccessor_get_constant (VALUE self)
{
    AttenuationAccessor* p;
    Data_Get_Struct (self, AttenuationAccessor, p);
    float constant;
    __TRY__;
    constant = p->light->getConstantAttenuation();
    __CATCH__;
    return rb_float_new (constant);
}

VALUE ruby_Light_AttenuationAccessor_get_linear (VALUE self)
{
    AttenuationAccessor* p;
    Data_Get_Struct (self, AttenuationAccessor, p);
    float linear;
    __TRY__;
    linear = p->light->getLinearAttenuation();
    __CATCH__;
    return rb_float_new (linear);
}

VALUE ruby_Light_AttenuationAccessor_get_quadratic (VALUE self)
{
    AttenuationAccessor* p;
    float quadratic;
    Data_Get_Struct (self, AttenuationAccessor, p);
    __TRY__;
    quadratic = p->light->getQuadraticAttenuation();
    __CATCH__;
    return rb_float_new (quadratic);
}

/**
 * Light_SpotAccessor
 */

VALUE ruby_Light_SpotAccessor_get_angle (VALUE self)
{
    SpotAccessor* p;
    Data_Get_Struct (self, SpotAccessor, p);
    float angle;
    __TRY__;
    angle = p->light->getSpotAngle();
    __CATCH__;
    return rb_float_new (angle);
}

VALUE ruby_Light_SpotAccessor_get_exponent (VALUE self)
{
    SpotAccessor* p;
    Data_Get_Struct (self, SpotAccessor, p);
    float exponent;
    __TRY__;
    exponent = p->light->getSpotExponent();
    __CATCH__;
    return rb_float_new (exponent);
}


void register_Light ()
{
    // Light
    rb_cLight = rb_define_class_under (rb_mM3G, "Light", rb_cNode);

    rb_define_const (rb_cLight, "AMBIENT",     INT2NUM(Light::AMBIENT));
    rb_define_const (rb_cLight, "DIRECTIONAL", INT2NUM(Light::DIRECTIONAL));
    rb_define_const (rb_cLight, "OMNI",        INT2NUM(Light::OMNI));
    rb_define_const (rb_cLight, "SPOT",        INT2NUM(Light::SPOT));

    rb_define_alloc_func (rb_cLight, ruby_Light_allocate);
    rb_define_private_method (rb_cLight, "initialize", (VALUE(*)(...))ruby_Light_initialize,      0);

    rb_define_method (rb_cLight, "color",              (VALUE(*)(...))ruby_Light_get_color,       0);
    rb_define_method (rb_cLight, "attenuation",        (VALUE(*)(...))ruby_Light_get_attenuation, 0);
    rb_define_method (rb_cLight, "intensity",          (VALUE(*)(...))ruby_Light_get_intensity,   0);
    rb_define_method (rb_cLight, "mode",               (VALUE(*)(...))ruby_Light_get_mode,        0);
    rb_define_method (rb_cLight, "spot",               (VALUE(*)(...))ruby_Light_get_spot,        0);
    rb_define_method (rb_cLight, "attenuation=",       (VALUE(*)(...))ruby_Light_set_attenuation, 1);
    rb_define_method (rb_cLight, "color=",             (VALUE(*)(...))ruby_Light_set_color,       1);
    rb_define_method (rb_cLight, "intensity=",         (VALUE(*)(...))ruby_Light_set_intensity,   1);
    rb_define_method (rb_cLight, "mode=",              (VALUE(*)(...))ruby_Light_set_mode,        1);
    rb_define_method (rb_cLight, "spot=",              (VALUE(*)(...))ruby_Light_set_spot,        1);

    // Light_AttenuationAccessor
    rb_cLight_AttenuationAccessor  = rb_define_class_under (rb_cLight, "AttenuationAccessor", rb_cObject);

    rb_define_method (rb_cLight_AttenuationAccessor, "constant",           (VALUE(*)(...))ruby_Light_AttenuationAccessor_get_constant,  0);
    rb_define_method (rb_cLight_AttenuationAccessor, "linear",             (VALUE(*)(...))ruby_Light_AttenuationAccessor_get_linear,    0);
    rb_define_method (rb_cLight_AttenuationAccessor, "quadratic",          (VALUE(*)(...))ruby_Light_AttenuationAccessor_get_quadratic, 0);

    // Light_SpotAccessor
    rb_cLight_SpotAccessor  = rb_define_class_under (rb_cLight, "SpotAccessor", rb_cObject);

    rb_define_method (rb_cLight_SpotAccessor, "angle",         (VALUE(*)(...))ruby_Light_SpotAccessor_get_angle,    0);
    rb_define_method (rb_cLight_SpotAccessor, "exponent",      (VALUE(*)(...))ruby_Light_SpotAccessor_get_exponent, 0);
}
