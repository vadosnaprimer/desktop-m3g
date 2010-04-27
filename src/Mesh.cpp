#include "Mesh.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Appearance.hpp"
#include "Exception.hpp"
#include "RenderState.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

Mesh:: Mesh (VertexBuffer* vertices_, int num_submesh,
             IndexBuffer** submeshes, Appearance** appearances_) : vertices(0)
{
  setObjectType (OBJTYPE_MESH);

  if (vertices_ == 0) {
    throw NullPointException (__FILE__, __func__, "VertexBuffer is NULL.");
  }
  if (num_submesh == 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of submesh is invalid, num_submesh=%d.", num_submesh);
  }
  if (submeshes == 0) {
    throw NullPointException (__FILE__, __func__, "IndexBuffer is NULL.");
  }
  if (appearances_ == 0) {
    throw NullPointException (__FILE__, __func__, "Appearances is NULL.");
  }

  vertices = vertices_;
  indices.reserve (num_submesh);
  for (int i = 0; i < num_submesh; i++ ) {
    indices.push_back (*submeshes++);
  }
  appearances.reserve (num_submesh);
  for (int i = 0; i < num_submesh; i++ ) {
    appearances.push_back (*appearances_++);
  }
}

Mesh:: Mesh (VertexBuffer* vertices, IndexBuffer* submesh, Appearance* appearance)
{
  *this = Mesh (vertices, 1, &submesh, &appearance);
}

Mesh:: ~Mesh ()
{
}

Mesh* Mesh:: duplicate () const
{
  Mesh* mesh = new Mesh (*this);
  Node* node = Node::duplicate();
  *(Node*)mesh = *node;
  delete node;
  return mesh;
}


int Mesh:: animate (int world_time)
{
  //cout << "Mesh: animate time=" << world_time << "\n";

  Node::animate (world_time);

  if (vertices) {
    vertices->animate (world_time);
  }

  for (int i = 0; i < (int)appearances.size(); i++) {
    appearances[i]->animate (world_time);
  }

  return 0;
}


Appearance* Mesh:: getAppearance (int index) const
{
  if (index < 0 || index >= (int)appearances.size()) {
    throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d, max=%d.", index, appearances.size());
  }
  return appearances[index];
}

IndexBuffer* Mesh:: getIndexBuffer (int index) const
{
  if (index < 0 || index >= (int)indices.size()) {
    throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d, max=%d.", index, indices.size());
  }
  return indices[index];
}

int Mesh:: getSubmeshCount () const
{
  return indices.size();
}

VertexBuffer* Mesh:: getVertexBuffer () const
{
  return vertices;
}

void Mesh:: setAppearance (int index, Appearance* appearance)
{
  if (index < 0 || index >= (int)appearances.size()) {
    throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d, max=%d.", index, appearances.size());
  }
  
  if (appearance) {
    appearances[index] = appearance;
  }
  else {
    std::vector<Appearance*>::iterator it = appearances.begin();
    it += index;
    appearances.erase (it);
  }

  // 古い方はdeleteした方が良い？
}

/**
 * Note: Mesh should be rendered only at second rendering pass(pass=2).
 *       In other cases, do nothing.
 */
void Mesh:: render (RenderState& state) const
{
  if (state.pass == -1) {
    for (int i = 0; i < (int)appearances.size(); i++) {
      state.valid_layers.push_back (appearances[i]->getLayer());
    }
  }
  if (state.pass != 2) {
    return;
  }

  //cout << "Mesh: render " << indices.size() << "メッシュ\n";

  // 注意：下の３つは厳密にこの順番でなければならない。変更不可

  // ノードαの設定
  Node::render (state);

  // 頂点データの指定
  vertices->render (state);

  // マテリアルとインデックスの指定
  for (int i = 0; i < (int)appearances.size(); i++) {
    if (appearances[i] && appearances[i]->getLayer() == state.layer) {
      appearances[i]->render (state);
      indices[i]->render (state);
    }
  }

}

std::ostream& Mesh:: print (std::ostream& out) const
{
  out << "Mesh: ";
  out << "  " << indices.size() << " submesh";
  VertexArray* vary = vertices->getPositions(0);
  if (vary)
    out << ",  " << vary->getVertexCount() << " vertices";
  else
    out << ",  0 vertices";
  out << ", node_alpha=" << getAlphaFactor();
  //for (int i = 0; i < (int)appearances.size(); i++) {
  //  out << *appearances[i];
  //}

  return out;
}


std::ostream& operator<< (std::ostream& out, const Mesh& mesh)
{
  return mesh.print (out);
}

