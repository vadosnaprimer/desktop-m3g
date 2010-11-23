#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;

TEST (Appearance)
{
    int             object_type = M3G_TYPE_APPEARANCE;
    unsigned int    object_index;

    M3GAppearanceStruct   appearance;

    appearance.layer                  = 3;
    appearance.compositing_mode_index = 4;
    appearance.fog_index              = 5;
    appearance.polygon_mode_index     = 6;
    appearance.material_index         = 7;
    appearance.textures_count         = 1;
    appearance.textures_index         = new unsigned int [1];
    appearance.textures_index[0]      = 8;

    M3GWriter* writer = new M3GWriter ("appearance.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeAppearance  (appearance);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;


    M3GReader* reader = new M3GReader ("appearance.m3g");
    M3GAppearanceStruct appearance2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readAppearance (&appearance2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_APPEARANCE, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3, appearance2.layer);
    CHECK_EQUAL (4, appearance2.compositing_mode_index);
    CHECK_EQUAL (5, appearance2.fog_index);
    CHECK_EQUAL (6, appearance2.polygon_mode_index);
    CHECK_EQUAL (7, appearance2.material_index);
    CHECK_EQUAL (1, appearance2.textures_count);
    CHECK_EQUAL (8, appearance2.textures_index[0]);

    delete reader;

}
