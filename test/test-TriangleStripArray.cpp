#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "TriangleStripArray.hpp"
using namespace std;
using namespace m3g;


TEST (TriangleStripArray_set_variables_explicit)
{
  // TriangleStripArray (int* indices, int num_strip_lengths, int* strip_lengths);

  int indices[10] = {2,4,6,8,10,12,14,16,18,20};
  int strip_lengths[3] = {4,3,3};
  TriangleStripArray* tris = new TriangleStripArray (indices, 3, strip_lengths);

  CHECK_EQUAL (OBJTYPE_TRIANGLE_STRIP_ARRAY, tris->getObjectType());
  CHECK_EQUAL (10, tris->getIndexCount());

  int index_buf[10];
  tris->getIndices (index_buf);
  CHECK_EQUAL (2, index_buf[0]);
  CHECK_EQUAL (20, index_buf[9]);

  CHECK_EQUAL (3, (int)tris->strips.size());
  CHECK_EQUAL (4, tris->strips[0]);
  CHECK_EQUAL (3, tris->strips[1]);
  CHECK_EQUAL (3, tris->strips[2]);
}

TEST (TriangleStripArray_set_variables_implicit)
{
  // TriangleStripArray (int first_index, int num_strip_lengths, int* strip_lengths);

  int strip_lengths[3] = {4,3,3};
  TriangleStripArray* tris = new TriangleStripArray (100, 3, strip_lengths);

  CHECK_EQUAL (10, tris->getIndexCount());

  int index_buf[10];
  tris->getIndices (index_buf);
  CHECK_EQUAL (100, index_buf[0]);
  CHECK_EQUAL (109, index_buf[9]);

  CHECK_EQUAL (3, (int)tris->strips.size());
  CHECK_EQUAL (4, tris->strips[0]);
  CHECK_EQUAL (3, tris->strips[1]);
  CHECK_EQUAL (3, tris->strips[2]);
}
