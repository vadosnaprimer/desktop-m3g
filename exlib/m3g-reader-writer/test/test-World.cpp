#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (World)
{
    int object_type = M3G_TYPE_WORLD;
    unsigned int object_index;
    M3GWorldStruct world;

    world.active_camera_index = 3;
    world.background_index    = 4;

    M3GWriter* writer = new M3GWriter ("world.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeWorld   (world);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("world.m3g");
    M3GWorldStruct world2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readWorld    (&world2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_WORLD, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3,  world2.active_camera_index);
    CHECK_EQUAL (4,  world2.background_index);

    delete reader;
}

