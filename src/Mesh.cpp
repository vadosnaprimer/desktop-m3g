#include "Mesh.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Appearance.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

Mesh:: Mesh (VertexBuffer* vertices_,
	     int num_submesh, IndexBuffer** submeshes,
	     int num_appearance, Appearance** appearances_) :
  vertices(0)
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
  if (num_appearance == 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of appearance is invalid, num_appearance=%d.", num_appearance);
  }
  if (appearances_ == 0) {
    throw NullPointException (__FILE__, __func__, "Appearances is NULL.");
  }

  vertices = vertices_;
  indices.reserve (num_submesh);
  for (int i = 0; i < num_submesh; i++ ) {
    indices.push_back (*submeshes++);
  }
  appearances.reserve (num_appearance);
  for (int i = 0; i < num_appearance; i++ ) {
    appearances.push_back (*appearances_++);
  }
}

Mesh:: Mesh (VertexBuffer* vertices_, IndexBuffer* submesh, Appearance* appearance)
{
  if (vertices_ == 0) {
    throw NullPointException (__FILE__, __func__, "VertexBuffer is NULL.");
  }
  if (submesh == 0) {
    throw NullPointException (__FILE__, __func__, "IndexBuffer is NULL.");
  }
  if (appearance == 0) {
    throw NullPointException (__FILE__, __func__, "Appearance is NULL.");
  }
  //cout << "Mesh: add submesh = " << submesh << "\n";

  vertices = vertices_;
  indices.push_back (submesh);
  appearances.push_back (appearance);

  //for (int i = 0; i < (int)indices.size(); i++) {
  //  cout << "indices[" << i << "] = "<< indices[i] << "\n";
  //}
}

Mesh:: ~Mesh ()
{
}

Mesh* Mesh:: duplicate () const
{
  Mesh* mesh = new Mesh (*this);
  Node* node = Node::duplicate();
  *(Node*)mesh = *node;
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
 * 注意：この関数を修正した場合SkinnedMesh::render()も変更する。
 *       両者は vertices が skinned_vertices に変わった事を除けば
 *      まったく同一でなければならない。
 */
void Mesh:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  //for (int i = 0; i < (int)indices.size(); i++) {
  //  cout << "indices[" << i << "] = "<< indices[i] << "\n";
  //}


  //cout << "Mesh: render " << indices.size() << "メッシュ\n";
  Node::render (pass, index);

  if (vertices->getPositions(0)) {
    //cout << "Mesh: glEnableClientState (GL_VERTEX_ARRAY)\n";
    glEnableClientState (GL_VERTEX_ARRAY);
  }
  if (vertices->getNormals()) {
    //cout << "Mesh: glEnableClientState (GL_NORMAL_ARRAY)\n";
    glEnableClientState (GL_NORMAL_ARRAY);
  }
  if (vertices->getColors()) {
    //cout << "Mesh: glEnableClientState (GL_COLOR_ARRAY)\n";
    glEnableClientState (GL_COLOR_ARRAY);
  }
  
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (vertices->getTexCoords(i, 0)) {
      //cout << "Mesh: glEnableClientState (GL_TEXTURE_COORD_ARRAY)\n";
      glClientActiveTexture (GL_TEXTURE0+i);
      glEnableClientState (GL_TEXTURE_COORD_ARRAY);
    }
  }
  
  // 頂点データの指定
  vertices->render (pass, index);

  //cout << "Mesh: size = " << indices.size() << "\n";

  // インデックスの指定
  for (int i = 0; i < (int)indices.size(); i++) {
    //cout << "i = " << i << "\n";
    //cout << "app = " << appearances[i] << "\n";
    //cout << "ind = " << indices[i] << "\n";
    appearances[i]->render (pass, index);
    indices[i]->render (pass, index);
  }
  

  if (vertices->getPositions(0)) {
    glDisableClientState (GL_VERTEX_ARRAY);
  }
  if (vertices->getNormals()) {
    glDisableClientState (GL_NORMAL_ARRAY);
  }
  if (vertices->getColors()) {
    glDisableClientState (GL_COLOR_ARRAY);
  }
  
  for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
    if (vertices->getTexCoords(i, 0)) {
      glClientActiveTexture (GL_TEXTURE0+i);
      glDisableClientState (GL_TEXTURE_COORD_ARRAY);
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

  return out << "\n";
}


std::ostream& operator<< (std::ostream& out, const Mesh& mesh)
{
  return mesh.print (out);
}

