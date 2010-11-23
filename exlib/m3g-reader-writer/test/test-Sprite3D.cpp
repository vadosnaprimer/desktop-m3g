#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (Sprite3D)
{
    int object_type = M3G_TYPE_SPRITE3D;
    unsigned int object_index;
    M3GSprite3DStruct sprite;

    sprite.image_index      = 3;
    sprite.appearance_index = 4;
    sprite.is_scaled        = true;
    sprite.crop_x           = 5;
    sprite.crop_y           = 6;
    sprite.crop_width       = 7;
    sprite.crop_height      = 8;

    M3GWriter* writer = new M3GWriter ("sprite3D.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeSprite3D (sprite);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("sprite3D.m3g");
    M3GSprite3DStruct sprite2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readSprite3D (&sprite2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_SPRITE3D, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3,    sprite.image_index);
    CHECK_EQUAL (4,    sprite.appearance_index);
    CHECK_EQUAL (true, sprite.is_scaled);
    CHECK_EQUAL (5,    sprite.crop_x);
    CHECK_EQUAL (6,    sprite.crop_y);
    CHECK_EQUAL (7,    sprite.crop_width);
    CHECK_EQUAL (8,    sprite.crop_height);

    delete reader;
}
