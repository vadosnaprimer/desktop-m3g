#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;


VALUE ruby_PolygonMode_free (PolygonMode* ptr)
{
    __TRY__;
    ptr->~PolygonMode ();
    __CATCH__;
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
    __TRY__;
    new (p) PolygonMode;
    __CATCH__;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_PolygonMode_get_culling (VALUE self)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    int culling;
    __TRY__;
    culling = p->getCulling ();
    __CATCH__;
    return INT2NUM (culling);
}

VALUE ruby_PolygonMode_get_shading (VALUE self)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    int shading;
    __TRY__;
    shading = p->getShading ();
    __CATCH__;
    return INT2NUM(shading);
}

VALUE ruby_PolygonMode_get_winding (VALUE self)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    int winding;
    __TRY__;
    winding = p->getWinding ();
    __CATCH__;
    return INT2NUM(winding);
}

VALUE ruby_PolygonMode_is_local_camera_lighting_enabled (VALUE self)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    bool enabled;
    __TRY__;
    enabled = p->isLocalCameraLightingEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_PolygonMode_is_perspective_correction_enabled (VALUE self)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    bool enabled;
    __TRY__;
    enabled = p->isPerspectiveCorrectionEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_PolygonMode_is_two_sided_lighting_enabled (VALUE self)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    bool enabled;
    __TRY__;
    enabled = p->isTwoSidedLightingEnabled ();
    __CATCH__;
    return enabled ? Qtrue : Qfalse;
}

VALUE ruby_PolygonMode_set_culling (VALUE self, VALUE val_mode)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    int mode = NUM2INT (val_mode);
    __TRY__;
    p->setCulling (mode);
    __CATCH__;
    return Qnil;
}

VALUE ruby_PolygonMode_set_local_camera_lighting_enable (VALUE self, VALUE val_enable)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setLocalCameraLightingEnable (enable);
    __CATCH__;
    return Qnil;
}

VALUE ruby_PolygonMode_set_perspective_correction_enable (VALUE self, VALUE val_enable)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setPerspectiveCorrectionEnable (enable);
    __CATCH__;
    return Qnil;
}

VALUE ruby_PolygonMode_set_shading (VALUE self, VALUE val_mode)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    int mode = NUM2INT (val_mode);
    __TRY__;
    p->setShading (mode);
    __CATCH__;
    return Qnil;
}

VALUE ruby_PolygonMode_set_two_sided_lighting_enable (VALUE self, VALUE val_enable)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    bool enable = (val_enable == Qtrue) ? true : false;
    __TRY__;
    p->setTwoSidedLightingEnable (enable);
    __CATCH__;
    return Qnil;
}

VALUE ruby_PolygonMode_set_winding (VALUE self, VALUE val_mode)
{
    PolygonMode* p;
    Data_Get_Struct (self, PolygonMode, p);
    int mode = NUM2INT (val_mode);
    __TRY__;
    p->setWinding (mode);
    __CATCH__;
    return Qnil;
}


void register_PolygonMode ()
{
    // PolygonMode
    rb_cPolygonMode         = rb_define_class_under (rb_mM3G, "PolygonMode",         rb_cObject3D);

    rb_define_const (rb_cPolygonMode, "CULL_BACK",    INT2NUM(PolygonMode::CULL_BACK));
    rb_define_const (rb_cPolygonMode, "CULL_FRONT",   INT2NUM(PolygonMode::CULL_FRONT));
    rb_define_const (rb_cPolygonMode, "CULL_NONE",    INT2NUM(PolygonMode::CULL_NONE));
    rb_define_const (rb_cPolygonMode, "SHADE_FLAT",   INT2NUM(PolygonMode::SHADE_FLAT));
    rb_define_const (rb_cPolygonMode, "SHADE_SMOOTH", INT2NUM(PolygonMode::SHADE_SMOOTH));
    rb_define_const (rb_cPolygonMode, "WINDING_CCW",  INT2NUM(PolygonMode::WINDING_CCW));
    rb_define_const (rb_cPolygonMode, "WINDING_CW",   INT2NUM(PolygonMode::WINDING_CW));
     
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
