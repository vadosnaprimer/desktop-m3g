#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


VALUE ruby_PolygonMode_free (PolygonMode* ptr)
{
    ptr->~PolygonMode ();
    ruby_xfree (ptr);
}

VALUE ruby_PolygonMode_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(PolygonMode));
    return Data_Wrap_Struct (self, 0, ruby_PolygonMode_free, p);
}

VALUE ruby_PolygonMode_initialize (VALUE self)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    new (p) PolygonMode;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_PolygonMode_get_culling (VALUE self)
{
    PolygonMode* p;
    int culling;

    Data_Get_Struct (self, PolygonMode, p);
    culling = p->getCulling ();

    return INT2FIX (culling);
}

VALUE ruby_PolygonMode_get_shading (VALUE self)
{
    PolygonMode* p;
    int shading;

    Data_Get_Struct (self, PolygonMode, p);
    shading = p->getShading ();

    return INT2FIX(shading);
}

VALUE ruby_PolygonMode_get_winding (VALUE self)
{
    PolygonMode* p;
    int winding;

    Data_Get_Struct (self, PolygonMode, p);
    winding = p->getWinding ();

    return INT2FIX(winding);
}

VALUE ruby_PolygonMode_is_local_camera_lighting_enabled (VALUE self)
{
    PolygonMode* p;
    bool enabled;

    Data_Get_Struct (self, PolygonMode, p);
    enabled = p->isLocalCameraLightingEnabled ();
    
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_PolygonMode_is_perspective_correction_enabled (VALUE self)
{
    PolygonMode* p;
    bool enabled;

    Data_Get_Struct (self, PolygonMode, p);
    enabled = p->isPerspectiveCorrectionEnabled ();

    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_PolygonMode_is_two_sided_lighting_enabled (VALUE self)
{
    PolygonMode* p;
    bool enabled;

    Data_Get_Struct (self, PolygonMode, p);
    enabled = p->isTwoSidedLightingEnabled ();

    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_PolygonMode_set_culling (VALUE self, VALUE val_mode)
{
    PolygonMode* p;
    int mode;

    Data_Get_Struct (self, PolygonMode, p);
    mode = FIX2INT (val_mode);

    p->setCulling (mode);

    return Qnil;
}

VALUE ruby_PolygonMode_set_local_camera_lighting_enable (VALUE self, VALUE val_enable)
{
    PolygonMode* p;
    bool enable;

    Data_Get_Struct (self, PolygonMode, p);
    enable = (val_enable == Qtrue) ? true : false;

    p->setLocalCameraLightingEnable (enable);

    return Qnil;
}

VALUE ruby_PolygonMode_set_perspective_correction_enable (VALUE self, VALUE val_enable)
{
    PolygonMode* p;
    bool enable;

    Data_Get_Struct (self, PolygonMode, p);
    enable = (val_enable == Qtrue) ? true : false;

    p->setPerspectiveCorrectionEnable (enable);

    return Qnil;
}

VALUE ruby_PolygonMode_set_shading (VALUE self, VALUE val_mode)
{
    PolygonMode* p;
    int mode;

    Data_Get_Struct (self, PolygonMode, p);
    mode = FIX2INT (val_mode);

    p->setShading (mode);

    return Qnil;
}

VALUE ruby_PolygonMode_set_two_sided_lighting_enable (VALUE self, VALUE val_enable)
{
    PolygonMode* p;
    bool enable;

    Data_Get_Struct (self, PolygonMode, p);
    enable = (val_enable == Qtrue) ? true : false;

    p->setTwoSidedLightingEnable (enable);

    return Qnil;
}

VALUE ruby_PolygonMode_set_winding (VALUE self, VALUE val_mode)
{
    PolygonMode* p;
    int mode; 

    mode = FIX2INT (val_mode);

    Data_Get_Struct (self, PolygonMode, p);
    p->setWinding (mode);

    return Qnil;
}


void register_PolygonMode ()
{
     // PolygonMode
    rb_cPolygonMode         = rb_define_class_under (rb_mM3G, "PolygonMode",         rb_cObject3D);

     rb_define_const (rb_cPolygonMode, "CULL_BACK",    INT2FIX(PolygonMode::CULL_BACK));
     rb_define_const (rb_cPolygonMode, "CULL_FRONT",   INT2FIX(PolygonMode::CULL_FRONT));
     rb_define_const (rb_cPolygonMode, "CULL_NONE",    INT2FIX(PolygonMode::CULL_NONE));
     rb_define_const (rb_cPolygonMode, "SHADE_FLAT",   INT2FIX(PolygonMode::SHADE_FLAT));
     rb_define_const (rb_cPolygonMode, "SHADE_SMOOTH", INT2FIX(PolygonMode::SHADE_SMOOTH));
     rb_define_const (rb_cPolygonMode, "WINDING_CCW",  INT2FIX(PolygonMode::WINDING_CCW));
     rb_define_const (rb_cPolygonMode, "WINDING_CW",   INT2FIX(PolygonMode::WINDING_CW));
     
     rb_define_alloc_func (rb_cPolygonMode, ruby_PolygonMode_allocate);
     rb_define_private_method (rb_cPolygonMode, "initialize",              (VALUE(*)(...))ruby_PolygonMode_initialize,0);

     rb_define_method (rb_cPolygonMode, "culling",                         (VALUE(*)(...))ruby_PolygonMode_get_culling,                       0);
     rb_define_method (rb_cPolygonMode, "shading",                         (VALUE(*)(...))ruby_PolygonMode_get_shading,                       0);
     rb_define_method (rb_cPolygonMode, "winding",                         (VALUE(*)(...))ruby_PolygonMode_get_winding,                       0);
     rb_define_method (rb_cPolygonMode, "local_camera_lighting_enabled?",  (VALUE(*)(...))ruby_PolygonMode_is_local_camera_lighting_enabled,  0);
     rb_define_method (rb_cPolygonMode, "perspective_correction_enabled?", (VALUE(*)(...))ruby_PolygonMode_is_perspective_correction_enabled, 0);
     rb_define_method (rb_cPolygonMode, "two_sided_lighting_enabled?",     (VALUE(*)(...))ruby_PolygonMode_is_two_sided_lighting_enabled,     0);
     rb_define_method (rb_cPolygonMode, "culling=",                        (VALUE(*)(...))ruby_PolygonMode_set_culling,                       1);
     rb_define_method (rb_cPolygonMode, "local_camera_lighting_enable=",   (VALUE(*)(...))ruby_PolygonMode_set_local_camera_lighting_enable,  1);
     rb_define_method (rb_cPolygonMode, "perspective_correction_enable=",  (VALUE(*)(...))ruby_PolygonMode_set_perspective_correction_enable, 1);
     rb_define_method (rb_cPolygonMode, "shading=",                        (VALUE(*)(...))ruby_PolygonMode_set_shading,                       1);
     rb_define_method (rb_cPolygonMode, "two_sided_lighting_enable=",      (VALUE(*)(...))ruby_PolygonMode_set_two_sided_lighting_enable,     1);
     rb_define_method (rb_cPolygonMode, "winding=",                        (VALUE(*)(...))ruby_PolygonMode_set_winding,                       1);
}
