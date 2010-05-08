#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


VALUE ruby_Object3D_free (Object3D* ptr)
{
    ptr->~Object3D ();
    ruby_xfree (ptr);
}

VALUE ruby_Object3D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Object3D));
    return Data_Wrap_Struct (self, 0, ruby_Object3D_free, p);
}

VALUE ruby_Object3D_initialize (VALUE self)
{
    Object3D* p;
    Data_Get_Struct (self, Object3D, p);
    new (p) Object3D;
    p->setExportedEntity ((void*)self);
    return self;
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
  int world_time = FIX2INT(val_world_time);

  int ret = p->animate (world_time);

  return INT2FIX(ret);
}

VALUE ruby_Object3D_duplicate (VALUE self)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);

  Object3D* d = p->duplicate();
  VALUE val_d = Data_Wrap_Struct (rb_cObject3D, 0, ruby_Object3D_free, d);
  
  return val_d;
}

VALUE ruby_Object3D_find (VALUE self, VALUE val_user_id)
{
  Object3D* p;
  int user_id;
  
  Data_Get_Struct (self, Object3D, p);
  user_id = FIX2INT (val_user_id);

  Object3D* obj = p->find (user_id);
  cout << "obj = " << obj << "\n";
  return obj ? (VALUE)obj->getExportedEntity() : Qnil;
}

VALUE ruby_Object3D_get_animation_track (VALUE self, VALUE val_index)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);
  int index = FIX2INT (val_index);

  AnimationTrack* anim_track = p->getAnimationTrack (index);

  return anim_track ? (VALUE)anim_track->getExportedEntity() : Qnil;
}

VALUE ruby_Object3D_get_animation_track_count (VALUE self)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);

  int count = p->getAnimationTrackCount ();

  return INT2FIX(count);
}

VALUE ruby_Object3D_get_references (VALUE self)
{
  Object3D* p;
  Data_Get_Struct (self, Object3D, p);
  
  int num = p->getReferences (0);
  Object3D** objs = (Object3D**)ruby_xmalloc (sizeof(Object3D*)*num);

  VALUE val_objs = rb_ary_new ();
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

  return INT2FIX(id);
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
  id = FIX2INT (val_id);
  
  p->setUserID (id);

  return Qnil;
}

VALUE ruby_Object3D_set_user_object (VALUE self, VALUE val_user_object)
{
  Object3D* p;

  Data_Get_Struct (self, Object3D, p);

  // 未実装
  //p->setUserObject (0, 0);

  return Qnil;
}


void register_Object3D ()
{
    // Object3D
    rb_define_alloc_func (rb_cObject3D, ruby_Object3D_allocate);
    rb_define_private_method (rb_cObject3D, "initialize", (VALUE(*)(...))ruby_Object3D_initialize, 0);

    rb_define_method (rb_cObject3D, "add_animation_track",    (VALUE(*)(...))ruby_Object3D_add_animation_track, 1); 
    rb_define_method (rb_cObject3D, "animate",                (VALUE(*)(...))ruby_Object3D_animate, 1); 
    rb_define_method (rb_cObject3D, "duplicate",              (VALUE(*)(...))ruby_Object3D_duplicate, 0); 
    rb_define_method (rb_cObject3D, "find",                   (VALUE(*)(...))ruby_Object3D_find, 1); 
    rb_define_method (rb_cObject3D, "animation_track",        (VALUE(*)(...))ruby_Object3D_get_animation_track, 1); 
    rb_define_method (rb_cObject3D, "animation_track_count",  (VALUE(*)(...))ruby_Object3D_get_animation_track_count, 0);
    rb_define_method (rb_cObject3D, "references",             (VALUE(*)(...))ruby_Object3D_get_references, 0);
    rb_define_method (rb_cObject3D, "user_id",                (VALUE(*)(...))ruby_Object3D_get_user_id, 0);
    rb_define_method (rb_cObject3D, "user_object",            (VALUE(*)(...))ruby_Object3D_get_user_object, 0);
    rb_define_method (rb_cObject3D, "remove_animation_track", (VALUE(*)(...))ruby_Object3D_remove_animation_track, 1);
    rb_define_method (rb_cObject3D, "user_id=",               (VALUE(*)(...))ruby_Object3D_set_user_id, 1);
    rb_define_method (rb_cObject3D, "user_object=",           (VALUE(*)(...))ruby_Object3D_set_user_object, 1);
}
