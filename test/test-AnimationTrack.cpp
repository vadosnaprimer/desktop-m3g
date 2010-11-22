#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


TEST (AnimationTrack_default_variables)
{
    KeyframeSequence* keyframe = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
    AnimationTrack*   track    = new AnimationTrack   (keyframe, AnimationTrack::COLOR);

    CHECK_EQUAL ((AnimationController*)0, track->getController());
    CHECK_EQUAL (keyframe,                track->getKeyframeSequence());
    CHECK_EQUAL (AnimationTrack::COLOR,   track->getTargetProperty());

    delete track;
    delete keyframe;
}

TEST (AnimationTrack_set_variables)
{
    AnimationController* controller = new AnimationController;
    KeyframeSequence*    keyframe   = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
    AnimationTrack*      track      = new AnimationTrack   (keyframe, AnimationTrack::COLOR);
    track->setController (controller);

    CHECK_EQUAL ((AnimationController*)controller, track->getController());
    CHECK_EQUAL (keyframe,                         track->getKeyframeSequence());
    CHECK_EQUAL (AnimationTrack::COLOR,            track->getTargetProperty());

    delete track;
    delete keyframe;
    delete controller;
}

TEST (AnimationTrack_duplicate)
{
    AnimationController* controller = new AnimationController;
    KeyframeSequence*    keyframe   = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
    AnimationTrack*      track0     = new AnimationTrack   (keyframe, AnimationTrack::COLOR);
    track0->setController (controller);

    AnimationTrack* track1 = track0->duplicate();
    CHECK_EQUAL (track0->getController(),       track1->getController());
    CHECK_EQUAL (track0->getKeyframeSequence(), track1->getKeyframeSequence());
    CHECK_EQUAL (track0->getTargetProperty(),   track1->getTargetProperty());
}

TEST (AnimationTrack_getReferences)
{
    AnimationController* controller = new AnimationController;
    KeyframeSequence*    keyframe   = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
    AnimationTrack*      track      = new AnimationTrack   (keyframe, AnimationTrack::COLOR);
    track->setController (controller);

    Object3D* objs[2];
    int n = track->getReferences (objs);

    CHECK_EQUAL (2, n);
    CHECK_EQUAL (keyframe  , objs[0]);
    CHECK_EQUAL (controller, objs[1]);

    delete track;
    delete keyframe;
    delete controller;
}




