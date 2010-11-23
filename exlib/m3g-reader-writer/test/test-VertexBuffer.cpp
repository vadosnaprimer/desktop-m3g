#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (VertexBuffer)
{
    int object_type = M3G_TYPE_VERTEX_BUFFER;
    unsigned int object_index;
    M3GVertexBufferStruct vbuf;

    vbuf.default_color    = 0x12345678;
    vbuf.positions_index  = 3;
    vbuf.position_bias[0] = 4;
    vbuf.position_bias[1] = 5;
    vbuf.position_bias[2] = 6;
    vbuf.position_scale   = 7;
    vbuf.normals_index    = 8;
    vbuf.colors_index     = 9;
    vbuf.texcoord_array_count  = 1;
    vbuf.texcoords_index       = new unsigned int [1];
    vbuf.texcoords_index[0]    = 10;
    vbuf.texcoord_bias         = new float* [1];
    vbuf.texcoord_bias[0]      = new float [3];
    vbuf.texcoord_bias[0][0]   = 11;
    vbuf.texcoord_bias[0][1]   = 12;
    vbuf.texcoord_bias[0][2]   = 13;
    vbuf.texcoord_scale        = new float [1];
    vbuf.texcoord_scale[0]     = 14;

    M3GWriter* writer = new M3GWriter ("vbuf.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeVertexBuffer     (vbuf);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("vbuf.m3g");
    M3GVertexBufferStruct vbuf2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readVertexBuffer      (&vbuf2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_VERTEX_BUFFER, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (0x12345678, vbuf2.default_color);
    CHECK_EQUAL (3,          vbuf2.positions_index);
    CHECK_EQUAL (4,          vbuf2.position_bias[0]);
    CHECK_EQUAL (5,          vbuf2.position_bias[1]);
    CHECK_EQUAL (6,          vbuf2.position_bias[2]);
    CHECK_EQUAL (7,          vbuf2.position_scale);
    CHECK_EQUAL (8,          vbuf2.normals_index);
    CHECK_EQUAL (9,          vbuf2.colors_index);
    CHECK_EQUAL (1,          vbuf2.texcoord_array_count);
    CHECK_EQUAL (10,         vbuf2.texcoords_index[0]);
    CHECK_EQUAL (11,         vbuf2.texcoord_bias[0][0]);
    CHECK_EQUAL (12,         vbuf2.texcoord_bias[0][1]);
    CHECK_EQUAL (13,         vbuf2.texcoord_bias[0][2]);
    CHECK_EQUAL (14,         vbuf2.texcoord_scale[0]);

    delete reader;
}

