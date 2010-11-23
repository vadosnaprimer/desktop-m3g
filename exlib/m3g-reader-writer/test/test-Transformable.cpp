#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (Transformable)
{
    M3GTransformableStruct transformable;

    transformable.has_component_transform = true;
    transformable.translation[0]          = 3;
    transformable.translation[1]          = 4;
    transformable.translation[2]          = 5;
    transformable.scale[0]                = 6;
    transformable.scale[1]                = 7;
    transformable.scale[2]                = 8;
    transformable.orientation_angle       = 9;
    transformable.orientation_axis[0]     = 10;
    transformable.orientation_axis[1]     = 11;
    transformable.orientation_axis[2]     = 12;
    transformable.has_general_transform   = true;
    for (int i = 0; i < 16; i++) {
        transformable.transform[i] = i;
    }

    M3GWriter* writer = new M3GWriter ("transformable.m3g");

    writer->writeTransformable     (transformable);

    delete writer;

    M3GReader* reader = new M3GReader ("transformable.m3g");
    M3GTransformableStruct transformable2;

    reader->readTransformable      (&transformable2);

    CHECK_EQUAL (true,       transformable2.has_component_transform);
    CHECK_EQUAL (3,          transformable2.translation[0]);
    CHECK_EQUAL (4,          transformable2.translation[1]);
    CHECK_EQUAL (5,          transformable2.translation[2]);
    CHECK_EQUAL (6,          transformable2.scale[0]);
    CHECK_EQUAL (7,          transformable2.scale[1]);
    CHECK_EQUAL (8,          transformable2.scale[2]);
    CHECK_EQUAL (9,          transformable2.orientation_angle);
    CHECK_EQUAL (10,         transformable2.orientation_axis[0]);
    CHECK_EQUAL (11,         transformable2.orientation_axis[1]);
    CHECK_EQUAL (12,         transformable2.orientation_axis[2]);
    CHECK_EQUAL (true,       transformable2.has_general_transform);
    for (int i = 0; i < 16; i++) {
        CHECK_EQUAL (i, transformable2.transform[i]);
    }

    delete reader;
}

