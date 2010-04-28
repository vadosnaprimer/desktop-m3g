#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "VertexArray.hpp"
using namespace std;
using namespace m3g;

TEST (VertexArray_set_variables_1byte)
{
  VertexArray* varry = new VertexArray(16, 3, 1);
  CHECK_EQUAL (OBJTYPE_VERTEX_ARRAY, varry->getObjectType());
  CHECK_EQUAL (16, varry->getVertexCount());
  CHECK_EQUAL (3, varry->getComponentCount());
  CHECK_EQUAL (1, varry->getComponentType());

  char values[16*3];
  for (int i = 0; i < 16; i++) {
    values[i*3] = i;
    values[i*3+1] = i+10;
    values[i*3+2] = i+20;
  }
  varry->set (0, 16, values);

  char buf[16*3];
  memset (buf, 3, sizeof(buf));
  varry->get (0, 16, buf);

  CHECK_EQUAL ((int)buf[1*3+0], (int)values[1*3+0]);
  CHECK_EQUAL ((int)buf[1*3+1], (int)values[1*3+1]);
  CHECK_EQUAL ((int)buf[1*3+2], (int)values[1*3+2]);
  CHECK_EQUAL ((int)buf[15*3+0], (int)values[15*3+0]);
  CHECK_EQUAL ((int)buf[15*3+1], (int)values[15*3+1]);
  CHECK_EQUAL ((int)buf[15*3+2], (int)values[15*3+2]);

  char buf2[16*3];
  memset (buf2, 0, sizeof(buf2));
  varry->set (10, 1, values+10*3);
  varry->get (10, 1, buf2);

  CHECK_EQUAL ((int)values[10*3+0], (int)buf2[0]);
  CHECK_EQUAL ((int)values[10*3+1], (int)buf2[1]);
  CHECK_EQUAL ((int)values[10*3+2], (int)buf2[2]);
  CHECK_EQUAL (0, (int)buf2[1*3+0]);
  CHECK_EQUAL (0, (int)buf2[1*3+1]);
  CHECK_EQUAL (0, (int)buf2[1*3+2]);

}

TEST (VertexArray_set_variables_2byte)
{
  VertexArray* varry = new VertexArray(16, 3, 2);
  CHECK_EQUAL (OBJTYPE_VERTEX_ARRAY, varry->getObjectType());
  CHECK_EQUAL (16, varry->getVertexCount());
  CHECK_EQUAL (3, varry->getComponentCount());
  CHECK_EQUAL (2, varry->getComponentType());

  short values[16*3];
  for (int i = 0; i < 16; i++) {
    values[i*3] = i;
    values[i*3+1] = i;
    values[i*3+2] = i;
  }
  varry->set (0, 16, values);

  short buf[16*3];
  memset (buf, 0, sizeof(buf));
  varry->get (0, 16, buf);

  CHECK_EQUAL ((int)buf[1*3+0], (int)values[1*3+0]);
  CHECK_EQUAL ((int)buf[1*3+1], (int)values[1*3+1]);
  CHECK_EQUAL ((int)buf[1*3+2], (int)values[1*3+2]);
  CHECK_EQUAL ((int)buf[15*3+0], (int)values[15*3+0]);
  CHECK_EQUAL ((int)buf[15*3+1], (int)values[15*3+1]);
  CHECK_EQUAL ((int)buf[15*3+2], (int)values[15*3+2]);


  short buf2[16*3];
  memset (buf2, 0, sizeof(buf2));
  varry->set (10, 1, values+10*3);
  varry->get (10, 1, buf2);

  CHECK_EQUAL ((int)values[10*3+0], (int)buf2[0]);
  CHECK_EQUAL ((int)values[10*3+1], (int)buf2[1]);
  CHECK_EQUAL ((int)values[10*3+2], (int)buf2[2]);
  CHECK_EQUAL ((int)0, (int)buf2[1*3+0]);
  CHECK_EQUAL ((int)0, (int)buf2[1*3+1]);
  CHECK_EQUAL ((int)0, (int)buf2[1*3+2]);

}

TEST (VertexArray_set_variables_4byte)
{
  VertexArray* varry = new VertexArray(16, 3, 4);
  CHECK_EQUAL (OBJTYPE_VERTEX_ARRAY, varry->getObjectType());
  CHECK_EQUAL (16, varry->getVertexCount());
  CHECK_EQUAL (3, varry->getComponentCount());
  CHECK_EQUAL (4, varry->getComponentType());

  float values[16*3];
  for (int i = 0; i < 16; i++) {
    values[i*3]   = i;
    values[i*3+1] = i;
    values[i*3+2] = i;
  }
  varry->set (0, 16, values);

  float buf[16*3];
  memset (buf, 0, sizeof(buf));
  varry->get (0, 16, buf);

  CHECK_EQUAL (buf[1*3+0], values[1*3+0]);
  CHECK_EQUAL (buf[1*3+1], values[1*3+1]);
  CHECK_EQUAL (buf[1*3+2], values[1*3+2]);
  CHECK_EQUAL (buf[15*3+0], values[15*3+0]);
  CHECK_EQUAL (buf[15*3+1], values[15*3+1]);
  CHECK_EQUAL (buf[15*3+2], values[15*3+2]);


  float buf2[16*3];
  memset (buf2, 0, sizeof(buf2));
  varry->set (10, 1, values+10*3);
  varry->get (10, 1, buf2);

  CHECK_EQUAL (values[10*3+0], buf2[0]);
  CHECK_EQUAL (values[10*3+1], buf2[1]);
  CHECK_EQUAL (values[10*3+2], buf2[2]);
  CHECK_EQUAL (0, buf2[1*3+0]);
  CHECK_EQUAL (0, buf2[1*3+1]);
  CHECK_EQUAL (0, buf2[1*3+2]);

}


TEST (VertexArray_duplicate)
{
  VertexArray* varry0 = new VertexArray(16, 3, 2);

  short values[16*3];
  for (int i = 0; i < 16; i++) {
    values[i*3]   = i;
    values[i*3+1] = i;
    values[i*3+2] = i;
  }
  varry0->set (0, 16, values);

  // VertexArray::valuesは"深いコピー"
  VertexArray* varry1 = varry0->duplicate();

  CHECK_EQUAL (varry0->getVertexCount()   , varry1->getVertexCount());
  CHECK_EQUAL (varry0->getComponentCount(), varry1->getComponentCount());
  CHECK_EQUAL (varry0->getComponentType()    , varry1->getComponentType());

  // ここでvarry0の方の値をセットし直す。
  short values0[16*3];
  for (int i = 0; i < 16; i++) {
    values0[i*3]   = 0;
    values0[i*3+1] = 0;
    values0[i*3+2] = 0;
  }
  varry0->set (0, 16, values0);

  // varry1の方は古い値のまま
  short buf[16*3];
  memset (buf, 0, sizeof(buf));
  varry1->get (0, 16, buf);

  CHECK_EQUAL ((int)buf[1*3+0], (int)values[1*3+0]);
  CHECK_EQUAL ((int)buf[1*3+1], (int)values[1*3+1]);
  CHECK_EQUAL ((int)buf[1*3+2], (int)values[1*3+2]);
  CHECK_EQUAL ((int)buf[15*3+0], (int)values[15*3+0]);
  CHECK_EQUAL ((int)buf[15*3+1], (int)values[15*3+1]);
  CHECK_EQUAL ((int)buf[15*3+2], (int)values[15*3+2]);

}
