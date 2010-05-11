#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
    struct DistanceAccessor {
        Fog* fog;
    };
    VALUE rb_cFog_DistanceAccessor;
}

VALUE ruby_Fog_free (Fog* ptr)
{
    __TRY__;
    ptr->~Fog ();
    __CATCH__;
    ruby_xfree (ptr);
}

VALUE ruby_Fog_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Fog));
    return Data_Wrap_Struct (self, 0, ruby_Fog_free, p);
}

VALUE ruby_Fog_initialize (VALUE self)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    __TRY__;
    new (p) Fog;
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Fog_get_color (VALUE self)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    int color;
    __TRY__;
    color = p->getColor ();
    __CATCH__;
    return INT2NUM (color);
}

VALUE ruby_Fog_get_density (VALUE self)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    float density;
    __TRY__;
    density = p->getDensity ();
    __CATCH__;
    return rb_float_new(density);
}

VALUE ruby_Fog_get_distance (VALUE self)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    DistanceAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cFog_DistanceAccessor, DistanceAccessor, 0, -1, accessor);
    accessor->fog = p;
    return val_accessor;
}

VALUE ruby_Fog_get_mode (VALUE self)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    int mode;
    __TRY__;
    mode = p->getMode ();
    __CATCH__;
    return INT2NUM(mode);
}

VALUE ruby_Fog_set_color (VALUE self, VALUE val_rgb)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    int rgb = NUM2INT (val_rgb);
    __TRY__;
    p->setColor (rgb);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Fog_set_density (VALUE self, VALUE val_density)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    float density = NUM2DBL (val_density);
    __TRY__;
    p->setDensity (density);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Fog_set_linear (VALUE self, VALUE val_linear)
{
    VALUE val_near = rb_ary_entry (val_linear, 0);
    VALUE val_far  = rb_ary_entry (val_linear, 1);
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    float near = NUM2DBL (val_near);
    float far  = NUM2DBL (val_far);
    __TRY__;
    p->setLinear (near, far);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Fog_set_mode (VALUE self, VALUE val_mode)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    int mode = NUM2INT (val_mode);
    __TRY__;
    p->setMode (mode);
    __CATCH__;
    return Qnil;
}


/**
 * Fog::DistanceAccessor
 */


VALUE ruby_Fog_DistanceAccessor_get_near (VALUE self)
{
    DistanceAccessor* p;
    Data_Get_Struct (self, DistanceAccessor, p);
    float near;
    __TRY__;
    near = p->fog->getNearDistance ();
    __CATCH__;
    return rb_float_new(near);
}

VALUE ruby_Fog_DistanceAccessor_get_far (VALUE self)
{
    DistanceAccessor* p;
    Data_Get_Struct (self, DistanceAccessor, p);
    float far;
    __TRY__;
    far = p->fog->getFarDistance ();
    __CATCH__;
    return rb_float_new(far);
}



void register_Fog ()
{
    // Fog
    rb_cFog                 = rb_define_class_under (rb_mM3G, "Fog",                 rb_cObject3D);

	rb_define_const (rb_cFog, "EXPONENTIAL", INT2NUM(Fog::EXPONENTIAL));
	rb_define_const (rb_cFog, "LINEAR",      INT2NUM(Fog::LINEAR));

    rb_define_alloc_func (rb_cFog, ruby_Fog_allocate);
    rb_define_private_method (rb_cFog, "initialize", (VALUE(*)(...))ruby_Fog_initialize, 0);

    rb_define_method (rb_cFog, "color",       (VALUE(*)(...))ruby_Fog_get_color,   0);
    rb_define_method (rb_cFog, "density",     (VALUE(*)(...))ruby_Fog_get_density, 0);
    rb_define_method (rb_cFog, "distance",    (VALUE(*)(...))ruby_Fog_get_distance,0);
    rb_define_method (rb_cFog, "mode",        (VALUE(*)(...))ruby_Fog_get_mode,    0);
    rb_define_method (rb_cFog, "color=",      (VALUE(*)(...))ruby_Fog_set_color,   1);
    rb_define_method (rb_cFog, "density=",    (VALUE(*)(...))ruby_Fog_set_density, 1);
    rb_define_method (rb_cFog, "linear=",     (VALUE(*)(...))ruby_Fog_set_linear,  1);
    rb_define_method (rb_cFog, "mode=",       (VALUE(*)(...))ruby_Fog_set_mode,    1);

    // DistanceAccessor
    rb_cFog_DistanceAccessor  = rb_define_class_under (rb_cFog, "DistanceAccessor", rb_cObject);

    rb_define_method (rb_cFog_DistanceAccessor, "near",       (VALUE(*)(...))ruby_Fog_DistanceAccessor_get_near,   0);
    rb_define_method (rb_cFog_DistanceAccessor, "far",        (VALUE(*)(...))ruby_Fog_DistanceAccessor_get_far,    0);

}
