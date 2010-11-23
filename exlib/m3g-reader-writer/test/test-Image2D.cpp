#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;

TEST (Image2D)
{
    int             object_type = M3G_TYPE_IMAGE2D;
    unsigned int    object_index;

    M3GImage2DStruct   image;

    image.format        = 3;
    image.is_mutable    = false;
    image.width         = 4;
    image.height        = 5;
    image.palette_count = 0;
    image.palette       = 0;
    image.pixels_count  = 2;
    image.pixels        = new unsigned char[2];
    image.pixels[0]     = 1;
    image.pixels[1]     = 2;

    M3GWriter* writer = new M3GWriter ("image.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeImage2D (image);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;


    M3GReader* reader = new M3GReader ("image.m3g");
    M3GImage2DStruct image2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readImage2D  (&image2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_IMAGE2D, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3,     image2.format);
    CHECK_EQUAL (false, image2.is_mutable);
    CHECK_EQUAL (4,     image2.width);
    CHECK_EQUAL (5,     image2.height);
    CHECK_EQUAL (false, image2.palette_count);
    CHECK_EQUAL (2,     image2.pixels_count);
    CHECK_EQUAL (1,     image2.pixels[0]);
    CHECK_EQUAL (2,     image2.pixels[1]);

    delete reader;

}
