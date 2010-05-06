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
    int num_vertices;
    int num_components;
    int component_size;
    Data_Get_Struct (self, VertexArray, p);
    num_vertices   = FIX2INT (val_num_vertices);
    num_components = FIX2INT (val_num_components);
    component_size = FIX2INT (val_component_size);

    new (p) VertexArray (num_vertices, num_components, component_size);
    p->setExportedEntity ((void*)self);

    return self;
}

VALUE ruby_VertexArray_get (VALUE self, VALUE val_first_vertex, VALUE val_num_vertices)
{
  VertexArray* p;
  Data_Get_Struct (self, VertexArray, p);
  int first_vertex = FIX2INT (val_first_vertex);
  int num_vertices = FIX2INT (val_num_vertices);

  float* values = (float*)ruby_xmalloc (sizeof(float)*num_vertices);
  int component_size = p->getComponentType ();

  p->get (first_vertex, num_vertices, values);

  VALUE val_values = rb_ary_new ();
  for (int i = 0; i < num_vertices; i++) {
    switch (component_size) {
    case 1:
    case 2:
      rb_ary_push (val_values, INT2FIX(values[i]));
      break;
    case 4:
      rb_ary_push (val_values, rb_float_new(values[i]));
      break;
    default:
      // エラー
      ;
    }
  }
  ruby_xfree (values);

  return val_values;
}

VALUE ruby_VertexArray_get_component_count (VALUE self)
{
  VertexArray* p;
  int component_count;
  Data_Get_Struct (self, VertexArray, p);

  component_count = p->getComponentCount ();

  return INT2FIX(component_count);
}

VALUE ruby_VertexArray_get_component_type (VALUE self)
{
  VertexArray* p;
  int component_type;
  Data_Get_Struct (self, VertexArray, p);

  component_type = p->getComponentType ();

  return INT2FIX(component_type);
}

VALUE ruby_VertexArray_get_vertex_count (VALUE self)
{
  VertexArray* p;
  int vertex_count;
  Data_Get_Struct (self, VertexArray, p);

  vertex_count = p->getVertexCount ();

  return INT2FIX(vertex_count);
}

VALUE ruby_VertexArray_set (VALUE self, VALUE val_first_vertex, VALUE val_num_vertices, VALUE val_values)
{
  VertexArray* p;
  int first_vertex;
  int num_vertices;
  float* values;
  int component_size;

  Data_Get_Struct (self, VertexArray, p);
  first_vertex = INT2FIX (first_vertex);
  num_vertices = INT2FIX (num_vertices);
  component_size = p->getComponentType();

  switch (component_size) {
  case 1: {
    char* values = (char*)ruby_xmalloc(sizeof(char)*num_vertices);
    VALUE val_values = rb_ary_new ();
    for (int i = 0; i < num_vertices; i++) {
      values[i] = FIX2INT(rb_ary_entry(val_values, i));
    }
    p->set (first_vertex, num_vertices, values);
    ruby_xfree (values);
    break;
  }
  case 2: {
    short* values = (short*)ruby_xmalloc(sizeof(short)*num_vertices);
    VALUE val_values = rb_ary_new ();
    for (int i = 0; i < num_vertices; i++) {
      values[i] = FIX2INT(rb_ary_entry(val_values, i));
    }
    p->set (first_vertex, num_vertices, values);
    ruby_xfree (values);
    break;
  }
  case 4: {
    float* values = (float*)ruby_xmalloc(sizeof(float)*num_vertices);
    VALUE val_values = rb_ary_new ();
    for (int i = 0; i < num_vertices; i++) {
      values[i] = FIX2INT(rb_ary_entry(val_values, i));
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
  int component_type;

  Data_Get_Struct (self, VertexArray, p);
  component_type = FIX2INT(val_component_type);

  p->convert (component_type);

  return Qnil;
}


void register_VertexArray (VALUE rb_cVertexArray)
{
     // VertexArray
     rb_define_alloc_func (rb_cVertexArray, ruby_VertexArray_allocate);
     rb_define_private_method (rb_cVertexArray, "initialize", (VALUE(*)(...))ruby_VertexArray_initialize, 3);

     rb_define_method (rb_cVertexArray, "get",             (VALUE(*)(...))ruby_VertexArray_get, 2);
     rb_define_method (rb_cVertexArray, "component_count", (VALUE(*)(...))ruby_VertexArray_get_component_count, 0);
     rb_define_method (rb_cVertexArray, "component_type",  (VALUE(*)(...))ruby_VertexArray_get_component_type, 0);
     rb_define_method (rb_cVertexArray, "vertex_count",    (VALUE(*)(...))ruby_VertexArray_get_vertex_count, 0);
     rb_define_method (rb_cVertexArray, "set",             (VALUE(*)(...))ruby_VertexArray_set, 3);
     rb_define_method (rb_cVertexArray, "convert",         (VALUE(*)(...))ruby_VertexArray_set, 1);
}
