#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

VALUE ruby_Transform_free (Transform* ptr);

namespace {
  // この構造体はm3g本体のCameraに取り込む
  //struct Projection {
  //  int        type;
  //  float      params[4];
  //  Transform* transform;
  //};
  struct ProjectionAccessor {
    Camera* camera;
  };
  VALUE rb_cCamera_ProjectionAccessor;
};

extern VALUE ruby_Transform_allocate   (VALUE self);
extern VALUE ruby_Transform_initialize (int argc, VALUE* argv, VALUE self);


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
    Data_Get_Struct (self, Camera, p);
    ProjectionAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cCamera_ProjectionAccessor, ProjectionAccessor, 0, -1, accessor);
    accessor->camera = p;
    return val_accessor;
}

VALUE ruby_Camera_look_at (VALUE self, VALUE val_px, VALUE val_py, VALUE val_pz, VALUE val_dx, VALUE val_dy, VALUE val_dz, VALUE val_ux, VALUE val_uy, VALUE val_uz)
{
    Camera* p;
    Data_Get_Struct (self, Camera, p);
    float px = NUM2DBL(val_px);
    float py = NUM2DBL(val_py);
    float pz = NUM2DBL(val_pz);
    float dx = NUM2DBL(val_dx);
    float dy = NUM2DBL(val_dy);
    float dz = NUM2DBL(val_dz);
    float ux = NUM2DBL(val_ux);
    float uy = NUM2DBL(val_uy);
    float uz = NUM2DBL(val_uz);
    p->lookAt (px, py, pz,
               dx, dy, dz,
               ux, uy, uz);
    return Qnil;
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

VALUE ruby_Camera_set_parallel (VALUE self, VALUE val_args)
{
  VALUE val_fovy         = rb_ary_entry(val_args, 0);
  VALUE val_aspect_ratio = rb_ary_entry(val_args, 1);
  VALUE val_near         = rb_ary_entry(val_args, 2);
  VALUE val_far          = rb_ary_entry(val_args, 3);
  Camera* p;
  Data_Get_Struct (self, Camera, p);
  float height       = NUM2DBL (val_fovy);
  float aspect_ratio = NUM2DBL (val_aspect_ratio);
  float near         = NUM2DBL (val_near);
  float far          = NUM2DBL (val_far);

    p->setParallel (height, aspect_ratio, near, far);

    return Qnil;
}

VALUE ruby_Camera_set_perspective (VALUE self, VALUE val_args)
{
  VALUE val_fovy         = rb_ary_entry(val_args, 0);
  VALUE val_aspect_ratio = rb_ary_entry(val_args, 1);
  VALUE val_near         = rb_ary_entry(val_args, 2);
  VALUE val_far          = rb_ary_entry(val_args, 3);
  Camera* p;
  Data_Get_Struct (self, Camera, p);
  float fovy         = NUM2DBL (val_fovy);
  float aspect_ratio = NUM2DBL (val_aspect_ratio);
  float near         = NUM2DBL (val_near);
  float far          = NUM2DBL (val_far);

    p->setPerspective (fovy, aspect_ratio, near, far);

    return Qnil;
}


/**
 * Camera::ProjectionAccessor
 */

VALUE ruby_Camera_ProjectionAccessor_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Camera));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Camera_ProjectionAccessor_initialize (VALUE self)
{
    ProjectionAccessor* p;
    Data_Get_Struct (self, ProjectionAccessor, p);
    return self;
}

VALUE ruby_Camera_ProjectionAccessor_get_type (VALUE self)
{
  ProjectionAccessor* p;
  Data_Get_Struct (self, ProjectionAccessor, p);
  int type = p->camera->getProjection ((float*)0);
  return INT2NUM(type);
}


VALUE ruby_Camera_ProjectionAccessor_get_params (VALUE self)
{
  ProjectionAccessor* p;
  Data_Get_Struct (self, ProjectionAccessor, p);
  float params[4];
  p->camera->getProjection (params);
  VALUE val_params = rb_ary_new2 (4);
  for (int i = 0; i < 4; i++) {
    rb_ary_push (val_params, rb_float_new(params[i]));
  }
  return val_params;
}

VALUE ruby_Camera_ProjectionAccessor_get_transform (VALUE self)
{
  ProjectionAccessor* p;
  Data_Get_Struct (self, ProjectionAccessor, p);
  Transform* trans = 0;
  VALUE val_trans = Data_Make_Struct (rb_cTransform, Transform, 0, ruby_Transform_free, trans);
  p->camera->getProjection (trans);
  return val_trans;
}

void register_Camera ()
{
     // Camera
    rb_cCamera              = rb_define_class_under (rb_mM3G, "Camera",              rb_cNode);

     rb_define_const (rb_cCamera, "GENERIC",     INT2NUM(Camera::GENERIC));
     rb_define_const (rb_cCamera, "PARALLEL",    INT2NUM(Camera::PARALLEL));
     rb_define_const (rb_cCamera, "PERSPECTIVE", INT2NUM(Camera::PERSPECTIVE));

     rb_define_alloc_func (rb_cCamera, ruby_Camera_allocate);
     rb_define_private_method (rb_cCamera, "initialize", (VALUE(*)(...))ruby_Camera_initialize, 0);

     rb_define_method (rb_cCamera, "projection",   (VALUE(*)(...))ruby_Camera_get_projection,  0);
     rb_define_method (rb_cCamera, "look_at",      (VALUE(*)(...))ruby_Camera_look_at,         9);
     rb_define_method (rb_cCamera, "generic=",     (VALUE(*)(...))ruby_Camera_set_generic,     1);
     rb_define_method (rb_cCamera, "parallel=",    (VALUE(*)(...))ruby_Camera_set_parallel,    1);
     rb_define_method (rb_cCamera, "perspective=", (VALUE(*)(...))ruby_Camera_set_perspective, 1);


     // Camera:: ProjectionAccessor
     rb_cCamera_ProjectionAccessor  = rb_define_class_under (rb_cCamera, "ProjectionAccessor", rb_cObject);

    rb_define_method (rb_cCamera_ProjectionAccessor, "type",       (VALUE(*)(...))ruby_Camera_ProjectionAccessor_get_type,      0);
    rb_define_method (rb_cCamera_ProjectionAccessor, "params",     (VALUE(*)(...))ruby_Camera_ProjectionAccessor_get_params,    0);
    rb_define_method (rb_cCamera_ProjectionAccessor, "transform",  (VALUE(*)(...))ruby_Camera_ProjectionAccessor_get_transform, 0);

}
