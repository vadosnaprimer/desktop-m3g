#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
#include <fstream>
using namespace std;

TEST (MorphingMesh)
{
    int object_type = M3G_TYPE_MORPHING_MESH;
    unsigned int object_index;
    M3GMorphingMeshStruct mesh;

    mesh.morph_target_count    = 1;
    mesh.morph_target_index   = new unsigned int[1];
    mesh.morph_target_index[0] = 2;
    mesh.initial_weight        = new float[1];
    mesh.initial_weight[0]     = 3;

    M3GWriter* writer = new M3GWriter ("mesh.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeMorphingMesh   (mesh);
    writer->endObject    ();
    writer->endSection   ();

    delete writer;

    M3GReader* reader = new M3GReader ("mesh.m3g");
    M3GMorphingMeshStruct mesh2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readMorphingMesh    (&mesh2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_MORPHING_MESH, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (1, mesh2.morph_target_count);
    CHECK_EQUAL (2, mesh2.morph_target_index[0]);
    CHECK_EQUAL (3, mesh2.initial_weight[0]);

    delete reader;
}
