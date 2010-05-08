#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
  VALUE rb_cAnimationController_ActiveInterval;
};

VALUE ruby_AnimationController_free (AnimationController* ptr)
{
    ptr->~AnimationController ();
    ruby_xfree (ptr);
}

VALUE ruby_AnimationController_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(AnimationController));
    return Data_Wrap_Struct (self, 0, ruby_AnimationController_free, p);
}

VALUE ruby_AnimationController_initialize (VALUE self)
{
    AnimationController* p;
    Data_Get_Struct (self, AnimationController, p);
    new (p) AnimationController;

    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_AnimationController_get_active_interval (VALUE self)
{
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);
  
  AnimationController::ActiveInterval* active_interval;
  VALUE val_active_interval = Data_Make_Struct (rb_cAnimationController_ActiveInterval, AnimationController::ActiveInterval, 0, -1, active_interval);
  active_interval->start = p->getActiveIntervalStart ();
  active_interval->end   = p->getActiveIntervalEnd ();
  return val_active_interval;
}

VALUE ruby_AnimationController_get_position (VALUE self, VALUE val_world_time)
{
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);
  int world_time = FIX2INT(val_world_time);

  float sequence_time = sequence_time = p->getPosition (world_time);

  return rb_float_new (sequence_time);
}

VALUE ruby_AnimationController_get_ref_world_time (VALUE self)
{
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);

  int ref_world_time = p->getRefWorldTime ();

  return INT2FIX(ref_world_time);
}

VALUE ruby_AnimationController_get_speed (VALUE self)
{
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);

  float speed = p->getSpeed ();

  return rb_float_new(speed);
}

VALUE ruby_AnimationController_get_weight (VALUE self)
{
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);

  float weight = p->getWeight ();

  return rb_float_new(weight);
}

VALUE ruby_AnimationController_set_active_interval (VALUE self, VALUE val_args)
{
  VALUE val_start = rb_ary_entry(val_args, 0);
  VALUE val_end   = rb_ary_entry(val_args, 1);
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);
  int start = FIX2INT(val_start);
  int end   = FIX2INT(val_end);

  p->setActiveInterval (start, end);

  return Qnil;
}

VALUE ruby_AnimationController_set_position (VALUE self, VALUE val_args)
{
  VALUE val_sequence_time = rb_ary_entry(val_args, 0);
  VALUE val_world_time    = rb_ary_entry(val_args, 1);
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);
  float sequence_time = NUMERIC2FLOAT(val_sequence_time);
  int  world_time     = FIX2INT(val_world_time);

  p->setPosition (sequence_time, world_time);

  return Qnil;
}

VALUE ruby_AnimationController_set_speed (VALUE self, VALUE val_args)
{
  VALUE val_speed      = rb_ary_entry(val_args, 0);
  VALUE val_world_time = rb_ary_entry(val_args, 1);
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);
  float speed      = NUMERIC2FLOAT (val_speed);
  int   world_time = FIX2INT (val_world_time);

  p->setSpeed (speed, world_time);

  return Qnil;
}

VALUE ruby_AnimationController_set_weight (VALUE self, VALUE val_weight)
{
  AnimationController* p;
  Data_Get_Struct (self, AnimationController, p);
  int weight = FIX2INT(val_weight);

  p->setWeight (weight);

  return Qnil;
}

/**
 * AnimationController::ActiveInterval
 */

VALUE ruby_AnimationController_ActiveInterval_allocate (VALUE self)
{
  void* p = ruby_xmalloc (sizeof(AnimationController::ActiveInterval));
  return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_AnimationController_ActiveInterval_initialize (VALUE self, VALUE val_start, VALUE val_end)
{
  AnimationController::ActiveInterval* p;
  Data_Get_Struct (self, AnimationController::ActiveInterval, p);
  p->start = NUMERIC2FLOAT(val_start);
  p->end   = NUMERIC2FLOAT(val_end);
  return self;
}

VALUE ruby_AnimationController_ActiveInterval_get_start (VALUE self)
{
  AnimationController::ActiveInterval* p;
  Data_Get_Struct (self, AnimationController::ActiveInterval, p);
  return rb_float_new(p->start);
}

VALUE ruby_AnimationController_ActiveInterval_get_end (VALUE self)
{
  AnimationController::ActiveInterval* p;
  Data_Get_Struct (self, AnimationController::ActiveInterval, p);
  return rb_float_new(p->end);
}


void register_AnimationController ()
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

    // AnimationController::ActiveInterval
     rb_cAnimationController_ActiveInterval  = rb_define_class_under (rb_cAnimationController, "ActiveInterval", rb_cObject);

     rb_define_alloc_func (rb_cAnimationController_ActiveInterval, ruby_AnimationController_ActiveInterval_allocate);
     rb_define_private_method (rb_cAnimationController_ActiveInterval, "initialize", (VALUE(*)(...))ruby_AnimationController_ActiveInterval_initialize, 2);

     rb_define_method (rb_cAnimationController_ActiveInterval, "start",        (VALUE(*)(...))ruby_AnimationController_ActiveInterval_get_start,    0);
     rb_define_method (rb_cAnimationController_ActiveInterval, "end",        (VALUE(*)(...))ruby_AnimationController_ActiveInterval_get_end,    0);

}
