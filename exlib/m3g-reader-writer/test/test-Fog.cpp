#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (Fog)
{
    int object_type = M3G_TYPE_FOG;
    unsigned int object_index;
    M3GFogStruct fog;

    fog.color = 0x12345678;
    fog.mode = M3GFogStruct::LINEAR;
    fog.near = 100;
    fog.far = 200;

    M3GWriter* writer = new M3GWriter ("fog.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeFog     (fog);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("fog.m3g");
    M3GFogStruct fog2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readFog      (&fog2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_FOG, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (0x00345678, fog2.color);
    CHECK_EQUAL (M3GFogStruct::LINEAR, fog2.mode);
    CHECK_EQUAL (100,        fog2.near);
    CHECK_EQUAL (200,        fog2.far);

    delete reader;
}

