#include <iostream>
#include <vector>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  struct LightAccessor {
    Graphics3D* graphics3D;
  };
  VALUE rb_cGraphics3D_Viewport;
  VALUE rb_cGraphics3D_DepthRange;
};

VALUE ruby_Graphics3D_free (Graphics3D* ptr)
{
    ptr->~Graphics3D ();
    ruby_xfree (ptr);
}

VALUE ruby_Graphics3D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Graphics3D));
    return Data_Wrap_Struct (self, NULL, ruby_Graphics3D_free, p);
}

VALUE ruby_Graphics3D_initialize (VALUE self)
{
    Graphics3D* p;
    Data_Get_Struct (self, Graphics3D, p);
    p = Graphics3D::getInstance();
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Graphics3D_add_light (VALUE self, VALUE val_light, VALUE val_transform)
{
    Graphics3D* p;
    Light*      light;
    Transform*  transform;

    Data_Get_Struct (self, Graphics3D, p);
    Data_Get_Struct (val_light, Light, light);
    Data_Get_Struct (val_transform, Transform, transform);

    int ret;
    ret = p->addLight (light, *transform);

    return INT2FIX(ret);
}

VALUE ruby_Graphics3D_bind_target (int argc, VALUE* argv, VALUE self)
{
  Graphics3D* p;
  Data_Get_Struct (self, Graphics3D, p);

  VALUE val_arg1, val_arg2, val_arg3;
  int num = rb_scan_args (argc, argv, "12", &val_arg1, &val_arg2, &val_arg3);
  switch (num) {
  case 1:
  case 2:
  case 3:
  default:
    // この関数はC++でも実装されていない
    p->bindTarget (0);
  }

  return Qnil;
}

VALUE ruby_Graphics3D_clear (VALUE self, VALUE val_background)
{
  Graphics3D* p;
  Background* bg;
  Data_Get_Struct (self, Graphics3D, p);
  Data_Get_Struct (val_background, Background, bg);
  p->clear (bg);
  return Qnil;
}

VALUE ruby_Graphics3D_get_camera (VALUE self, VALUE val_transform)
{
  Graphics3D* p;
  Camera* cam;
  Transform* trans;
  
  Data_Get_Struct (self, Graphics3D, p);
  Data_Get_Struct (val_transform, Transform, trans);

  cam = p->getCamera (*trans);

  return (VALUE)cam->getExportedEntity();
}

VALUE ruby_Graphics3D_get_depth_range (VALUE self)
{
    Graphics3D* p;
    Data_Get_Struct (self, Graphics3D, p);

    Graphics3D::DepthRange* depth_range;
    VALUE val_depth_range = Data_Make_Struct (rb_cGraphics3D_DepthRange, Graphics3D::DepthRange, 0, -1, depth_range);

    depth_range->near = p->getDepthRangeNear();
    depth_range->far  = p->getDepthRangeFar();

    return val_depth_range;
}

VALUE ruby_Graphics3D_get_hints (VALUE self)
{
  Graphics3D* p;
  Data_Get_Struct (self, Graphics3D, p);

  int ret;
  ret = p->getHints ();

  return INT2FIX(ret);
}

VALUE ruby_Graphics3D_get_instance (VALUE self)
{
  Graphics3D* p = Graphics3D:: getInstance();
  
  VALUE val_g3d = (VALUE)p->getExportedEntity();

  if (val_g3d == 0) {
    val_g3d = Data_Wrap_Struct (self, 0, ruby_Graphics3D_free, p);
    p->setExportedEntity ((void*)val_g3d);
  }

  return val_g3d;
}

VALUE ruby_Graphics3D_get_light (VALUE self, VALUE val_index, VALUE val_transform)
{
  Graphics3D* p;
  int         index;
  Transform*  trans;

  Data_Get_Struct (self, Graphics3D, p);
  index = FIX2INT (val_index);
  Data_Get_Struct (val_transform, Transform, trans);

  Light* lig;
  lig = p->getLight (index, *trans);

  return (VALUE)lig->getExportedEntity();
}

VALUE ruby_Graphics3D_get_light_count (VALUE self)
{
  Graphics3D* p;
  int count;
  
  Data_Get_Struct (self, Graphics3D, p);

  count = p->getLightCount ();

  return INT2FIX (count);
}

VALUE ruby_Graphics3D_get_properties (VALUE self)
{
  Graphics3D* p;
  Data_Get_Struct (self, Graphics3D, p);

  std::vector<Property*> properties;

  properties = p->getProperties();

  // 未実装
  return Qnil;
}

VALUE ruby_Graphics3D_get_target (VALUE self)
{
  Graphics3D* p;
  Data_Get_Struct (self, Graphics3D, p);

  p->getTarget ();

  // 未実装
  return Qnil;
}

VALUE ruby_Graphics3D_get_viewport (VALUE self)
{
  Graphics3D* p;
  Graphics3D::Viewport* viewport;
  VALUE val_viewport;

  Data_Get_Struct (self, Graphics3D, p);
  val_viewport = Data_Make_Struct (rb_cGraphics3D_Viewport, Graphics3D::Viewport, 0, -1, viewport);

  viewport->x = p->getViewportX();
  viewport->y = p->getViewportY();
  viewport->width = p->getViewportWidth();
  viewport->height = p->getViewportHeight();

  return val_viewport;
}

VALUE ruby_Graphics3D_is_depth_buffer_enabled (VALUE self)
{
  Graphics3D* p;
  Data_Get_Struct (self, Graphics3D, p);

  bool ret;

  ret = p->isDepthBufferEnabled ();

  if (ret)
    return Qtrue;
  else
    return Qfalse;
}


VALUE ruby_Graphics3D_release_target (VALUE self)
{
  Graphics3D* p;
  Data_Get_Struct (self, Graphics3D, p);

  p->releaseTarget ();
  
  return Qnil;
}


VALUE ruby_Graphics3D_render (int argc, VALUE* argv, VALUE self)
{
  Graphics3D* p;
  Data_Get_Struct (self, Graphics3D, p);

  VALUE val_arg1, val_arg2, val_arg3, val_arg4, val_arg5;
  int num = rb_scan_args (argc, argv, "14", &val_arg1, &val_arg2, &val_arg3, &val_arg4, &val_arg5);

  switch (num) {
  case 1: {
    World* wld;
    Data_Get_Struct (self, World, wld);
    p->render (wld);
    break;
  }
  case 2:
  case 3:
  case 4:
  case 5:
  default: {
    // その他は実装していない
  }
  }

  return Qnil;
}


VALUE ruby_Graphics3D_reset_lights (VALUE self)
{
  Graphics3D* p;
  Data_Get_Struct (self, Graphics3D, p);

  p->resetLights ();

  return Qnil;
}


VALUE ruby_Graphics3D_set_camera (VALUE self, VALUE val_camera, VALUE val_transform)
{
  Graphics3D* p;
  Camera*     cam;
  Transform*  trans;

  Data_Get_Struct (self, Graphics3D, p);
  Data_Get_Struct (val_camera, Camera, cam);
  Data_Get_Struct (val_transform, Transform, trans);

  p->setCamera (cam, *trans);
  
  return Qnil;
}

VALUE ruby_Graphics3D_set_depth_range (VALUE self, VALUE val_depth_range)
{
  Graphics3D* p;
  Graphics3D::DepthRange* depth_range;

  Data_Get_Struct (self, Graphics3D, p);
  Data_Get_Struct (val_depth_range, Graphics3D::DepthRange, depth_range);

  p->setDepthRange (depth_range->near, depth_range->far);

  return Qnil;
}

VALUE ruby_Graphics3D_set_light (VALUE self, VALUE val_index, VALUE val_light, VALUE val_transform)
{
  Graphics3D* p;
  int index;
  Light* lig;
  Transform* trans;

  Data_Get_Struct (self, Graphics3D, p);
  index = FIX2INT (val_index);
  Data_Get_Struct (val_light, Light, lig);

  p->setLight (index, lig, *trans);

  return Qnil;
}

VALUE ruby_Graphics3D_set_viewport (VALUE self, VALUE val_viewport)
{
  Graphics3D* p;
  Graphics3D::Viewport* viewport;

  Data_Get_Struct (self, Graphics3D, p);
  Data_Get_Struct (val_viewport, Graphics3D::Viewport, viewport);

  p->setViewport (viewport->x, viewport->y, viewport->width, viewport->height);

  return Qnil;
}

/**
 *  Graphics3D:: Viewport
 */

VALUE ruby_Graphics3D_Viewport_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(Graphics3D::Viewport));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Graphics3D_Viewport_initialize (VALUE self, VALUE val_x, VALUE val_y, VALUE val_width, VALUE val_height)
{
  Graphics3D::Viewport* p;
  Data_Get_Struct (self, Graphics3D::Viewport, p);
  p->x = RFLOAT_VALUE (val_x);
  p->y = RFLOAT_VALUE (val_y);
  p->width = RFLOAT_VALUE (val_width);
  p->height = RFLOAT_VALUE (val_height);
    return self;
}

VALUE ruby_Graphics3D_Viewport_get_x (VALUE self)
{
  Graphics3D::Viewport* p;
  Data_Get_Struct (self, Graphics3D::Viewport, p);
  return rb_float_new (p->x);
}

VALUE ruby_Graphics3D_Viewport_get_y (VALUE self)
{
  Graphics3D::Viewport* p;
  Data_Get_Struct (self, Graphics3D::Viewport, p);
  return rb_float_new (p->y);
}

VALUE ruby_Graphics3D_Viewport_get_width (VALUE self)
{
  Graphics3D::Viewport* p;
  Data_Get_Struct (self, Graphics3D::Viewport, p);
  return rb_float_new (p->width);
}

VALUE ruby_Graphics3D_Viewport_get_height (VALUE self)
{
  Graphics3D::Viewport* p;
  Data_Get_Struct (self, Graphics3D::Viewport, p);
  return rb_float_new (p->height);
}

/**
 * Graphics3D:: DepthRange
 */

VALUE ruby_Graphics3D_DepthRange_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(Graphics3D::DepthRange));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Graphics3D_DepthRange_initialize (VALUE self, VALUE val_near, VALUE val_far)
{
  Graphics3D::DepthRange* p;
  Data_Get_Struct (self, Graphics3D::DepthRange, p);
  p->near = RFLOAT_VALUE(val_near);
  p->far  = RFLOAT_VALUE(val_far);
    return self;
}

VALUE ruby_Graphics3D_DepthRange_get_near (VALUE self)
{
  Graphics3D::DepthRange* p;
  Data_Get_Struct (self, Graphics3D::DepthRange, p);
  return rb_float_new (p->near);
}

VALUE ruby_Graphics3D_DepthRange_get_far (VALUE self)
{
  Graphics3D::DepthRange* p;
  Data_Get_Struct (self, Graphics3D::DepthRange, p);
  return rb_float_new (p->far);
}


/**
 * Graphics3Dクラスのメンバー関数のRubyへの登録.
 */
void register_Graphics3D ()
{
  // Graphics3D
    rb_define_const (rb_cGraphics3D, "ANTIALIAS",  INT2FIX(Graphics3D::ANTIALIAS));
    rb_define_const (rb_cGraphics3D, "DITHER",     INT2FIX(Graphics3D::DITHER));
    rb_define_const (rb_cGraphics3D, "OVERWRITE",  INT2FIX(Graphics3D::OVERWRITE));
    rb_define_const (rb_cGraphics3D, "TRUE_COLOR", INT2FIX(Graphics3D::TRUE_COLOR));

    rb_define_alloc_func (rb_cGraphics3D, ruby_Graphics3D_allocate);
    rb_define_private_method (rb_cGraphics3D, "initialize", (VALUE(*)(...))ruby_Graphics3D_initialize, 0);

    rb_define_method (rb_cGraphics3D, "add_light",          (VALUE(*)(...))ruby_Graphics3D_add_light, 2);
    rb_define_method (rb_cGraphics3D, "bind_target",        (VALUE(*)(...))ruby_Graphics3D_bind_target, -1);
    rb_define_method (rb_cGraphics3D, "clear",              (VALUE(*)(...))ruby_Graphics3D_clear, 1);
    rb_define_method (rb_cGraphics3D, "camera",             (VALUE(*)(...))ruby_Graphics3D_get_camera, 1);
    rb_define_method (rb_cGraphics3D, "depth_range",        (VALUE(*)(...))ruby_Graphics3D_get_depth_range, 0);
    rb_define_method (rb_cGraphics3D, "hints",              (VALUE(*)(...))ruby_Graphics3D_get_hints, 0);
    rb_define_singleton_method (rb_cGraphics3D, "instance", (VALUE(*)(...))ruby_Graphics3D_get_instance, 0);
    rb_define_method (rb_cGraphics3D, "light",              (VALUE(*)(...))ruby_Graphics3D_get_light, 2);
    rb_define_method (rb_cGraphics3D, "light_count",        (VALUE(*)(...))ruby_Graphics3D_get_light_count, 0);
    rb_define_method (rb_cGraphics3D, "properties",         (VALUE(*)(...))ruby_Graphics3D_get_properties, 0);
    rb_define_method (rb_cGraphics3D, "target",             (VALUE(*)(...))ruby_Graphics3D_get_target, 0);
    rb_define_method (rb_cGraphics3D, "viewport",           (VALUE(*)(...))ruby_Graphics3D_get_viewport, 0);
    rb_define_method (rb_cGraphics3D, "depth_buffer_enabled?", (VALUE(*)(...))ruby_Graphics3D_is_depth_buffer_enabled, 0);
    rb_define_method (rb_cGraphics3D, "release_target",     (VALUE(*)(...))ruby_Graphics3D_release_target, 0);
    rb_define_method (rb_cGraphics3D, "render",             (VALUE(*)(...))ruby_Graphics3D_render, -1);
    rb_define_method (rb_cGraphics3D, "reset_lights",       (VALUE(*)(...))ruby_Graphics3D_reset_lights, 0);
    rb_define_method (rb_cGraphics3D, "camera=",            (VALUE(*)(...))ruby_Graphics3D_set_camera, 2);
    rb_define_method (rb_cGraphics3D, "depth_range=",       (VALUE(*)(...))ruby_Graphics3D_set_depth_range, 1);
    rb_define_method (rb_cGraphics3D, "light=",             (VALUE(*)(...))ruby_Graphics3D_set_light, 3);
    rb_define_method (rb_cGraphics3D, "viewport=",          (VALUE(*)(...))ruby_Graphics3D_set_viewport, 1);

  // Graphics3D::Viewport
     rb_cGraphics3D_Viewport  = rb_define_class_under (rb_cGraphics3D, "Viewport", rb_cObject);

     rb_define_alloc_func (rb_cGraphics3D_Viewport, ruby_Graphics3D_Viewport_allocate);
     rb_define_private_method (rb_cGraphics3D_Viewport, "initialize", (VALUE(*)(...))ruby_Graphics3D_Viewport_initialize, 4);

     rb_define_method (rb_cGraphics3D_Viewport, "x",        (VALUE(*)(...))ruby_Graphics3D_Viewport_get_x,    0);
     rb_define_method (rb_cGraphics3D_Viewport, "y",        (VALUE(*)(...))ruby_Graphics3D_Viewport_get_y,    0);
     rb_define_method (rb_cGraphics3D_Viewport, "width",        (VALUE(*)(...))ruby_Graphics3D_Viewport_get_width,    0);
     rb_define_method (rb_cGraphics3D_Viewport, "height",        (VALUE(*)(...))ruby_Graphics3D_Viewport_get_height,    0);

  // Graphics3D::DepthRange
     rb_cGraphics3D_DepthRange  = rb_define_class_under (rb_cGraphics3D, "DepthRange", rb_cObject);

     rb_define_alloc_func (rb_cGraphics3D_DepthRange, ruby_Graphics3D_DepthRange_allocate);
     rb_define_private_method (rb_cGraphics3D_DepthRange, "initialize", (VALUE(*)(...))ruby_Graphics3D_DepthRange_initialize, 2);

     rb_define_method (rb_cGraphics3D_DepthRange, "near",        (VALUE(*)(...))ruby_Graphics3D_DepthRange_get_near,    0);
     rb_define_method (rb_cGraphics3D_DepthRange, "far",        (VALUE(*)(...))ruby_Graphics3D_DepthRange_get_far,    0);

}
