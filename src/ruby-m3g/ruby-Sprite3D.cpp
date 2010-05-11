#include <new>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
    struct CropAccessor {
        Sprite3D* sprite3D;
    };
    VALUE rb_cSprite3D_CropAccessor;
}

VALUE ruby_Sprite3D_free (Sprite3D* ptr)
{
    __TRY__;
    ptr->~Sprite3D ();
    __CATCH__;
    ruby_xfree (ptr);
}

VALUE ruby_Sprite3D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Sprite3D));
    return Data_Wrap_Struct (self, 0, ruby_Sprite3D_free, p);
}

VALUE ruby_Sprite3D_initialize (VALUE self, VALUE val_scaled, VALUE val_image, VALUE val_appearance)
{
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    bool     scaled = (val_scaled == Qtrue) ? true : false;
    Image2D* img;
    Data_Get_Struct (val_image, Image2D, img);
    Appearance* app;
    Data_Get_Struct (val_appearance, Appearance, app);

    __TRY__;
    new (p) Sprite3D (scaled, img, app);
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Sprite3D_get_appearance (VALUE self)
{
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    Appearance* app;
    __TRY__;
    app = p->getAppearance ();
    __CATCH__;
    return app ? (VALUE)app->getExportedEntity() : Qnil;
}

VALUE ruby_Sprite3D_get_crop (VALUE self)
{
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    CropAccessor* accessor;
    VALUE     val_accessor = Data_Make_Struct (rb_cSprite3D_CropAccessor, CropAccessor, 0, -1, accessor);
    accessor->sprite3D = p;
    return val_accessor;
}

VALUE ruby_Sprite3D_get_image (VALUE self)
{
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    Image2D* img;
    __TRY__;
    img = p->getImage ();
    __CATCH__;
    return img ? (VALUE)img->getExportedEntity() : Qnil;
}

VALUE ruby_Sprite3D_is_scaled (VALUE self)
{
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    bool scaled;
    __TRY__;
    scaled = p->isScaled();
    __CATCH__;
    return scaled ? Qtrue : Qfalse;
}

VALUE ruby_Sprite3D_set_appearance (VALUE self, VALUE val_appearance)
{
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    Appearance* app;
    Data_Get_Struct (val_appearance, Appearance, app);
    __TRY__;
    p->setAppearance (app);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Sprite3D_set_crop (VALUE self, VALUE val_crop)
{
    VALUE val_x      = rb_ary_entry(val_crop, 0);
    VALUE val_y      = rb_ary_entry(val_crop, 1);
    VALUE val_width  = rb_ary_entry(val_crop, 2);
    VALUE val_height = rb_ary_entry(val_crop, 3);
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    float x      = NUM2DBL(val_x);
    float y      = NUM2DBL(val_y);
    float width  = NUM2DBL(val_width);
    float height = NUM2DBL(val_height);
    __TRY__;
    p->setCrop (x, y, width, height);
    __CATCH__;
    return Qnil;
}

VALUE ruby_Sprite3D_set_image (VALUE self, VALUE val_image)
{
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    Image2D*  img;
    Data_Get_Struct (val_image, Image2D, img);
    __TRY__;
    p->setImage (img);
    __CATCH__;
    return Qnil;
}

/**
 * Sprite3D::CropAccessor
 */

VALUE ruby_Sprite3D_CropAccessor_get_x (VALUE self)
{
    CropAccessor* p;
    Data_Get_Struct (self, CropAccessor, p);
    int x;
    __TRY__;
    x = p->sprite3D->getCropX ();
    __CATCH__;
    return INT2NUM(x);
}

VALUE ruby_Sprite3D_CropAccessor_get_y (VALUE self)
{
    CropAccessor* p;
    Data_Get_Struct (self, CropAccessor, p);
    int y;
    __TRY__;
    y = p->sprite3D->getCropY ();
    __CATCH__;
    return INT2NUM(y);
}

VALUE ruby_Sprite3D_CropAccessor_get_width (VALUE self)
{
    CropAccessor* p;
    Data_Get_Struct (self, CropAccessor, p);
    int width;
    __TRY__;
    width = p->sprite3D->getCropWidth ();
    __CATCH__;
    return INT2NUM(width);
}

VALUE ruby_Sprite3D_CropAccessor_get_height (VALUE self)
{
    CropAccessor* p;
    Data_Get_Struct (self, CropAccessor, p);
    int height;
    __TRY__;
    height = p->sprite3D->getCropHeight ();
    __CATCH__;
    return INT2NUM(height);
}


void register_Sprite3D ()
{
    // Sprite3D
    rb_cSprite3D            = rb_define_class_under (rb_mM3G, "Sprite3D",            rb_cNode);

    rb_define_alloc_func (rb_cSprite3D, ruby_Sprite3D_allocate);
    rb_define_private_method (rb_cSprite3D, "initialize", (VALUE(*)(...))ruby_Sprite3D_initialize, 3);

    rb_define_method (rb_cSprite3D, "appearance",  (VALUE(*)(...))ruby_Sprite3D_get_appearance, 0);
    rb_define_method (rb_cSprite3D, "crop",        (VALUE(*)(...))ruby_Sprite3D_get_crop,       0);
    rb_define_method (rb_cSprite3D, "image",       (VALUE(*)(...))ruby_Sprite3D_get_image,      0);
    rb_define_method (rb_cSprite3D, "scaled?",     (VALUE(*)(...))ruby_Sprite3D_is_scaled,      0);
    rb_define_method (rb_cSprite3D, "appearance=", (VALUE(*)(...))ruby_Sprite3D_set_appearance, 1);
    rb_define_method (rb_cSprite3D, "crop=",       (VALUE(*)(...))ruby_Sprite3D_set_crop,       1);
    rb_define_method (rb_cSprite3D, "image=",      (VALUE(*)(...))ruby_Sprite3D_set_image,      1);

    // Srpte3D::CropAccessor
    rb_cSprite3D_CropAccessor = rb_define_class_under (rb_cSprite3D, "CropAccessor", rb_cObject);

    rb_define_method (rb_cSprite3D_CropAccessor, "x",      (VALUE(*)(...))ruby_Sprite3D_CropAccessor_get_x,      0);
    rb_define_method (rb_cSprite3D_CropAccessor, "y",      (VALUE(*)(...))ruby_Sprite3D_CropAccessor_get_y,      0);
    rb_define_method (rb_cSprite3D_CropAccessor, "width",  (VALUE(*)(...))ruby_Sprite3D_CropAccessor_get_width,  0);
    rb_define_method (rb_cSprite3D_CropAccessor, "height", (VALUE(*)(...))ruby_Sprite3D_CropAccessor_get_height, 0);
}
