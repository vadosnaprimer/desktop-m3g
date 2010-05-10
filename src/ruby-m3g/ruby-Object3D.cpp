#include <iostream>
#include <typeinfo>
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



VALUE ruby_Object3D_free (Object3D* ptr)
{
    ptr->~Object3D ();
    ruby_xfree (ptr);
}


VALUE ruby_Object3D_add_animation_track (VALUE self, VALUE val_animation_track)
{
  Object3D* p;
  AnimationTrack* anim_track;

  Data_Get_Struct (self, Object3D, p);
  Data_Get_Struct (val_animation_track, AnimationTrack, anim_track);

  p->addAnimationTrack (anim_track);

  return Qnil;
}

VALUE ruby_Object3D_animate (VALUE self, VALUE val_world_time)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);
  int world_time = NUM2INT(val_world_time);

  int ret = p->animate (world_time);

  return INT2NUM(ret);
}

VALUE ruby_Object3D_duplicate (VALUE self)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);

  Object3D* obj     = p->duplicate();
  VALUE     val_obj = Qnil;

      if      (typeid(*obj) == typeid(AnimationController)) val_obj = Data_Wrap_Struct(rb_cAnimationController, 0, ruby_AnimationController_free, obj);
      else if (typeid(*obj) == typeid(AnimationTrack))      val_obj = Data_Wrap_Struct(rb_cAnimationTrack,      0, ruby_AnimationTrack_free,      obj);
      else if (typeid(*obj) == typeid(Appearance))          val_obj = Data_Wrap_Struct(rb_cAppearance,          0, ruby_Appearance_free,          obj);
      else if (typeid(*obj) == typeid(Background))          val_obj = Data_Wrap_Struct(rb_cBackground,          0, ruby_Background_free,          obj);
      else if (typeid(*obj) == typeid(CompositingMode))     val_obj = Data_Wrap_Struct(rb_cCompositingMode,     0, ruby_CompositingMode_free,     obj);
      else if (typeid(*obj) == typeid(Fog))                 val_obj = Data_Wrap_Struct(rb_cFog,                 0, ruby_Fog_free,                 obj);
      else if (typeid(*obj) == typeid(Image2D))             val_obj = Data_Wrap_Struct(rb_cImage2D,             0, ruby_Image2D_free,             obj);
      else if (typeid(*obj) == typeid(TriangleStripArray))  val_obj = Data_Wrap_Struct(rb_cTriangleStripArray,  0, ruby_TriangleStripArray_free,  obj);
      else if (typeid(*obj) == typeid(KeyframeSequence))    val_obj = Data_Wrap_Struct(rb_cKeyframeSequence,    0, ruby_KeyframeSequence_free,    obj);
      else if (typeid(*obj) == typeid(Material))            val_obj = Data_Wrap_Struct(rb_cMaterial,            0, ruby_Material_free,            obj);
      else if (typeid(*obj) == typeid(PolygonMode))         val_obj = Data_Wrap_Struct(rb_cPolygonMode,         0, ruby_PolygonMode_free,         obj);
      else if (typeid(*obj) == typeid(Camera))              val_obj = Data_Wrap_Struct(rb_cCamera,              0, ruby_Camera_free,              obj);
      else if (typeid(*obj) == typeid(Group))               val_obj = Data_Wrap_Struct(rb_cGroup,               0, ruby_Group_free,               obj);
      else if (typeid(*obj) == typeid(World))               val_obj = Data_Wrap_Struct(rb_cWorld,               0, ruby_World_free,               obj);
      else if (typeid(*obj) == typeid(Light))               val_obj = Data_Wrap_Struct(rb_cLight,               0, ruby_Light_free,               obj);
      else if (typeid(*obj) == typeid(Mesh))                val_obj = Data_Wrap_Struct(rb_cMesh,                0, ruby_Mesh_free,                obj);
      else if (typeid(*obj) == typeid(MorphingMesh))        val_obj = Data_Wrap_Struct(rb_cMorphingMesh,        0, ruby_MorphingMesh_free,        obj);
      else if (typeid(*obj) == typeid(SkinnedMesh))         val_obj = Data_Wrap_Struct(rb_cSkinnedMesh,         0, ruby_SkinnedMesh_free,         obj);
      else if (typeid(*obj) == typeid(Sprite3D))            val_obj = Data_Wrap_Struct(rb_cSprite3D,            0, ruby_Sprite3D_free,            obj);
      else if (typeid(*obj) == typeid(Texture2D))           val_obj = Data_Wrap_Struct(rb_cTexture2D,           0, ruby_Texture2D_free,           obj);
      else if (typeid(*obj) == typeid(VertexArray))         val_obj = Data_Wrap_Struct(rb_cVertexArray,         0, ruby_VertexArray_free,         obj);
      else if (typeid(*obj) == typeid(VertexBuffer))        val_obj = Data_Wrap_Struct(rb_cVertexBuffer,        0, ruby_VertexBuffer_free,        obj);
      else 	rb_raise(rb_eRuntimeError, "Duplicated object is invalid, name=%s.", typeid(*obj).name());


  return val_obj;
}

VALUE ruby_Object3D_find (VALUE self, VALUE val_user_id)
{
  Object3D* p;
  int user_id;
  
  Data_Get_Struct (self, Object3D, p);
  user_id = NUM2INT (val_user_id);

  Object3D* obj = p->find (user_id);
  cout << "obj = " << obj << "\n";
  return obj ? (VALUE)obj->getExportedEntity() : Qnil;
}

VALUE ruby_Object3D_get_animation_track (VALUE self, VALUE val_index)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);
  int index = NUM2INT (val_index);

  AnimationTrack* anim_track = p->getAnimationTrack (index);

  return anim_track ? (VALUE)anim_track->getExportedEntity() : Qnil;
}

VALUE ruby_Object3D_get_animation_track_count (VALUE self)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);

  int count = p->getAnimationTrackCount ();

  return INT2NUM(count);
}

VALUE ruby_Object3D_get_references (VALUE self)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);
  
  int num = p->getReferences (0);
  Object3D** objs = (Object3D**)ruby_xmalloc (sizeof(Object3D*)*num);

  VALUE val_objs = rb_ary_new2 (num);
  for (int i = 0;i < num; i++) {
    rb_ary_push (val_objs, (VALUE)objs[i]->getExportedEntity());
  }
  ruby_xfree (objs);
  
  return val_objs;
}

VALUE ruby_Object3D_get_user_id (VALUE self)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);

  int id = p->getUserID ();

  return INT2NUM(id);
}

VALUE ruby_Object3D_get_user_object (VALUE self)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);

  void* ptr = p->getUserObject ();

  // 未実装。
  // ユーザーオブジェクトはRuby側からどう見えるべきなのか?

  return Qnil;
}

VALUE ruby_Object3D_remove_animation_track (VALUE self, VALUE val_animation_track)
{
  Object3D* p;
  AnimationTrack* anim_track;

  Data_Get_Struct (self, Object3D, p);
  Data_Get_Struct (val_animation_track, AnimationTrack, anim_track);

  p->removeAnimationTrack (anim_track);

  return Qnil;
}

VALUE ruby_Object3D_set_user_id (VALUE self, VALUE val_id)
{
  Object3D* p;
  int id;

  Data_Get_Struct (self, Object3D, p);
  id = NUM2INT (val_id);
  
  p->setUserID (id);

  return Qnil;
}

VALUE ruby_Object3D_set_user_object (VALUE self, VALUE val_user_object)
{
  Object3D* p;

  Data_Get_Struct (self, Object3D, p);

  // 未実装
  // Ruby側からどう見えるべきか？

  return Qnil;
}

/**
 * Object3DクラスのRubyへの登録.
 */
void register_Object3D ()
{
    // Object3D
    rb_cObject3D            = rb_define_class_under (rb_mM3G, "Object3D",            rb_cObject);

    rb_define_method (rb_cObject3D, "add_animation_track",    (VALUE(*)(...))ruby_Object3D_add_animation_track,       1);
    rb_define_method (rb_cObject3D, "animate",                (VALUE(*)(...))ruby_Object3D_animate,                   1);
    rb_define_method (rb_cObject3D, "duplicate",              (VALUE(*)(...))ruby_Object3D_duplicate,                 0);
    rb_define_method (rb_cObject3D, "find",                   (VALUE(*)(...))ruby_Object3D_find,                      1);
    rb_define_method (rb_cObject3D, "animation_track",        (VALUE(*)(...))ruby_Object3D_get_animation_track,       1);
    rb_define_method (rb_cObject3D, "animation_track_count",  (VALUE(*)(...))ruby_Object3D_get_animation_track_count, 0);
    rb_define_method (rb_cObject3D, "references",             (VALUE(*)(...))ruby_Object3D_get_references,            0);
    rb_define_method (rb_cObject3D, "user_id",                (VALUE(*)(...))ruby_Object3D_get_user_id,               0);
    rb_define_method (rb_cObject3D, "user_object",            (VALUE(*)(...))ruby_Object3D_get_user_object,           0);
    rb_define_method (rb_cObject3D, "remove_animation_track", (VALUE(*)(...))ruby_Object3D_remove_animation_track,    1);
    rb_define_method (rb_cObject3D, "user_id=",               (VALUE(*)(...))ruby_Object3D_set_user_id,               1);
    rb_define_method (rb_cObject3D, "user_object=",           (VALUE(*)(...))ruby_Object3D_set_user_object,           1);
}
