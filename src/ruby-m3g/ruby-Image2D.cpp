#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


VALUE ruby_Image2D_free (Image2D* ptr)
{
    __TRY__;
    ptr->~Image2D ();
    __CATCH__;
    ruby_xfree (ptr);
}

VALUE ruby_Image2D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Image2D));
    return Data_Wrap_Struct (self, 0, ruby_Image2D_free, p);
}

VALUE ruby_Image2D_initialize (int argc, VALUE* argv, VALUE self)
{
    Image2D* p;
    Data_Get_Struct (self, Image2D, p);

    VALUE val_arg1, val_arg2, val_arg3, val_arg4, val_arg5;
    int num = rb_scan_args (argc, argv, "32", &val_arg1, &val_arg2, &val_arg3, &val_arg4, &val_arg5);

    switch (num) {
    case 3: {
        int format = NUM2INT (val_arg1);
        int width  = NUM2INT (val_arg2);
        int height = NUM2INT (val_arg3);
        __TRY__;
        new (p) Image2D (format, width, height);
        __CATCH__;
        break;
    }
    case 4: {
        int format = NUM2INT (val_arg1);
        int width  = NUM2INT (val_arg2);
        int height = NUM2INT (val_arg3);
        void* image = (void*)StringValue (val_arg4);
        __TRY__;
        new (p) Image2D (format, width, height, image);
        __CATCH__;
        break;
    }
    case 5: {
        int format = NUM2INT (val_arg1);
        int width = NUM2INT (val_arg2);
        int height = NUM2INT (val_arg3);
        void* image = (void*)StringValue (val_arg4);
        void* palette = (void*)StringValue (val_arg5);
        __TRY__;
        new (p) Image2D (format, width, height, image, palette);
        __CATCH__;
        break;
    }
    default: {
        // エラー
    }
    }

    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Image2D_get_format (VALUE self)
{
    Image2D* p;
    Data_Get_Struct (self, Image2D, p);
    int format;
    __TRY__;
    format = p->getFormat ();
    __CATCH__;
    return INT2NUM(format);
}

VALUE ruby_Image2D_get_height (VALUE self)
{
    Image2D* p;
    Data_Get_Struct (self, Image2D, p);
    int height;
    __TRY__;
    height = p->getHeight ();
    __CATCH__;
    return INT2NUM(height);
}

VALUE ruby_Image2D_get_width (VALUE self)
{
    Image2D* p;
    Data_Get_Struct (self, Image2D, p);
    int width;
    __TRY__;
    width = p->getWidth ();
    __CATCH__;
    return INT2NUM(width);
}

VALUE ruby_Image2D_is_mutable (VALUE self)
{
    Image2D* p;
    Data_Get_Struct (self, Image2D, p);
    bool mutabl;
    __TRY__;
    mutabl = p->isMutable();
    __CATCH__;
    return mutabl ? Qtrue : Qfalse;
}

VALUE ruby_Image2D_set_image (VALUE self, VALUE val_index, VALUE val_image)
{
    VALUE val_x      = rb_ary_entry(val_index, 0);
    VALUE val_y      = rb_ary_entry(val_index, 1);
    VALUE val_width  = rb_ary_entry(val_index, 2);
    VALUE val_height = rb_ary_entry(val_index, 3);
    Image2D* p;
    Data_Get_Struct (self, Image2D, p);
    int x      = NUM2INT (val_x);
    int y      = NUM2INT (val_y);
    int width  = NUM2INT (val_width);
    int height = NUM2INT (val_height);
    void* image = (void*)StringValue (val_image);
    __TRY__;
    p->set (x, y, width, height, image);
    __CATCH__;
    return Qnil;
}

void register_Image2D ()
{
    // Image2D
    rb_cImage2D = rb_define_class_under (rb_mM3G, "Image2D",             rb_cObject3D);

    rb_define_const (rb_cImage2D, "ALPHA",           INT2NUM(Image2D::ALPHA));
    rb_define_const (rb_cImage2D, "LUMINANCE",       INT2NUM(Image2D::LUMINANCE));
    rb_define_const (rb_cImage2D, "LUMINANCE_ALPHA", INT2NUM(Image2D::LUMINANCE_ALPHA));
    rb_define_const (rb_cImage2D, "RGB",             INT2NUM(Image2D::RGB));
    rb_define_const (rb_cImage2D, "RGBA",            INT2NUM(Image2D::RGBA));

    rb_define_alloc_func (rb_cImage2D, ruby_Image2D_allocate);
    rb_define_private_method (rb_cImage2D, "initialize", (VALUE(*)(...))ruby_Image2D_initialize, -1);

    rb_define_method (rb_cImage2D, "format",   (VALUE(*)(...))ruby_Image2D_get_format, 0);
    rb_define_method (rb_cImage2D, "height",   (VALUE(*)(...))ruby_Image2D_get_height, 0);
    rb_define_method (rb_cImage2D, "width",    (VALUE(*)(...))ruby_Image2D_get_width,  0);
    rb_define_method (rb_cImage2D, "mutable?", (VALUE(*)(...))ruby_Image2D_is_mutable, 0);
    rb_define_method (rb_cImage2D, "[]=",      (VALUE(*)(...))ruby_Image2D_set_image,  2);
}
