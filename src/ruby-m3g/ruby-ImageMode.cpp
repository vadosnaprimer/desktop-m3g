#include <new>
#include "ruby.h"
#include "ImageMode.hpp"
using namespace m3g;


VALUE ruby_ImageMode_free (ImageMode* ptr)
{
    ptr->~ImageMode ();
    ruby_xfree (ptr);
}

VALUE ruby_ImageMode_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(ImageMode));
    return Data_Wrap_Struct (self, NULL, ruby_ImageMode_free, p);
}

VALUE ruby_ImageMode_initialize (VALUE self)
{
    ImageMode* p;
    Data_Get_Struct (self, ImageMode, p);
    new (p) ImageMode;
    return Qnil;
}

VALUE ruby_ImageMode_get_x (VALUE self)
{
    return Qnil;
}

VALUE ruby_ImageMode_get_y (VALUE self)
{
    return Qnil;
}


void register_ImageMode (VALUE rb_cImageMode)
{
    // ImageMode
    rb_define_alloc_func (rb_cImageMode, ruby_ImageMode_allocate);
    rb_define_private_method (rb_cImageMode, "initialize", (VALUE(*)(...))ruby_ImageMode_initialize, 0);

    rb_define_method (rb_cImageMode, "x",         (VALUE(*)(...))ruby_ImageMode_get_x, 0); 
    rb_define_method (rb_cImageMode, "y",         (VALUE(*)(...))ruby_ImageMode_get_y, 0); 


}
