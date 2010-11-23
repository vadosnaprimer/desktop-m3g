#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (Node)
{
    M3GNodeStruct node;

    node.enable_rendering = true;
    node.enable_picking   = true;
    node.alpha_factor     = 3;
    node.scope            = 4;
    node.has_alignment    = true;
    node.z_target         = 5;
    node.y_target         = 6;
    node.z_reference_index = 7;
    node.y_reference_index = 8;


    M3GWriter* writer = new M3GWriter ("node.m3g");

    writer->writeNode    (node);

    delete writer;

    M3GReader* reader = new M3GReader ("node.m3g");
    M3GNodeStruct node2;

    reader->readNode     (&node2);

    CHECK_EQUAL (true,   node2.enable_rendering);
    CHECK_EQUAL (true,   node2.enable_picking);
    CHECK_EQUAL (3,      node2.alpha_factor);
    CHECK_EQUAL (4,      node2.scope);
    CHECK_EQUAL (true,   node2.has_alignment);
    CHECK_EQUAL (5,      node2.z_target);
    CHECK_EQUAL (6,      node2.y_target);
    CHECK_EQUAL (7,      node2.z_reference_index);
    CHECK_EQUAL (8,      node2.y_reference_index);

    delete reader;
}
