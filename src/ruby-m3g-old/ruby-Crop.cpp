#include <new>
#include "ruby.h"
#include "Crop.hpp"
using namespace m3g;


VALUE ruby_Crop_free (Crop* ptr)
{
    ptr->~Crop ();
    ruby_xfree (ptr);
}

VALUE ruby_Crop_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Crop));
    return Data_Wrap_Struct (self, NULL, ruby_Crop_free, p);
}

VALUE ruby_Crop_initialize (VALUE self)
{
    Crop* p;
    Data_Get_Struct (self, Crop, p);
    new (p) Crop;
    return Qnil;
}

VALUE ruby_Crop_get_x (VALUE self)
{
    return Qnil;
}

VALUE ruby_Crop_get_y (VALUE self)
{
    return Qnil;
}

VALUE ruby_Crop_get_width (VALUE self)
{
    return Qnil;
}

VALUE ruby_Crop_get_height (VALUE self)
{
    return Qnil;
}

void register_Crop (VALUE rb_cCrop)
{
    // Crop
    rb_define_alloc_func (rb_cCrop, ruby_Crop_allocate);
    rb_define_private_method (rb_cCrop, "initialize", (VALUE(*)(...))ruby_Crop_initialize, 0);

    rb_define_method (rb_cCrop, "x",         (VALUE(*)(...))ruby_Crop_get_x, 0); 
    rb_define_method (rb_cCrop, "y",         (VALUE(*)(...))ruby_Crop_get_y, 0); 
    rb_define_method (rb_cCrop, "width",     (VALUE(*)(...))ruby_Crop_get_width, 0);
    rb_define_method (rb_cCrop, "height",    (VALUE(*)(...))ruby_Crop_get_height, 0);


}
