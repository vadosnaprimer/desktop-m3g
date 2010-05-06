#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;
namespace {
  // この構造体はm3g本体のCameraに取り込む
  struct Projection {
    int        type;
    float      params[4];
    Transform* transform;
  };
  VALUE rb_cCamera_Projection;
};

extern VALUE ruby_Transform_allocate (VALUE self);

VALUE ruby_Camera_free (Camera* ptr)
{
    ptr->~Camera ();
    ruby_xfree (ptr);
}

VALUE ruby_Camera_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Camera));
    return Data_Wrap_Struct (self, 0, ruby_Camera_free, p);
}

VALUE ruby_Camera_initialize (VALUE self)
{
    Camera* p;
    Data_Get_Struct (self, Camera, p);
    new (p) Camera;
    p->setExportedEntity((void*)self);
    return self;
}

VALUE ruby_Camera_get_projection (VALUE self)
{
    Camera* p;
    Projection* proj;
    VALUE val_proj;

    Data_Get_Struct (self, Camera, p);
    val_proj = Data_Make_Struct (rb_cCamera_Projection, Projection, 0, -1, proj);
    
    proj->type = p->getProjection (proj->transform);
    if (proj->type == Camera::PARALLEL || proj->type == Camera::PERSPECTIVE) {
      p->getProjection (proj->params);
    }
    
    return val_proj;
}

VALUE ruby_Camera_set_generic (VALUE self, VALUE val_transform)
{
    Camera* p;
    Transform* trans;

    Data_Get_Struct (self, Camera, p);
    Data_Get_Struct (val_transform, Transform, trans);

    p->setGeneric (*trans);

    return Qnil;
}

VALUE ruby_Camera_set_parallel (VALUE self, VALUE val_fovy, VALUE val_aspect_ratio, VALUE val_near, VALUE val_far)
{
    Camera* p;
    float height, aspect_ratio, near, far;

    Data_Get_Struct (self, Camera, p);
    height       = RFLOAT_VALUE (val_fovy);
    aspect_ratio = RFLOAT_VALUE (val_aspect_ratio);
    near         = RFLOAT_VALUE (val_near);
    far          = RFLOAT_VALUE (val_far);

    p->setParallel (height, aspect_ratio, near, far);

    return Qnil;
}

VALUE ruby_Camera_set_perspective (VALUE self, VALUE val_fovy, VALUE val_aspect_ratio, VALUE val_near, VALUE val_far)
{
    Camera* p;
    float fovy, aspect_ratio, near, far;

    Data_Get_Struct (self, Camera, p);
    fovy         = RFLOAT_VALUE (val_fovy);
    aspect_ratio = RFLOAT_VALUE (val_aspect_ratio);
    near         = RFLOAT_VALUE (val_near);
    far          = RFLOAT_VALUE (val_far);

    p->setPerspective (fovy, aspect_ratio, near, far);

    return Qnil;
}


/**
 * Camera::Projection
 */

VALUE ruby_Camera_Projection_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Camera));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Camera_Projection_initialize (VALUE self)
{
    Projection* p;
    Data_Get_Struct (self, Projection, p);
    return self;
}

VALUE ruby_Camera_Projection_get_type (VALUE self)
{
  Projection* p;
  Data_Get_Struct (self, Projection, p);
  return INT2FIX (p->type);
}


VALUE ruby_Camera_Projection_get_params (VALUE self)
{

  Projection* p;
  Data_Get_Struct (self, Projection, p);
  VALUE val_params = rb_ary_new ();
  for (int i = 0; i < 4; i++) {
    rb_ary_push (val_params, rb_float_new(p->params[i]));
  }
  return val_params;
}

VALUE ruby_Camera_Projection_get_transform (VALUE self)
{
  Projection* p;
  Data_Get_Struct (self, Projection, p);
  // TODO: 返したTransform行列を直接書き換えられるのはまずい。
  // 何か対応をとる
  return (VALUE)p->transform->getExportedEntity();
}

void register_Camera ()
{
     // Camera
     rb_define_const (rb_cCamera, "GENERIC",     INT2FIX(Camera::GENERIC));
     rb_define_const (rb_cCamera, "PARALLEL",    INT2FIX(Camera::PARALLEL));
     rb_define_const (rb_cCamera, "PERSPECTIVE", INT2FIX(Camera::PERSPECTIVE));

     rb_define_alloc_func (rb_cCamera, ruby_Camera_allocate);
     rb_define_private_method (rb_cCamera, "initialize", (VALUE(*)(...))ruby_Camera_initialize, 0);

     rb_define_method (rb_cCamera, "projection",  (VALUE(*)(...))ruby_Camera_get_projection, 0);
     rb_define_method (rb_cCamera, "set_generic",     (VALUE(*)(...))ruby_Camera_set_generic,     1);
     rb_define_method (rb_cCamera, "set_parallel",    (VALUE(*)(...))ruby_Camera_set_parallel,    4);
     rb_define_method (rb_cCamera, "set_perspective", (VALUE(*)(...))ruby_Camera_set_perspective, 4);

     // Camera:: Projection
     rb_cCamera_Projection  = rb_define_class_under (rb_cCamera, "Projection", rb_cObject);

     rb_define_alloc_func (rb_cCamera_Projection, ruby_Camera_Projection_allocate);
     rb_define_private_method (rb_cCamera_Projection, "initialize", (VALUE(*)(...))ruby_Camera_Projection_initialize, 0);

    rb_define_method (rb_cCamera_Projection, "type",     (VALUE(*)(...))ruby_Camera_Projection_get_type, 0); 
    rb_define_method (rb_cCamera_Projection, "params",     (VALUE(*)(...))ruby_Camera_Projection_get_params, 0); 
    rb_define_method (rb_cCamera_Projection, "transform",     (VALUE(*)(...))ruby_Camera_Projection_get_transform, 0); 



}
