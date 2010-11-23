#include "m3g/M3GWriter.hpp"
#include "m3g/M3GReader.hpp"
#include "unittest++/UnitTest++.h"
using namespace std;

TEST (AnimationTrack)
{
    int             object_type = M3G_TYPE_ANIMATION_TRACK;
    unsigned int    object_index;
    M3GAnimationTrackStruct anim_track;

    anim_track.keyframe_sequence_index    = 4;
    anim_track.animation_controller_index = 5;
    anim_track.property_id                = 6;

    M3GWriter* writer = new M3GWriter ("animation_track.m3g");

    writer->startSection ();
    writer->startObject  (object_type, &object_index);
    writer->writeAnimationTrack  (anim_track);
    writer->endObject    ();
    writer->endSection   ();
    
    delete writer;


    M3GReader*      reader = new M3GReader ("animation_track.m3g");
    M3GAnimationTrackStruct anim_track2;

    reader->startSection ();
    reader->startObject  (&object_type, &object_index);
    reader->readAnimationTrack   (&anim_track2);
    reader->endObject    ();
    reader->endSection   ();

    CHECK_EQUAL (M3G_TYPE_ANIMATION_TRACK, object_type);
    CHECK_EQUAL (1, object_index);

    CHECK_EQUAL (4,    anim_track2.keyframe_sequence_index);
    CHECK_EQUAL (5,    anim_track2.animation_controller_index);
    CHECK_EQUAL (6,   anim_track2.property_id);

    delete reader;

}
