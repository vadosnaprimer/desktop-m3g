#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (Texture2D)
{
    int object_type = M3G_TYPE_TEXTURE2D;
    unsigned int object_index;
    M3GTexture2DStruct texture;

    texture.image_index  = 3;
    texture.blend_color  = 0x12345678;
    texture.blending     = 4;
    texture.wrapping_s   = 5;
    texture.wrapping_t   = 6;
    texture.level_filter = 7;
    texture.image_filter = 8;

    M3GWriter* writer = new M3GWriter ("texture.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeTexture2D     (texture);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("texture.m3g");
    M3GTexture2DStruct texture2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readTexture2D      (&texture2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_TEXTURE2D, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3,          texture2.image_index );
    CHECK_EQUAL (0x00345678, texture2.blend_color );
    CHECK_EQUAL (4,          texture2.blending    );
    CHECK_EQUAL (5,          texture2.wrapping_s  );
    CHECK_EQUAL (6,          texture2.wrapping_t  );
    CHECK_EQUAL (7,          texture2.level_filter);
    CHECK_EQUAL (8,          texture2.image_filter);

    delete reader;
}
