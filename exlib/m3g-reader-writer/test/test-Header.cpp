#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
#include <cstring>
using namespace std;

TEST (Header)
{
    int             object_type = M3G_TYPE_HEADER;
    unsigned int    object_index;
    M3GHeaderStruct header;

    header.version_major           = 1;
    header.version_minor           = 0;
    header.has_external_references = false;
    header.authoring_field         = new char[16];
    strncpy (header.authoring_field, "Hello world", 15);


    M3GWriter* writer = new M3GWriter ("header.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeHeader  (header);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;

    M3GReader*      reader = new M3GReader ("header.m3g");
    M3GHeaderStruct header2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readHeader   (&header2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_HEADER, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (1, (int)header2.version_major);
    CHECK_EQUAL (0, (int)header2.version_minor);
    CHECK_EQUAL (0, (int)header2.has_external_references);
    CHECK_EQUAL (41, header2.total_file_size);
    CHECK_EQUAL (41, header2.approximate_content_size);
    CHECK_EQUAL ("Hello world", header2.authoring_field);

    delete reader;
}
