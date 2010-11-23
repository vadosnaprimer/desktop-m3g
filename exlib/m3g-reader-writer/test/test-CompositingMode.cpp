#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;

TEST (CompositingMode)
{
    int             object_type = M3G_TYPE_COMPOSITING_MODE;
    unsigned int    object_index;

    M3GCompositingModeStruct   comp_mode;

    comp_mode.depth_test_enabled  = true;
    comp_mode.depth_write_enabled = true;
    comp_mode.color_write_enabled = true;
    comp_mode.alpha_write_enabled = true;
    comp_mode.blending            = 1;
    comp_mode.alpha_threshold     = 2;
    comp_mode.depth_offset_factor = 3;
    comp_mode.depth_offset_units  = 4;


    M3GWriter* writer = new M3GWriter ("comp_mode.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeCompositingMode  (comp_mode);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;


    M3GReader* reader = new M3GReader ("comp_mode.m3g");
    M3GCompositingModeStruct comp_mode2;

    reader->startSection  ();
    reader->startObject   (&object_type, &object_index);
    reader->readCompositingMode (&comp_mode2);
    reader->endObject     ();
    reader->endSection    ();

    CHECK_EQUAL (M3G_TYPE_COMPOSITING_MODE, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (true, comp_mode2.depth_test_enabled);
    CHECK_EQUAL (true, comp_mode2.depth_write_enabled);
    CHECK_EQUAL (true, comp_mode2.color_write_enabled);
    CHECK_EQUAL (true, comp_mode2.alpha_write_enabled);
    CHECK_EQUAL (1,    comp_mode2.blending);
    CHECK_EQUAL (2,    comp_mode2.alpha_threshold);
    CHECK_EQUAL (3,    comp_mode2.depth_offset_factor);
    CHECK_EQUAL (4,    comp_mode2.depth_offset_units);

    delete reader;
}
