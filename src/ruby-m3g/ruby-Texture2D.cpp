#include <iostream>
#include "ruby.h"
#include "ruby-m3g.hpp"
#include "m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
    struct FilterAccessor {
        Texture2D* texture2D;
    };
    struct WrappingAccessor {
        Texture2D* texture2D;
    };
    VALUE rb_cTexture2D_FilterAccessor;
    VALUE rb_cTexture2D_WrappingAccessor;
}


VALUE ruby_Texture2D_free (Texture2D* ptr)
{
    __TRY__;
    ptr->~Texture2D ();
    __CATCH__;
    ruby_xfree (ptr);
}

VALUE ruby_Texture2D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Texture2D));
    return Data_Wrap_Struct (self, 0, ruby_Texture2D_free, p);
}

VALUE ruby_Texture2D_initialize (VALUE self, VALUE val_image)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    Image2D*   img;
    Data_Get_Struct (val_image, Image2D, img);
    __TRY__;
    new (p) Texture2D (img);
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Texture2D_get_blend_color (VALUE self)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    int argb;
    __TRY__;
    argb = p->getBlendColor ();
    __CATCH__;
    return INT2NUM(argb);
}

VALUE ruby_Texture2D_get_blending (VALUE self)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    int mode;
    __TRY__;
    mode = p->getBlending();
    __CATCH__;
    return INT2NUM(mode);
}

VALUE ruby_Texture2D_get_filter (VALUE self)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    FilterAccessor* accessor;
    VALUE       val_accessor = Data_Make_Struct (rb_cTexture2D_FilterAccessor, FilterAccessor, 0, -1, accessor);
    accessor->texture2D = p;
    return val_accessor;
}

VALUE ruby_Texture2D_get_image (VALUE self)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    Image2D* img;
    __TRY__;
    img = p->getImage ();
    __CATCH__;
    return img ? (VALUE)img->getExportedEntity() : Qnil;
}


VALUE ruby_Texture2D_get_wrapping (VALUE self)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    WrappingAccessor* accessor;
    VALUE         val_accessor = Data_Make_Struct (rb_cTexture2D_WrappingAccessor, WrappingAccessor, 0, -1, accessor);
    accessor->texture2D = p;     
    return val_accessor;
}

VALUE ruby_Texture2D_set_blend_color (VALUE self, VALUE val_rgb)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    int rgb = NUM2INT(val_rgb);
    __TRY__;
    p->setBlendColor (rgb);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Texture2D_set_blending (VALUE self, VALUE val_func)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    int func = NUM2INT (val_func);
    __TRY__;
    p->setBlending (func);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Texture2D_set_filtering (VALUE self, VALUE val_filter)
{
    VALUE val_level = rb_ary_entry(val_filter, 0);
    VALUE val_image = rb_ary_entry(val_filter, 1);
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    int level = NUM2INT (val_level);
    int image = NUM2INT (val_image);
    __TRY__;
    p->setFiltering (level, image);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Texture2D_set_image (VALUE self, VALUE val_image)
{
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    Image2D*   img;
    Data_Get_Struct (val_image, Image2D, img);
    __TRY__;
    p->setImage (img);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Texture2D_set_wrapping (VALUE self, VALUE val_wrapping)
{
    VALUE val_wrap_s = rb_ary_entry (val_wrapping, 0);
    VALUE val_wrap_t = rb_ary_entry (val_wrapping, 1);
    Texture2D* p;
    Data_Get_Struct (self, Texture2D, p);
    int wrap_s = NUM2INT (val_wrap_s);
    int wrap_t = NUM2INT (val_wrap_t);
    __TRY__;
    p->setWrapping (wrap_s,wrap_t);
    __CATCH__;
    return Qnil;
}

/**
 *  Texture2D::FilterAccessor
 */

VALUE ruby_Texture2D_FilterAccessor_get_level (VALUE self)
{
    FilterAccessor* p;
    Data_Get_Struct (self, FilterAccessor, p);
    int level;
    __TRY__;
    level = p->texture2D->getLevelFilter ();
    __CATCH__;
    return INT2NUM(level);
}

VALUE ruby_Texture2D_FilterAccessor_get_image (VALUE self)
{
    FilterAccessor* p;
    Data_Get_Struct (self, FilterAccessor, p);
	int image;
    __TRY__;
    image = p->texture2D->getImageFilter ();
    __CATCH__;
    return INT2NUM(image);
}

/**
 *  Texture2D::WrappingAccessor
 */

VALUE ruby_Texture2D_WrappingAccessor_get_s (VALUE self)
{
    WrappingAccessor* p;
    Data_Get_Struct (self, WrappingAccessor, p);
	int wrap_s;
    __TRY__;
    wrap_s = p->texture2D->getWrappingS ();
    __CATCH__;
    return INT2NUM(wrap_s);
}

VALUE ruby_Texture2D_WrappingAccessor_get_t (VALUE self)
{
    WrappingAccessor* p;
    Data_Get_Struct (self, WrappingAccessor, p);
	int wrap_t;
    __TRY__;
    wrap_t = p->texture2D->getWrappingT ();
    __CATCH__;
    return INT2NUM(wrap_t);
}

void register_Texture2D ()
{
    // Texture2D
    rb_cTexture2D           = rb_define_class_under (rb_mM3G, "Texture2D",           rb_cTransformable);

	rb_define_const (rb_cTexture2D, "FILTER_BASE_LEVEL", INT2NUM(Texture2D::FILTER_BASE_LEVEL));
    rb_define_const (rb_cTexture2D, "FILTER_LINEAR",     INT2NUM(Texture2D::FILTER_LINEAR));
    rb_define_const (rb_cTexture2D, "FILTER_NEAREST",    INT2NUM(Texture2D::FILTER_NEAREST));
    rb_define_const (rb_cTexture2D, "FUNC_ADD",          INT2NUM(Texture2D::FUNC_ADD));
    rb_define_const (rb_cTexture2D, "FUNC_BLEND",        INT2NUM(Texture2D::FUNC_BLEND));
    rb_define_const (rb_cTexture2D, "FUNC_DECAL",        INT2NUM(Texture2D::FUNC_DECAL));
    rb_define_const (rb_cTexture2D, "FUNC_MODULATE",     INT2NUM(Texture2D::FUNC_MODULATE));
    rb_define_const (rb_cTexture2D, "FUNC_REPLACE",      INT2NUM(Texture2D::FUNC_REPLACE));
    rb_define_const (rb_cTexture2D, "WRAP_CLAMP",        INT2NUM(Texture2D::WRAP_CLAMP));
    rb_define_const (rb_cTexture2D, "WRAP_REPEAT",       INT2NUM(Texture2D::WRAP_REPEAT));

    rb_define_alloc_func (rb_cTexture2D, ruby_Texture2D_allocate);
    rb_define_private_method (rb_cTexture2D, "initialize", (VALUE(*)(...))ruby_Texture2D_initialize, 1);

    rb_define_method (rb_cTexture2D, "blend_color",   (VALUE(*)(...))ruby_Texture2D_get_blend_color, 0);
    rb_define_method (rb_cTexture2D, "blending",      (VALUE(*)(...))ruby_Texture2D_get_blending,    0);
    rb_define_method (rb_cTexture2D, "filter",        (VALUE(*)(...))ruby_Texture2D_get_filter,      0);
    rb_define_method (rb_cTexture2D, "image",         (VALUE(*)(...))ruby_Texture2D_get_image,       0);
    rb_define_method (rb_cTexture2D, "wrapping",      (VALUE(*)(...))ruby_Texture2D_get_wrapping,    0);
    rb_define_method (rb_cTexture2D, "blend_color=",  (VALUE(*)(...))ruby_Texture2D_set_blend_color, 1);
    rb_define_method (rb_cTexture2D, "blending=",     (VALUE(*)(...))ruby_Texture2D_set_blending,    1);
    rb_define_method (rb_cTexture2D, "filtering=",    (VALUE(*)(...))ruby_Texture2D_set_filtering,   1);
    rb_define_method (rb_cTexture2D, "image=",        (VALUE(*)(...))ruby_Texture2D_set_image,       1);
    rb_define_method (rb_cTexture2D, "wrapping=",     (VALUE(*)(...))ruby_Texture2D_set_wrapping,    1);

    // FilterAccessoring
    rb_cTexture2D_FilterAccessor = rb_define_class_under (rb_cTexture2D, "FilterAccessor", rb_cObject);

    rb_define_method (rb_cTexture2D_FilterAccessor, "level",      (VALUE(*)(...))ruby_Texture2D_FilterAccessor_get_level, 0);
    rb_define_method (rb_cTexture2D_FilterAccessor, "image",      (VALUE(*)(...))ruby_Texture2D_FilterAccessor_get_image, 0);


    // WrappingAccessor
    rb_cTexture2D_WrappingAccessor = rb_define_class_under (rb_cTexture2D, "WrappingAccessor", rb_cObject);

    rb_define_method (rb_cTexture2D_WrappingAccessor, "s",      (VALUE(*)(...))ruby_Texture2D_WrappingAccessor_get_s, 0);
    rb_define_method (rb_cTexture2D_WrappingAccessor, "t",      (VALUE(*)(...))ruby_Texture2D_WrappingAccessor_get_t, 0);
}
