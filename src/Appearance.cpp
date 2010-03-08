#include <iostream>
#include "Appearance.hpp"
#include "CompositingMode.hpp"
#include "Fog.hpp"
#include "Material.hpp"
#include "PolygonMode.hpp"
#include "Texture2D.hpp"
#include "CompositingMode.hpp"
#include "m3gexcept.hpp"
using namespace std;
using namespace m3g;


Appearance:: Appearance () :
  rendering_layer(0), polygon_mode(0), compositing_mode(0),
  material(0), fog(0)
{
  setObjectType (OBJTYPE_APPEARANCE);

  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    textures[i] = 0;
  }
}

Appearance:: ~Appearance ()
{
}

int Appearance:: animate (int world_time)
{
  //cout << "Appearance: animate, time=" << world_time << "\n";

  Object3D:: animate (world_time);

  if (polygon_mode) {
    polygon_mode->animate (world_time);
  }
  if (compositing_mode) {
    compositing_mode->animate (world_time);
  }
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (textures[i]) {
      textures[i]->animate (world_time);
    }
  }
  if (material) {
    material->animate (world_time);
  }
  if (fog) {
    fog->animate (world_time);
  }

  return 0;
}


CompositingMode* Appearance:: getCompositingMode () const
{
    return compositing_mode;
}

Fog* Appearance:: getFog () const
{
    return fog;
}

int Appearance:: getLayer () const
{
    return rendering_layer;
}

Material* Appearance:: getMaterial () const
{
    return material;
}

PolygonMode* Appearance:: getPolygonMode () const
{
    return polygon_mode;
}

Texture2D* Appearance:: getTexture (int index) const
{
  if (index < 0 || index >= MAX_TEXTURE_UNITS) {
    throw invalid_argument ("Too large texture index rather than you can use is specifi");
  }
  return textures[index];
}

void Appearance:: setCompositingMode (CompositingMode* mode)
{
  if (mode == NULL) {
    throw null_point_error ("Null compositing mode is specified.\n");
  }
  compositing_mode = mode;
}

void Appearance:: setFog (Fog* f)
{
  if (f == NULL) {
    throw null_point_error ("Null fog is specified.\n");
  }
  fog = f;
}

void Appearance:: setLayer (int layer)
{
  rendering_layer = layer;
}

void Appearance:: setMaterial (Material* mat)
{
  if (mat == NULL) {
    throw null_point_error ("Null material is specified.\n");
  }
  material = mat;
}

void Appearance:: setPolygonMode (PolygonMode* mode)
{
  if (mode == NULL) {
    throw null_point_error ("Null polygon mode is specified.\n");
  }
  polygon_mode = mode;
}

void Appearance:: setTexture (int index, Texture2D* texture)
{
  if (index < 0 || index >= MAX_TEXTURE_UNITS) {
    throw invalid_argument ("Too large texture index rather than you can use is specifi");
  }
  if (texture == NULL) {
    throw null_point_error ("Null texture is specified.\n");
  }

  textures[index] = texture;
}


void Appearance:: findByObjectType (int type, std::vector<Object3D*>& objs) const
{
  if (polygon_mode) {
    polygon_mode->findByObjectType (type, objs);
  }
  if (compositing_mode) {
    compositing_mode->findByObjectType (type, objs);
  }
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (textures[i]) {
      textures[i]->findByObjectType (type, objs);
    }
  }
  if (material) {
    material->findByObjectType (type, objs);
  }
  if (fog) {
    fog->findByObjectType (type, objs);
  }

  if (getObjectType() == type) {
    objs.push_back (const_cast<Appearance*>(this));
  }
}

/**
 * Note: Appearance should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Appearance:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  //cout << "Appearance: render\n";

  if (fog) {
    fog->render (pass, index);
  }
  if (material) {
    material->render (pass, index);
  }
  if (compositing_mode) {
    compositing_mode->render (pass, index);
  }

  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (textures[i]) {
      textures[i]->render (pass, i);
    }
  }

}



std::ostream& Appearance:: print (std::ostream& out) const
{
  return out;
}


ostream& operator<< (ostream& out, const Appearance& a)
{
    return out;
}

