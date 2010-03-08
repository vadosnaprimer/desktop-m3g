#include <new>
#include "ruby.h"
#include "Camera.hpp"
using namespace m3g;


VALUE ruby_Camera_free (Camera* ptr)
{
    ptr->~Camera ();
    ruby_xfree (ptr);
}

VALUE ruby_Camera_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Camera));
    return Data_Wrap_Struct (self, NULL, ruby_Camera_free, p);
}

VALUE ruby_Camera_initialize (VALUE self)
{
    Camera* p;
    Data_Get_Struct (self, Camera, p);
    new (p) Camera;
    return Qnil;
}

VALUE ruby_Camera_get_projection (int argc, VALUE* argv, VALUE self)
{
    return Qnil;
}

VALUE ruby_Camera_set_generic (VALUE self, VALUE val_transform)
{
    return Qnil;
}

VALUE ruby_Camera_set_parallel (VALUE self, VALUE val_fovy, VALUE val_aspect_ratio, VALUE val_near, VALUE val_far)
{
    return Qnil;
}

VALUE ruby_Camera_set_perspective (VALUE self, VALUE val_fovy_and_aspect_ratio_and_near_and_far)
{
    return Qnil;
}

void register_Camera (VALUE rb_cCamera)
{
     // Camera
     rb_define_const (rb_cCamera, "GENERIC",     INT2FIX(Camera::GENERIC));
     rb_define_const (rb_cCamera, "PARALLEL",    INT2FIX(Camera::PARALLEL));
     rb_define_const (rb_cCamera, "PERSPECTIVE", INT2FIX(Camera::PERSPECTIVE));

     rb_define_alloc_func (rb_cCamera, ruby_Camera_allocate);
     rb_define_private_method (rb_cCamera, "initialize", (VALUE(*)(...))ruby_Camera_initialize, 0);

     rb_define_method (rb_cCamera, "projection",  (VALUE(*)(...))ruby_Camera_get_projection, 0);
     rb_define_method (rb_cCamera, "generic=",     (VALUE(*)(...))ruby_Camera_set_generic,     1);
     rb_define_method (rb_cCamera, "parallel=",    (VALUE(*)(...))ruby_Camera_set_parallel,    1);
     rb_define_method (rb_cCamera, "perspective=", (VALUE(*)(...))ruby_Camera_set_perspective, 1);

}
