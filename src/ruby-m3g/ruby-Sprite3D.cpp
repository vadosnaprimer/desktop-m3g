#include <new>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  VALUE rb_cSprite3D_CropRect;
}

VALUE ruby_Sprite3D_free (Sprite3D* ptr)
{
    ptr->~Sprite3D ();
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
    bool scaled;
    Image2D* img;
    Appearance* app;

    Data_Get_Struct (self, Sprite3D, p);
    scaled = (val_scaled == Qtrue) ? true : false;
    Data_Get_Struct (val_image, Image2D, img);
    Data_Get_Struct (val_appearance, Appearance, app);

    new (p) Sprite3D (scaled, img, app);
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Sprite3D_get_appearance (VALUE self)
{
  Sprite3D* p;
  Appearance* app;

  Data_Get_Struct (self, Sprite3D, p);
  app = p->getAppearance ();
  
  return (VALUE)app->getExportedEntity();
}

VALUE ruby_Sprite3D_get_crop (VALUE self)
{
  Sprite3D* p;
  Sprite3D::CropRect* crop;
  VALUE val_crop;

  Data_Get_Struct (self, Sprite3D, p);
  val_crop = Data_Make_Struct (rb_cSprite3D_CropRect, Sprite3D::CropRect, 0, -1, crop);
  
  crop->x = p->getCropX();
  crop->y = p->getCropY();
  crop->width = p->getCropWidth ();
  crop->height = p->getCropHeight ();

  return val_crop;
}

VALUE ruby_Sprite3D_get_image (VALUE self)
{
  Sprite3D* p;
  Image2D* img;

  Data_Get_Struct (self, Sprite3D, p);
  img = p->getImage ();

  if (img)
    return (VALUE)img->getExportedEntity();
  else
    return Qnil;
}

VALUE ruby_Sprite3D_is_scaled (VALUE self)
{
  Sprite3D* p;
  bool scaled;
  Data_Get_Struct (self, Sprite3D, p);
  scaled = p->isScaled();

  return scaled ? Qtrue : Qfalse;
}

VALUE ruby_Sprite3D_set_appearance (VALUE self, VALUE val_appearance)
{
  Sprite3D* p;
  Appearance* app;

  Data_Get_Struct (self, Sprite3D, p);
  Data_Get_Struct (val_appearance, Appearance, app);

  p->setAppearance (app);

  return Qnil;
}

VALUE ruby_Sprite3D_set_crop (VALUE self, VALUE val_crop)
{
  Sprite3D* p;
  Sprite3D::CropRect* crop;

  Data_Get_Struct (self, Sprite3D, p);
  Data_Get_Struct (val_crop, Sprite3D::CropRect, crop);

  p->setCrop (crop->x, crop->y, crop->width, crop->height);
  
  return Qnil;
}

VALUE ruby_Sprite3D_set_image (VALUE self, VALUE val_image)
{
  Sprite3D* p;
  Image2D*    img;
  Data_Get_Struct (self, Sprite3D, p);
  Data_Get_Struct (val_image, Image2D, img);
  p->setImage (img);
    return Qnil;
}

/**
 * Sprite3D::CropRect
 */

VALUE ruby_Sprite3D_CropRect_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(Sprite3D::CropRect));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Sprite3D_CropRect_initialize (VALUE self, VALUE val_x, VALUE val_y, VALUE val_width, VALUE val_height)
{
  Sprite3D::CropRect* p;
    Data_Get_Struct (self, Sprite3D::CropRect, p);
    p->x = FIX2INT (val_x);
    p->y = FIX2INT (val_y);
    p->width = FIX2INT (val_width);
    p->height = FIX2INT (val_height);
    return self;
}

VALUE ruby_Sprite3D_CropRect_get_x (VALUE self)
{
  Sprite3D::CropRect* p;
    Data_Get_Struct (self, Sprite3D::CropRect, p);
    return INT2FIX(p->x);
}

VALUE ruby_Sprite3D_CropRect_get_y (VALUE self)
{
  Sprite3D::CropRect* p;
    Data_Get_Struct (self, Sprite3D::CropRect, p);
    return INT2FIX(p->y);
}

VALUE ruby_Sprite3D_CropRect_get_width (VALUE self)
{
  Sprite3D::CropRect* p;
    Data_Get_Struct (self, Sprite3D::CropRect, p);
    return INT2FIX(p->width);
}

VALUE ruby_Sprite3D_CropRect_get_height (VALUE self)
{
  Sprite3D::CropRect* p;
    Data_Get_Struct (self, Sprite3D::CropRect, p);
    return INT2FIX(p->height);
}


void register_Sprite3D (VALUE rb_cSprite3D)
{
     // Sprite3D
     rb_define_alloc_func (rb_cSprite3D, ruby_Sprite3D_allocate);
     rb_define_private_method (rb_cSprite3D, "initialize", (VALUE(*)(...))ruby_Sprite3D_initialize, 3);

     rb_define_method (rb_cSprite3D, "appearance",  (VALUE(*)(...))ruby_Sprite3D_get_appearance, 0);
     rb_define_method (rb_cSprite3D, "crop",        (VALUE(*)(...))ruby_Sprite3D_get_crop, 0);
     rb_define_method (rb_cSprite3D, "image",       (VALUE(*)(...))ruby_Sprite3D_get_image, 0);
     rb_define_method (rb_cSprite3D, "scaled?",     (VALUE(*)(...))ruby_Sprite3D_is_scaled, 0);
     rb_define_method (rb_cSprite3D, "appearance=", (VALUE(*)(...))ruby_Sprite3D_set_appearance, 1);
     rb_define_method (rb_cSprite3D, "crop=",       (VALUE(*)(...))ruby_Sprite3D_set_crop,  1);
     rb_define_method (rb_cSprite3D, "image=",      (VALUE(*)(...))ruby_Sprite3D_set_image, 1);

     // Srpte3D::CropRect
     rb_cSprite3D_CropRect = rb_define_class_under (rb_cSprite3D, "CropRect", rb_cObject);
     rb_define_alloc_func (rb_cSprite3D_CropRect, ruby_Sprite3D_CropRect_allocate);
     rb_define_private_method (rb_cSprite3D_CropRect, "initialize", (VALUE(*)(...))ruby_Sprite3D_CropRect_initialize, 4);

     rb_define_method (rb_cSprite3D_CropRect, "x",      (VALUE(*)(...))ruby_Sprite3D_CropRect_get_x, 0);
     rb_define_method (rb_cSprite3D_CropRect, "y",      (VALUE(*)(...))ruby_Sprite3D_CropRect_get_y, 0);
     rb_define_method (rb_cSprite3D_CropRect, "width",  (VALUE(*)(...))ruby_Sprite3D_CropRect_get_width, 0);
     rb_define_method (rb_cSprite3D_CropRect, "height", (VALUE(*)(...))ruby_Sprite3D_CropRect_get_height, 0);
}
