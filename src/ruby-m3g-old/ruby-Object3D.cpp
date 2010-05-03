#include <new>
#include "ruby.h"
#include "Object3D.hpp"
using namespace m3g;


VALUE ruby_Object3D_free (Object3D* ptr)
{
    ptr->~Object3D ();
    ruby_xfree (ptr);
}

VALUE ruby_Object3D_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Object3D));
    return Data_Wrap_Struct (self, NULL, ruby_Object3D_free, p);
}

VALUE ruby_Object3D_initialize (VALUE self)
{
    Object3D* p;
    Data_Get_Struct (self, Object3D, p);
    new (p) Object3D;
    return Qnil;
}


VALUE binder_Object3D_add_animation_track (VALUE self, VALUE val_animationTrack)
{
    return Qnil;
}

VALUE binder_Object3D_animate (VALUE self)
{
    return Qnil;
}

VALUE binder_Object3D_duplicate (VALUE self)
{
    return Qnil;
}

VALUE binder_Object3D_find (VALUE self, VALUE val_userID)
{
    return Qnil;
}

VALUE binder_Object3D_get_animation_track (VALUE self, VALUE index)
{
    return Qnil;
}

VALUE binder_Object3D_get_animation_track_count (VALUE self)
{
    return Qnil;
}

VALUE binder_Object3D_get_references (VALUE self)
{
    // 戻り値はObject3Dの配列
    return Qnil;
}

VALUE binder_Object3D_get_user_id (VALUE self)
{
    return Qnil;
}

VALUE binder_Object3D_get_user_object (VALUE self)
{
    return Qnil;
}

VALUE binder_Object3D_remove_animation_track (VALUE self, VALUE val_animationTrack)
{
    return Qnil;
}

VALUE binder_Object3D_set_user_id (VALUE self)
{
    return Qnil;
}

VALUE binder_Object3D_set_user_object (VALUE self, VALUE val_userObject)
{
    return Qnil;
}


void register_Object3D (VALUE rb_cObject3D)
{
    // Object3D
    rb_define_alloc_func (rb_cObject3D, ruby_Object3D_allocate);
    rb_define_private_method (rb_cObject3D, "initialize", (VALUE(*)(...))ruby_Object3D_initialize, 0);

    rb_define_method (rb_cObject3D, "add_animation_track",    (VALUE(*)(...))binder_Object3D_add_animation_track, 1); 
    rb_define_method (rb_cObject3D, "animate",                (VALUE(*)(...))binder_Object3D_animate, 1); 
    rb_define_method (rb_cObject3D, "duplicate",              (VALUE(*)(...))binder_Object3D_duplicate, 0); 
    rb_define_method (rb_cObject3D, "find",                   (VALUE(*)(...))binder_Object3D_find, 1); 
    rb_define_method (rb_cObject3D, "animation_track",        (VALUE(*)(...))binder_Object3D_get_animation_track, 1); 
    rb_define_method (rb_cObject3D, "animation_track_count",  (VALUE(*)(...))binder_Object3D_get_animation_track_count, 0); 
    rb_define_method (rb_cObject3D, "references",             (VALUE(*)(...))binder_Object3D_get_references, 0);
    rb_define_method (rb_cObject3D, "user_id",                (VALUE(*)(...))binder_Object3D_get_user_id, 0);
    rb_define_method (rb_cObject3D, "user_object",            (VALUE(*)(...))binder_Object3D_get_user_object, 0);
    rb_define_method (rb_cObject3D, "remove_animation_track", (VALUE(*)(...))binder_Object3D_remove_animation_track, 1);
    rb_define_method (rb_cObject3D, "user_id=",               (VALUE(*)(...))binder_Object3D_set_user_id, 1);
    rb_define_method (rb_cObject3D, "user_object=",           (VALUE(*)(...))binder_Object3D_set_user_object, 1);

}
