#include <iostream>
#include "Appearance.hpp"
#include "CompositingMode.hpp"
#include "Fog.hpp"
#include "Material.hpp"
#include "PolygonMode.hpp"
#include "Texture2D.hpp"
#include "CompositingMode.hpp"
#include "Exception.hpp"
#include "RenderState.hpp"
using namespace std;
using namespace m3g;


Appearance:: Appearance () :
  rendering_layer(0), polygon_mode(0), compositing_mode(0),
  material(0), fog(0)
{
  setObjectType (OBJTYPE_APPEARANCE);

  for (int i = 0; i < MAX_TEXTURE_UNITS; i++)
    textures.push_back (0);
}

Appearance:: ~Appearance ()
{
}

Appearance* Appearance:: duplicate () const
{
  return new Appearance (*this);
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

  for (int i = 0; i < (int)textures.size(); i++) {
    if (textures[i])
      textures[i]->animate (world_time);
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
  if (index < 0 || index >= (int)textures.size()) {
    throw IndexOutOfBoundsException (__FILE__, __func__, "Texture index is inalid, index=%d", index);
  }
  return textures[index];
}

void Appearance:: setCompositingMode (CompositingMode* mode)
{
  // null is ok, use default.
  compositing_mode = mode;
}

void Appearance:: setFog (Fog* f)
{
  if (f == NULL) {
    throw NullPointException (__FILE__, __func__, "Null fog is specified.");
  }
  fog = f;
}

void Appearance:: setLayer (int layer)
{
  // TODO: ここ値の範囲チェック忘れてないか？
  if (layer < -63 || layer > 64) {
    throw IllegalArgumentException (__FILE__, __func__, "Lyaer is invalid, layer=%d.", layer);
  }
  rendering_layer = layer;
}

void Appearance:: setMaterial (Material* mat)
{
  // null is ok, use default.
  material = mat;
}

void Appearance:: setPolygonMode (PolygonMode* mode)
{
  // null is ok, use default.
  polygon_mode = mode;
}

void Appearance:: setTexture (int index, Texture2D* texture)
{
  if (index < 0 || index >= (int)textures.size()) {
    throw IndexOutOfBoundsException (__FILE__, __func__, "Texture unit index is invalid, i=%d in [0,%d).", index, textures.size());
  }
  if (texture == NULL) {
    throw NullPointException (__FILE__, __func__, "Null texture is specified.");
  }

  textures[index] = texture;
}


/**
 * Note: Appearance should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void Appearance:: render (RenderState& state) const
{
  if (state.pass != 2) {
    return;
  }

  //cout << "Appearance: render\n";

  if (fog)
    fog->render (state);
  else
    Fog:: renderX ();

  if (material)
    material->render (state);
  else
    Material:: renderX ();

  if (compositing_mode)
    compositing_mode->render (state);
  else
    CompositingMode:: renderX ();

  if (polygon_mode)
    polygon_mode->render (state);
  else
    PolygonMode:: renderX ();

  // ここのgl関数はTexture2Dの中に移動しようか？
  // 注意：テクスチャーマトリックスは独立に複数あるので
  // それぞれについて初期化が必要。

  glMatrixMode (GL_TEXTURE);

  glEnable (GL_TEXTURE_2D);
  for (int i = 0; i < (int)textures.size(); i++) {
    if (textures[i]) {
      glActiveTexture       (GL_TEXTURE0+i);           // テクスチャーユニットの選択     
      glEnable              (GL_TEXTURE_2D);           // テクスチャーユニットの有効化
      textures[i]->render (state);
    } else {
      glActiveTexture       (GL_TEXTURE0+i);            // テクスチャーユニットの選択     
      glDisable             (GL_TEXTURE_2D);            // テクスチャーユニットの無効化
      Texture2D:: renderX ();
    }
  }

  glMatrixMode (GL_MODELVIEW);
}



std::ostream& Appearance:: print (std::ostream& out) const
{
  out << "Appearance: ";
  out << "  layer=" << rendering_layer;
  if (polygon_mode)
    out << ", polygon_mode=" << *polygon_mode;
  else
    out << ", polygon_mode=DEFAULT";
  if (compositing_mode)
    out << ", compositing_mode=" << *compositing_mode;
  else
    out << ", compositing_mode=DEFAULT";
  if (material)
    out << ", material=" << *material;
  else
    out << ", mterial=DEFAULT";
  for (int i = 0; i < (int)textures.size(); i++) {
    if (textures[i])
      out << ", textures[" << i << "]=" << *textures[i];
    else
      out << ", textures[" << i << "]=NOT FOUND";
  }
  if (fog) 
    out << ", fog=" << *fog;
  else
    out << ", fog=DEFAULT";
  return out;
}


ostream& operator<< (ostream& out, const Appearance& app)
{
  return app.print(out);
}

