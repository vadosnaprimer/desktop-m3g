#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  struct TextureAccessor
  {
    RayIntersection* ray_intersection;
  };
  VALUE rb_cRayIntersection_TextureAccessor;
}

VALUE ruby_RayIntersection_free (RayIntersection* ptr)
{
    ptr->~RayIntersection ();
    ruby_xfree (ptr);
}

VALUE ruby_RayIntersection_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(RayIntersection));
    return Data_Wrap_Struct (self, 0, ruby_RayIntersection_free, p);
}

VALUE ruby_RayIntersection_initialize (VALUE self)
{
    RayIntersection* p;
    Data_Get_Struct (self, RayIntersection, p);
    new (p) RayIntersection;
    p->setExportedEntity((void*)self);
    return self;
}

VALUE ruby_RayIntersection_get_distance (VALUE self)
{
    RayIntersection* p;
    float distance;

    Data_Get_Struct (self, RayIntersection, p);
    distance = p->getDistance ();

    return rb_float_new(distance);
}

VALUE ruby_RayIntersection_get_intersected (VALUE self)
{
    RayIntersection* p;
    Node* node;

    Data_Get_Struct (self, RayIntersection, p);
    node = p->getIntersected ();

    return node ? (VALUE)node->getExportedEntity() : Qnil;
}

VALUE ruby_RayIntersection_get_normal (VALUE self)
{
  float x,y,z;
  RayIntersection* p;

  Data_Get_Struct (self, RayIntersection, p);
  x = p->getNormalX ();
  y = p->getNormalY ();
  z = p->getNormalZ ();

  VALUE val_ret = rb_ary_new ();
  rb_ary_push (val_ret, rb_float_new(x));
  rb_ary_push (val_ret, rb_float_new(y));
  rb_ary_push (val_ret, rb_float_new(z));

    return val_ret;
}

VALUE ruby_RayIntersection_get_ray (VALUE self, VALUE val_ray)
{
    RayIntersection* p;
    Data_Get_Struct (self, RayIntersection, p);

    float ray[6];
    p->getRay (ray);

    VALUE val_pos = rb_ary_new ();
    VALUE val_dir = rb_ary_new ();
    VALUE val_ret = rb_ary_new ();

    rb_ary_push (val_pos, rb_float_new(ray[0]));
    rb_ary_push (val_pos, rb_float_new(ray[1]));
    rb_ary_push (val_pos, rb_float_new(ray[2]));
    rb_ary_push (val_dir, rb_float_new(ray[3]));
    rb_ary_push (val_dir, rb_float_new(ray[4]));
    rb_ary_push (val_dir, rb_float_new(ray[5]));
    rb_ary_push (val_ret, val_pos);
    rb_ary_push (val_ret, val_dir);

    return Qnil;
}

VALUE ruby_RayIntersection_get_submesh_index (VALUE self)
{
    RayIntersection* p;
    Data_Get_Struct (self, RayIntersection, p);
    int index;

    index = p->getSubmeshIndex();
    
    return INT2FIX(index);
}

VALUE ruby_RayIntersection_get_texture (VALUE self)
{
    RayIntersection* p;
    TextureAccessor* accessor;
    VALUE val_accessor;

    Data_Get_Struct (self, RayIntersection, p);
    val_accessor = Data_Make_Struct (rb_cRayIntersection_TextureAccessor, TextureAccessor, 0, -1, accessor);
    
    accessor->ray_intersection = p;
    
    return val_accessor;
}


VALUE ruby_RayIntersection_TextureAccessor_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(TextureAccessor));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_RayIntersection_TextureAccessor_initialize (VALUE self)
{
    TextureAccessor* p;
    Data_Get_Struct (self, TextureAccessor, p);
    return self;
}



VALUE ruby_RayIntersection_TextureAccessor_get_tex_coord (VALUE self, VALUE val_index)
{
    TextureAccessor* p;
    int index;
    float s, t;


    Data_Get_Struct (self, TextureAccessor, p);
    index = FIX2INT (val_index);

    s = p->ray_intersection->getTextureS (index);
    t = p->ray_intersection->getTextureT (index);

    VALUE val_ret = rb_ary_new ();
    rb_ary_push (val_ret, rb_float_new(s));
    rb_ary_push (val_ret, rb_float_new(t));

    return val_ret;
}

void register_RayIntersection (VALUE rb_cRayIntersection)
{

     // RayIntersection
     rb_define_alloc_func (rb_cRayIntersection, ruby_RayIntersection_allocate);
     rb_define_private_method (rb_cRayIntersection, "initialize", (VALUE(*)(...))ruby_RayIntersection_initialize,  0);

     rb_define_method (rb_cRayIntersection, "distance",      (VALUE(*)(...))ruby_RayIntersection_get_distance, 0);
     rb_define_method (rb_cRayIntersection, "intersected",   (VALUE(*)(...))ruby_RayIntersection_get_intersected, 0);
     rb_define_method (rb_cRayIntersection, "normal",        (VALUE(*)(...))ruby_RayIntersection_get_normal,   0);
     rb_define_method (rb_cRayIntersection, "ray",           (VALUE(*)(...))ruby_RayIntersection_get_ray,      0);
     rb_define_method (rb_cRayIntersection, "submesh_index", (VALUE(*)(...))ruby_RayIntersection_get_submesh_index, 0);
     rb_define_method (rb_cRayIntersection, "texture",       (VALUE(*)(...))ruby_RayIntersection_get_texture,  0);

     // RayIntersection_TextureAccessor
     rb_cRayIntersection_TextureAccessor  = rb_define_class_under (rb_cRayIntersection, "TextureAccessor", rb_cObject);

     rb_define_alloc_func     (rb_cRayIntersection_TextureAccessor, ruby_RayIntersection_TextureAccessor_allocate);
     rb_define_private_method (rb_cRayIntersection_TextureAccessor, "initialize", (VALUE(*)(...))ruby_RayIntersection_TextureAccessor_initialize, 0);

     rb_define_method (rb_cRayIntersection_TextureAccessor, "[]",        (VALUE(*)(...))ruby_RayIntersection_TextureAccessor_get_tex_coord,    1);

}
