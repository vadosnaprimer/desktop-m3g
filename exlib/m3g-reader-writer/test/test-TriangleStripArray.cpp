#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (TriangleStripArray_encoding_0)
{
    int object_type = M3G_TYPE_TRIANGLE_STRIP_ARRAY;
    unsigned int object_index;
    M3GTriangleStripArrayStruct tris;

    tris.encoding            = M3GTriangleStripArrayStruct:: ENCODING_0;
    tris.start_index         = 3;
    tris.strip_lengths_count = 1;
    tris.strip_lengths       = new unsigned int[1];
    tris.strip_lengths[0]    = 4;


    M3GWriter* writer = new M3GWriter ("tris.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeTriangleStripArray   (tris);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("tris.m3g");
    M3GTriangleStripArrayStruct tris2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readTriangleStripArray    (&tris2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_TRIANGLE_STRIP_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (M3GTriangleStripArrayStruct::ENCODING_0,   tris2.encoding);
    CHECK_EQUAL (3,   tris2.start_index);
    CHECK_EQUAL ((unsigned int*)0,   tris2.indices);
    CHECK_EQUAL (1,   tris2.strip_lengths_count);
    CHECK_EQUAL (4,   tris2.strip_lengths[0]);

    delete reader;
}

TEST (TriangleStripArray_encoding_1)
{
    int object_type = M3G_TYPE_TRIANGLE_STRIP_ARRAY;
    unsigned int object_index;
    M3GTriangleStripArrayStruct tris;

    tris.encoding            = M3GTriangleStripArrayStruct:: ENCODING_1;
    tris.start_index         = 3;
    tris.strip_lengths_count = 1;
    tris.strip_lengths       = new unsigned int[1];
    tris.strip_lengths[0]    = 4;


    M3GWriter* writer = new M3GWriter ("tris.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeTriangleStripArray   (tris);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("tris.m3g");
    M3GTriangleStripArrayStruct tris2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readTriangleStripArray    (&tris2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_TRIANGLE_STRIP_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (M3GTriangleStripArrayStruct::ENCODING_1,   tris2.encoding);
    CHECK_EQUAL (3,   tris2.start_index);
    CHECK_EQUAL ((unsigned int*)0,   tris2.indices);
    CHECK_EQUAL (1,   tris2.strip_lengths_count);
    CHECK_EQUAL (4,   tris2.strip_lengths[0]);

    delete reader;
}

TEST (TriangleStripArray_encoding_2)
{
    int object_type = M3G_TYPE_TRIANGLE_STRIP_ARRAY;
    unsigned int object_index;
    M3GTriangleStripArrayStruct tris;

    tris.encoding            = M3GTriangleStripArrayStruct:: ENCODING_2;
    tris.start_index         = 3;
    tris.strip_lengths_count = 1;
    tris.strip_lengths       = new unsigned int[1];
    tris.strip_lengths[0]    = 4;


    M3GWriter* writer = new M3GWriter ("tris.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeTriangleStripArray   (tris);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("tris.m3g");
    M3GTriangleStripArrayStruct tris2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readTriangleStripArray    (&tris2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_TRIANGLE_STRIP_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (M3GTriangleStripArrayStruct::ENCODING_2,   tris2.encoding);
    CHECK_EQUAL (3,   tris2.start_index);
    CHECK_EQUAL ((unsigned int*)0,   tris2.indices);
    CHECK_EQUAL (1,   tris2.strip_lengths_count);
    CHECK_EQUAL (4,   tris2.strip_lengths[0]);

    delete reader;
}

TEST (TriangleStripArray_encoding_128)
{
    int object_type = M3G_TYPE_TRIANGLE_STRIP_ARRAY;
    unsigned int object_index;
    M3GTriangleStripArrayStruct tris;

    tris.encoding            = M3GTriangleStripArrayStruct:: ENCODING_128;
    tris.indices_count       = 1;
    tris.indices             = new unsigned int[1];
    tris.indices[0]          = 3;
    tris.strip_lengths_count = 1;
    tris.strip_lengths       = new unsigned int[1];
    tris.strip_lengths[0]    = 4;


    M3GWriter* writer = new M3GWriter ("tris.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeTriangleStripArray   (tris);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("tris.m3g");
    M3GTriangleStripArrayStruct tris2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readTriangleStripArray    (&tris2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_TRIANGLE_STRIP_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (M3GTriangleStripArrayStruct::ENCODING_128,   tris2.encoding);
    CHECK_EQUAL (3,   tris2.indices[0]);
    CHECK_EQUAL (1,   tris2.strip_lengths_count);
    CHECK_EQUAL (4,   tris2.strip_lengths[0]);

    delete reader;
}


TEST (TriangleStripArray_encoding_129)
{
    int object_type = M3G_TYPE_TRIANGLE_STRIP_ARRAY;
    unsigned int object_index;
    M3GTriangleStripArrayStruct tris;

    tris.encoding            = M3GTriangleStripArrayStruct:: ENCODING_129;
    tris.indices_count       = 1;
    tris.indices             = new unsigned int[1];
    tris.indices[0]          = 3;
    tris.strip_lengths_count = 1;
    tris.strip_lengths       = new unsigned int[1];
    tris.strip_lengths[0]    = 4;


    M3GWriter* writer = new M3GWriter ("tris.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeTriangleStripArray   (tris);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("tris.m3g");
    M3GTriangleStripArrayStruct tris2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readTriangleStripArray    (&tris2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_TRIANGLE_STRIP_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (M3GTriangleStripArrayStruct::ENCODING_129,   tris2.encoding);
    CHECK_EQUAL (3,   tris2.indices[0]);
    CHECK_EQUAL (1,   tris2.strip_lengths_count);
    CHECK_EQUAL (4,   tris2.strip_lengths[0]);

    delete reader;
}


TEST (TriangleStripArray_encoding_130)
{
    int object_type = M3G_TYPE_TRIANGLE_STRIP_ARRAY;
    unsigned int object_index;
    M3GTriangleStripArrayStruct tris;

    tris.encoding            = M3GTriangleStripArrayStruct:: ENCODING_130;
    tris.indices_count       = 1;
    tris.indices             = new unsigned int[1];
    tris.indices[0]          = 3;
    tris.strip_lengths_count = 1;
    tris.strip_lengths       = new unsigned int[1];
    tris.strip_lengths[0]    = 4;


    M3GWriter* writer = new M3GWriter ("tris.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeTriangleStripArray   (tris);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("tris.m3g");
    M3GTriangleStripArrayStruct tris2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readTriangleStripArray    (&tris2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_TRIANGLE_STRIP_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (M3GTriangleStripArrayStruct::ENCODING_130,   tris2.encoding);
    CHECK_EQUAL (3,   tris2.indices[0]);
    CHECK_EQUAL (1,   tris2.strip_lengths_count);
    CHECK_EQUAL (4,   tris2.strip_lengths[0]);

    delete reader;
}
