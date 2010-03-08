#include <new>
#include "ruby.h"
#include "Transform.hpp"
using namespace m3g;

VALUE ruby_Transform_free (Transform* ptr)
{
    ptr->~Transform ();
    ruby_xfree (ptr);
}

VALUE ruby_Transform_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Transform));
    return Data_Wrap_Struct (self, NULL, ruby_Transform_free, p);
}

VALUE ruby_Transform_initialize (int argc, VALUE* argv, VALUE self)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    new (p) Transform;
    return Qnil;
}

VALUE ruby_Transform_get (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transform_invert (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transform_post_multiply (VALUE self, VALUE val_transform)
{
    return Qnil;
}

VALUE ruby_Transform_post_rotate (VALUE self, VALUE val_angle, VALUE val_ax, VALUE val_ay, VALUE val_az)
{
    return Qnil;
}

VALUE ruby_Transform_post_rotate_quat (VALUE self, VALUE val_qx, VALUE val_qy, VALUE val_qz, VALUE val_qw)
{
    return Qnil;
}

VALUE ruby_Transform_post_scale (VALUE self, VALUE val_sx, VALUE val_sy, VALUE val_sz)
{
    return Qnil;
}

VALUE ruby_Transform_post_translate (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transform_set (VALUE self, VALUE val_matrix_or_transform)
{
    return Qnil;
}

VALUE ruby_Transform_set_identity (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transform_transform (int argc, VALUE* argv, VALUE self)
{
    return Qnil;
}

VALUE ruby_Transform_transpose (VALUE self)
{
    return Qnil;
}


void register_Transform (VALUE rb_cTransform)
{
     // Transform
     rb_define_alloc_func (rb_cTransform, ruby_Transform_allocate);
     rb_define_private_method (rb_cTransform, "initialize", (VALUE(*)(...))ruby_Transform_initialize, -1);

     rb_define_method (rb_cTransform, "get",           (VALUE(*)(...))ruby_Transform_get,  0);
     rb_define_method (rb_cTransform, "invert",           (VALUE(*)(...))ruby_Transform_invert,        0);
     rb_define_method (rb_cTransform, "post_multiply",    (VALUE(*)(...))ruby_Transform_post_multiply,  1);
     rb_define_method (rb_cTransform, "post_rotate",      (VALUE(*)(...))ruby_Transform_post_rotate,    4);
     rb_define_method (rb_cTransform, "post_rotate_quat", (VALUE(*)(...))ruby_Transform_post_rotate_quat,4);
     rb_define_method (rb_cTransform, "post_scale",       (VALUE(*)(...))ruby_Transform_post_scale,     3);
     rb_define_method (rb_cTransform, "post_translate",   (VALUE(*)(...))ruby_Transform_post_translate, 3);
     rb_define_method (rb_cTransform, "set",              (VALUE(*)(...))ruby_Transform_set,           1);
     rb_define_method (rb_cTransform, "identity",         (VALUE(*)(...))ruby_Transform_set_identity,   0);
     rb_define_method (rb_cTransform, "transform",        (VALUE(*)(...))ruby_Transform_transform,     1);
     rb_define_method (rb_cTransform, "transpose",        (VALUE(*)(...))ruby_Transform_transpose,     0);
}
