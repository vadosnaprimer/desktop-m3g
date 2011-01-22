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
    AnimationController* controller   = new AnimationController;
    KeyframeSequence*    key_sequence = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
    AnimationTrack*      track        = new AnimationTrack   (key_sequence, AnimationTrack::COLOR);
    track->setController (controller);

    CHECK_EQUAL (controller           , track->getController());
    CHECK_EQUAL (key_sequence         , track->getKeyframeSequence());
    CHECK_EQUAL (AnimationTrack::COLOR, track->getTargetProperty());

    delete track;
    delete key_sequence;
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

    delete track0;
    delete track1;
    delete keyframe;
    delete controller;
}

TEST (AnimationTrack_find)
{
    AnimationController* controller   = new AnimationController;
    KeyframeSequence*    key_sequence = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
    AnimationTrack*      track        = new AnimationTrack   (key_sequence, AnimationTrack::COLOR);
    track->setController (controller);

    controller  ->setUserID (100);
    key_sequence->setUserID (101);
    track       ->setUserID (102);

    CHECK_EQUAL (controller  , track->find(100));
    CHECK_EQUAL (key_sequence, track->find(101));
    CHECK_EQUAL (track       , track->find(102));

    delete track;
    delete key_sequence;
    delete controller;
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




