#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

VALUE ruby_Transform_free (Transform* ptr)
{
    __TRY__;
    ptr->~Transform ();
    __CATCH__;
    ruby_xfree (ptr);
}

VALUE ruby_Transform_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Transform));
    return Data_Wrap_Struct (self, 0, ruby_Transform_free, p);
}

VALUE ruby_Transform_initialize (int argc, VALUE* argv, VALUE self)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    VALUE val_arg1;

    int num = rb_scan_args (argc, argv, "01", &val_arg1);
    switch (num) {
    case 0: {
        __TRY__;
        new (p) Transform();
        __CATCH__;
        break;
    }
    case 1: {
        Transform* trans;
        Data_Get_Struct (val_arg1, Transform, trans);
        __TRY__;
        new (p) Transform(*trans);
        __CATCH__;
        break;
    }
    default: {
        rb_raise (rb_eIllegalArgumentException, "Argument num is invalid. num=%d.", num);
    }
    }

    return self;
}

VALUE ruby_Transform_get_matrix (VALUE self)
{
    Transform* p;
    float matrix[16];
    Data_Get_Struct (self, Transform, p);
    __TRY__;
    p->get (matrix);
    __CATCH__;

    VALUE val_matrix = rb_ary_new2 (16);
    for (int i = 0; i < 16; i++) {
        rb_ary_push (val_matrix, rb_float_new(matrix[i]));
    }
    return val_matrix;
}

VALUE ruby_Transform_invert (VALUE self)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    __TRY__;
    p->invert ();
    __CATCH__;

    return Qnil;
}

VALUE ruby_Transform_post_multiply (VALUE self, VALUE val_transform)
{
    Transform* p;
    Transform* trans;

    Data_Get_Struct (self, Transform, p);
    Data_Get_Struct (val_transform, Transform, trans);
    __TRY__;
    p->postMultiply (*trans);
    __CATCH__;

    return Qnil;
}

VALUE ruby_Transform_post_rotate (VALUE self, VALUE val_angle, VALUE val_ax, VALUE val_ay, VALUE val_az)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    float angle = NUM2DBL (val_angle);
    float ax    = NUM2DBL (val_ax);
    float ay    = NUM2DBL (val_ay);
    float az    = NUM2DBL (val_az);
    __TRY__;
    p->postRotate (angle, ax, ay, az);
    __CATCH__;

    return Qnil;
}

VALUE ruby_Transform_post_rotate_quat (VALUE self, VALUE val_qx, VALUE val_qy, VALUE val_qz, VALUE val_qw)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    float qx = NUM2DBL (val_qx);
    float qy = NUM2DBL (val_qy);
    float qz = NUM2DBL (val_qz);
    float qw = NUM2DBL (val_qw);
    __TRY__;
    p->postRotateQuat (qx, qy, qz, qw);
    __CATCH__;

    return Qnil;
}

VALUE ruby_Transform_post_scale (VALUE self, VALUE val_sx, VALUE val_sy, VALUE val_sz)
{
    Transform* p;
    float sx, sy, sz;

    Data_Get_Struct (self, Transform, p);
    sx = NUM2DBL (val_sx);
    sy = NUM2DBL (val_sy);
    sz = NUM2DBL (val_sz);
    __TRY__;
    p->postScale (sx, sy, sz);
    __CATCH__;

    return Qnil;
}

VALUE ruby_Transform_post_translate (VALUE self, VALUE val_tx, VALUE val_ty, VALUE val_tz)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    float tx = NUM2DBL (val_tx);
    float ty = NUM2DBL (val_ty);
    float tz = NUM2DBL (val_tz);
    __TRY__;
    p->postTranslate (tx, ty, tz);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Transform_set_matrix (VALUE self, VALUE val_matrix)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    float m[16];
    for (int i = 0; i < 16; i++) {
        m[i] = NUM2DBL(rb_ary_entry (val_matrix, i));
    }
    __TRY__;
    p->set (m);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Transform_set_transform (VALUE self, VALUE val_transform)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    Transform *transform;
    Data_Get_Struct (val_transform, Transform, transform);
    __TRY__;
    p->set (*transform);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Transform_set_identity (VALUE self)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    __TRY__;
    p->setIdentity ();
    __CATCH__;
    return Qnil;
}

VALUE ruby_Transform_transform (int argc, VALUE* argv, VALUE self)
{

    Transform* p;
    Data_Get_Struct (self, Transform, p);

    VALUE val_arg1, val_arg2, val_arg3;
    int num = rb_scan_args (argc, argv, "12", &val_arg1, &val_arg2, &val_arg3);

    switch (num) {
    case 1: {
        float vectors[4];
        for (int i = 0; i < 4; i++) {
            vectors[i] = NUM2DBL (rb_ary_entry(val_arg1, i));
        }
        __TRY__;
        p->transform (vectors);
        __CATCH__;
        for (int i = 0; i < 4; i++) {
            rb_ary_store(val_arg1, i, rb_float_new(vectors[i]));
        }
        break;
    }
    case 3: {
        VertexArray* in;
        Data_Get_Struct (val_arg1, VertexArray, in);
        int    num = RARRAY_LEN(val_arg1);
        float* out = (float*)ruby_xmalloc (sizeof(float)*num);
        bool   w   = (val_arg3 == Qtrue) ? true : false;

        __TRY__;
        p->transform (in, out, w);
        __CATCH__;
        ruby_xfree (out);
        break;
    }
    default: {
        // エラー
    }
    }

    return Qnil;
}

VALUE ruby_Transform_transpose (VALUE self)
{
    Transform* p;
    Data_Get_Struct (self, Transform, p);
    __TRY__;
    p->transpose ();
    __CATCH__;
    return Qnil;
}


void register_Transform ()
{
    // Transform
    rb_cTransform           = rb_define_class_under (rb_mM3G, "Transform",           rb_cObject);

    rb_define_alloc_func (rb_cTransform, ruby_Transform_allocate);
    rb_define_private_method (rb_cTransform, "initialize", (VALUE(*)(...))ruby_Transform_initialize, -1);

    rb_define_method (rb_cTransform, "matrix",           (VALUE(*)(...))ruby_Transform_get_matrix,      0);
    rb_define_method (rb_cTransform, "invert",           (VALUE(*)(...))ruby_Transform_invert,          0);
    rb_define_method (rb_cTransform, "post_multiply",    (VALUE(*)(...))ruby_Transform_post_multiply,   1);
    rb_define_method (rb_cTransform, "post_rotate",      (VALUE(*)(...))ruby_Transform_post_rotate,     4);
    rb_define_method (rb_cTransform, "post_rotate_quat", (VALUE(*)(...))ruby_Transform_post_rotate_quat,4);
    rb_define_method (rb_cTransform, "post_scale",       (VALUE(*)(...))ruby_Transform_post_scale,      3);
    rb_define_method (rb_cTransform, "post_translate",   (VALUE(*)(...))ruby_Transform_post_translate,  3);
    rb_define_method (rb_cTransform, "identity",         (VALUE(*)(...))ruby_Transform_set_identity,    0);
    rb_define_method (rb_cTransform, "transform",        (VALUE(*)(...))ruby_Transform_transform,      -1);
    rb_define_method (rb_cTransform, "transpose",        (VALUE(*)(...))ruby_Transform_transpose,       0);
    rb_define_method (rb_cTransform, "matrix=",          (VALUE(*)(...))ruby_Transform_set_matrix,      1);
    rb_define_method (rb_cTransform, "transform=",       (VALUE(*)(...))ruby_Transform_set_transform,   1);
}
