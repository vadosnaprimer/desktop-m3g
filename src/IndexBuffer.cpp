#include "IndexBuffer.hpp"
#include "Exception.hpp"
#include <iostream>
#include <cstring>
using namespace m3g;
using namespace std;


IndexBuffer:: IndexBuffer ()
{
  setObjectType (OBJTYPE_INDEX_BUFFER);

  //glGenBuffers (1, &ibuf);
}

IndexBuffer:: ~IndexBuffer ()
{
  //if (indices) {
  //  delete indices;
  //  indices = 0;
  //}
}
/*
int IndexBuffer:: getIndexCount () const
{
    return index_count;
}

void IndexBuffer:: getIndices (int* indices_)
{
  if (indices_ == NULL) {
    throw NullPointException (__FILE__, __func__, "Indices is NULL.");
  }

  memcpy (indices_, indices, sizeof(int)*index_count);
}
*/
/*
void IndexBuffer:: setIndices (int index_count_, int* indices_)
{
  // メモ：インデックス配列の確保だがコンストラクタで行った方が良くないか？
  //cout << "IndexBuffer: setIndices 1\n";
  if (index_count_ < 0) {
    throw IllegalArgumentException (__FILE__, __func__, "Index count is invalid, count=%d.", index_count_);
  }
  if (indices_ == NULL) {
    throw NullPointException (__FILE__, __func__, "Indices is NULL.");
  }

  if (indices) {
    delete indices;
    indices = 0;
  }

  index_count = index_count_;
  indices = new int [index_count];
  memcpy (indices, indices_, sizeof(int)*index_count);

  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibuf); 
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*index_count, indices, GL_STATIC_DRAW);
}

void IndexBuffer:: setIndices (int index_count_, int first_index)
{
  // メモ：インデックス配列の確保だがコンストラクタで行った方が良くないか？
  //cout << "IndexBuffer: setIndices 2\n";
  if (index_count_ < 1 || index_count_ > 65535) {
    throw IllegalArgumentException (__FILE__, __func__, "Index count is invalid, count=%d.", index_count_);
  }
  if (first_index + index_count_ < 1 || first_index + index_count_ > 65535) {
    throw IllegalArgumentException (__FILE__, __func__, "First index + Index count is invalid, first_index=%d, index_count=%d.", first_index, index_count_);
  }

  if (indices) {
    delete indices;
    indices = 0;
  }

  index_count = index_count_;
  indices = new int [index_count];
  for (int i = 0; i < index_count; i++) {
    indices[i] = first_index + i;
  }
  
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibuf); 
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*index_count, indices, GL_STATIC_DRAW);
}
*/

/**
 * Note: Background should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void IndexBuffer:: render (int pass, int index) const
{
  //if (pass != 2) {
  //  return;
  //}

  //if (ibuf == 0) {
  //  throw OpenGLException (__FILE__, __func__, "Buffer object of index is not ready, ibuf=%d.", ibuf);
  //}

  //glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibuf);
}

std::ostream& IndexBuffer:: print (std::ostream& out) const
{
  out << "IndexBuffer: ";
  //out << " index_count=" << index_count;
  //out << " indices=" << indices;
  //out << " ibuf=" << ibuf;
  return out << "\n";
}


std::ostream& operator<< (std::ostream& out, const IndexBuffer& ibuf)
{
  return ibuf.print (out);
}


