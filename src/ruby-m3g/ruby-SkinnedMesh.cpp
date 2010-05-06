#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

extern VALUE ruby_Transform_free (Transform* ptr);

VALUE ruby_SkinnedMesh_free (SkinnedMesh* ptr)
{
    ptr->~SkinnedMesh ();
    ruby_xfree (ptr);
}

VALUE ruby_SkinnedMesh_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(SkinnedMesh));
    return Data_Wrap_Struct (self, 0, ruby_SkinnedMesh_free, p);
}

VALUE ruby_SkinnedMesh_initialize (VALUE self, VALUE val_vertices, VALUE val_submeshes, VALUE val_appearances, VALUE val_skeleton)
{
  SkinnedMesh* p;
  VertexBuffer* vertices;
  Group* skeleton;

  Data_Get_Struct (self, SkinnedMesh, p);
  Data_Get_Struct (val_vertices, VertexBuffer, vertices);
  Data_Get_Struct (val_skeleton, Group, skeleton);

  if (TYPE(val_submeshes) == T_ARRAY) {
      int num_submesh = RARRAY(val_submeshes)->len;
      IndexBuffer** submeshes   = (IndexBuffer**)ruby_xmalloc (sizeof(IndexBuffer*)*num_submesh);
      Appearance**  appearances = (Appearance**)ruby_xmalloc (sizeof(Appearance*)*num_submesh);
      for (int i = 0; i < num_submesh; i++) {
	Data_Get_Struct (rb_ary_entry(val_submeshes, i), IndexBuffer, submeshes[i]);
	Data_Get_Struct (rb_ary_entry(val_submeshes, i), Appearance, appearances[i]);
      }
      new (p) SkinnedMesh (vertices,
                           num_submesh,
                           submeshes,
                           appearances,
                           skeleton);
      ruby_xfree (submeshes);
      ruby_xfree (appearances);
      
    } else {
      IndexBuffer* submesh;
      Appearance*  appearance;
      Data_Get_Struct (val_submeshes, IndexBuffer, submesh);
      Data_Get_Struct (val_appearances, Appearance, appearance);
      new (p) SkinnedMesh (vertices, 
                           submesh,
                           appearance,
                           skeleton);
    }

    return self;
}

VALUE ruby_SkinnedMesh_add_transform (VALUE self, VALUE val_bone, VALUE val_weight, VALUE val_first_vertex, VALUE val_num_vertices)
{
  SkinnedMesh* p;
  Node* bone;
  int weight;
  int first_vertex;
  int num_vertices;

  Data_Get_Struct (self, SkinnedMesh, p);
  Data_Get_Struct (val_bone, Node, bone);
  weight = FIX2INT (val_weight);
  first_vertex = FIX2INT (val_first_vertex);
  num_vertices = FIX2INT (num_vertices);

  p->addTransform (bone, weight, first_vertex, num_vertices);
    
  return Qnil;
}

VALUE ruby_SkinnedMesh_get_bone_transform (VALUE self, VALUE val_bone)
{
  SkinnedMesh* p;
  Node*        bone;
  Transform*   transform;
  VALUE        val_transform;

    Data_Get_Struct (self, SkinnedMesh, p);
    Data_Get_Struct (val_bone, Node, bone);
    val_transform = Data_Make_Struct (rb_cTransform, Transform, 0, ruby_Transform_free, transform);

    p->getBoneTransform (bone, transform);
    
    return val_transform;
}

VALUE ruby_SkinnedMesh_get_bone_vertices (VALUE self, VALUE val_bone)
{
  SkinnedMesh* p;
  Node* bone;
  int count;

    Data_Get_Struct (self, SkinnedMesh, p);
    Data_Get_Struct (val_bone, Node, bone);
    count = p->getBoneVertices (bone, 0, 0);

    int*   indices = (int*)ruby_xmalloc (sizeof(int)*count);
    float* weights = (float*)ruby_xmalloc (sizeof(float)*count);
    p->getBoneVertices (bone, indices, weights);
    
    VALUE val_indices = rb_ary_new ();
    VALUE val_weights = rb_ary_new ();
    for (int i = 0; i < count; i++) {
      rb_ary_push (val_indices, rb_float_new(indices[i]));
      rb_ary_push (val_weights, rb_float_new(weights[i]));
    }
    ruby_xfree (indices);
    ruby_xfree (weights);

    VALUE val_ret = rb_ary_new ();
    rb_ary_push (val_ret, val_indices);
    rb_ary_push (val_ret, val_weights);
    
    return val_ret;
}

VALUE ruby_SkinnedMesh_get_skeleton (VALUE self)
{
  SkinnedMesh* p;
  Group* skeleton;
  
  Data_Get_Struct (self, SkinnedMesh, p);
  skeleton = p->getSkeleton ();
  
  return (VALUE)skeleton->getExportedEntity();
}


void register_SkinnedMesh (VALUE rb_cSkinnedMesh)
{
     // SkinnedMesh
     rb_define_alloc_func (rb_cSkinnedMesh, ruby_SkinnedMesh_allocate);
     rb_define_private_method (rb_cSkinnedMesh, "initialize", (VALUE(*)(...))ruby_SkinnedMesh_initialize, -1);

     rb_define_method (rb_cSkinnedMesh, "add_transform",       (VALUE(*)(...))ruby_SkinnedMesh_add_transform,  4);
     rb_define_method (rb_cSkinnedMesh, "bone_transform", (VALUE(*)(...))ruby_SkinnedMesh_get_bone_transform, 1);
     rb_define_method (rb_cSkinnedMesh, "bone_vertices",   (VALUE(*)(...))ruby_SkinnedMesh_get_bone_vertices,  1);
     rb_define_method (rb_cSkinnedMesh, "skeleton",         (VALUE(*)(...))ruby_SkinnedMesh_get_skeleton, 0);
}
