#include <new>
#include "ruby.h"
#include "Camera.hpp"
using namespace m3g;

VALUE ruby_Projection_free (Projection* ptr)
{
    ptr->~Projection ();
    ruby_xfree (ptr);
}

VALUE ruby_Projection_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Projection));
    return Data_Wrap_Struct (self, NULL, ruby_Projection_free, p);
}

VALUE ruby_Projection_initialize (VALUE self)
{
    Projection* p;
    Data_Get_Struct (self, Projection, p);
    new (p) Projection;
    return Qnil;
}

VALUE ruby_Projection_get_type (VALUE self)
{
    return Qnil;
}

VALUE ruby_Projection_get_params (VALUE self)
{
    return Qnil;
}

VALUE ruby_Projection_get_transform (VALUE self)
{
    return Qnil;
}

void register_Projection (VALUE rb_cProjection)
{
     // Projection
     rb_define_alloc_func (rb_cProjection, ruby_Projection_allocate);
     rb_define_private_method (rb_cProjection, "initialize", (VALUE(*)(...))ruby_Projection_initialize, 0);

     rb_define_method (rb_cProjection, "type",      (VALUE(*)(...))ruby_Projection_get_type, 0); 
     rb_define_method (rb_cProjection, "params",    (VALUE(*)(...))ruby_Projection_get_params, 0); 
     rb_define_method (rb_cProjection, "transform", (VALUE(*)(...))ruby_Projection_get_transform, 0); 

}

