#include <iostream>
#include "ruby.h"
#include "m3g.hpp"
#include "ruby-m3g.hpp"
using namespace m3g;
using namespace std;

namespace {
	struct TextureAccessor {
		Appearance* appearance;
	};
	VALUE rb_cAppearance_TextureAccessor;
}

VALUE ruby_Appearance_free (Appearance* ptr)
{
    ptr->~Appearance ();
    ruby_xfree (ptr);
}

VALUE ruby_Appearance_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(Appearance));
    return Data_Wrap_Struct (self, 0, ruby_Appearance_free, p);
}

VALUE ruby_Appearance_initialize (VALUE self)
{
    Appearance* p;
    Data_Get_Struct (self, Appearance, p);
    new (p) Appearance;
    p->setExportedEntity ((void*)self);
    return self;
}

VALUE ruby_Appearance_get_compositing_mode (VALUE self)
{
  Appearance* p;
  CompositingMode* cmode;

  Data_Get_Struct (self, Appearance, p);

  cmode = p->getCompositingMode ();

  return (VALUE)cmode->getExportedEntity();
}

VALUE ruby_Appearance_get_fog (VALUE self)
{
  Appearance* p;
  Fog* fog;

  Data_Get_Struct (self, Appearance, p);

  fog = p->getFog ();
  
  return (VALUE)fog->getExportedEntity();
}

VALUE ruby_Appearance_get_layer (VALUE self)
{
  Appearance* p;
  int layer;

  Data_Get_Struct (self, Appearance, p);
  
  layer = p->getLayer ();

  return INT2FIX(layer);
}

VALUE ruby_Appearance_get_material (VALUE self)
{
  Appearance* p;
  Material* mat;

  Data_Get_Struct (self, Appearance, p);

  mat = p->getMaterial ();

  return mat ? (VALUE)mat->getExportedEntity() : Qnil;
}

VALUE ruby_Appearance_get_polygon_mode (VALUE self)
{
  Appearance* p;
  PolygonMode* pmode;

  Data_Get_Struct (self, Appearance, p);

  pmode = p->getPolygonMode ();

  return pmode ? (VALUE)pmode->getExportedEntity() : Qnil;
}

VALUE ruby_Appearance_get_texture (VALUE self)
{
  Appearance* p;
  Data_Get_Struct (self, Appearance, p);

  TextureAccessor* accessor;
  VALUE val_accessor = Data_Make_Struct (rb_cAppearance_TextureAccessor, TextureAccessor, 0, -1, accessor);
  accessor->appearance = p;

  return val_accessor;
}

VALUE ruby_Appearance_set_compositing_mode (VALUE self, VALUE val_compositing_mode)
{
  Appearance* p;
  CompositingMode* cmode;

  Data_Get_Struct (self, Appearance, p);
  Data_Get_Struct (val_compositing_mode, CompositingMode, cmode);

  p->setCompositingMode (cmode);

  return Qnil;
}

VALUE ruby_Appearance_set_fog (VALUE self, VALUE val_fog)
{
  Appearance* p;
  Fog* fog;

  Data_Get_Struct (self, Appearance, p);
  Data_Get_Struct (val_fog, Fog, fog);

  p->setFog (fog);

  return Qnil;
}

VALUE ruby_Appearance_set_layer (VALUE self, VALUE val_layer)
{
  Appearance* p;
  int layer;

  Data_Get_Struct (self, Appearance, p);
  layer = FIX2INT (val_layer);

  p->setLayer (layer);

  return Qnil;
}

VALUE ruby_Appearance_set_material (VALUE self, VALUE val_material)
{
  Appearance* p;
  Material* mat;

  Data_Get_Struct (self, Appearance, p);
  Data_Get_Struct (val_material, Material, mat);

  p->setMaterial (mat);

  return Qnil;
}

VALUE ruby_Appearance_set_polygon_mode (VALUE self, VALUE val_polygon_mode)
{
  Appearance* p;
  PolygonMode* pmode;

  Data_Get_Struct (self, Appearance, p);
  Data_Get_Struct (val_polygon_mode, PolygonMode, pmode);

  p->setPolygonMode (pmode);

  return Qnil;
}


/**
 * Appearance_TextureAccessor
 */

VALUE ruby_Appearance_TextureAccessor_allocate (VALUE self)
{
    void* p = ruby_xmalloc (sizeof(TextureAccessor));
    return Data_Wrap_Struct (self, 0, -1, p);
}

VALUE ruby_Appearance_TextureAccessor_initialize (VALUE self)
{
    TextureAccessor* p;
    Data_Get_Struct (self, TextureAccessor, p);
    return self;
}

VALUE ruby_Appearance_TextureAccessor_get_texture (VALUE self, VALUE val_index)
{
  TextureAccessor* p;
  Data_Get_Struct (self, TextureAccessor, p);
  int index = FIX2INT (val_index);
  Texture2D* tex;

  tex = p->appearance->getTexture (index);

  return tex ? (VALUE)tex->getExportedEntity() : Qnil;
}

VALUE ruby_Appearance_TextureAccessor_set_texture (VALUE self, VALUE val_index, VALUE val_tex)
{
  TextureAccessor* p;
  Data_Get_Struct (self, TextureAccessor, p);
  int index = FIX2INT (val_index);
  Texture2D* tex;
  Data_Get_Struct (val_tex, Texture2D, tex);

  p->appearance->setTexture (index, tex);

  return Qnil;
}

void register_Appearance ()
{
    // Appearance
    rb_cAppearance          = rb_define_class_under (rb_mM3G, "Appearance",          rb_cObject3D);

    rb_define_alloc_func (rb_cAppearance, ruby_Appearance_allocate);
    rb_define_private_method (rb_cAppearance, "initialize", (VALUE(*)(...))ruby_Appearance_initialize,          0);

    rb_define_method (rb_cAppearance, "compositing_mode", (VALUE(*)(...))ruby_Appearance_get_compositing_mode,  0); 
    rb_define_method (rb_cAppearance, "fog",              (VALUE(*)(...))ruby_Appearance_get_fog,               0); 
    rb_define_method (rb_cAppearance, "layer",            (VALUE(*)(...))ruby_Appearance_get_layer,             0); 
    rb_define_method (rb_cAppearance, "material",         (VALUE(*)(...))ruby_Appearance_get_material,          0); 
    rb_define_method (rb_cAppearance, "polygonMode",      (VALUE(*)(...))ruby_Appearance_get_polygon_mode,      0); 
    rb_define_method (rb_cAppearance, "texture",          (VALUE(*)(...))ruby_Appearance_get_texture,           0); 
    rb_define_method (rb_cAppearance, "compositing_mode=", (VALUE(*)(...))ruby_Appearance_set_compositing_mode, 1); 
    rb_define_method (rb_cAppearance, "fog=",              (VALUE(*)(...))ruby_Appearance_set_fog,              1); 
    rb_define_method (rb_cAppearance, "layer=",            (VALUE(*)(...))ruby_Appearance_set_layer,            1); 
    rb_define_method (rb_cAppearance, "material=",         (VALUE(*)(...))ruby_Appearance_set_material,         1); 
    rb_define_method (rb_cAppearance, "polygon_mode=",     (VALUE(*)(...))ruby_Appearance_set_polygon_mode,     1); 

    // Appearance_TextureAccessor
     rb_cAppearance_TextureAccessor  = rb_define_class_under (rb_cAppearance, "TextureAccessor", rb_cObject);

    rb_define_method (rb_cAppearance_TextureAccessor, "[]",     (VALUE(*)(...))ruby_Appearance_TextureAccessor_get_texture,  1); 
    rb_define_method (rb_cAppearance_TextureAccessor, "[]=",    (VALUE(*)(...))ruby_Appearance_TextureAccessor_set_texture,  2); 

}
