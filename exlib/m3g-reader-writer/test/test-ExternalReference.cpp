#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
#include <cstring>
using namespace std;

TEST (ExternalReference)
{
    int             object_type = M3G_TYPE_EXTERNAL_REFERENCE;
    unsigned int    object_index;
    M3GExternalReferenceStruct ex_ref;

    ex_ref.uri         = new char[16];
    strncpy (ex_ref.uri, "Hello world", 15);


    M3GWriter* writer = new M3GWriter ("external_reference.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeExternalReference  (ex_ref);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;

    M3GReader*      reader = new M3GReader ("external_reference.m3g");
    M3GExternalReferenceStruct ex_ref2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readExternalReference   (&ex_ref2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_EXTERNAL_REFERENCE, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL ("Hello world", ex_ref2.uri);

    delete reader;
}
