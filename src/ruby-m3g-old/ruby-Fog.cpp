#include <new>
#include "ruby.h"
#include "Fog.hpp"
using namespace m3g;

VALUE ruby_Fog_free (Fog* ptr)
{
    ptr->~Fog ();
    ruby_xfree (ptr);
}

VALUE ruby_Fog_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Fog));
    return Data_Wrap_Struct (self, NULL, ruby_Fog_free, p);
}

VALUE ruby_Fog_initialize (VALUE self)
{
    Fog* p;
    Data_Get_Struct (self, Fog, p);
    new (p) Fog;
    return Qnil;
}

VALUE ruby_Fog_get_color (VALUE self)
{
    return Qnil;
}

VALUE ruby_Fog_get_density (VALUE self)
{
    return Qnil;
}

VALUE ruby_Fog_get_distance (VALUE self)
{
    return Qnil;
}

VALUE ruby_Fog_get_mode (VALUE self)
{
    return Qnil;
}

VALUE ruby_Fog_set_color (VALUE self, VALUE val_rgb)
{
    return Qnil;
}

VALUE ruby_Fog_set_density (VALUE self, VALUE val_density)
{
    return Qnil;
}

VALUE ruby_Fog_set_linear (VALUE self, VALUE val_near_and_far)
{
    return Qnil;
}

VALUE ruby_Fog_set_mode (VALUE self, VALUE val_mode)
{
    return Qnil;
}


void register_Fog (VALUE rb_cFog)
{
     // Fog
     rb_define_const (rb_cFog, "EXPONENTIAL", INT2FIX(Fog::EXPONENTIAL));
     rb_define_const (rb_cFog, "LINEAR",      INT2FIX(Fog::LINEAR));

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
}
