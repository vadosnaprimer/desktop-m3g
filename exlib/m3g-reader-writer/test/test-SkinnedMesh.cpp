#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (SkinnedMesh)
{
    int object_type = M3G_TYPE_SKINNED_MESH;
    unsigned int object_index;
    M3GSkinnedMeshStruct mesh;

    mesh.skeleton_index            = 2;
    mesh.transform_reference_count = 1;
    mesh.transform_node_index      = new unsigned int[1];
    mesh.transform_node_index[0]   = 3;
    mesh.first_vertex              = new unsigned int[1];
    mesh.first_vertex[0]           = 4;
    mesh.vertex_count              = new unsigned int[1];
    mesh.vertex_count[0]           = 5;
    mesh.weight                    = new int[1];
    mesh.weight[0]                 = 6;

    M3GWriter* writer = new M3GWriter ("mesh.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeSkinnedMesh    (mesh);
    writer->endObject    ();
    writer->endSection   ();


    delete writer;

    M3GReader* reader = new M3GReader ("mesh.m3g");
    M3GSkinnedMeshStruct mesh2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readSkinnedMesh  (&mesh2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (2,      mesh2.skeleton_index);
    CHECK_EQUAL (1,      mesh2.transform_reference_count);
    CHECK_EQUAL (3,      mesh2.transform_node_index[0]);
    CHECK_EQUAL (4,      mesh2.first_vertex[0]);
    CHECK_EQUAL (5,      mesh2.vertex_count[0]);
    CHECK_EQUAL (6,      mesh2.weight[0]);

    delete reader;
}
