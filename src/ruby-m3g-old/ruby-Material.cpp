#include <new>
#include "ruby.h"
#include "Material.hpp"
using namespace m3g;

VALUE ruby_Material_free (Material* ptr)
{
    ptr->~Material ();
    ruby_xfree (ptr);
}

VALUE ruby_Material_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Material));
    return Data_Wrap_Struct (self, NULL, ruby_Material_free, p);
}

VALUE ruby_Material_initialize (VALUE self)
{
    Material* p;
    Data_Get_Struct (self, Material, p);
    new (p) Material;
    return Qnil;
}

VALUE ruby_Material_get_color (VALUE self, VALUE val_target)
{
    return Qnil;
}

VALUE ruby_Material_get_shininess (VALUE self)
{
    return Qnil;
}

VALUE ruby_Material_is_vertex_color_tracking_enabled (VALUE self)
{
    return Qnil;
}

VALUE ruby_Material_set_color (VALUE self, VALUE val_target_and_argb)
{
    return Qnil;
}

VALUE ruby_Material_set_shininess (VALUE self, VALUE val_shininess)
{
    return Qnil;
}

VALUE ruby_Material_set_vertex_color_tracking_enable (VALUE self, VALUE val_enable)
{
    return Qnil;
}

void register_Material (VALUE rb_cMaterial)
{
     // Material
     rb_define_const (rb_cMaterial, "AMBIENT",  INT2FIX(Material::AMBIENT));
     rb_define_const (rb_cMaterial, "DIFFUSE",  INT2FIX(Material::DIFFUSE));
     rb_define_const (rb_cMaterial, "EMISSIVE", INT2FIX(Material::EMISSIVE));
     rb_define_const (rb_cMaterial, "SPECULAR", INT2FIX(Material::SPECULAR));

     rb_define_alloc_func (rb_cMaterial, ruby_Material_allocate);
     rb_define_private_method (rb_cMaterial, "initialize", (VALUE(*)(...))ruby_Material_initialize,0);

     rb_define_method (rb_cMaterial, "color",                          (VALUE(*)(...))ruby_Material_get_color, 1);
     rb_define_method (rb_cMaterial, "shininess",                      (VALUE(*)(...))ruby_Material_get_shininess, 0);
     rb_define_method (rb_cMaterial, "vertex_color_tracking_enabled?", (VALUE(*)(...))ruby_Material_is_vertex_color_tracking_enabled, 0);
     rb_define_method (rb_cMaterial, "color=",                         (VALUE(*)(...))ruby_Material_set_color, 1);
     rb_define_method (rb_cMaterial, "shininess=",                     (VALUE(*)(...))ruby_Material_set_shininess, 1);
     rb_define_method (rb_cMaterial, "vertex_color_tracking_enable=",  (VALUE(*)(...))ruby_Material_set_vertex_color_tracking_enable, 1);


}
