#include <new>
#include "ruby.h"
#include "World.hpp"
using namespace m3g;


VALUE ruby_World_free (World* ptr)
{
    ptr->~World ();
    ruby_xfree (ptr);
}

VALUE ruby_World_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(World));
    return Data_Wrap_Struct (self, NULL, ruby_World_free, p);
}

VALUE ruby_World_initialize (VALUE self)
{
    World* p;
    Data_Get_Struct (self, World, p);
    new (p) World;
    return Qnil;
}

VALUE ruby_World_get_active_camera (VALUE self)
{
    return Qnil;
}

VALUE ruby_World_get_background (VALUE self)
{
    return Qnil;
}

VALUE ruby_World_set_active_camera (VALUE self, VALUE val_camera)
{
    return Qnil;
}

VALUE ruby_World_set_background (VALUE self, VALUE val_background)
{
    return Qnil;
}

void register_World (VALUE rb_cWorld)
{
     // World
     rb_define_alloc_func (rb_cWorld, ruby_World_allocate);
     rb_define_private_method (rb_cWorld, "initialize", (VALUE(*)(...))ruby_World_initialize, 0);

     rb_define_method (rb_cWorld, "active_camera", (VALUE(*)(...))ruby_World_get_active_camera,  0);
     rb_define_method (rb_cWorld, "background",    (VALUE(*)(...))ruby_World_get_background,     0);
     rb_define_method (rb_cWorld, "active_camera=", (VALUE(*)(...))ruby_World_set_active_camera, 1);
     rb_define_method (rb_cWorld, "background=",    (VALUE(*)(...))ruby_World_set_background,    1);


}
