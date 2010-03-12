#include "TriangleStripArray.hpp"
#include <iostream>
#include <cstdlib>
#include "m3gexcept.hpp"
using namespace std;
using namespace m3g;


TriangleStripArray:: TriangleStripArray (int* indices, int num_strips, int* strip_array)
{
  setObjectType (OBJTYPE_TRIANGLE_STRIP_ARRAY);

  if (indices == NULL) {
    throw null_point_error ("Indices is NULL.");
  }
  if (strip_array == NULL) {
    throw null_point_error ("Stips is NULL.");
  }
  if (num_strips < 1 || num_strips > 65535) {
    throw invalid_argument ("Num_strip_lengths is invalid.");
  }

  int num = 0;
  for (int i = 0; i < num_strips; i++) {
    num += strip_array[i];
    strips.push_back (strip_array[i]);
  }
  //cout << "num = " << num << "\n";
  setIndices (num, indices);

}

TriangleStripArray:: TriangleStripArray (int first_index, int num_strips, int* strip_array) 
{
  if (strip_array == NULL) {
    throw null_point_error ("Stips is NULL.");
  }
  if (first_index < 0 || first_index > 65535) {
    throw invalid_argument ("Fist_index is invalid.");
  }
  if (num_strips < 1 || first_index + num_strips > 65536) {
    throw invalid_argument ("Num_strip_lengths is invalid.");
  }

  int num = 0;
  for (int i = 0; i < num_strips; i++) {
    num += strip_array[i];
    strips.push_back (strip_array[i]);
  }
  
  setIndices (num, first_index);

}

TriangleStripArray:: ~TriangleStripArray ()
{
}

/**
 * Note: TriangleStripArray should be rendered only at second rendering pass(pass=2).
 * In other cases, do nothing.
 */
void TriangleStripArray:: render (int pass, int index) const
{
  if (pass != 2) {
    return;
  }

  //cout << "TriangleStripArray: rendered stips=" << strips.size() << "\n";
  
  IndexBuffer:: render(pass, index);

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


