#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  VALUE rb_cFog_Distance;
}

VALUE ruby_Fog_free (Fog* ptr)
{
    ptr->~Fog ();
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
    new (p) Fog;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Fog_get_color (VALUE self)
{
 Fog* p;
 int color;

 Data_Get_Struct (self, Fog, p);

 color = p->getColor ();

 return INT2FIX (color);
}

VALUE ruby_Fog_get_density (VALUE self)
{
  Fog* p;
  float density;

  Data_Get_Struct (self, Fog, p);
  density = p->getDensity ();

  return rb_float_new(density);
}

VALUE ruby_Fog_get_distance (VALUE self)
{
  Fog* p;
  Data_Get_Struct (self, Fog, p);
  Fog::Distance* dist;
  VALUE val_dist = Data_Make_Struct (rb_cFog_Distance, Fog::Distance, 0, -1, dist);
  dist->near = p->getNearDistance();
  dist->far  = p->getFarDistance();
  return val_dist;
}

VALUE ruby_Fog_get_mode (VALUE self)
{
  Fog* p;
  int mode;
  
  Data_Get_Struct (self, Fog, p);
  mode = p->getMode ();

  return INT2FIX(mode);
}

VALUE ruby_Fog_set_color (VALUE self, VALUE val_rgb)
{
  Fog* p;
  int rgb;

  Data_Get_Struct (self, Fog, p);
  rgb = FIX2INT (val_rgb);

  p->setColor (rgb);

  return Qnil;
}

VALUE ruby_Fog_set_density (VALUE self, VALUE val_density)
{
  Fog* p;
  float density;

  Data_Get_Struct (self, Fog, p);
  density = RFLOAT_VALUE (val_density);

  p->setDensity (density);

  return Qnil;
}

VALUE ruby_Fog_set_linear (VALUE self, VALUE val_linear)
{
  VALUE val_near = rb_ary_entry (val_linear, 0);
  VALUE val_far  = rb_ary_entry (val_linear, 1);
  Fog* p;
  Data_Get_Struct (self, Fog, p);
  float near = RFLOAT_VALUE (val_near);
  float far  = RFLOAT_VALUE (val_far);

  p->setLinear (near, far);

  return Qnil;
}

VALUE ruby_Fog_set_mode (VALUE self, VALUE val_mode)
{
  Fog* p;
  int mode;

  Data_Get_Struct (self, Fog, p);
  mode = FIX2INT (val_mode);

  p->setMode (mode);

  return Qnil;
}


/**
 * Fog::Distance
 */

VALUE ruby_Fog_Distance_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(Fog::Distance));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Fog_Distance_initialize (VALUE self, VALUE val_near, VALUE val_far)
{
  Fog::Distance* p;
    Data_Get_Struct (self, Fog::Distance, p);
    p->near = RFLOAT_VALUE (val_near);
    p->far  = RFLOAT_VALUE (val_far);
    return self;
}

VALUE ruby_Fog_Distance_get_near (VALUE self)
{
  Fog::Distance* p;
  Data_Get_Struct (self, Fog::Distance, p);
  return rb_float_new(p->near);
}

VALUE ruby_Fog_Distance_get_far (VALUE self)
{
  Fog::Distance* p;
  Data_Get_Struct (self, Fog::Distance, p);
  return rb_float_new(p->far);
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

     // Fog::Distance
     rb_cFog_Distance  = rb_define_class_under (rb_cFog, "Distance", rb_cObject);

     rb_define_alloc_func (rb_cFog_Distance, ruby_Fog_Distance_allocate);
     rb_define_private_method (rb_cFog_Distance, "initialize", (VALUE(*)(...))ruby_Fog_Distance_initialize, 0);

     rb_define_method (rb_cFog_Distance, "near",        (VALUE(*)(...))ruby_Fog_Distance_get_near,   0);
     rb_define_method (rb_cFog_Distance, "far",        (VALUE(*)(...))ruby_Fog_Distance_get_far,    0);

}
