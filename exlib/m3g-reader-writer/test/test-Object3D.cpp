#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;


TEST (Object3D)
{
    M3GObject3DStruct object3D;

    object3D.user_id                   = 3;
    object3D.animation_tracks_count    = 1;
    object3D.animation_tracks_index    = new unsigned int[1];
    object3D.animation_tracks_index[0] = 4;
    object3D.user_parameter_count      = 1;
    object3D.parameter_id              = new unsigned int[1];
    object3D.parameter_id[0]           = 5;
    object3D.parameter_value_length    = new unsigned int[1];
    object3D.parameter_value_length[0] = 6;
    object3D.parameter_value           = new char*[1];
    object3D.parameter_value[0]        = new char[6];
    object3D.parameter_value[0][0]     = 7;
    object3D.parameter_value[0][1]     = 8;
    object3D.parameter_value[0][2]     = 9;
    object3D.parameter_value[0][3]     = 10;
    object3D.parameter_value[0][4]     = 11;
    object3D.parameter_value[0][5]     = 12;

    M3GWriter* writer = new M3GWriter ("object3D.m3g");
    
    writer->writeObject3D (object3D);
    
    delete writer;
#if 0
    M3GReader* reader = new M3GReader ("object3D.m3g");
    M3GObject3DStruct object3D2;

    reader->readObject3D (&object3D2);

    CHECK_EQUAL (3,   object3D2.user_id);
    CHECK_EQUAL (1,   object3D2.animation_tracks_count);
    CHECK_EQUAL (4,   object3D2.animation_tracks_index[0]);
    CHECK_EQUAL (1,   object3D2.user_parameter_count);
    CHECK_EQUAL (5,   object3D2.parameter_id[0]);
    CHECK_EQUAL (6,   object3D2.parameter_value_length[0]);
    CHECK_EQUAL (7,   object3D2.parameter_value[0][0]);

    delete reader;
#endif
}
