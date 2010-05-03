#include <new>
#include "ruby.h"
#include "Mesh.hpp"
using namespace m3g;

VALUE ruby_Mesh_free (Mesh* ptr)
{
    ptr->~Mesh ();
    ruby_xfree (ptr);
}

VALUE ruby_Mesh_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Mesh));
    return Data_Wrap_Struct (self, NULL, ruby_Mesh_free, p);
}

VALUE ruby_Mesh_initialize (VALUE self, VALUE val_vertices, VALUE val_submeshes, VALUE val_appearance)
{
    Mesh* p;
    Data_Get_Struct (self, Mesh, p);
    new (p) Mesh (0,0,(Appearance*)0);
    return Qnil;
}

VALUE ruby_Mesh_get_appearance (VALUE self, VALUE val_index)
{
    return Qnil;
}

VALUE ruby_Mesh_get_index_buffer (VALUE self, VALUE val_index)
{
    return Qnil;
}

VALUE ruby_Mesh_get_submesh_count (VALUE self)
{
    return Qnil;
}

VALUE ruby_Mesh_get_vertex_buffer (VALUE self)
{
    return Qnil;
}

VALUE ruby_Mesh_set_appearance (VALUE self, VALUE val_index_and_val_appearance)
{
    return Qnil;
}

void register_Mesh (VALUE rb_cMesh)
{
     // Mesh
     rb_define_alloc_func (rb_cMesh, ruby_Mesh_allocate);
     rb_define_private_method (rb_cMesh, "initialize", (VALUE(*)(...))ruby_Mesh_initialize, 3);

     rb_define_method (rb_cMesh, "appearance",     (VALUE(*)(...))ruby_Mesh_get_appearance, 1);
     rb_define_method (rb_cMesh, "index_buffer",   (VALUE(*)(...))ruby_Mesh_get_index_buffer, 1);
     rb_define_method (rb_cMesh, "submesh_count",  (VALUE(*)(...))ruby_Mesh_get_submesh_count, 0);
     rb_define_method (rb_cMesh, "vertex_buffer",  (VALUE(*)(...))ruby_Mesh_get_vertex_buffer, 0);
     rb_define_method (rb_cMesh, "appearance=",    (VALUE(*)(...))ruby_Mesh_set_appearance, 1);

}
