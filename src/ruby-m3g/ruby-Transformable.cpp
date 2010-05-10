#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

extern VALUE ruby_Transform_free (Transform* ptr);


VALUE ruby_Transformable_free (Transformable* ptr)
{
    ptr->~Transformable ();
    ruby_xfree (ptr);
}

VALUE ruby_Transformable_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Transformable));
    return Data_Wrap_Struct (self, 0, ruby_Transformable_free, p);
}

VALUE ruby_Transformable_initialize (VALUE self)
{
    Transformable* p;
    Data_Get_Struct (self, Transformable, p);
    new (p) Transformable;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Transformable_get_composite_transform (VALUE self)
{
  Transformable* p;
  Data_Get_Struct (self, Transformable, p);
  Transform* trans;
  VALUE val_trans = Data_Make_Struct (rb_cTransform, Transform, 0, ruby_Transform_free, trans);

  p->getCompositeTransform (trans);

    return val_trans;
}

VALUE ruby_Transformable_get_orientation (VALUE self)
{
    Transformable* p;
    float angle_axis[4];

    Data_Get_Struct (self, Transformable, p);

    p->getOrientation (angle_axis);

    VALUE val_angle_axis = rb_ary_new ();
    rb_ary_push (val_angle_axis, rb_float_new(angle_axis[0]));
    rb_ary_push (val_angle_axis, rb_float_new(angle_axis[1]));
    rb_ary_push (val_angle_axis, rb_float_new(angle_axis[2]));
    rb_ary_push (val_angle_axis, rb_float_new(angle_axis[3]));

    return val_angle_axis;
}

VALUE ruby_Transformable_get_scale (VALUE self)
{
    Transformable* p;
    Data_Get_Struct (self, Transformable, p);

    float scale[3];
    p->getScale (scale);

    VALUE val_scale = rb_ary_new ();
    rb_ary_push (val_scale, rb_float_new(scale[0]));
    rb_ary_push (val_scale, rb_float_new(scale[1]));
    rb_ary_push (val_scale, rb_float_new(scale[2]));

    return val_scale;
}

VALUE ruby_Transformable_get_transform (VALUE self)
{
    Transformable* p;
    Data_Get_Struct (self, Transformable, p);
    Transform* trans;
    VALUE val_trans = Data_Make_Struct (rb_cTransform, Transform, 0, ruby_Transform_free, trans);

    p->getTransform (trans);

    return val_trans;
}

VALUE ruby_Transformable_get_translation (VALUE self)
{
    Transformable* p;
    float trans[3];

    Data_Get_Struct (self, Transformable, p);

    p->getTranslation (trans);

    VALUE val_trans = rb_ary_new ();
    rb_ary_push (val_trans, rb_float_new(trans[0]));
    rb_ary_push (val_trans, rb_float_new(trans[1]));
    rb_ary_push (val_trans, rb_float_new(trans[2]));

    return val_trans;
}

VALUE ruby_Transformable_post_rotate (VALUE self, VALUE val_angle, VALUE val_ax, VALUE val_ay, VALUE val_az)
{
  Transformable* p;
  Data_Get_Struct (self, Transformable, p);
  float angle = NUM2DBL(val_angle);
  float ax    = NUM2DBL(val_ax);
  float ay    = NUM2DBL(val_ay);
  float az    = NUM2DBL(val_az);
  
  p->postRotate (angle, ax, ay, az);

  return Qnil;
}

VALUE ruby_Transformable_pre_rotate (VALUE self, VALUE val_angle, VALUE val_ax, VALUE val_ay, VALUE val_az)
{
    Transformable* p;
    float angle, ax, ay, az;

    Data_Get_Struct (self, Transformable, p);
    angle = NUM2DBL(val_angle);
    ax    = NUM2DBL(val_ax);
    ay    = NUM2DBL(val_ay);
    az    = NUM2DBL(val_az);

    p->preRotate (angle, ax, ay, az);

    return Qnil;
}

VALUE ruby_Transformable_scale (VALUE self, VALUE val_sx, VALUE val_sy, VALUE val_sz)
{
    Transformable* p;
    Data_Get_Struct (self, Transformable, p);
    float sx  = NUM2DBL (val_sx);
    float sy  = NUM2DBL (val_sy);
    float sz  = NUM2DBL (val_sz);

    p->setScale (sx, sy, sz);

    return Qnil;
}

VALUE ruby_Transformable_set_orientation (VALUE self,  VALUE val_args)
{
  VALUE val_angle = rb_ary_entry(val_args, 0);
  VALUE val_ax    = rb_ary_entry(val_args, 1);
  VALUE val_ay    = rb_ary_entry(val_args, 2);
  VALUE val_az    = rb_ary_entry(val_args, 3);
  Transformable* p;
  Data_Get_Struct (self, Transformable, p);
  float angle = NUM2DBL (val_angle);
  float ax    = NUM2DBL (val_ax);
  float ay    = NUM2DBL (val_ay);
  float az    = NUM2DBL (val_az);

    p->setOrientation (angle, ax, ay, az);

    return Qnil;
}

VALUE ruby_Transformable_set_scale (VALUE self, VALUE val_args)
{
  VALUE val_sx = rb_ary_entry(val_args, 0);
  VALUE val_sy = rb_ary_entry(val_args, 1);
  VALUE val_sz = rb_ary_entry(val_args, 2);
  Transformable* p;
  Data_Get_Struct (self, Transformable, p);
  float sx = NUM2DBL (val_sx);
  float sy = NUM2DBL (val_sy);
  float sz = NUM2DBL (val_sz);

  p->setScale (sx, sy, sz);

  return Qnil;
}

VALUE ruby_Transformable_set_transform (VALUE self, VALUE val_tranform)
{
    Transformable* p;
    Transform* trans;

    Data_Get_Struct (self, Transformable, p);
    Data_Get_Struct (val_tranform, Transform, trans);

    p->setTransform (*trans);

    return Qnil;
}

VALUE ruby_Transformable_set_translation (VALUE self, VALUE val_txyz)
{
    VALUE val_tx = rb_ary_entry(val_txyz, 0);
    VALUE val_ty = rb_ary_entry(val_txyz, 1);
    VALUE val_tz = rb_ary_entry(val_txyz, 2);
    Transformable* p;
    Data_Get_Struct (self, Transformable, p);
    float tx  = NUM2DBL (val_tx);
    float ty  = NUM2DBL (val_ty);
    float tz  = NUM2DBL (val_tz);

    p->setTranslation (tx, ty, tz);

    return Qnil;
}

VALUE ruby_Transformable_translate (VALUE self, VALUE val_tx, VALUE val_ty, VALUE val_tz)
{
  Transformable* p;
  Data_Get_Struct (self, Transformable, p);
  float tx = NUM2DBL (val_tx);
  float ty = NUM2DBL (val_ty);
  float tz = NUM2DBL (val_tz);

  p->translate (tx, ty, tz);

  return Qnil;
}

/**
 *
 */
void register_Transformable ()
{
     // Transformable
    rb_cTransformable       = rb_define_class_under (rb_mM3G, "Transformable",       rb_cObject3D);

     rb_define_alloc_func (rb_cTransformable, ruby_Transformable_allocate);
     rb_define_private_method (rb_cTransformable, "initialize", (VALUE(*)(...))ruby_Transformable_initialize,       0);

     rb_define_method (rb_cTransformable, "composite_transform", (VALUE(*)(...))ruby_Transformable_get_composite_transform, 0);
     rb_define_method (rb_cTransformable, "orientation",         (VALUE(*)(...))ruby_Transformable_get_orientation, 0);
     rb_define_method (rb_cTransformable, "scaling",             (VALUE(*)(...))ruby_Transformable_get_scale,       0);
     rb_define_method (rb_cTransformable, "transform",           (VALUE(*)(...))ruby_Transformable_get_transform,   0);
     rb_define_method (rb_cTransformable, "translate",           (VALUE(*)(...))ruby_Transformable_translate,       3);
     rb_define_method (rb_cTransformable, "translation",         (VALUE(*)(...))ruby_Transformable_get_translation, 0);
     rb_define_method (rb_cTransformable, "post_rotate",         (VALUE(*)(...))ruby_Transformable_post_rotate,     4);
     rb_define_method (rb_cTransformable, "pre_rotate",          (VALUE(*)(...))ruby_Transformable_pre_rotate,      4);
     rb_define_method (rb_cTransformable, "scale",               (VALUE(*)(...))ruby_Transformable_scale,           3);
     rb_define_method (rb_cTransformable, "orientation=",        (VALUE(*)(...))ruby_Transformable_set_orientation, 1);
     rb_define_method (rb_cTransformable, "scaling=",            (VALUE(*)(...))ruby_Transformable_set_scale,       1);
     rb_define_method (rb_cTransformable, "transform=",          (VALUE(*)(...))ruby_Transformable_set_transform,   1);
     rb_define_method (rb_cTransformable, "translation=",        (VALUE(*)(...))ruby_Transformable_set_translation, 1);


}
