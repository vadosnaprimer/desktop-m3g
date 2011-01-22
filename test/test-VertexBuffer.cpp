#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cstring>
#include "m3g/VertexBuffer.hpp"
#include "m3g/VertexArray.hpp"
using namespace std;
using namespace m3g;


TEST (VertexBuffer_default_variables)
{
    VertexBuffer* vbuf = new VertexBuffer;

    CHECK_EQUAL (0xffffffff     , vbuf->getDefaultColor());
    CHECK_EQUAL ((VertexArray*)0, vbuf->getColors());
    CHECK_EQUAL ((VertexArray*)0, vbuf->getNormals());
    CHECK_EQUAL ((VertexArray*)0, vbuf->getPositions(0));
    CHECK_EQUAL ((VertexArray*)0, vbuf->getTexCoords(0, 0));
    CHECK_EQUAL ((VertexArray*)0, vbuf->getTexCoords(1, 0));
    CHECK_EQUAL (0              , vbuf->getVertexCount ());

    delete vbuf;
}

TEST (VertexBuffer_set_variables)
{
    VertexBuffer* vbuf      = new VertexBuffer;
    VertexArray*  colors    = new VertexArray (1, 3, 1);
    VertexArray*  normals   = new VertexArray (1, 3, 2);
    VertexArray*  positions = new VertexArray (1, 3, 2);
    VertexArray*  texcoords = new VertexArray (1, 2, 2);
    float scale   = 3;
    float bias[3] = {1,2,3};

    vbuf->setDefaultColor (0x12345678);
    vbuf->setColors (colors);
    vbuf->setNormals (normals);
    vbuf->setPositions (positions, scale, bias);
    vbuf->setTexCoords (1, texcoords, scale, bias);

    float scale_bias[4];

    CHECK_EQUAL (0x12345678, vbuf->getDefaultColor());
    CHECK_EQUAL (1         , vbuf->getVertexCount());
    CHECK_EQUAL (positions , vbuf->getPositions(scale_bias));
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



TEST (VertexBuffer_find)
{
    VertexBuffer* vbuf      = new VertexBuffer;
    VertexArray*  colors    = new VertexArray (1, 3, 1);
    VertexArray*  normals   = new VertexArray (1, 3, 2);
    VertexArray*  positions = new VertexArray (1, 3, 2);
    VertexArray*  tex_coords = new VertexArray (1, 2, 2);
    float scale   = 3;
    float bias[3] = {1,2,3};

    vbuf->setDefaultColor (0x12345678);
    vbuf->setColors (colors);
    vbuf->setNormals (normals);
    vbuf->setPositions (positions, scale, bias);
    vbuf->setTexCoords (0, tex_coords, scale, bias);

    vbuf->setUserID (100);
    colors->setUserID (101);
    normals->setUserID (102);
    positions->setUserID (103);
    tex_coords->setUserID (104);

    CHECK_EQUAL (vbuf      , vbuf->find(100));
    CHECK_EQUAL (colors    , vbuf->find(101));
    CHECK_EQUAL (normals   , vbuf->find(102));
    CHECK_EQUAL (positions , vbuf->find(103));
    CHECK_EQUAL (tex_coords, vbuf->find(104));

    delete tex_coords;
    delete positions;
    delete normals;
    delete colors;
    delete vbuf;
}


TEST (VertexBuffer_getReferences)
{
    VertexBuffer* vbuf      = new VertexBuffer;
    VertexArray*  colors    = new VertexArray (1, 3, 1);
    VertexArray*  normals   = new VertexArray (1, 3, 2);
    VertexArray*  positions = new VertexArray (1, 3, 2);
    VertexArray*  texcoords = new VertexArray (1, 2, 2);
    float scale   = 3;
    float bias[3] = {1,2,3};

    vbuf->setDefaultColor (0x12345678);
    vbuf->setColors (colors);
    vbuf->setNormals (normals);
    vbuf->setPositions (positions, scale, bias);
    vbuf->setTexCoords (0, texcoords, scale, bias);

    int n;
    Object3D* objs[4];
    n = vbuf->getReferences (objs);

    CHECK_EQUAL (4, n);
    CHECK_EQUAL (positions, objs[0]);
    CHECK_EQUAL (normals  , objs[1]);
    CHECK_EQUAL (colors   , objs[2]);
    CHECK_EQUAL (texcoords, objs[3]);

    delete texcoords;
    delete positions;
    delete normals;
    delete colors;
    delete vbuf;
}


