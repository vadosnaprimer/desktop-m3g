#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (Light)
{
    int object_type = M3G_TYPE_LIGHT;
    unsigned int object_index;
    M3GLightStruct light;

    light.attenuation_constant  = 3;
    light.attenuation_linear    = 4;
    light.attenuation_quadratic = 5;
    light.color                 = 0x12345678;
    light.mode                  = M3GLightStruct::SPOT;
    light.intensity             = 7;
    light.spot_angle            = 8;
    light.spot_exponent         = 9;

    M3GWriter* writer = new M3GWriter ("light.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeLight   (light);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("light.m3g");
    M3GLightStruct light2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readLight    (&light2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_LIGHT, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3,   light2.attenuation_constant);
    CHECK_EQUAL (4,   light2.attenuation_linear);
    CHECK_EQUAL (5,   light2.attenuation_quadratic);
    CHECK_EQUAL (0x00345678,           light2.color);
    CHECK_EQUAL (M3GLightStruct::SPOT, light2.mode);
    CHECK_EQUAL (7,   light2.intensity);
    CHECK_EQUAL (8,   light2.spot_angle);
    CHECK_EQUAL (9,   light2.spot_exponent);

    delete reader;
}
