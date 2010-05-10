#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

// 30クラスのfree関数
extern VALUE ruby_Object3D_free            (Object3D* ptr);
extern VALUE ruby_AnimationController_free (AnimationController* ptr);
extern VALUE ruby_AnimationTrack_free      (AnimationTrack* ptr);
extern VALUE ruby_Appearance_free          (Appearance* ptr);
extern VALUE ruby_Background_free          (Background* ptr);
extern VALUE ruby_CompositingMode_free     (CompositingMode* ptr);
extern VALUE ruby_Fog_free                 (Fog* ptr);
extern VALUE ruby_Image2D_free             (Image2D* ptr);
extern VALUE ruby_TriangleStripArray_free  (TriangleStripArray* ptr);
extern VALUE ruby_KeyframeSequence_free    (KeyframeSequence* ptr);
extern VALUE ruby_Material_free            (Material* ptr);
extern VALUE ruby_PolygonMode_free         (PolygonMode* ptr);
extern VALUE ruby_Camera_free              (Camera* ptr);
extern VALUE ruby_Group_free               (Group* ptr);
extern VALUE ruby_World_free               (World* ptr);
extern VALUE ruby_Light_free               (Light* ptr);
extern VALUE ruby_Mesh_free                (Mesh* ptr);
extern VALUE ruby_MorphingMesh_free        (MorphingMesh* ptr);
extern VALUE ruby_SkinnedMesh_free         (SkinnedMesh* ptr);
extern VALUE ruby_Sprite3D_free            (Sprite3D* ptr);
extern VALUE ruby_Texture2D_free           (Texture2D* ptr);
extern VALUE ruby_VertexArray_free         (VertexArray* ptr);
extern VALUE ruby_VertexBuffer_free        (VertexBuffer* ptr);


namespace {
	struct TextureAccessor {
		RayIntersection* ray_intersection;
	};
	struct TextureSTAccessor {
		RayIntersection* ray_intersection;
		int index;
	};
	
	VALUE rb_cRayIntersection_TextureAccessor;
	VALUE rb_cRayIntersection_TextureSTAccessor;
}

VALUE ruby_RayIntersection_free (RayIntersection* ptr)
{
    ptr->~RayIntersection ();
    ruby_xfree (ptr);
}

VALUE ruby_RayIntersection_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(RayIntersection));
    return Data_Wrap_Struct (self, 0, ruby_RayIntersection_free, p);
}

VALUE ruby_RayIntersection_initialize (VALUE self)
{
    RayIntersection* p;
    Data_Get_Struct (self, RayIntersection, p);
    new (p) RayIntersection;
    p->setExportedEntity((void*)self);
    return self;
}

VALUE ruby_RayIntersection_get_distance (VALUE self)
{
    RayIntersection* p;
    float distance;

    Data_Get_Struct (self, RayIntersection, p);
    distance = p->getDistance ();

    return rb_float_new(distance);
}

VALUE ruby_RayIntersection_get_intersected (VALUE self)
{
    RayIntersection* p;
    Node* node;

    Data_Get_Struct (self, RayIntersection, p);
    node = p->getIntersected ();

    return node ? (VALUE)node->getExportedEntity() : Qnil;
}

VALUE ruby_RayIntersection_get_normal (VALUE self)
{
  float x,y,z;
  RayIntersection* p;

  Data_Get_Struct (self, RayIntersection, p);
  x = p->getNormalX ();
  y = p->getNormalY ();
  z = p->getNormalZ ();

  VALUE val_ret = rb_ary_new2 (3);
  rb_ary_push (val_ret, rb_float_new(x));
  rb_ary_push (val_ret, rb_float_new(y));
  rb_ary_push (val_ret, rb_float_new(z));

    return val_ret;
}

VALUE ruby_RayIntersection_get_ray (VALUE self, VALUE val_ray)
{
    RayIntersection* p;
    Data_Get_Struct (self, RayIntersection, p);

    float ray[6];
    p->getRay (ray);

    VALUE val_pos = rb_ary_new ();
    VALUE val_dir = rb_ary_new ();
    VALUE val_ret = rb_ary_new ();

    rb_ary_push (val_pos, rb_float_new(ray[0]));
    rb_ary_push (val_pos, rb_float_new(ray[1]));
    rb_ary_push (val_pos, rb_float_new(ray[2]));
    rb_ary_push (val_dir, rb_float_new(ray[3]));
    rb_ary_push (val_dir, rb_float_new(ray[4]));
    rb_ary_push (val_dir, rb_float_new(ray[5]));
    rb_ary_push (val_ret, val_pos);
    rb_ary_push (val_ret, val_dir);

    return Qnil;
}

VALUE ruby_RayIntersection_get_submesh_index (VALUE self)
{
    RayIntersection* p;
    Data_Get_Struct (self, RayIntersection, p);
    int index;

    index = p->getSubmeshIndex();
    
    return INT2NUM(index);
}

VALUE ruby_RayIntersection_get_texture (VALUE self)
{
    RayIntersection* p;
    Data_Get_Struct (self, RayIntersection, p);
    TextureAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cRayIntersection_TextureAccessor, TextureAccessor, 0, -1, accessor);
    accessor->ray_intersection = p;
    return val_accessor;
}

/**
 * RayIntersection::TextureAccessor
 */

VALUE ruby_RayIntersection_TextureAccessor_get_st (VALUE self, VALUE val_index)
{
    TextureAccessor* p;
    Data_Get_Struct (self, TextureAccessor, p);
    int index = NUM2INT(val_index);
    TextureSTAccessor* accessor;
    VALUE val_accessor = Data_Make_Struct (rb_cRayIntersection_TextureSTAccessor, TextureSTAccessor, 0, -1, accessor);
    accessor->ray_intersection = p->ray_intersection;
    accessor->index = index;
    return val_accessor;
}


/**
 * RayIntersection::TextureAccessor
 */

VALUE ruby_RayIntersection_TextureSTAccessor_get_s (VALUE self)
{
    TextureSTAccessor* p;
    Data_Get_Struct (self, TextureSTAccessor, p);
    float s = p->ray_intersection->getTextureS (p->index);
    return rb_float_new(s);
}

VALUE ruby_RayIntersection_TextureSTAccessor_get_t (VALUE self)
{
    TextureSTAccessor* p;
    Data_Get_Struct (self, TextureSTAccessor, p);
    float t = p->ray_intersection->getTextureT (p->index);
    return rb_float_new(t);
}

/**
 *
 */
void register_RayIntersection ()
{
     // RayIntersection
    rb_cRayIntersection     = rb_define_class_under (rb_mM3G, "RayIntersection",     rb_cObject);

     rb_define_alloc_func (rb_cRayIntersection, ruby_RayIntersection_allocate);
     rb_define_private_method (rb_cRayIntersection, "initialize", (VALUE(*)(...))ruby_RayIntersection_initialize,   0);

     rb_define_method (rb_cRayIntersection, "distance",      (VALUE(*)(...))ruby_RayIntersection_get_distance,      0);
     rb_define_method (rb_cRayIntersection, "intersected",   (VALUE(*)(...))ruby_RayIntersection_get_intersected,   0);
     rb_define_method (rb_cRayIntersection, "normal",        (VALUE(*)(...))ruby_RayIntersection_get_normal,        0);
     rb_define_method (rb_cRayIntersection, "ray",           (VALUE(*)(...))ruby_RayIntersection_get_ray,           0);
     rb_define_method (rb_cRayIntersection, "submesh_index", (VALUE(*)(...))ruby_RayIntersection_get_submesh_index, 0);
     rb_define_method (rb_cRayIntersection, "texture",       (VALUE(*)(...))ruby_RayIntersection_get_texture,       0);

     // RayIntersection::TextureAccessor
     rb_cRayIntersection_TextureAccessor  = rb_define_class_under (rb_cRayIntersection, "TextureAccessor", rb_cObject);

     rb_define_method (rb_cRayIntersection_TextureAccessor, "[]",        (VALUE(*)(...))ruby_RayIntersection_TextureAccessor_get_st,    1);

     // RayIntersection::TextureSTAccessor
     rb_cRayIntersection_TextureSTAccessor  = rb_define_class_under (rb_cRayIntersection, "TextureAccessor", rb_cObject);

     rb_define_method (rb_cRayIntersection_TextureSTAccessor, "s",        (VALUE(*)(...))ruby_RayIntersection_TextureSTAccessor_get_s,    0);
     rb_define_method (rb_cRayIntersection_TextureSTAccessor, "t",        (VALUE(*)(...))ruby_RayIntersection_TextureSTAccessor_get_t,    0);

}
