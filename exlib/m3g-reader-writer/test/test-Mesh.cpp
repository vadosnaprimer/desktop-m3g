#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (Mesh)
{
    int object_type = M3G_TYPE_MESH;
    unsigned int object_index;
    M3GMeshStruct mesh;

    mesh.vertex_buffer_index = 3;
    mesh.submesh_count = 1;
    mesh.index_buffer_index    = new unsigned int[1];
    mesh.index_buffer_index[0] = 4;
    mesh.appearance_index      = new unsigned int[1];
    mesh.appearance_index[0]   = 5;

    M3GWriter* writer = new M3GWriter ("mesh.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeMesh   (mesh);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("mesh.m3g");
    M3GMeshStruct mesh2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readMesh    (&mesh2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_MESH, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (3, mesh2.vertex_buffer_index);
    CHECK_EQUAL (1, mesh2.submesh_count);
    CHECK_EQUAL (4, mesh2.index_buffer_index[0]);
    CHECK_EQUAL (5, mesh2.appearance_index[0]);

    delete reader;
}
