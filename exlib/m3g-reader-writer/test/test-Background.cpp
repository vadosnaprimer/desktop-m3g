#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;

TEST (Background)
{
    int             object_type = M3G_TYPE_BACKGROUND;
    unsigned int    object_index;

    M3GBackgroundStruct   background;

    background.background_color        = 0x12345678;
    background.background_image_index  = 3;
    background.background_image_mode_x = 4;
    background.background_image_mode_y = 5;
    background.crop_x                  = 6;
    background.crop_y                  = 7;
    background.crop_width              = 8;
    background.crop_height             = 9;
    background.depth_clear_enabled     = true;
    background.color_clear_enabled     = true;

    M3GWriter* writer = new M3GWriter ("background.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeBackground  (background);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;


    M3GReader* reader = new M3GReader ("background.m3g");
    M3GBackgroundStruct background2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readBackground (&background2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_BACKGROUND, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (0x12345678, background2.background_color);
    CHECK_EQUAL (3,          background2.background_image_index);
    CHECK_EQUAL (4,          background2.background_image_mode_x);
    CHECK_EQUAL (5,          background2.background_image_mode_y);
    CHECK_EQUAL (6,          background2.crop_x);
    CHECK_EQUAL (7,          background2.crop_y);
    CHECK_EQUAL (8,          background2.crop_width);
    CHECK_EQUAL (9,          background2.crop_height);
    CHECK_EQUAL (true,       background2.depth_clear_enabled);
    CHECK_EQUAL (true,       background2.color_clear_enabled);

    delete reader;

}
