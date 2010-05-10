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
    struct ViewportAccessor {
		Graphics3D* graphics3D;
    };
    struct DepthRangeAccessor {
		Graphics3D* graphics3D;
    };
    VALUE rb_cGraphics3D_LightAccessor;
    VALUE rb_cGraphics3D_ViewportAccessor;
    VALUE rb_cGraphics3D_DepthRangeAccessor;
};

VALUE ruby_Graphics3D_free (Graphics3D* ptr)
{
    ptr->~Graphics3D ();
    ruby_xfree (ptr);
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

    return INT2NUM(ret);
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
    DepthRangeAccessor* accessor;
    VALUE               val_accessor = Data_Make_Struct (rb_cGraphics3D_DepthRangeAccessor, DepthRangeAccessor, 0, -1, accessor);
    accessor->graphics3D = p;
    return val_accessor;
}

VALUE ruby_Graphics3D_get_hints (VALUE self)
{
    Graphics3D* p;
    Data_Get_Struct (self, Graphics3D, p);

    int ret;
    ret = p->getHints ();

    return INT2NUM(ret);
}

VALUE ruby_Graphics3D_get_instance (VALUE self)
{
	Graphics3D* p = Graphics3D::getInstance();
  
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
    index = NUM2INT (val_index);
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

    return INT2NUM (count);
}

VALUE ruby_Graphics3D_get_properties (VALUE self)
{
    Graphics3D* p;
    Data_Get_Struct (self, Graphics3D, p);

    std::map<const char*, int> properties = p->getProperties();

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
    Graphics3D*       p;
    ViewportAccessor* accessor;
    VALUE             val_accessor;

    Data_Get_Struct (self, Graphics3D, p);
    val_accessor = Data_Make_Struct (rb_cGraphics3D_ViewportAccessor, ViewportAccessor, 0, -1, accessor);
    accessor->graphics3D = p;
    return val_accessor;
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
		Data_Get_Struct (val_arg1, World, wld);
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
    VALUE val_near = rb_ary_entry(val_depth_range, 0);
    VALUE val_far  = rb_ary_entry(val_depth_range, 1);
    Graphics3D* p;
    Data_Get_Struct (self, Graphics3D, p);
    float near = NUM2DBL(val_near);
    float far  = NUM2DBL(val_far);

    p->setDepthRange (near, far);

    return Qnil;
}

VALUE ruby_Graphics3D_set_light (VALUE self, VALUE val_index, VALUE val_light, VALUE val_transform)
{
    Graphics3D* p;
    int index;
    Light* lig;
    Transform* trans;

    Data_Get_Struct (self, Graphics3D, p);
    index = NUM2INT (val_index);
    Data_Get_Struct (val_light, Light, lig);

    p->setLight (index, lig, *trans);

    return Qnil;
}

VALUE ruby_Graphics3D_set_viewport (VALUE self, VALUE val_viewport)
{
    VALUE val_x      = rb_ary_entry(val_viewport, 0);
    VALUE val_y      = rb_ary_entry(val_viewport, 1);
    VALUE val_width  = rb_ary_entry(val_viewport, 2);
    VALUE val_height = rb_ary_entry(val_viewport, 3);
    Graphics3D* p;
    Data_Get_Struct (self, Graphics3D, p);
    float x      = NUM2DBL(val_x);
    float y      = NUM2DBL(val_y);
    float width  = NUM2DBL(val_width);
    float height = NUM2DBL(val_height);

    p->setViewport (x, y, width, height);

    return Qnil;
}

/**
 *  Graphics3D:: ViewportAccessor
 */


VALUE ruby_Graphics3D_ViewportAccessor_get_x (VALUE self)
{
    ViewportAccessor* p;
    Data_Get_Struct (self, ViewportAccessor, p);
    float x = p->graphics3D->getViewportX();
    return rb_float_new (x);
}

VALUE ruby_Graphics3D_ViewportAccessor_get_y (VALUE self)
{
    ViewportAccessor* p;
    Data_Get_Struct (self, ViewportAccessor, p);
    float y = p->graphics3D->getViewportY();
    return rb_float_new (y);
}

VALUE ruby_Graphics3D_ViewportAccessor_get_width (VALUE self)
{
    ViewportAccessor* p;
    Data_Get_Struct (self, ViewportAccessor, p);
    float width = p->graphics3D->getViewportWidth();
    return rb_float_new (width);
}

VALUE ruby_Graphics3D_ViewportAccessor_get_height (VALUE self)
{
    ViewportAccessor* p;
    Data_Get_Struct (self, ViewportAccessor, p);
    float height = p->graphics3D->getViewportHeight();
    return rb_float_new (height);
}

/**
 * Graphics3D:: DepthRangeAccessor
 */


VALUE ruby_Graphics3D_DepthRangeAccessor_get_near (VALUE self)
{
    DepthRangeAccessor* p;
    Data_Get_Struct (self, DepthRangeAccessor, p);
    float near = p->graphics3D->getDepthRangeNear ();
    return rb_float_new (near);
}

VALUE ruby_Graphics3D_DepthRangeAccessor_get_far (VALUE self)
{
    DepthRangeAccessor* p;
    Data_Get_Struct (self, DepthRangeAccessor, p);
    float far = p->graphics3D->getDepthRangeFar ();
    return rb_float_new (far);
}


/**
 * Graphics3DクラスのRubyへの登録.
 */
void register_Graphics3D ()
{
    // Graphics3D
    rb_cGraphics3D          = rb_define_class_under (rb_mM3G, "Graphics3D",          rb_cObject);

    rb_define_const (rb_cGraphics3D, "ANTIALIAS",  INT2NUM(Graphics3D::ANTIALIAS));
    rb_define_const (rb_cGraphics3D, "DITHER",     INT2NUM(Graphics3D::DITHER));
    rb_define_const (rb_cGraphics3D, "OVERWRITE",  INT2NUM(Graphics3D::OVERWRITE));
    rb_define_const (rb_cGraphics3D, "TRUE_COLOR", INT2NUM(Graphics3D::TRUE_COLOR));

    rb_define_method (rb_cGraphics3D, "add_light",          (VALUE(*)(...))ruby_Graphics3D_add_light,       2);
    rb_define_method (rb_cGraphics3D, "bind_target",        (VALUE(*)(...))ruby_Graphics3D_bind_target,    -1);
    rb_define_method (rb_cGraphics3D, "clear",              (VALUE(*)(...))ruby_Graphics3D_clear,           1);
    rb_define_method (rb_cGraphics3D, "camera",             (VALUE(*)(...))ruby_Graphics3D_get_camera,      1);
    rb_define_method (rb_cGraphics3D, "depth_range",        (VALUE(*)(...))ruby_Graphics3D_get_depth_range, 0);
    rb_define_method (rb_cGraphics3D, "hints",              (VALUE(*)(...))ruby_Graphics3D_get_hints,       0);
    rb_define_singleton_method (rb_cGraphics3D, "instance", (VALUE(*)(...))ruby_Graphics3D_get_instance,    0);
    rb_define_method (rb_cGraphics3D, "light",              (VALUE(*)(...))ruby_Graphics3D_get_light,       2);
    rb_define_method (rb_cGraphics3D, "light_count",        (VALUE(*)(...))ruby_Graphics3D_get_light_count, 0);
    rb_define_method (rb_cGraphics3D, "properties",         (VALUE(*)(...))ruby_Graphics3D_get_properties,  0);
    rb_define_method (rb_cGraphics3D, "target",             (VALUE(*)(...))ruby_Graphics3D_get_target,      0);
    rb_define_method (rb_cGraphics3D, "viewport",           (VALUE(*)(...))ruby_Graphics3D_get_viewport,    0);
    rb_define_method (rb_cGraphics3D, "depth_buffer_enabled?", (VALUE(*)(...))ruby_Graphics3D_is_depth_buffer_enabled, 0);
    rb_define_method (rb_cGraphics3D, "release_target",     (VALUE(*)(...))ruby_Graphics3D_release_target,  0);
    rb_define_method (rb_cGraphics3D, "render",             (VALUE(*)(...))ruby_Graphics3D_render,         -1);
    rb_define_method (rb_cGraphics3D, "reset_lights",       (VALUE(*)(...))ruby_Graphics3D_reset_lights,    0);
    rb_define_method (rb_cGraphics3D, "camera=",            (VALUE(*)(...))ruby_Graphics3D_set_camera,      2);
    rb_define_method (rb_cGraphics3D, "depth_range=",       (VALUE(*)(...))ruby_Graphics3D_set_depth_range, 1);
    rb_define_method (rb_cGraphics3D, "light=",             (VALUE(*)(...))ruby_Graphics3D_set_light,       3);
    rb_define_method (rb_cGraphics3D, "viewport=",          (VALUE(*)(...))ruby_Graphics3D_set_viewport,    1);

    // Graphics3D::ViewportAccessor
    rb_cGraphics3D_ViewportAccessor  = rb_define_class_under (rb_cGraphics3D, "ViewportAccessor", rb_cObject);

    rb_define_method (rb_cGraphics3D_ViewportAccessor, "x",        (VALUE(*)(...))ruby_Graphics3D_ViewportAccessor_get_x,      0);
    rb_define_method (rb_cGraphics3D_ViewportAccessor, "y",        (VALUE(*)(...))ruby_Graphics3D_ViewportAccessor_get_y,      0);
    rb_define_method (rb_cGraphics3D_ViewportAccessor, "width",    (VALUE(*)(...))ruby_Graphics3D_ViewportAccessor_get_width,  0);
    rb_define_method (rb_cGraphics3D_ViewportAccessor, "height",   (VALUE(*)(...))ruby_Graphics3D_ViewportAccessor_get_height, 0);
    
    // Graphics3D::DepthRangeAccessor
    rb_cGraphics3D_DepthRangeAccessor  = rb_define_class_under (rb_cGraphics3D, "DepthRangeAccessor", rb_cObject);
    
    rb_define_method (rb_cGraphics3D_DepthRangeAccessor, "near",  (VALUE(*)(...))ruby_Graphics3D_DepthRangeAccessor_get_near,  0);
    rb_define_method (rb_cGraphics3D_DepthRangeAccessor, "far",   (VALUE(*)(...))ruby_Graphics3D_DepthRangeAccessor_get_far,   0);

}
