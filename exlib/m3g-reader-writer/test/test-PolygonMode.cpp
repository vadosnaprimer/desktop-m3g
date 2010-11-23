#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (PolygonMode)
{
    int object_type = M3G_TYPE_POLYGON_MODE;
    unsigned int object_index;
    M3GPolygonModeStruct poly_mode;

    poly_mode.culling = 3;
    poly_mode.shading = 4;
    poly_mode.winding = 5;
    poly_mode.two_sided_lighting_enabled     = true;
    poly_mode.local_camera_lighting_enabled  = true;
    poly_mode.perspective_correction_enabled = true;


    M3GWriter* writer = new M3GWriter ("poly_mode.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writePolygonMode    (poly_mode);
    writer->endObject    ();
    writer->endSection   ();


    delete writer;

    M3GReader* reader = new M3GReader ("poly_mode.m3g");
    M3GPolygonModeStruct poly_mode2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readPolygonMode  (&poly_mode2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (3,      poly_mode2.culling);
    CHECK_EQUAL (4,      poly_mode2.shading);
    CHECK_EQUAL (5,      poly_mode2.winding);
    CHECK_EQUAL (true,   poly_mode2.two_sided_lighting_enabled);
    CHECK_EQUAL (true,   poly_mode2.local_camera_lighting_enabled);
    CHECK_EQUAL (true,   poly_mode2.perspective_correction_enabled);

    delete reader;
}
