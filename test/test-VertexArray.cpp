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

TEST (VertexArray_set_variables_scale_bias)
{
  VertexArray* varry0 = new VertexArray(8, 2, 2);
  short values0[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  varry0->set (0, 8, values0);

  float scale = 2;
  float bias[2] = {1,1};
  float values1[16];
  varry0->get (0, 8, scale, bias, values1);

  CHECK_EQUAL (1, values1[0]);
  CHECK_EQUAL (3, values1[1]);
  CHECK_EQUAL (31, values1[15]);

  VertexArray* varry1 = new VertexArray(8, 2, 1);
  char values2[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  varry1->set (0, 8, values2);

  scale = 3;
  float values3[16];
  varry0->get (0, 8, scale, bias, values3);

  CHECK_EQUAL (1, values3[0]);
  CHECK_EQUAL (4, values3[1]);
  CHECK_EQUAL (46, values3[15]);

  
}
