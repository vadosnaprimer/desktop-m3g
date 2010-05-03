#include <new>
#include "ruby.h"
#include "SkinnedMesh.hpp"
using namespace m3g;

VALUE ruby_SkinnedMesh_free (SkinnedMesh* ptr)
{
    ptr->~SkinnedMesh ();
    ruby_xfree (ptr);
}

VALUE ruby_SkinnedMesh_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(SkinnedMesh));
    return Data_Wrap_Struct (self, NULL, ruby_SkinnedMesh_free, p);
    return Qnil;
}

VALUE ruby_SkinnedMesh_initialize (int argc, VALUE* argv, VALUE self)
{
    SkinnedMesh* p;
    Data_Get_Struct (self, SkinnedMesh, p);
    new (p) SkinnedMesh (0,(IndexBuffer*)0,0,0);
    return Qnil;
}

VALUE ruby_SkinnedMesh_add_transform (VALUE self, VALUE val_bone, VALUE val_weight, VALUE val_first_vertex, VALUE val_num_vertices)
{
    return Qnil;
}

VALUE ruby_SkinnedMesh_get_bone_transform (VALUE self, VALUE val_bone, VALUE val_transform)
{
    return Qnil;
}

VALUE ruby_SkinnedMesh_get_bone_vertices (VALUE self, VALUE val_bone, VALUE val_indices, VALUE val_weights)
{
    return Qnil;
}

VALUE ruby_SkinnedMesh_get_skelton (VALUE self)
{
    return Qnil;
}


void register_SkinnedMesh (VALUE rb_cSkinnedMesh)
{
     // SkinnedMesh
     rb_define_alloc_func (rb_cSkinnedMesh, ruby_SkinnedMesh_allocate);
     rb_define_private_method (rb_cSkinnedMesh, "initialize", (VALUE(*)(...))ruby_SkinnedMesh_initialize, -1);

     rb_define_method (rb_cSkinnedMesh, "add_transform",       (VALUE(*)(...))ruby_SkinnedMesh_add_transform,  4);
     rb_define_method (rb_cSkinnedMesh, "bone_transform", (VALUE(*)(...))ruby_SkinnedMesh_get_bone_transform, 2);
     rb_define_method (rb_cSkinnedMesh, "bone_vertices",   (VALUE(*)(...))ruby_SkinnedMesh_get_bone_vertices,  3);
     rb_define_method (rb_cSkinnedMesh, "skelton",         (VALUE(*)(...))ruby_SkinnedMesh_get_skelton, 0);



}
