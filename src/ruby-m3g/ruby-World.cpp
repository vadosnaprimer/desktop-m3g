#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


VALUE ruby_World_free (World* ptr)
{
    __TRY__;
    ptr->~World ();
    __CATCH__;
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
    __TRY__;
    new (p) World;
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_World_get_active_camera (VALUE self)
{
    World* p;
    Data_Get_Struct (self, World, p);
    Camera* cam;
    __TRY__;
    cam = p->getActiveCamera();
    __CATCH__;
    return cam ? (VALUE)cam->getExportedEntity() : Qnil;
}

VALUE ruby_World_get_background (VALUE self)
{
    World* p;
    Data_Get_Struct (self, World, p);
    Background* bg;
    __TRY__;
    bg = p->getBackground();
    __CATCH__;
    return bg ? (VALUE)bg->getExportedEntity() : Qnil;
}

VALUE ruby_World_set_active_camera (VALUE self, VALUE val_camera)
{
    World* p;
    Data_Get_Struct (self, World, p);
    Camera* cam;
    Data_Get_Struct (val_camera, Camera, cam);
    __TRY__;
    p->setActiveCamera (cam);
    __CATCH__;
    return Qnil;
}

VALUE ruby_World_set_background (VALUE self, VALUE val_background)
{
    World* p;
    Data_Get_Struct (self, World, p);
    Background* bg;
    Data_Get_Struct (val_background, Background, bg);
    __TRY__;
    p->setBackground (bg);
    __CATCH__;
    return Qnil;
}

void register_World ()
{
    // World
    rb_cWorld = rb_define_class_under (rb_mM3G, "World",               rb_cGroup);

    rb_define_alloc_func (rb_cWorld, ruby_World_allocate);
    rb_define_private_method (rb_cWorld, "initialize", (VALUE(*)(...))ruby_World_initialize, 0);

    rb_define_method (rb_cWorld, "active_camera",  (VALUE(*)(...))ruby_World_get_active_camera,  0);
    rb_define_method (rb_cWorld, "background",     (VALUE(*)(...))ruby_World_get_background,     0);
    rb_define_method (rb_cWorld, "active_camera=", (VALUE(*)(...))ruby_World_set_active_camera,  1);
    rb_define_method (rb_cWorld, "background=",    (VALUE(*)(...))ruby_World_set_background,     1);


}
