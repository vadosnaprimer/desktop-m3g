#include <new>
#include "ruby.h"
#include "Transformable.hpp"
using namespace m3g;

VALUE ruby_Transformable_free (Transformable* ptr)
{
    ptr->~Transformable ();
    ruby_xfree (ptr);
}

VALUE ruby_Transformable_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Transformable));
    return Data_Wrap_Struct (self, NULL, ruby_Transformable_free, p);
}

VALUE ruby_Transformable_initialize (VALUE self)
{
    Transformable* p;
    Data_Get_Struct (self, Transformable, p);
    new (p) Transformable;
    return Qnil;
}

VALUE ruby_Transformable_get_composite_transform (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transformable_get_orientation (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transformable_get_scale (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transformable_get_transform (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transformable_get_translation (VALUE self)
{
    return Qnil;
}

VALUE ruby_Transformable_post_rotate (VALUE self, VALUE val_angle, VALUE val_ax, VALUE val_ay, VALUE val_az)
{
    return Qnil;
}

VALUE ruby_Transformable_pre_rotate (VALUE self, VALUE val_angle, VALUE val_ax, VALUE val_ay, VALUE val_az)
{
    return Qnil;
}

VALUE ruby_Transformable_scale (VALUE self, VALUE val_sx, VALUE val_sy, VALUE val_sz)
{
    return Qnil;
}

VALUE ruby_Transformable_set_orientation (VALUE self,  VALUE val_angle_and_ax_and_ay_and_az)
{
    return Qnil;
}

VALUE ruby_Transformable_set_scale (VALUE self, VALUE val_sx_and_sy_and_sz)
{
    return Qnil;
}

VALUE ruby_Transformable_set_transform (VALUE self, VALUE val_tranform)
{
    return Qnil;
}

VALUE ruby_Transformable_translate (VALUE self, VALUE val_tx_and_ty_and_tz)
{
    return Qnil;
}

void register_Transformable (VALUE rb_cTransformable)
{
     // Transformable
     rb_define_alloc_func (rb_cTransformable, ruby_Transformable_allocate);
     rb_define_private_method (rb_cTransformable, "initialize", (VALUE(*)(...))ruby_Transformable_initialize, 0);

     rb_define_method (rb_cTransformable, "composite_transform", (VALUE(*)(...))ruby_Transformable_get_composite_transform, 0);
     rb_define_method (rb_cTransformable, "orientation",         (VALUE(*)(...))ruby_Transformable_get_orientation, 0);
     rb_define_method (rb_cTransformable, "scale",               (VALUE(*)(...))ruby_Transformable_get_scale, 0);
     rb_define_method (rb_cTransformable, "transform",           (VALUE(*)(...))ruby_Transformable_get_transform, 0);
     rb_define_method (rb_cTransformable, "translation",         (VALUE(*)(...))ruby_Transformable_get_translation, 0);
     rb_define_method (rb_cTransformable, "post_rotate",         (VALUE(*)(...))ruby_Transformable_post_rotate, 4);
     rb_define_method (rb_cTransformable, "pre_rotate",          (VALUE(*)(...))ruby_Transformable_pre_rotate, 4);
     rb_define_method (rb_cTransformable, "scale",               (VALUE(*)(...))ruby_Transformable_scale, 3);
     rb_define_method (rb_cTransformable, "orientation=",        (VALUE(*)(...))ruby_Transformable_set_orientation, 1);
     rb_define_method (rb_cTransformable, "scale=",              (VALUE(*)(...))ruby_Transformable_set_scale, 1);
     rb_define_method (rb_cTransformable, "transform=",          (VALUE(*)(...))ruby_Transformable_set_transform, 1);
     rb_define_method (rb_cTransformable, "translate",           (VALUE(*)(...))ruby_Transformable_translate, 1);


}
