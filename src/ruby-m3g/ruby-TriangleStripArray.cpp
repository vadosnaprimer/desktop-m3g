#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


VALUE ruby_TriangleStripArray_free (TriangleStripArray* ptr)
{
  ptr->~TriangleStripArray ();
  ruby_xfree (ptr);
}

VALUE ruby_TriangleStripArray_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(TriangleStripArray));
    return Data_Wrap_Struct (self, 0, ruby_TriangleStripArray_free, p);
}

VALUE ruby_TriangleStripArray_initialize (VALUE self, VALUE val_arg1, VALUE val_strips)
{
    TriangleStripArray* p;
    Data_Get_Struct (self, TriangleStripArray, p);
    
    switch (TYPE(val_arg1)) {
    case T_ARRAY: {
      VALUE val_indices = val_arg1;
      int  num_indices  = RARRAY_LEN(val_indices);
      int* indices      = (int*)ruby_xmalloc(sizeof(int)*num_indices*10);
      //cout << "indices = " << indices << "\n";
      for (int i = 0; i < num_indices; i++) {
	indices[i] = FIX2INT (rb_ary_entry(val_indices, i));
      }
      int  num_strips = RARRAY_LEN(val_strips);
      int* strips     = (int*)ruby_xmalloc(sizeof(int)*num_strips*10);
      //cout << "strips = " << strips << "\n";
      for (int i = 0; i < num_strips; i++) {
	strips[i] = FIX2INT (rb_ary_entry(val_strips, i));
      }
      // TODO: indicesの長さがstripsの合計と等しいかチェック
      new (p) TriangleStripArray (indices, num_strips, strips);
      ruby_xfree (indices);
      ruby_xfree (strips);
      break;
    }
    case T_FIXNUM: 
    case T_BIGNUM: {
      VALUE val_first_index = val_arg1;
      int   first_index     = FIX2INT (val_first_index);
      int   num_strips      = RARRAY_LEN(val_strips);
      int* strips     = (int*)ruby_xmalloc(sizeof(int)*num_strips);
      for (int i = 0; i < num_strips; i++) {
	strips[i] = FIX2INT (rb_ary_entry(val_strips, i));
      }
      // TODO: indicesの長さがstripsの合計と等しいかチェック
      new (p) TriangleStripArray (first_index, num_strips, strips);
      ruby_xfree (strips);
      break;
    }
    default: {
      // エラー
    }
    }

    return self;
}


void register_TriangleStripArray ()
{
     // TriangleStripArray
    rb_cTriangleStripArray  = rb_define_class_under (rb_mM3G, "TriangleStripArray",  rb_cIndexBuffer);

     rb_define_alloc_func (rb_cTriangleStripArray, ruby_TriangleStripArray_allocate);
     rb_define_private_method (rb_cTriangleStripArray, "initialize", (VALUE(*)(...))ruby_TriangleStripArray_initialize, 2);
}
