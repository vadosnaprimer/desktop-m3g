#include <new>
#include "ruby.h"
#include "Appearance.hpp"
using namespace m3g;

VALUE ruby_Appearance_free (Appearance* ptr)
{
    ptr->~Appearance ();
    ruby_xfree (ptr);
}

VALUE ruby_Appearance_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Appearance));
    return Data_Wrap_Struct (self, NULL, ruby_Appearance_free, p);
}

VALUE ruby_Appearance_initialize (VALUE self)
{
    Appearance* p;
    Data_Get_Struct (self, Appearance, p);
    new (p) Appearance;
    return Qnil;
}

VALUE ruby_Appearance_get_compositing_mode (VALUE self)
{
    return Qnil;
}

VALUE ruby_Appearance_get_fog (VALUE self)
{
    return Qnil;
}

VALUE ruby_Appearance_get_layer (VALUE self)
{
    return Qnil;
}

VALUE ruby_Appearance_get_material (VALUE self)
{
    return Qnil;
}

VALUE ruby_Appearance_get_polygon_mode (VALUE self)
{
    return Qnil;
}

VALUE ruby_Appearance_get_texture (VALUE self)
{
    return Qnil;
}

VALUE ruby_Appearance_set_compositing_mode (VALUE self, VALUE val_compositingMode)
{
    return Qnil;
}

VALUE ruby_Appearance_set_fog (VALUE self, VALUE val_fog)
{
    return Qnil;
}

VALUE ruby_Appearance_set_layer (VALUE self, VALUE val_layer)
{
    return Qnil;
}

VALUE ruby_Appearance_set_material (VALUE self, VALUE val_material)
{
    return Qnil;
}

VALUE ruby_Appearance_set_polygon_mode (VALUE self, VALUE val_polygon_mode)
{
    return Qnil;
}

VALUE ruby_Appearance_set_texture (VALUE self, VALUE val_index_and_texture)
{
    return Qnil;
}

void register_Appearance (VALUE rb_cAppearance)
{
    // Appearance
    rb_define_alloc_func (rb_cAppearance, ruby_Appearance_allocate);
    rb_define_private_method (rb_cAppearance, "initialize", (VALUE(*)(...))ruby_Appearance_initialize, 0);

    rb_define_method (rb_cAppearance, "compositing_mode", (VALUE(*)(...))ruby_Appearance_get_compositing_mode, 0); 
    rb_define_method (rb_cAppearance, "fog",              (VALUE(*)(...))ruby_Appearance_get_fog, 0); 
    rb_define_method (rb_cAppearance, "layer",            (VALUE(*)(...))ruby_Appearance_get_layer, 0); 
    rb_define_method (rb_cAppearance, "material",         (VALUE(*)(...))ruby_Appearance_get_material, 0); 
    rb_define_method (rb_cAppearance, "polygonMode",      (VALUE(*)(...))ruby_Appearance_get_polygon_mode, 0); 
    rb_define_method (rb_cAppearance, "texture",          (VALUE(*)(...))ruby_Appearance_get_texture, 1); 
    rb_define_method (rb_cAppearance, "compositing_mode=", (VALUE(*)(...))ruby_Appearance_set_compositing_mode, 1); 
    rb_define_method (rb_cAppearance, "fog=",              (VALUE(*)(...))ruby_Appearance_set_fog, 1); 
    rb_define_method (rb_cAppearance, "layer=",            (VALUE(*)(...))ruby_Appearance_set_layer, 1); 
    rb_define_method (rb_cAppearance, "material=",         (VALUE(*)(...))ruby_Appearance_set_material, 1); 
    rb_define_method (rb_cAppearance, "polygon_mode=",     (VALUE(*)(...))ruby_Appearance_set_polygon_mode, 1); 
    rb_define_method (rb_cAppearance, "texture=",          (VALUE(*)(...))ruby_Appearance_set_texture, 1);

}
