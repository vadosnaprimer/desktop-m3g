#include <new>
#include "ruby.h"
#include "MorphingMesh.hpp"
using namespace m3g;

VALUE ruby_MorphingMesh_free (MorphingMesh* ptr)
{
    ptr->~MorphingMesh ();
    ruby_xfree (ptr);
}

VALUE ruby_MorphingMesh_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(MorphingMesh));
    return Data_Wrap_Struct (self, NULL, ruby_MorphingMesh_free, p);
}

VALUE ruby_MorphingMesh_initialize (int argc, VALUE* argv, VALUE self)
{
    MorphingMesh* p;
    Data_Get_Struct (self, MorphingMesh, p);
    new (p) MorphingMesh (0,0,0,(Appearance*)0);
    return Qnil;
}

VALUE ruby_MorphingMesh_get_morph_target (VALUE self, VALUE val_index)
{
    return Qnil;
}

VALUE ruby_MorphingMesh_get_morph_target_count (VALUE self)
{
    return Qnil;
}

VALUE ruby_MorphingMesh_get_weights (VALUE self)
{
    // weightの配列
    return Qnil;
}

VALUE ruby_MorphingMesh_set_weights (VALUE self, VALUE val_weights)
{
    return Qnil;
}

void register_MorphingMesh (VALUE rb_cMorphingMesh)
{
     // MorphingMesh
     rb_define_alloc_func (rb_cMorphingMesh, ruby_MorphingMesh_allocate);
     rb_define_private_method (rb_cMorphingMesh, "initialize", (VALUE(*)(...))ruby_MorphingMesh_initialize, -1);

     rb_define_method (rb_cMorphingMesh, "morph_target",       (VALUE(*)(...))ruby_MorphingMesh_get_morph_target, 1);
     rb_define_method (rb_cMorphingMesh, "morph_target_count", (VALUE(*)(...))ruby_MorphingMesh_get_morph_target_count, 0);
     rb_define_method (rb_cMorphingMesh, "weights",            (VALUE(*)(...))ruby_MorphingMesh_get_weights, 0);
     rb_define_method (rb_cMorphingMesh, "weights=",           (VALUE(*)(...))ruby_MorphingMesh_set_weights, 1);

}
