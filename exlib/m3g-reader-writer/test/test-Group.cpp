#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;

TEST (Group)
{
    int             object_type = M3G_TYPE_GROUP;
    unsigned int    object_index;

    M3GGroupStruct   group;

    group.children_index_count = 1;
    group.children_index       = new unsigned int[1];
    group.children_index[0]    = 3;

    M3GWriter* writer = new M3GWriter ("group.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeGroup   (group);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;


    M3GReader* reader = new M3GReader ("group.m3g");
    M3GGroupStruct group2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readGroup    (&group2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_GROUP, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (1,    group2.children_index_count);
    CHECK_EQUAL (3,    group2.children_index[0]);

    delete reader;

}
