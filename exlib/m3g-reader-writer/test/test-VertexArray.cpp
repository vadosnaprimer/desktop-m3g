#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (VertexArray_component_size_1_encoding_0)
{
    int object_type = M3G_TYPE_VERTEX_ARRAY;
    unsigned int object_index;
    M3GVertexArrayStruct varry;

    varry.component_size   = 1;
    varry.component_count  = 2;
    varry.encoding         = M3GVertexArrayStruct::ENCODING_0;
    varry.vertex_count     = 1;
    varry.char_components   = new char* [1];
    varry.char_components[0] = new char [2];
    varry.char_components[0][0] = 10;
    varry.char_components[0][1] = 11;

    M3GWriter* writer = new M3GWriter ("varry.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeVertexArray (varry);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("varry.m3g");
    M3GVertexArrayStruct varry2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readVertexArray      (&varry2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_VERTEX_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (1,   varry2.component_size);
    CHECK_EQUAL (2,   varry2.component_count);
    CHECK_EQUAL (M3GVertexArrayStruct::ENCODING_0, varry.encoding);
    CHECK_EQUAL (1,   varry2.vertex_count);
    CHECK_EQUAL (10,  varry2.char_components[0][0]);
    CHECK_EQUAL (11,  varry2.char_components[0][1]);

    delete reader;
}

TEST (VertexArray_component_size_1_encoding_1)
{
    int object_type = M3G_TYPE_VERTEX_ARRAY;
    unsigned int object_index;
    M3GVertexArrayStruct varry;

    varry.component_size   = 1;
    varry.component_count  = 2;
    varry.encoding         = M3GVertexArrayStruct::ENCODING_0;
    varry.vertex_count     = 1;
    varry.char_components = new char* [1];
    varry.char_components[0] = new char [2];
    varry.char_components[0][0] = 10;
    varry.char_components[0][1] = 11;

    M3GWriter* writer = new M3GWriter ("varry.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeVertexArray (varry);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("varry.m3g");
    M3GVertexArrayStruct varry2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readVertexArray      (&varry2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_VERTEX_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (1,   varry2.component_size);
    CHECK_EQUAL (2,   varry2.component_count);
    CHECK_EQUAL (M3GVertexArrayStruct::ENCODING_0, varry.encoding);
    CHECK_EQUAL (1,   varry2.vertex_count);
    CHECK_EQUAL (10,  varry2.char_components[0][0]);
    CHECK_EQUAL (11,  varry2.char_components[0][1]);

    delete reader;
}

TEST (VertexArray_component_size_2_encoding_0)
{
    int object_type = M3G_TYPE_VERTEX_ARRAY;
    unsigned int object_index;
    M3GVertexArrayStruct varry;

    varry.component_size   = 2;
    varry.component_count  = 2;
    varry.encoding         = M3GVertexArrayStruct::ENCODING_1;
    varry.vertex_count     = 1;
    varry.short_components  = new short* [1];
    varry.short_components[0] = new short [2];
    varry.short_components[0][0] = 10;
    varry.short_components[0][1] = 11;

    M3GWriter* writer = new M3GWriter ("varry.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeVertexArray (varry);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("varry.m3g");
    M3GVertexArrayStruct varry2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readVertexArray      (&varry2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_VERTEX_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (2,   varry2.component_size);
    CHECK_EQUAL (2,   varry2.component_count);
    CHECK_EQUAL (M3GVertexArrayStruct::ENCODING_1, varry.encoding);
    CHECK_EQUAL (1,   varry2.vertex_count);
    CHECK_EQUAL (10,  varry2.short_components[0][0]);
    CHECK_EQUAL (11,  varry2.short_components[0][1]);

    delete reader;
}

TEST (VertexArray_component_size_2_encoding_1)
{
    int object_type = M3G_TYPE_VERTEX_ARRAY;
    unsigned int object_index;
    M3GVertexArrayStruct varry;

    varry.component_size   = 2;
    varry.component_count  = 2;
    varry.encoding         = M3GVertexArrayStruct::ENCODING_1;
    varry.vertex_count     = 1;
    varry.short_components  = new short* [1];
    varry.short_components[0] = new short [2];
    varry.short_components[0][0] = 10;
    varry.short_components[0][1] = 11;

    M3GWriter* writer = new M3GWriter ("varry.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeVertexArray (varry);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("varry.m3g");
    M3GVertexArrayStruct varry2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readVertexArray      (&varry2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_VERTEX_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (2,   varry2.component_size);
    CHECK_EQUAL (2,   varry2.component_count);
    CHECK_EQUAL (M3GVertexArrayStruct::ENCODING_1, varry.encoding);
    CHECK_EQUAL (1,   varry2.vertex_count);
    CHECK_EQUAL (10,  varry2.short_components[0][0]);
    CHECK_EQUAL (11,  varry2.short_components[0][1]);

    delete reader;
}

TEST (VertexArray_component_size_4_encoding_0)
{
    int object_type = M3G_TYPE_VERTEX_ARRAY;
    unsigned int object_index;
    M3GVertexArrayStruct varry;

    varry.component_size   = 4;
    varry.component_count  = 2;
    varry.encoding         = M3GVertexArrayStruct::ENCODING_0;
    varry.vertex_count     = 1;
    varry.float_components  = new float* [1];
    varry.float_components[0] = new float [2];
    varry.float_components[0][0] = 10.1;
    varry.float_components[0][1] = 11.1;

    M3GWriter* writer = new M3GWriter ("varry.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeVertexArray (varry);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("varry.m3g");
    M3GVertexArrayStruct varry2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readVertexArray      (&varry2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_VERTEX_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (4,   varry2.component_size);
    CHECK_EQUAL (2,   varry2.component_count);
    CHECK_EQUAL (M3GVertexArrayStruct::ENCODING_0, varry.encoding);
    CHECK_EQUAL (1,   varry2.vertex_count);
    CHECK_EQUAL (10.1f,  varry2.float_components[0][0]);
    CHECK_EQUAL (11.1f,  varry2.float_components[0][1]);

    delete reader;
}

TEST (VertexArray_component_size_4_encoding_1)
{
    int object_type = M3G_TYPE_VERTEX_ARRAY;
    unsigned int object_index;
    M3GVertexArrayStruct varry;

    varry.component_size   = 4;
    varry.component_count  = 2;
    varry.encoding         = M3GVertexArrayStruct::ENCODING_1;
    varry.vertex_count     = 1;
    varry.float_components  = new float* [1];
    varry.float_components[0] = new float [2];
    varry.float_components[0][0] = 10.1;
    varry.float_components[0][1] = 11.1;

    M3GWriter* writer = new M3GWriter ("varry.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeVertexArray (varry);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("varry.m3g");
    M3GVertexArrayStruct varry2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readVertexArray      (&varry2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_VERTEX_ARRAY, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (4,   varry2.component_size);
    CHECK_EQUAL (2,   varry2.component_count);
    CHECK_EQUAL (M3GVertexArrayStruct::ENCODING_1, varry.encoding);
    CHECK_EQUAL (1,   varry2.vertex_count);
    CHECK_EQUAL (10.1f,  varry2.float_components[0][0]);
    CHECK_EQUAL (11.1f,  varry2.float_components[0][1]);

    delete reader;
}

