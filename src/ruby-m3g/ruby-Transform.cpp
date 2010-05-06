#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

VALUE ruby_Transform_free (Transform* ptr)
{
    ptr->~Transform ();
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
      new (p) Transform();
      break;
    }
    case 1: {
      Transform* trans;
      Data_Get_Struct (val_arg1, Transform, trans);
      new (p) Transform(*trans);
    }
    default: {
      // エラー
    }
    }

    return self;
}

VALUE ruby_Transform_get (VALUE self)
{
  Transform* p;
  float matrix[16];
  Data_Get_Struct (self, Transform, p);

  p->get (matrix);

  VALUE val_matrix = rb_ary_new ();
  for (int i = 0; i < 16; i++) {
    rb_ary_push (val_matrix, rb_float_new(matrix[i]));
  }
  return val_matrix;
}

VALUE ruby_Transform_invert (VALUE self)
{
  Transform* p;
  Data_Get_Struct (self, Transform, p);

  p->invert ();

  return Qnil;
}

VALUE ruby_Transform_post_multiply (VALUE self, VALUE val_transform)
{
  Transform* p;
  Transform* trans;

  Data_Get_Struct (self, Transform, p);
  Data_Get_Struct (val_transform, Transform, trans);

  p->postMultiply (*trans);

  return Qnil;
}

VALUE ruby_Transform_post_rotate (VALUE self, VALUE val_angle, VALUE val_ax, VALUE val_ay, VALUE val_az)
{
  Transform* p;
  float angle, ax, ay, az;

  Data_Get_Struct (self, Transform, p);
  angle = RFLOAT_VALUE (val_angle);
  ax  = RFLOAT_VALUE (val_ax);
  ay  = RFLOAT_VALUE (val_ay);
  az  = RFLOAT_VALUE (val_az);

  p->postRotate (angle, ax, ay, az);

  return Qnil;
}

VALUE ruby_Transform_post_rotate_quat (VALUE self, VALUE val_qx, VALUE val_qy, VALUE val_qz, VALUE val_qw)
{
  Transform* p;
  float qx, qy, qz, qw;

  Data_Get_Struct (self, Transform, p);
  qx = RFLOAT_VALUE (val_qx);
  qy = RFLOAT_VALUE (val_qy);
  qz = RFLOAT_VALUE (val_qz);
  qw = RFLOAT_VALUE (val_qw);

  p->postRotateQuat (qx, qy, qz, qw);

  return Qnil;
}

VALUE ruby_Transform_post_scale (VALUE self, VALUE val_sx, VALUE val_sy, VALUE val_sz)
{
  Transform* p;
  float sx, sy, sz;

  Data_Get_Struct (self, Transform, p);
  sx = RFLOAT_VALUE (val_sx);
  sy = RFLOAT_VALUE (val_sy);
  sz = RFLOAT_VALUE (val_sz);

  p->postScale (sx, sy, sz);

  return Qnil;
}

VALUE ruby_Transform_post_translate (VALUE self, VALUE val_args)
{
  VALUE val_tx = rb_ary_entry(val_args, 0);
  VALUE val_ty = rb_ary_entry(val_args, 1);
  VALUE val_tz = rb_ary_entry(val_args, 2);
  Transform* p;
  Data_Get_Struct (self, Transform, p);
  float tx = RFLOAT_VALUE (val_tx);
  float ty = RFLOAT_VALUE (val_ty);
  float tz = RFLOAT_VALUE (val_tz);

  p->postTranslate (tx, ty, tz);

  return Qnil;
}

VALUE ruby_Transform_set (VALUE self, VALUE val_arg1)
{
  Transform* p;
  Data_Get_Struct (self, Transform, p);

  if (TYPE(val_arg1) == T_ARRAY) {
    float m[16];
    for (int i = 0; i < 16; i++) {
      m[i] = RFLOAT_VALUE (rb_ary_entry (val_arg1, i));
    }
    p->set (m);

  } else {
    Transform *trans;
    Data_Get_Struct (val_arg1, Transform, trans);
    p->set (*trans);
  }
    return Qnil;
}

VALUE ruby_Transform_set_identity (VALUE self)
{
  Transform* p;
  Data_Get_Struct (self, Transform, p);
  p->setIdentity ();
  return Qnil;
}

VALUE ruby_Transform_transform (int argc, VALUE* argv, VALUE self)
{
  VALUE val_arg1, val_arg2, val_arg3;
  Transform* p;

  Data_Get_Struct (self, Transform, p);
  int num = rb_scan_args (argc, argv, "12", &val_arg1, &val_arg2, &val_arg3);

  switch (num) {
  case 1: {
    float vectors[4];
    for (int i = 0; i < 4; i++) {
      vectors[i] = RFLOAT_VALUE (rb_ary_entry(val_arg1, i));
    }
    p->transform (vectors);
    // メモ:これval\arg1が実際にさしている実体が変わってないか?
    // もう少し良い書き方がある気がする。
    for (int i = 0; i < 4; i++) {
      rb_ary_push (val_arg1, rb_float_new(vectors[i]));
    }
  }
  case 3: {
    VertexArray* in;
    Data_Get_Struct (val_arg1, VertexArray, in);
    int    num = RARRAY(val_arg2)->len;
    float* out = (float*)ruby_xmalloc (sizeof(float)*num);
    bool   w   = (val_arg3 == Qtrue) ? true : false;
    
    p->transform (in, out, w);
    ruby_xfree (out);
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
  p->transpose ();

  return Qnil;
}


void register_Transform ()
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
