#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;


TEST (AnimationController)
{
    int             object_type = M3G_TYPE_ANIMATION_CONTROLLER;
    unsigned int    object_index;
    M3GAnimationControllerStruct anim_controller;

    anim_controller.speed = 2;
    anim_controller.weight = 3;
    anim_controller.active_interval_start = 10;
    anim_controller.active_interval_end   = 20;
    anim_controller.reference_sequence_time = 1300;
    anim_controller.reference_world_time    = 2600;

    M3GWriter* writer = new M3GWriter ("animation_controller.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeAnimationController  (anim_controller);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;

    M3GReader*      reader = new M3GReader ("animation_controller.m3g");
    M3GAnimationControllerStruct anim_controller2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readAnimationController   (&anim_controller2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_ANIMATION_CONTROLLER, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (2,    anim_controller2.speed);
    CHECK_EQUAL (3,    anim_controller2.weight);
    CHECK_EQUAL (10,   anim_controller2.active_interval_start);
    CHECK_EQUAL (20,   anim_controller2.active_interval_end);
    CHECK_EQUAL (1300, anim_controller2.reference_sequence_time);
    CHECK_EQUAL (2600, anim_controller2.reference_world_time);

    delete reader;

}
