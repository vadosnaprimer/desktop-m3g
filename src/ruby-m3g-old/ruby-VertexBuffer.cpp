#include <new>
#include "ruby.h"
#include "VertexBuffer.hpp"
using namespace m3g;

VALUE ruby_VertexBuffer_free (VertexBuffer* ptr)
{
    ptr->~VertexBuffer ();
    ruby_xfree (ptr);
}

VALUE ruby_VertexBuffer_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(VertexBuffer));
    return Data_Wrap_Struct (self, NULL, ruby_VertexBuffer_free, p);
}

VALUE ruby_VertexBuffer_initialize (VALUE self)
{
    VertexBuffer* p;
    Data_Get_Struct (self, VertexBuffer, p);
    new (p) VertexBuffer;
    return Qnil;
}

VALUE ruby_VertexBuffer_get_colors (VALUE self)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_get_default_color (VALUE self)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_get_normals (VALUE self)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_get_positions (VALUE self)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_get_tex_coords (VALUE self)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_set_colors (VALUE self, VALUE val_colors)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_set_default_color (VALUE self, VALUE val_rgb)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_set_normals (VALUE self, VALUE val_normals)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_set_positions (VALUE self, VALUE val_positions_and_scale_and_bias)
{
    return Qnil;
}

VALUE ruby_VertexBuffer_set_tex_coords (VALUE self, VALUE val_index_and_tex_coord_and_scale_and_bias)
{
    return Qnil;
}


void register_VertexBuffer (VALUE rb_cVertexBuffer)
{
     // VertexBuffer
     rb_define_alloc_func (rb_cVertexBuffer, ruby_VertexBuffer_allocate);
     rb_define_private_method (rb_cVertexBuffer, "initialize", (VALUE(*)(...))ruby_VertexBuffer_initialize, 0);

     rb_define_method (rb_cVertexBuffer, "colors",        (VALUE(*)(...))ruby_VertexBuffer_get_colors,    0);
     rb_define_method (rb_cVertexBuffer, "default_color", (VALUE(*)(...))ruby_VertexBuffer_get_default_color, 0);
     rb_define_method (rb_cVertexBuffer, "normals",       (VALUE(*)(...))ruby_VertexBuffer_get_normals,   0);
     rb_define_method (rb_cVertexBuffer, "positions",     (VALUE(*)(...))ruby_VertexBuffer_get_positions, 0);
     rb_define_method (rb_cVertexBuffer, "tex_coords",    (VALUE(*)(...))ruby_VertexBuffer_get_tex_coords, 0);
     rb_define_method (rb_cVertexBuffer, "colors=",        (VALUE(*)(...))ruby_VertexBuffer_set_colors,    1);
     rb_define_method (rb_cVertexBuffer, "default_color=", (VALUE(*)(...))ruby_VertexBuffer_set_default_color, 1);
     rb_define_method (rb_cVertexBuffer, "normals=",       (VALUE(*)(...))ruby_VertexBuffer_set_normals,   1);
     rb_define_method (rb_cVertexBuffer, "positions=",     (VALUE(*)(...))ruby_VertexBuffer_set_positions, 1);
     rb_define_method (rb_cVertexBuffer, "tex_coords=",    (VALUE(*)(...))ruby_VertexBuffer_set_tex_coords, 1);
}
