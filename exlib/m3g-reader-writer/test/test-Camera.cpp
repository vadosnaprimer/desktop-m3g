#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;

TEST (Camera)
{
    int             object_type = M3G_TYPE_CAMERA;
    unsigned int    object_index;

    M3GCameraStruct   camera;

    camera.projection_type = M3GCameraStruct::PERSPECTIVE;
    for (int i = 0; i < 16; i++) {
        camera.matrix[i] = i;
    }
    camera.fovy            = 4;
    camera.aspect_ratio    = 5;
    camera.near            = 6;
    camera.far             = 7;

    M3GWriter* writer = new M3GWriter ("camera.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeCamera  (camera);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;


    M3GReader* reader = new M3GReader ("camera.m3g");
    M3GCameraStruct camera2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readCamera   (&camera2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_CAMERA, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (M3GCameraStruct::PERSPECTIVE, camera2.projection_type);
    CHECK_EQUAL (4,          camera2.fovy);
    CHECK_EQUAL (5,          camera2.aspect_ratio);
    CHECK_EQUAL (6,          camera2.near);
    CHECK_EQUAL (7,          camera2.far);

    delete reader;

}
