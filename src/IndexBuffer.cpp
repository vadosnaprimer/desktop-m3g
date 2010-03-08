#include "IndexBuffer.hpp"
#include "m3gexcept.hpp"
#include <iostream>
#include <cstring>
using namespace m3g;
using namespace std;


IndexBuffer:: IndexBuffer () :
  index_count(0), indices(0), ibuf(0)
{
  setObjectType (OBJTYPE_INDEX_BUFFER);

  glGenBuffers (1, &ibuf);
}

IndexBuffer:: ~IndexBuffer ()
{
  if (indices) {
    delete indices;
    indices = 0;
  }
}

int IndexBuffer:: getIndexCount () const
{
    return index_count;
}

void IndexBuffer:: getIndices (int* indices_)
{
  if (indices_ == NULL) {
    throw null_point_error ("Indices is NULL.");
  }

  memcpy (indices_, indices, sizeof(int)*index_count);
}

void IndexBuffer:: setIndices (int index_count_, int* indices_)
{
  //cout << "IndexBuffer: setIndices 1\n";
  if (index_count_ < 0) {
    throw invalid_argument ("Number of indices is < 0.");
  }
  if (indices_ == NULL) {
    throw null_point_error ("Indices is NULL.");
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
  //cout << "IndexBuffer: setIndices 2\n";
  if (index_count_ < 1 || index_count_ > 65535) {
    throw invalid_argument ("Number of indices is < 1 or >65535.");
  }
  if (first_index + index_count_ < 1 || first_index + index_count_ > 65535) {
    throw invalid_argument ("Number of indices is < 1 or >65535.");
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

GLuint IndexBuffer:: getIBO () const
{
  // これ使っている？
  // 使ってないなら削除
  return ibuf;
}

/**
 * Note: Background should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void IndexBuffer:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  if (ibuf == 0) {
    throw opengl_error ("Index Buffer Object is not ready.");
  }

  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, ibuf);
}

std::ostream& IndexBuffer:: print (std::ostream& out) const
{
  out << "\n";
  return out;
}


std::ostream& operator<< (std::ostream& out, const IndexBuffer& ibuf)
{
  return ibuf.print (out);
}


