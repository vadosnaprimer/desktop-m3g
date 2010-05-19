#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "VertexArray.hpp"
using namespace std;
using namespace m3g;

TEST (VertexArray_set_variables_1byte)
{
    VertexArray* varry = new VertexArray(16, 3, 1);
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


TEST (VertexArray_getOpenGLFormat)
{
    VertexArray* varry1 = new VertexArray (4,3,1);
    CHECK_EQUAL (GL_BYTE, varry1->getOpenGLFormat());

    VertexArray* varry2 = new VertexArray (4,3,2);
    CHECK_EQUAL (GL_SHORT, varry2->getOpenGLFormat());

    VertexArray* varry4 = new VertexArray (4,3,4);
    CHECK_EQUAL (GL_FLOAT, varry4->getOpenGLFormat());
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

TEST (VertexArray_convert)
{
    char  initial_values[] = {1,2,3, 4,5,6, -1,-2,-3, -4,-5,-6}; 
    char  char_values[] = {0,0,0, 0,0,0, 0,0,0, 0,0,0};
    short short_values[] = {0,0,0, 0,0,0, 0,0,0, 0,0,0};
    float float_values[] = {0,0,0, 0,0,0, 0,0,0, 0,0,0};
    char  char_values_answer[] = {1,2,3, 4,5,6, -1,-2,-3, -4,-5,-6};
    short short_values_answer[] = {1,2,3, 4,5,6, -1,-2,-3, -4,-5,-6};
    float float_values_answer[] = {1,2,3, 4,5,6, -1,-2,-3, -4,-5,-6};

    VertexArray* varry = new VertexArray (4,3,1);
    varry->set (0, 4, initial_values);

    varry->get (0, 4, char_values);

    varry->convert (1);  
    CHECK_EQUAL (1, varry->getComponentType());
    CHECK_ARRAY_CLOSE (char_values_answer, char_values, 12, 0.0001f);

    varry->convert (2);
    varry->get (0, 4, short_values);
    CHECK_EQUAL (2, varry->getComponentType());
    CHECK_ARRAY_CLOSE (short_values_answer, short_values, 12, 0.0001f);

    varry->convert (4);
    varry->get (0, 4, float_values);
    CHECK_EQUAL (4, varry->getComponentType());
    CHECK_ARRAY_CLOSE (float_values_answer, float_values, 12, 0.0001f);

    varry->convert (2);
    varry->get (0, 4, short_values);
    CHECK_EQUAL (2, varry->getComponentType());
    CHECK_ARRAY_CLOSE (short_values_answer, short_values, 12, 0.0001f);

    varry->convert (1);  
    CHECK_EQUAL (1, varry->getComponentType());
    CHECK_ARRAY_CLOSE (char_values_answer, char_values, 12, 0.0001f);

    varry->convert (4);
    varry->get (0, 4, float_values);
    CHECK_EQUAL (4, varry->getComponentType());
    CHECK_ARRAY_CLOSE (float_values_answer, float_values, 12, 0.0001f);

    varry->convert (1);  
    CHECK_EQUAL (1, varry->getComponentType());
    CHECK_ARRAY_CLOSE (char_values_answer, char_values, 12, 0.0001f);

    delete varry;
}

TEST (VertexArray_get_scale_bias_char)
{
    char  char_values[] = {-128,0,127, 127,127,127, 0,0,0, -128,-128,-128};

    VertexArray* varry = new VertexArray (4,3,1);
    varry->set (0, 4, char_values);

    float scale = 2;
    float bias[3]  = {256, 0, -254};

    float float_values[] = {0,0,0, 0,0,0, 0,0,0, 0,0,0};

    varry->get (0, 4, scale, bias, float_values);
    CHECK_CLOSE (0,     float_values[0], 0.00001f);
    CHECK_CLOSE (0,     float_values[1], 0.00001f);
    CHECK_CLOSE (0,     float_values[2], 0.00001f);

    CHECK_CLOSE (510,   float_values[3], 0.00001f);
    CHECK_CLOSE (254,   float_values[4], 0.00001f);
    CHECK_CLOSE (0,     float_values[5], 0.00001f);

    CHECK_CLOSE (256,   float_values[6], 0.00001f);
    CHECK_CLOSE (0,     float_values[7], 0.00001f);
    CHECK_CLOSE (-254,  float_values[8], 0.00001f);

    CHECK_CLOSE (0,     float_values[9], 0.00001f);
    CHECK_CLOSE (-256,  float_values[10], 0.00001f);
    CHECK_CLOSE (-510,  float_values[11], 0.00001f);


    varry->get (2, 2, scale, bias, float_values);
    CHECK_CLOSE (256,   float_values[0], 0.00001f);
    CHECK_CLOSE (0,     float_values[1], 0.00001f);
    CHECK_CLOSE (-254,  float_values[2], 0.00001f);

    CHECK_CLOSE (0,     float_values[3], 0.00001f);
    CHECK_CLOSE (-256,  float_values[4], 0.00001f);
    CHECK_CLOSE (-510,  float_values[5], 0.00001f);
}



