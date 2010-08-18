#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
using namespace std;
using namespace m3g;


TEST (VertexBuffer_default_variables)
{
    VertexBuffer* vbuf = new VertexBuffer;

    CHECK_EQUAL (0xffffffff,      vbuf->getDefaultColor());
    CHECK_EQUAL ((VertexArray*)0, vbuf->getColors());
    CHECK_EQUAL ((VertexArray*)0, vbuf->getNormals());
    CHECK_EQUAL ((VertexArray*)0, vbuf->getPositions(0));
    CHECK_EQUAL ((VertexArray*)0, vbuf->getTexCoords(0, 0));
    CHECK_EQUAL ((VertexArray*)0, vbuf->getTexCoords(1, 0));
  
    delete vbuf;
}

TEST (VertexBuffer_set_variables)
{
    VertexBuffer* vbuf = new VertexBuffer;
    VertexArray* colors = new VertexArray (1, 3, 1);
    VertexArray* normals = new VertexArray (1, 3, 2);
    VertexArray* positions = new VertexArray (1, 3, 2);
    VertexArray* texcoords = new VertexArray (1, 2, 2);
    float scale   = 3;
    float bias[3] = {1,2,3};

    vbuf->setDefaultColor (0x12345678);
    vbuf->setColors (colors);
    vbuf->setNormals (normals);
    vbuf->setPositions (positions, scale, bias);
    vbuf->setTexCoords (1, texcoords, scale, bias);

    float scale_bias[4];

    CHECK_EQUAL (0x12345678, vbuf->getDefaultColor());
    CHECK_EQUAL (positions, vbuf->getPositions(scale_bias));
    CHECK_EQUAL (3.f, scale_bias[0]);
    CHECK_EQUAL (1.f, scale_bias[1]);
    CHECK_EQUAL (2.f, scale_bias[2]);
    CHECK_EQUAL (3.f, scale_bias[3]);
    CHECK_EQUAL (colors, vbuf->getColors(scale_bias));
    CHECK_EQUAL (1/255.f, scale_bias[0]);
    CHECK_EQUAL (0.f, scale_bias[1]);
    CHECK_EQUAL (0.f, scale_bias[2]);
    CHECK_EQUAL (0.f, scale_bias[3]);
    CHECK_EQUAL (normals, vbuf->getNormals(scale_bias));
    CHECK_EQUAL (2/65535.f, scale_bias[0]);
    CHECK_EQUAL (1/65535.f, scale_bias[1]);
    CHECK_EQUAL (1/65535.f, scale_bias[2]);
    CHECK_EQUAL (1/65535.f, scale_bias[3]);
    CHECK_EQUAL (texcoords, vbuf->getTexCoords(1,scale_bias));
    CHECK_EQUAL (3.f, scale_bias[0]);
    CHECK_EQUAL (1.f, scale_bias[1]);
    CHECK_EQUAL (2.f, scale_bias[2]);
    CHECK_EQUAL ((VertexArray*)0, vbuf->getTexCoords(0,scale_bias));

    delete texcoords;
    delete positions;
    delete normals;
    delete colors;
    delete vbuf;
}

TEST (VertexBuffer_duplicate)
{
    VertexBuffer* vbuf0    = new VertexBuffer;
    VertexArray* colors    = new VertexArray (1, 3, 1);
    VertexArray* normals   = new VertexArray (1, 3, 2);
    VertexArray* positions = new VertexArray (1, 3, 2);
    VertexArray* texcoords = new VertexArray (1, 2, 2);
    float bias[4] = {32768/65535.f, 2*32768/65535.f, 3*32768/65535.f};

    vbuf0->setDefaultColor (0x12345678);
    vbuf0->setColors (colors);
    vbuf0->setNormals (normals);
    vbuf0->setPositions (positions, 1/65535.f, bias);
    vbuf0->setTexCoords (1, texcoords, 1/65535.f, bias);

    VertexBuffer* vbuf1 = vbuf0->duplicate();

    CHECK_EQUAL (vbuf0->getDefaultColor(), vbuf1->getDefaultColor());
    CHECK_EQUAL (vbuf0->getColors()      , vbuf1->getColors());
    CHECK_EQUAL (vbuf0->getNormals()     , vbuf1->getNormals());
    CHECK_EQUAL (vbuf0->getPositions(0)  , vbuf1->getPositions(0));
    CHECK_EQUAL (vbuf0->getTexCoords(1,0), vbuf1->getTexCoords(1,0));
    CHECK_EQUAL (vbuf0->getTexCoords(0,0), vbuf1->getTexCoords(0,0));

    delete texcoords;
    delete positions;
    delete normals;
    delete colors;
    delete vbuf0;
    delete vbuf1;
}

static int count = 0;
static void func (void* p)
{
    count++;
}

TEST (VertexBuffer_mark)
{
    VertexBuffer* vbuf    = new VertexBuffer;
    VertexArray* colors    = new VertexArray (1, 3, 1);
    VertexArray* normals   = new VertexArray (1, 3, 2);
    VertexArray* positions = new VertexArray (1, 3, 2);
    VertexArray* texcoords = new VertexArray (1, 2, 2);
    float scale   = 1;
    float bias[3] = {0,0,0};

    vbuf->setColors (colors);
    vbuf->setNormals (normals);
    vbuf->setPositions (positions, scale, bias);
    vbuf->setTexCoords (1, texcoords, scale, bias);

    vbuf->mark (func);

    CHECK_EQUAL (5, count);

    delete vbuf;
    delete colors;
    delete normals;
    delete positions;
    delete texcoords;
}
