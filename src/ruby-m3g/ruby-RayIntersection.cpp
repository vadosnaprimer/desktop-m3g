#include <new>
#include "ruby.h"
#include "RayIntersection.hpp"
using namespace m3g;

VALUE ruby_RayIntersection_free (RayIntersection* ptr)
{
    ptr->~RayIntersection ();
    ruby_xfree (ptr);
}

VALUE ruby_RayIntersection_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(RayIntersection));
    return Data_Wrap_Struct (self, NULL, ruby_RayIntersection_free, p);
}

VALUE ruby_RayIntersection_initialize (VALUE self)
{
    RayIntersection* p;
    Data_Get_Struct (self, RayIntersection, p);
    new (p) RayIntersection;
    return Qnil;
}

VALUE ruby_RayIntersection_get_distance (VALUE self)
{
    return Qnil;
}

VALUE ruby_RayIntersection_get_intersected (VALUE self)
{
    return Qnil;
}

VALUE ruby_RayIntersection_get_normal (VALUE self)
{
    return Qnil;
}

VALUE ruby_RayIntersection_get_ray (VALUE self, VALUE val_ray)
{
    return Qnil;
}

VALUE ruby_RayIntersection_get_submesh_index (VALUE self)
{
    return Qnil;
}

VALUE ruby_RayIntersection_get_texture (VALUE self, VALUE val_index)
{
    return Qnil;
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
     rb_define_method (rb_cRayIntersection, "texture",       (VALUE(*)(...))ruby_RayIntersection_get_texture,  1);

}
