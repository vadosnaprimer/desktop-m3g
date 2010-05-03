#include <new>
#include "ruby.h"
#include "TextureCoord2D.hpp"
using namespace m3g;


VALUE ruby_TextureCoord2D_free (TextureCoord2D* ptr)
{
    ptr->~TextureCoord2D ();
    ruby_xfree (ptr);
}

VALUE ruby_TextureCoord2D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(TextureCoord2D));
    return Data_Wrap_Struct (self, NULL, ruby_TextureCoord2D_free, p);
}

VALUE ruby_TextureCoord2D_initialize (VALUE self)
{
    TextureCoord2D* p;
    Data_Get_Struct (self, TextureCoord2D, p);
    new (p) TextureCoord2D;
    return Qnil;
}

VALUE ruby_TextureCoord2D_get_s (VALUE self)
{
    return Qnil;
}

VALUE ruby_TextureCoord2D_get_t (VALUE self)
{
    return Qnil;
}

void register_TextureCoord2D (VALUE rb_cTextureCoord2D)
{
    // TextureCoord2D
    rb_define_alloc_func (rb_cTextureCoord2D, ruby_TextureCoord2D_allocate);
    rb_define_private_method (rb_cTextureCoord2D, "initialize", (VALUE(*)(...))ruby_TextureCoord2D_initialize, 0);

    rb_define_method (rb_cTextureCoord2D, "s",         (VALUE(*)(...))ruby_TextureCoord2D_get_s, 0); 
    rb_define_method (rb_cTextureCoord2D, "t",         (VALUE(*)(...))ruby_TextureCoord2D_get_t, 0); 

}
