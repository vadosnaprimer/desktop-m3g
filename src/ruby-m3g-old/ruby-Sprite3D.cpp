#include <new>
#include "ruby.h"
#include "Sprite3D.hpp"
using namespace m3g;

VALUE ruby_Sprite3D_free (Sprite3D* ptr)
{
    ptr->~Sprite3D ();
    ruby_xfree (ptr);
}

VALUE ruby_Sprite3D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Sprite3D));
    return Data_Wrap_Struct (self, NULL, ruby_Sprite3D_free, p);
}

VALUE ruby_Sprite3D_initialize (VALUE self, VALUE val_scaled, VALUE val_image, VALUE val_appearance)
{
    Sprite3D* p;
    Data_Get_Struct (self, Sprite3D, p);
    new (p) Sprite3D (0,0,0);
    return Qnil;
}

VALUE ruby_Sprite3D_get_appearance (VALUE self)
{
    return Qnil;
}

VALUE ruby_Sprite3D_get_crop (VALUE self)
{
    // retrun x,y,width,height
    return Qnil;
}

VALUE ruby_Sprite3D_get_image (VALUE self)
{
    return Qnil;
}

VALUE ruby_Sprite3D_is_scaled (VALUE self)
{
    return Qnil;
}

VALUE ruby_Sprite3D_set_appearance (VALUE self, VALUE val_appearance)
{
    return Qnil;
}

VALUE ruby_Sprite3D_set_crop (VALUE self, VALUE val_x_and_y_and_width_height)
{
    return Qnil;
}

VALUE ruby_Sprite3D_set_image (VALUE self, VALUE val_image)
{
    return Qnil;
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

}
