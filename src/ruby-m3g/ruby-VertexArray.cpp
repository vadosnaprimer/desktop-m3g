#include <new>
#include "ruby.h"
#include "VertexArray.hpp"
using namespace m3g;

VALUE ruby_VertexArray_free (VertexArray* ptr)
{
    ptr->~VertexArray ();
    ruby_xfree (ptr);
}

VALUE ruby_VertexArray_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(VertexArray));
    return Data_Wrap_Struct (self, NULL, ruby_VertexArray_free, p);
}

VALUE ruby_VertexArray_initialize (VALUE self, VALUE val_num_vertices, VALUE val_num_components, VALUE val_component_size)
{
    VertexArray* p;
    Data_Get_Struct (self, VertexArray, p);
    new (p) VertexArray (0,0,0);
    return Qnil;
}

VALUE ruby_VertexArray_get (VALUE self, VALUE first_vertex, VALUE num_vertices, VALUE val_values)
{
    return Qnil;
}

VALUE ruby_VertexArray_get_component_count (VALUE self)
{
    return Qnil;
}

VALUE ruby_VertexArray_get_component_type (VALUE self)
{
    return Qnil;
}

VALUE ruby_VertexArray_get_vertex_count (VALUE self)
{
    return Qnil;
}

VALUE ruby_VertexArray_set (VALUE self, VALUE val_first_vertex, VALUE val_num_vertices, VALUE val_values)
{
    return Qnil;
}

void register_VertexArray (VALUE rb_cVertexArray)
{
     // VertexArray
     rb_define_alloc_func (rb_cVertexArray, ruby_VertexArray_allocate);
     rb_define_private_method (rb_cVertexArray, "initialize", (VALUE(*)(...))ruby_VertexArray_initialize, 3);

     rb_define_method (rb_cVertexArray, "get",             (VALUE(*)(...))ruby_VertexArray_get, 3);
     rb_define_method (rb_cVertexArray, "component_count", (VALUE(*)(...))ruby_VertexArray_get_component_count, 0);
     rb_define_method (rb_cVertexArray, "component_type",  (VALUE(*)(...))ruby_VertexArray_get_component_type, 0);
     rb_define_method (rb_cVertexArray, "vertex_count",    (VALUE(*)(...))ruby_VertexArray_get_vertex_count, 0);
     rb_define_method (rb_cVertexArray, "set",             (VALUE(*)(...))ruby_VertexArray_set, 3);
}
