#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


VALUE ruby_World_free (World* ptr)
{
    ptr->~World ();
    ruby_xfree (ptr);
}

VALUE ruby_World_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(World));
    return Data_Wrap_Struct (self, 0, ruby_World_free, p);
}

VALUE ruby_World_initialize (VALUE self)
{
    World* p;
    Data_Get_Struct (self, World, p);
    new (p) World;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_World_get_active_camera (VALUE self)
{
    World* p;
    Camera* cam;

    Data_Get_Struct (self, World, p);

    cam = p->getActiveCamera();

    if (cam)
      return (VALUE)cam->getExportedEntity();
    else
      return Qnil;
}

VALUE ruby_World_get_background (VALUE self)
{
    World* p;
    Background* bg;

    Data_Get_Struct (self, World, p);

    bg = p->getBackground();

    if (bg)
      return (VALUE)bg->getExportedEntity();
    else
    return Qnil;
}

VALUE ruby_World_set_active_camera (VALUE self, VALUE val_camera)
{
    World* p;
    Camera* cam;

    Data_Get_Struct (self, World, p);
    Data_Get_Struct (val_camera, Camera, cam);

    p->setActiveCamera (cam);

    return Qnil;
}

VALUE ruby_World_set_background (VALUE self, VALUE val_background)
{
    World* p;
    Background* bg;

    Data_Get_Struct (self, World, p);
    Data_Get_Struct (val_background, Background, bg);

    p->setBackground (bg);

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
