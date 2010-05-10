#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  struct ColorAccessor{
    Material* material;
  };
  VALUE rb_cMaterial_ColorAccessor;
}

VALUE ruby_Material_free (Material* ptr)
{
    ptr->~Material ();
    ruby_xfree (ptr);
}

VALUE ruby_Material_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Material));
    return Data_Wrap_Struct (self, 0, ruby_Material_free, p);
}

VALUE ruby_Material_initialize (VALUE self)
{
    Material* p;
    Data_Get_Struct (self, Material, p);
    new (p) Material;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Material_get_color (VALUE self)
{
    Material* p;
    Data_Get_Struct (self, Material, p);

    ColorAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cMaterial_ColorAccessor, ColorAccessor, 0, -1, accessor);
    accessor->material = p;

    return val_accessor;
}

VALUE ruby_Material_get_shininess (VALUE self)
{
  Material* p;
  float shininess;

  Data_Get_Struct (self, Material, p);
  shininess = p->getShininess ();

  return rb_float_new (shininess);
}

VALUE ruby_Material_is_vertex_color_tracking_enabled (VALUE self)
{
  Material* p;
  bool enabled;

  Data_Get_Struct (self, Material, p);
  enabled = p->isVertexColorTrackingEnabled ();

  if (enabled)
    return Qtrue;
  else
    return Qfalse;
}

VALUE ruby_Material_set_shininess (VALUE self, VALUE val_shininess)
{
  Material* p;
  float shininess;

  Data_Get_Struct (self, Material, p);
  shininess = NUMERIC2FLOAT (val_shininess);

  p->setShininess (shininess);

  return Qnil;
}

VALUE ruby_Material_set_vertex_color_tracking_enable (VALUE self, VALUE val_enable)
{
  Material* p;
  bool enable;

  Data_Get_Struct (self, Material, p);

  enable = (val_enable == Qtrue) ? Qtrue : Qfalse;
  p->setVertexColorTrackingEnable (enable);

  return Qnil;
}


/**
 * Material_ColorAccessor
 */

VALUE ruby_Material_ColorAccessor_get_color (VALUE self, VALUE val_target)
{
  ColorAccessor* p;
  Data_Get_Struct (self, ColorAccessor, p);
  int       target = FIX2INT(val_target);
  int       argb;

  argb = p->material->getColor (target);

  return INT2FIX(argb);
}

VALUE ruby_Material_ColorAccessor_set_color (VALUE self, VALUE val_target, VALUE val_color)
{
  ColorAccessor* p;
  Data_Get_Struct (self, ColorAccessor, p);
  int target = FIX2INT(val_target);
  int color  = FIX2INT(val_color);

  p->material->setColor (target, color);

  return Qnil;
}

void register_Material ()
{
     // Material
    rb_cMaterial            = rb_define_class_under (rb_mM3G, "Material",            rb_cObject3D);

     rb_define_const (rb_cMaterial, "AMBIENT",  INT2FIX(Material::AMBIENT));
     rb_define_const (rb_cMaterial, "DIFFUSE",  INT2FIX(Material::DIFFUSE));
     rb_define_const (rb_cMaterial, "EMISSIVE", INT2FIX(Material::EMISSIVE));
     rb_define_const (rb_cMaterial, "SPECULAR", INT2FIX(Material::SPECULAR));

     rb_define_alloc_func (rb_cMaterial, ruby_Material_allocate);
     rb_define_private_method (rb_cMaterial, "initialize", (VALUE(*)(...))ruby_Material_initialize,0);

     rb_define_method (rb_cMaterial, "color",                          (VALUE(*)(...))ruby_Material_get_color, 0);
     rb_define_method (rb_cMaterial, "shininess",                      (VALUE(*)(...))ruby_Material_get_shininess, 0);
     rb_define_method (rb_cMaterial, "vertex_color_tracking_enabled?", (VALUE(*)(...))ruby_Material_is_vertex_color_tracking_enabled, 0);
     rb_define_method (rb_cMaterial, "shininess=",                     (VALUE(*)(...))ruby_Material_set_shininess, 1);
     rb_define_method (rb_cMaterial, "vertex_color_tracking_enable=",  (VALUE(*)(...))ruby_Material_set_vertex_color_tracking_enable, 1);

     // Material_ColorAccessor
     rb_cMaterial_ColorAccessor  = rb_define_class_under (rb_cMaterial, "ColorAccessor", rb_cObject);

     rb_define_method (rb_cMaterial_ColorAccessor, "[]",     (VALUE(*)(...))ruby_Material_ColorAccessor_get_color, 1); 
     rb_define_method (rb_cMaterial_ColorAccessor, "[]=",     (VALUE(*)(...))ruby_Material_ColorAccessor_set_color, 2); 

}
