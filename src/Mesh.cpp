#include "Mesh.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Appearance.hpp"
#include "m3gexcept.hpp"
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
    throw null_point_error ("VertexBuffe is NULL.");
  }
  if (num_submesh == 0) {
    throw invalid_argument ("Number of submesh is invalid.");
  }
  if (submeshes == 0) {
    throw null_point_error ("IndexBuffer is NULL.");
  }
  if (num_appearance == 0) {
    throw invalid_argument ("Number of appearance is invalid.");
  }
  if (appearances_ == 0) {
    throw null_point_error ("Appearances is NULL.");
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
    throw null_point_error ("VertexBuffer is NULL.");
  }
  if (submesh == 0) {
    throw null_point_error ("IndexBuffer is NULL.");
  }
  if (appearance == 0) {
    throw null_point_error ("Appearance is NULL.");
  }
  cout << "Mesh: add submesh = " << submesh << "\n";

  vertices = vertices_;
  indices.push_back (submesh);
  appearances.push_back (appearance);

  for (int i = 0; i < (int)indices.size(); i++) {
    cout << "indices[" << i << "] = "<< indices[i] << "\n";
  }
}

Mesh:: ~Mesh ()
{
}

int Mesh:: animate (int world_time)
{
  cout << "Mesh: animate time=" << world_time << "\n";

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
    throw out_of_range ("Index of appearance is out of bound.");
  }
  return appearances[index];
}

IndexBuffer* Mesh:: getIndexBuffer (int index) const
{
  if (index < 0 || index >= (int)indices.size()) {
    throw out_of_range ("Index of indexbuffer is out of bound.");
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
    throw out_of_range ("Index of appearances is out of bound.");
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
 * In other cases, do nothing.
 */
void Mesh:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  for (int i = 0; i < (int)indices.size(); i++) {
    cout << "indices[" << i << "] = "<< indices[i] << "\n";
  }


  //cout << "Mesh: " << indices.size() << "メッシュ\n";
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

  cout << "Mesh: size = " << indices.size() << "\n";

  // インデックスの指定
  for (int i = 0; i < (int)indices.size(); i++) {
    cout << "i = " << i << "\n";
    cout << "app = " << appearances[i] << "\n";
    cout << "ind = " << indices[i] << "\n";
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
  VertexArray* vary = vertices->getPositions(0);
  if (vary)
    out << "Mesh: " << vary->getVertexCount() << " vertices\n";
  else
    out << "Mesh: 0 vertices\n";
  return out;
}


std::ostream& operator<< (std::ostream& out, const Mesh& mesh)
{
  return mesh.print (out);
}

