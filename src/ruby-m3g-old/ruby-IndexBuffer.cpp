#include <new>
#include "ruby.h"
#include "IndexBuffer.hpp"
using namespace m3g;

VALUE ruby_IndexBuffer_free (IndexBuffer* ptr)
{
    ptr->~IndexBuffer ();
    ruby_xfree (ptr);
}

VALUE ruby_IndexBuffer_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(IndexBuffer));
    return Data_Wrap_Struct (self, NULL, ruby_IndexBuffer_free, p);
}

VALUE ruby_IndexBuffer_initialize (int argc, VALUE* argv, VALUE self)
{
    IndexBuffer* p;
    Data_Get_Struct (self, IndexBuffer, p);
    new (p) IndexBuffer;
    return Qnil;
}

VALUE ruby_IndexBuffer_get_index_count (VALUE self)
{
    return Qnil;
}


VALUE ruby_IndexBuffer_get_indices (VALUE self)
{
    // indexの配列を返す
    return Qnil;
}


void register_IndexBuffer (VALUE rb_cIndexBuffer)
{
     // IndexBuffer
     rb_define_alloc_func (rb_cIndexBuffer, ruby_IndexBuffer_allocate);
     rb_define_private_method (rb_cIndexBuffer, "initialize", (VALUE(*)(...))ruby_IndexBuffer_initialize, -1);

     rb_define_method (rb_cIndexBuffer, "index_count", (VALUE(*)(...))ruby_IndexBuffer_get_index_count, 0);
     rb_define_method (rb_cIndexBuffer, "indices",     (VALUE(*)(...))ruby_IndexBuffer_get_indices,    0);
}
