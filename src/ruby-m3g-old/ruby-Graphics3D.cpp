#include <new>
#include "ruby.h"
#include "Graphics3D.hpp"
using namespace m3g;



VALUE ruby_Graphics3D_free (Graphics3D* ptr)
{
    ptr->~Graphics3D ();
    ruby_xfree (ptr);
}

VALUE ruby_Graphics3D_allocate (VALUE self)
{
    printf ("ruby_Graphics3D:: allocate\n");
    void* p = ruby_xmalloc (sizeof(Graphics3D));
    return Data_Wrap_Struct (self, NULL, ruby_Graphics3D_free, p);
}

VALUE ruby_Graphics3D_initialize (VALUE self)
{
    printf ("ruby_Graphics3D:: initialized\n");
    Graphics3D* p;
    Data_Get_Struct (self, Graphics3D, p);
    new (p) Graphics3D;
    return Qnil;
}

VALUE ruby_Graphics3D_add_light (VALUE self, VALUE val_light, VALUE val_transform)
{
    return Qnil;
}

VALUE ruby_Graphics3D_bind_target (VALUE self, VALUE val_graphics)
{
    return Qnil;
}

VALUE ruby_Graphics3D_clear (VALUE self, VALUE val_background)
{
    return Qnil;
}

VALUE ruby_Graphics3D_get_camera (VALUE self, VALUE transform)
{
    return Qnil;
}

VALUE ruby_Graphics3D_get_depth_range (VALUE self)
{
    // nearとfarの両方を返す
    return Qnil;
}

VALUE ruby_Graphics3D_get_hints (VALUE self)
{
    return Qnil;
}

VALUE ruby_Graphics3D_get_instance (VALUE self)
{
    static Graphics3D* g3d = 0;
    static VALUE val_g3d;
    if (!g3d) {
        g3d = (Graphics3D*)ruby_xmalloc (sizeof(Graphics3D));
        val_g3d = Data_Wrap_Struct (self, NULL, ruby_Graphics3D_free, g3d);
        new (g3d) Graphics3D;
    }
    return val_g3d;
}

VALUE ruby_Graphics3D_get_light (VALUE self, VALUE val_index, VALUE val_transform)
{
    return Qnil;
}

VALUE ruby_Graphics3D_get_light_count (VALUE self)
{
    return Qnil;
}

VALUE ruby_Graphics3D_get_properties (VALUE self)
{
    return Qnil;
}

VALUE ruby_Graphics3D_get_target (VALUE self)
{
    return Qnil;
}

VALUE ruby_Graphics3D_get_viewport (VALUE self)
{
    return Qnil;
}

VALUE ruby_Graphics3D_is_depth_buffer_enabled (VALUE self)
{
    return Qnil;
}


VALUE ruby_Graphics3D_release_target (VALUE self)
{
    return Qnil;
}


VALUE ruby_Graphics3D_render (VALUE self, VALUE val_vertices, VALUE val_triangles, VALUE val_appearance, VALUE transform, VALUE scope)
{
    // メモ：引数で４つに切り分ける
    return Qnil;
}


VALUE ruby_Graphics3D_reset_lights (VALUE self)
{
    return Qnil;
}


VALUE ruby_Graphics3D_set_camera (VALUE self, VALUE val_camera_and_transform)
{
    return Qnil;
}

VALUE ruby_Graphics3D_set_depth_range (VALUE self, VALUE val_near_and_far)
{
    return Qnil;
}

VALUE ruby_Graphics3D_set_light (VALUE self, VALUE index_and_light_and_transform)
{
    return Qnil;
}

VALUE ruby_Graphics3D_set_viewport (VALUE self, VALUE val_x_and_y_and_width_and_height)
{
    return Qnil;
}

/**
 * Graphics3Dクラスのメンバー関数のRubyへの登録.
 */
void register_Graphics3D (VALUE rb_cGraphics3D)
{
    rb_define_const (rb_cGraphics3D, "ANTIALIAS",  INT2FIX(Graphics3D::ANTIALIAS));
    rb_define_const (rb_cGraphics3D, "DITHER",     INT2FIX(Graphics3D::DITHER));
    rb_define_const (rb_cGraphics3D, "OVERWRITE",  INT2FIX(Graphics3D::OVERWRITE));
    rb_define_const (rb_cGraphics3D, "TRUE_COLOR", INT2FIX(Graphics3D::TRUE_COLOR));

    rb_define_alloc_func (rb_cGraphics3D, ruby_Graphics3D_allocate);
    rb_define_private_method (rb_cGraphics3D, "initialize", (VALUE(*)(...))ruby_Graphics3D_initialize, 0);

    rb_define_method (rb_cGraphics3D, "add_light",          (VALUE(*)(...))ruby_Graphics3D_add_light, 2);
    rb_define_method (rb_cGraphics3D, "bind_target",        (VALUE(*)(...))ruby_Graphics3D_bind_target, 1);
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
    rb_define_method (rb_cGraphics3D, "render",             (VALUE(*)(...))ruby_Graphics3D_render, 5);
    rb_define_method (rb_cGraphics3D, "reset_lights",       (VALUE(*)(...))ruby_Graphics3D_reset_lights, 0);
    rb_define_method (rb_cGraphics3D, "camera=",            (VALUE(*)(...))ruby_Graphics3D_set_camera, 1);
    rb_define_method (rb_cGraphics3D, "depth_range=",       (VALUE(*)(...))ruby_Graphics3D_set_depth_range, 1);
    rb_define_method (rb_cGraphics3D, "light=",             (VALUE(*)(...))ruby_Graphics3D_set_light, 1);
    rb_define_method (rb_cGraphics3D, "viewport=",          (VALUE(*)(...))ruby_Graphics3D_set_viewport, 1);

}
