#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

VALUE ruby_VertexArray_free (VertexArray* ptr)
{
    ptr->~VertexArray ();
    ruby_xfree (ptr);
}

VALUE ruby_VertexArray_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(VertexArray));
    return Data_Wrap_Struct (self, 0, ruby_VertexArray_free, p);
}

VALUE ruby_VertexArray_initialize (VALUE self, VALUE val_num_vertices, VALUE val_num_components, VALUE val_component_size)
{
    VertexArray* p;
    Data_Get_Struct (self, VertexArray, p);
    int num_vertices    = NUM2INT (val_num_vertices);
    int num_components  = NUM2INT (val_num_components);
    int component_size  = NUM2INT (val_component_size);
    new (p) VertexArray (num_vertices, num_components, component_size);
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_VertexArray_get (VALUE self, VALUE val_first_vertex, VALUE val_num_vertices)
{
  VertexArray* p;
  Data_Get_Struct (self, VertexArray, p);
  int first_vertex    = NUM2INT (val_first_vertex);
  int num_vertices    = NUM2INT (val_num_vertices);
  int component_size  = p->getComponentType ();
  int component_count = p->getComponentCount ();
  int num_components  = num_vertices * component_count;

  VALUE val_values = rb_ary_new2 (num_components);
  switch (component_size) {
  case 1: {
      char* values = (char*)ruby_xmalloc (sizeof(char)*num_components);
      p->get (first_vertex, num_vertices, values);
      for (int i = 0; i < num_components; i++) {
	rb_ary_push (val_values, INT2NUM(values[i]));
      }
      ruby_xfree (values);
      break;
  }
  case 2: {
      short* values = (short*)ruby_xmalloc (sizeof(short)*num_components);
      p->get (first_vertex, num_vertices, values);
      for (int i = 0; i < num_components; i++) {
	rb_ary_push (val_values, INT2NUM(values[i]));
      }
      ruby_xfree (values);
      break;
  }
  case 4: {
      float* values = (float*)ruby_xmalloc (sizeof(float)*num_components);
      p->get (first_vertex, num_vertices, values);
      for (int i = 0; i < num_components; i++) {
	rb_ary_push (val_values, rb_float_new(values[i]));
      }
      ruby_xfree (values);
      break;
  }
  default: {
    ; // エラー
  }
  }


  return val_values;
}

VALUE ruby_VertexArray_get_component_count (VALUE self)
{
  VertexArray* p;
  Data_Get_Struct (self, VertexArray, p);
  int component_count = p->getComponentCount ();
  return INT2NUM(component_count);
}

VALUE ruby_VertexArray_get_component_type (VALUE self)
{
  VertexArray* p;
  Data_Get_Struct (self, VertexArray, p);
  int component_type = p->getComponentType ();
  return INT2NUM(component_type);
}

VALUE ruby_VertexArray_get_vertex_count (VALUE self)
{
  VertexArray* p;
  Data_Get_Struct (self, VertexArray, p);
  int vertex_count = p->getVertexCount ();
  return INT2NUM(vertex_count);
}

VALUE ruby_VertexArray_set (VALUE self, VALUE val_first_vertex, VALUE val_num_vertices, VALUE val_values)
{
  VertexArray* p;
  Data_Get_Struct (self, VertexArray, p);
  int first_vertex    = NUM2INT(val_first_vertex);
  int num_vertices    = NUM2INT(val_num_vertices);
  int component_size  = p->getComponentType ();
  int component_count = p->getComponentCount ();
  int num_components  = num_vertices * component_count;

  //cout << first_vertex << ", " << num_vertices << ", " << component_size << "\n";

  switch (component_size) {
  case 1: {
    char* values = (char*)ruby_xmalloc(sizeof(char)*num_components);
    for (int i = 0; i < num_components; i++) {
      values[i] = NUM2INT(rb_ary_entry(val_values, i));
    }
    p->set (first_vertex, num_vertices, values);
    ruby_xfree (values);
    break;
  }
  case 2: {
    short* values = (short*)ruby_xmalloc(sizeof(short)*num_components);
    for (int i = 0; i < num_components; i++) {
      values[i] = NUM2INT(rb_ary_entry(val_values, i));
    }
    p->set (first_vertex, num_vertices, values);
    ruby_xfree (values);
    break;
  }
  case 4: {
    float* values = (float*)ruby_xmalloc(sizeof(float)*num_components);
    for (int i = 0; i < num_components; i++) {
      values[i] = NUM2DBL(rb_ary_entry(val_values, i));
    }
    p->set (first_vertex, num_vertices, values);
    ruby_xfree (values);
    break;
  }
  default: {
    // エラー
  }
  }

  return Qnil;
}

VALUE ruby_VertexArray_convert (VALUE self, VALUE val_component_type)
{
  VertexArray* p;
  Data_Get_Struct (self, VertexArray, p);
  int component_type = NUM2INT(val_component_type);
  p->convert (component_type);
  return Qnil;
}


void register_VertexArray ()
{
     // VertexArray
    rb_cVertexArray         = rb_define_class_under (rb_mM3G, "VertexArray",         rb_cObject3D);

     rb_define_alloc_func (rb_cVertexArray, ruby_VertexArray_allocate);
     rb_define_private_method (rb_cVertexArray, "initialize", (VALUE(*)(...))ruby_VertexArray_initialize, 3);

     rb_define_method (rb_cVertexArray, "get",             (VALUE(*)(...))ruby_VertexArray_get,                 2);
     rb_define_method (rb_cVertexArray, "component_count", (VALUE(*)(...))ruby_VertexArray_get_component_count, 0);
     rb_define_method (rb_cVertexArray, "component_type",  (VALUE(*)(...))ruby_VertexArray_get_component_type,  0);
     rb_define_method (rb_cVertexArray, "vertex_count",    (VALUE(*)(...))ruby_VertexArray_get_vertex_count,    0);
     rb_define_method (rb_cVertexArray, "set",             (VALUE(*)(...))ruby_VertexArray_set,                 3);
     rb_define_method (rb_cVertexArray, "convert",         (VALUE(*)(...))ruby_VertexArray_convert,             1);
}
