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

extern VALUE ruby_Transform_allocate (VALUE self);
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
    float px = NUMERIC2FLOAT(val_px);
    float py = NUMERIC2FLOAT(val_py);
    float pz = NUMERIC2FLOAT(val_pz);
    float dx = NUMERIC2FLOAT(val_dx);
    float dy = NUMERIC2FLOAT(val_dy);
    float dz = NUMERIC2FLOAT(val_dz);
    float ux = NUMERIC2FLOAT(val_ux);
    float uy = NUMERIC2FLOAT(val_uy);
    float uz = NUMERIC2FLOAT(val_uz);
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
  float height       = NUMERIC2FLOAT (val_fovy);
  float aspect_ratio = NUMERIC2FLOAT (val_aspect_ratio);
  float near         = NUMERIC2FLOAT (val_near);
  float far          = NUMERIC2FLOAT (val_far);

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
  float fovy         = NUMERIC2FLOAT (val_fovy);
  float aspect_ratio = NUMERIC2FLOAT (val_aspect_ratio);
  float near         = NUMERIC2FLOAT (val_near);
  float far          = NUMERIC2FLOAT (val_far);

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
  return INT2FIX(type);
}


VALUE ruby_Camera_ProjectionAccessor_get_params (VALUE self)
{
  ProjectionAccessor* p;
  Data_Get_Struct (self, ProjectionAccessor, p);
  float params[4];
  p->camera->getProjection (params);
  VALUE val_params = rb_ary_new ();
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
     rb_define_const (rb_cCamera, "GENERIC",     INT2FIX(Camera::GENERIC));
     rb_define_const (rb_cCamera, "PARALLEL",    INT2FIX(Camera::PARALLEL));
     rb_define_const (rb_cCamera, "PERSPECTIVE", INT2FIX(Camera::PERSPECTIVE));

     rb_define_alloc_func (rb_cCamera, ruby_Camera_allocate);
     rb_define_private_method (rb_cCamera, "initialize", (VALUE(*)(...))ruby_Camera_initialize, 0);

     rb_define_method (rb_cCamera, "projection",      (VALUE(*)(...))ruby_Camera_get_projection, 0);
     rb_define_method (rb_cCamera, "look_at",      (VALUE(*)(...))ruby_Camera_look_at,         9);
     rb_define_method (rb_cCamera, "generic=",     (VALUE(*)(...))ruby_Camera_set_generic,     1);
     rb_define_method (rb_cCamera, "parallel=",    (VALUE(*)(...))ruby_Camera_set_parallel,    1);
     rb_define_method (rb_cCamera, "perspective=", (VALUE(*)(...))ruby_Camera_set_perspective, 1);


     // Camera:: ProjectionAccessor
     rb_cCamera_ProjectionAccessor  = rb_define_class_under (rb_cCamera, "ProjectionAccessor", rb_cObject);

     rb_define_alloc_func (rb_cCamera_ProjectionAccessor, ruby_Camera_ProjectionAccessor_allocate);
     rb_define_private_method (rb_cCamera_ProjectionAccessor, "initialize", (VALUE(*)(...))ruby_Camera_ProjectionAccessor_initialize, 0);

    rb_define_method (rb_cCamera_ProjectionAccessor, "type",     (VALUE(*)(...))ruby_Camera_ProjectionAccessor_get_type, 0);
    rb_define_method (rb_cCamera_ProjectionAccessor, "params",     (VALUE(*)(...))ruby_Camera_ProjectionAccessor_get_params, 0);
    rb_define_method (rb_cCamera_ProjectionAccessor, "transform",     (VALUE(*)(...))ruby_Camera_ProjectionAccessor_get_transform, 0);

}
