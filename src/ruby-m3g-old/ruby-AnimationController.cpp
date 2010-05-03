#include <new>
#include "ruby.h"
#include "AnimationController.hpp"
using namespace m3g;

VALUE ruby_AnimationController_free (AnimationController* ptr)
{
    ptr->~AnimationController ();
    ruby_xfree (ptr);
}

VALUE ruby_AnimationController_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(AnimationController));
    return Data_Wrap_Struct (self, NULL, ruby_AnimationController_free, p);
}

VALUE ruby_AnimationController_initialize (VALUE self)
{
    AnimationController* p;
    Data_Get_Struct (self, AnimationController, p);
    new (p) AnimationController;
    return Qnil;
}

VALUE ruby_AnimationController_get_active_interval (VALUE self)
{
    return Qnil;
}

VALUE ruby_AnimationController_get_position (VALUE self, VALUE val_world_time)
{
    return Qnil;
}

VALUE ruby_AnimationController_get_ref_world_time (VALUE self)
{
    return Qnil;
}

VALUE ruby_AnimationController_get_speed (VALUE self)
{
    return Qnil;
}

VALUE ruby_AnimationController_get_weight (VALUE self)
{
    return Qnil;
}

VALUE ruby_AnimationController_set_active_interval (VALUE self, VALUE val_start_end)
{
    return Qnil;
}

VALUE ruby_AnimationController_set_position (VALUE self, VALUE val_sequence_time_world_time)
{
    return Qnil;
}

VALUE ruby_AnimationController_set_speed (VALUE self, VALUE val_spped_world_time)
{
    return Qnil;
}

VALUE ruby_AnimationController_set_weight (VALUE self, VALUE val_weight)
{
    return Qnil;
}

void register_AnimationController (VALUE rb_cAnimationController)
{
    // AnimationController
    rb_define_alloc_func (rb_cAnimationController, ruby_AnimationController_allocate);
    rb_define_private_method (rb_cAnimationController, "initialize", (VALUE(*)(...))ruby_AnimationController_initialize, 0);

    rb_define_method (rb_cAnimationController, "active_interval",  (VALUE(*)(...))ruby_AnimationController_get_active_interval, 0); 
    rb_define_method (rb_cAnimationController, "position",         (VALUE(*)(...))ruby_AnimationController_get_position, 1); 
    rb_define_method (rb_cAnimationController, "ref_world_time",   (VALUE(*)(...))ruby_AnimationController_get_ref_world_time, 0); 
    rb_define_method (rb_cAnimationController, "speed",            (VALUE(*)(...))ruby_AnimationController_get_speed, 0); 
    rb_define_method (rb_cAnimationController, "weight",           (VALUE(*)(...))ruby_AnimationController_get_weight, 0); 
    rb_define_method (rb_cAnimationController, "active_interval=", (VALUE(*)(...))ruby_AnimationController_set_active_interval, 1);
    rb_define_method (rb_cAnimationController, "position=",        (VALUE(*)(...))ruby_AnimationController_set_position, 1);
    rb_define_method (rb_cAnimationController, "speed=",           (VALUE(*)(...))ruby_AnimationController_set_speed, 1);
    rb_define_method (rb_cAnimationController, "weight=",          (VALUE(*)(...))ruby_AnimationController_set_weight, 1); 

}
