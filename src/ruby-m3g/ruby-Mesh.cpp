#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  struct IndexBufferAccessor {
    Mesh* mesh;
  };
  struct AppearanceAccessor {
    Mesh* mesh;
  };
  VALUE rb_cMesh_IndexBufferAccessor;
  VALUE rb_cMesh_AppearanceAccessor;
}


VALUE ruby_Mesh_free (Mesh* ptr)
{
    ptr->~Mesh ();
    ruby_xfree (ptr);
}

VALUE ruby_Mesh_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Mesh));
    return Data_Wrap_Struct (self, 0, ruby_Mesh_free, p);
}

VALUE ruby_Mesh_initialize (VALUE self, VALUE val_vertices, VALUE val_submeshes, VALUE val_appearances)
{
    Mesh* p;
    VertexBuffer* vertices;
    Data_Get_Struct (self, Mesh, p);
    Data_Get_Struct (val_vertices, VertexBuffer, vertices);

    if (TYPE(val_submeshes) == T_ARRAY) {
      int num_submesh = RARRAY(val_submeshes)->len;
      IndexBuffer** submeshes = (IndexBuffer**)ruby_xmalloc (sizeof(IndexBuffer*)*num_submesh);
      Appearance** appearances = (Appearance**)ruby_xmalloc (sizeof(Appearance*)*num_submesh);
      for (int i = 0; i < num_submesh; i++) {
	Data_Get_Struct (rb_ary_entry(val_submeshes, i), IndexBuffer, submeshes[i]);
	Data_Get_Struct (rb_ary_entry(val_submeshes, i), Appearance, appearances[i]);
      }

      new (p) Mesh (vertices, num_submesh, submeshes, appearances);

      ruby_xfree (submeshes);
      ruby_xfree (appearances);
      
    } else {

      IndexBuffer* submesh;
      Appearance* appearance;
      
      Data_Get_Struct (val_submeshes, IndexBuffer, submesh);
      Data_Get_Struct (val_appearances, Appearance, appearance);

      new (p) Mesh (vertices, submesh, appearance);

    }

    return self;
}

VALUE ruby_Mesh_get_appearance (VALUE self)
{
  Mesh* p;
  Data_Get_Struct (self, Mesh, p);
  AppearanceAccessor* accessor;
  VALUE val_accessor = Data_Make_Struct (rb_cMesh_AppearanceAccessor, AppearanceAccessor, 0, -1, accessor);
  accessor->mesh = p;
  return val_accessor;
}

VALUE ruby_Mesh_get_index_buffer (VALUE self)
{
  Mesh* p;
  Data_Get_Struct (self, Mesh, p);
  IndexBufferAccessor* accessor;
  VALUE val_accessor = Data_Make_Struct (rb_cMesh_IndexBufferAccessor, IndexBufferAccessor, 0, -1, accessor);
  accessor->mesh = p;
  return val_accessor;
}

VALUE ruby_Mesh_get_submesh_count (VALUE self)
{
  Mesh* p;
  int count;
  Data_Get_Struct (self, Mesh, p);

  count = p->getSubmeshCount ();

  return INT2FIX (count);
}

VALUE ruby_Mesh_get_vertex_buffer (VALUE self)
{
  Mesh* p;
  VertexBuffer* vertices;

  Data_Get_Struct (self, Mesh, p);

  vertices = p->getVertexBuffer();
  
  return (VALUE)vertices->getExportedEntity ();
}


/**
 * Mesh_IndexBufferAccessor
 */

VALUE ruby_Mesh_IndexBufferAccessor_get_index_buffer (VALUE self, VALUE val_index)
{
    IndexBufferAccessor* p;
    int index;
    IndexBuffer* ibuf;

    Data_Get_Struct (self, IndexBufferAccessor, p);
    index = FIX2INT (val_index);

    ibuf = p->mesh->getIndexBuffer (index);
    
    return ibuf ? (VALUE)ibuf->getExportedEntity() : Qnil;
}

/**
 * Mesh_AppearanceAccessor
 */

VALUE ruby_Mesh_AppearanceAccessor_get_appearance (VALUE self, VALUE val_index)
{
    AppearanceAccessor* p;
    Data_Get_Struct (self, AppearanceAccessor, p);
    int index = FIX2INT (val_index);
    Appearance* app;

    p->mesh->setAppearance (index, app);
    
    return app ? (VALUE)app->getExportedEntity() : Qnil;
}

VALUE ruby_Mesh_AppearanceAccessor_set_appearance (VALUE self, VALUE val_index, VALUE val_appearance)
{
    AppearanceAccessor* p;
    Data_Get_Struct (self, AppearanceAccessor, p);
    int index = FIX2INT (val_index);
    Appearance* app;
    Data_Get_Struct (val_appearance, Appearance, app);

    p->mesh->setAppearance (index, app);
    
    return Qnil;
}


void register_Mesh ()
{
     // Mesh
    rb_cMesh                = rb_define_class_under (rb_mM3G, "Mesh",                rb_cNode);

     rb_define_alloc_func (rb_cMesh, ruby_Mesh_allocate);
     rb_define_private_method (rb_cMesh, "initialize", (VALUE(*)(...))ruby_Mesh_initialize, 3);

     rb_define_method (rb_cMesh, "appearance",     (VALUE(*)(...))ruby_Mesh_get_appearance, 0);
     rb_define_method (rb_cMesh, "index_buffer",   (VALUE(*)(...))ruby_Mesh_get_index_buffer, 0);
     rb_define_method (rb_cMesh, "submesh_count",  (VALUE(*)(...))ruby_Mesh_get_submesh_count, 0);
     rb_define_method (rb_cMesh, "vertex_buffer",  (VALUE(*)(...))ruby_Mesh_get_vertex_buffer, 0);

     // Mesh_IndexBufferAccessor
     rb_cMesh_IndexBufferAccessor  = rb_define_class_under (rb_cMesh, "IndexBufferAccessor", rb_cObject);

     rb_define_method (rb_cMesh_IndexBufferAccessor, "[]",     (VALUE(*)(...))ruby_Mesh_IndexBufferAccessor_get_index_buffer, 1);

    // Mesh_AppearanceAccessor;
     rb_cMesh_AppearanceAccessor  = rb_define_class_under (rb_cMesh, "ApearanceAccessor", rb_cObject);

    rb_define_method (rb_cMesh_AppearanceAccessor, "[]",     (VALUE(*)(...))ruby_Mesh_AppearanceAccessor_get_appearance, 1);
    rb_define_method (rb_cMesh_AppearanceAccessor, "[]=",     (VALUE(*)(...))ruby_Mesh_AppearanceAccessor_set_appearance, 2);

}
