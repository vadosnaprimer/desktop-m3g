#include <new>
#include "ruby.h"
#include "TriangleStripArray.hpp"
using namespace m3g;

VALUE ruby_TriangleStripArray_free (TriangleStripArray* ptr)
{
    ptr->~TriangleStripArray ();
    ruby_xfree (ptr);
}

VALUE ruby_TriangleStripArray_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(TriangleStripArray));
    return Data_Wrap_Struct (self, NULL, ruby_TriangleStripArray_free, p);
}

VALUE ruby_TriangleStripArray_initialize (VALUE self, VALUE val_indices, VALUE val_strip_lengths)
{
    TriangleStripArray* p;
    Data_Get_Struct (self, TriangleStripArray, p);
    new (p) TriangleStripArray (0,0);
    return Qnil;
}


void register_TriangleStripArray (VALUE rb_cTriangleStripArray)
{
     // TriangleStripArray
     rb_define_alloc_func (rb_cTriangleStripArray, ruby_TriangleStripArray_allocate);
     rb_define_private_method (rb_cTriangleStripArray, "initialize", (VALUE(*)(...))ruby_TriangleStripArray_initialize, 2);

}
