#include "TriangleStripArray.hpp"
#include <iostream>
#include <cstdlib>
#include <numeric>
#include <cstring>
#include "Exception.hpp"
#include "RenderState.hpp"
using namespace std;
using namespace m3g;


TriangleStripArray:: TriangleStripArray (int* indices_, int num_strips, int* strip_array) :
  indices(0), ibuf(0)
{
  setObjectType (OBJTYPE_TRIANGLE_STRIP_ARRAY);

  if (indices_ == NULL) {
    throw NullPointException (__FILE__, __func__, "Indices is NULL.");
  }
  if (strip_array == NULL) {
    throw NullPointException (__FILE__, __func__, "Strips array is NULL.");
  }
  if (num_strips < 1 || num_strips > 65535) {
    throw IllegalArgumentException (__FILE__, __func__, "Number of strip lengths is invalid, num_strips=%d.", num_strips);
  }

  strips.reserve (num_strips);
  for (int i = 0; i < num_strips; i++) {
    strips.push_back (strip_array[i]);
  }
  int num = accumulate (strips.begin(), strips.end(), 0);

  indices = new int[num];
  memcpy (indices, indices_, sizeof(int)*num);

  glGenBuffers (1, &ibuf);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibuf); 
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*num, indices, GL_STATIC_DRAW);

}


TriangleStripArray:: TriangleStripArray (int first_index, int num_strips, int* strip_array)  :
  indices(0)
{
  if (strip_array == NULL) {
    throw NullPointException (__FILE__, __func__, "Strips array is NULL.");
  }
  if (first_index < 0 || first_index > 65535) {
    throw IllegalArgumentException (__FILE__, __func__, "Fist index is invalid, first_idex=%d.", first_index);
  }
  if (num_strips < 1 || first_index + num_strips > 65536) {
    throw IllegalArgumentException (__FILE__, __func__, "Nummber of strip lengths is invalid, first_index=%d, num_strips=%d.", first_index, num_strips);
  }

  strips.reserve (num_strips);
  for (int i = 0; i < num_strips; i++) {
    strips.push_back (strip_array[i]);
  }
  
  int num = accumulate (strips.begin(), strips.end(), 0);
  indices = new int[num];
  for (int i = 0; i < num; i++) {
    indices[i] = first_index + i;
  }

  glGenBuffers (1, &ibuf);
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibuf); 
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*num, indices, GL_STATIC_DRAW);
}

TriangleStripArray:: ~TriangleStripArray ()
{
}

TriangleStripArray* TriangleStripArray:: duplicate () const
{
  int index_count = getIndexCount();

  TriangleStripArray* tris = new TriangleStripArray (*this);
  tris->indices            = new int [index_count];
  memcpy (tris->indices, this->indices, 4*index_count);
  // 現状ではOpenGLのバッファーオブジェクトを共通で使用するのでコメントアウト
  //glGenBuffers (1, &tris->ibuf);
  //glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, tris->ibuf); 
  //glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*index_count, tris->indices, GL_STATIC_DRAW);
  return tris;
}

int TriangleStripArray:: getIndexCount () const
{
  return accumulate (strips.begin(), strips.end(), 0);
}

void TriangleStripArray:: getIndices (int* indices_)
{
  if (indices_ == NULL) {
    throw NullPointException (__FILE__, __func__, "Indices is NULL.");
  }

  int num = accumulate (strips.begin(), strips.end(), 0);
  memcpy (indices_, indices, sizeof(int)*num);
}

/**
 * Note: TriangleStripArray should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void TriangleStripArray:: render (RenderState& state) const
{
  if (state.pass != 2) {
    return;
  }

  if (ibuf == 0) {
    throw OpenGLException (__FILE__, __func__, "Buffer object of index is not ready, ibuf=%d.", ibuf);
  }

  //cout << "TriangleStripArray: rendered stips=" << strips.size() << "\n";
  
  //IndexBuffer:: render(pass, index);

  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibuf);

  int offset = 0;
  for (int i = 0; i < (int)strips.size(); i++) {
    //cout << "offset = " << offset << ", strip=" << strips[i] << "\n";
    glDrawElements (GL_TRIANGLE_STRIP, strips[i], GL_UNSIGNED_INT, (GLvoid*)offset);
    offset += strips[i] * sizeof(int);
  }
}

std::ostream& TriangleStripArray:: print (std::ostream& out) const
{
  out << "Triangle Strip Array : [";
  for (int i = 0; i < (int)strips.size(); i++) {
    out << strips[i] << " ";
  }
  out << "]";
  return out;
}

std::ostream& operator<< (std::ostream& out, const TriangleStripArray& tris)
{
  return tris.print(out);
}


