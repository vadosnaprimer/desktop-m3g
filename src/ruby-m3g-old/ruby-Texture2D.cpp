#include <new>
#include "ruby.h"
#include "Texture2D.hpp"
using namespace m3g;


VALUE ruby_Texture2D_free (Texture2D* ptr)
{
    ptr->~Texture2D ();
    ruby_xfree (ptr);
}

VALUE ruby_Texture2D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Texture2D));
    return Data_Wrap_Struct (self, NULL, ruby_Texture2D_free, p);
}

VALUE ruby_Texture2D_initialize (VALUE self, VALUE val_image)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    new (p) Texture2D (0);
    return Qnil;
}

VALUE ruby_Texture2D_get_blend_color (VALUE self, VALUE val_getBlendColor)
{
    return Qnil;
}

VALUE ruby_Texture2D_get_blending (VALUE self, VALUE val_getBlending)
{
    return Qnil;
}

VALUE ruby_Texture2D_get_image (VALUE self, VALUE val_getImage)
{
    return Qnil;
}

VALUE ruby_Texture2D_get_image_filter (VALUE self)
{
    return Qnil;
}

VALUE ruby_Texture2D_get_level_filter (VALUE self)
{
    return Qnil;
}

VALUE ruby_Texture2D_get_wrapping (VALUE self)
{
    return Qnil;
}

VALUE ruby_Texture2D_set_blend_color (VALUE self, VALUE val_rgb)
{
    return Qnil;
}

VALUE ruby_Texture2D_set_blending (VALUE self, VALUE val_func)
{
    return Qnil;
}

VALUE ruby_Texture2D_set_filtering (VALUE self, VALUE val_level_filter_and_image_filter)
{
    return Qnil;
}

VALUE ruby_Texture2D_set_image (VALUE self, VALUE val_image)
{
    return Qnil;
}

VALUE ruby_Texture2D_set_wrapping (VALUE self, VALUE val_wrap_s_and_wrap_t)
{
    return Qnil;
}

void register_Texture2D (VALUE rb_cTexture2D)
{
     // Texture2D
     rb_define_const (rb_cTexture2D, "FILTER_BASE_LEVEL", INT2FIX(Texture2D::FILTER_BASE_LEVEL));
     rb_define_const (rb_cTexture2D, "FILTER_LINEAR",     INT2FIX(Texture2D::FILTER_LINEAR));
     rb_define_const (rb_cTexture2D, "FILTER_NEAREST",    INT2FIX(Texture2D::FILTER_NEAREST));
     rb_define_const (rb_cTexture2D, "FUNC_ADD",          INT2FIX(Texture2D::FUNC_ADD));
     rb_define_const (rb_cTexture2D, "FUNC_BLEND",        INT2FIX(Texture2D::FUNC_BLEND));
     rb_define_const (rb_cTexture2D, "FUNC_DECAL",        INT2FIX(Texture2D::FUNC_DECAL));
     rb_define_const (rb_cTexture2D, "FUNC_MODULATE",     INT2FIX(Texture2D::FUNC_MODULATE));
     rb_define_const (rb_cTexture2D, "FUNC_REPLACE",      INT2FIX(Texture2D::FUNC_REPLACE));
     rb_define_const (rb_cTexture2D, "WRAP_CLAMP",        INT2FIX(Texture2D::WRAP_CLAMP));
     rb_define_const (rb_cTexture2D, "WRAP_REPEAT",       INT2FIX(Texture2D::WRAP_REPEAT));

     rb_define_alloc_func (rb_cTexture2D, ruby_Texture2D_allocate);
     rb_define_private_method (rb_cTexture2D, "initialize", (VALUE(*)(...))ruby_Texture2D_initialize, 1);

     rb_define_method (rb_cTexture2D, "blend_color",  (VALUE(*)(...))ruby_Texture2D_get_blend_color, 0);
     rb_define_method (rb_cTexture2D, "blending",     (VALUE(*)(...))ruby_Texture2D_get_blending,    0);
     rb_define_method (rb_cTexture2D, "image_filter", (VALUE(*)(...))ruby_Texture2D_get_image_filter, 0);
     rb_define_method (rb_cTexture2D, "level_filter", (VALUE(*)(...))ruby_Texture2D_get_level_filter, 0);
     rb_define_method (rb_cTexture2D, "wrapping",     (VALUE(*)(...))ruby_Texture2D_get_wrapping, 0);
     rb_define_method (rb_cTexture2D, "blend_color=",  (VALUE(*)(...))ruby_Texture2D_set_blend_color, 1);
     rb_define_method (rb_cTexture2D, "blending=",     (VALUE(*)(...))ruby_Texture2D_set_blending,  1);
     rb_define_method (rb_cTexture2D, "filtering=",    (VALUE(*)(...))ruby_Texture2D_set_filtering, 1);
     rb_define_method (rb_cTexture2D, "image=",        (VALUE(*)(...))ruby_Texture2D_set_image,     1);
     rb_define_method (rb_cTexture2D, "wrapping=",     (VALUE(*)(...))ruby_Texture2D_set_wrapping,  1);


}
