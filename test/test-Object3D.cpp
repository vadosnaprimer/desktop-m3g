#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/Object3D.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/KeyframeSequence.hpp"
#include "m3g/Node.hpp"
using namespace std;
using namespace m3g;


TEST (Object3D_defautlt_variables)
{
    Object3D* obj = new Object3D;

    CHECK_EQUAL (0       , obj->getAnimationTrackCount());
    CHECK_EQUAL (0       , obj->getReferences(0));
    CHECK_EQUAL (0       , obj->getUserID());
    CHECK_EQUAL ((void*)0, obj->getUserObject());

    delete obj;
}

TEST (Object3D_set_variables)
{
      Object3D* obj = new Object3D;

      obj->setUserID (100);
      obj->setUserObject ((void*)0x1234);

      CHECK_EQUAL (100          , obj->getUserID());
      CHECK_EQUAL ((void*)0x1234, obj->getUserObject());

}

TEST (Object3D_add_animation_track) 
{
    KeyframeSequence* keyframe   = new KeyframeSequence (1,1,KeyframeSequence::STEP);
    AnimationTrack*   anim_track = new AnimationTrack (keyframe, AnimationTrack::ALPHA);

    Object3D* obj = new Node;
    obj->addAnimationTrack (anim_track);

    CHECK_EQUAL (1, obj->getAnimationTrackCount());
    CHECK_EQUAL (anim_track, obj->getAnimationTrack(0));

    obj->removeAnimationTrack (anim_track);
  
    CHECK_EQUAL (0, obj->getAnimationTrackCount());

    delete obj;
    delete keyframe;
    delete anim_track;
}

TEST (Object3D_getReferences) 
{
    KeyframeSequence* keyframe   = new KeyframeSequence (1,1,KeyframeSequence::STEP);
    AnimationTrack*   anim_track = new AnimationTrack (keyframe, AnimationTrack::ALPHA);

    Object3D* obj = new Node;
    obj->addAnimationTrack (anim_track);

    int n;
    Object3D* objs[1];

    n = obj->getReferences (objs);

    CHECK_EQUAL (1, n);
    CHECK_EQUAL (anim_track, objs[0]);

    delete obj;
    delete keyframe;
    delete anim_track;
}

TEST (Object3D_find)
{
    KeyframeSequence* key_sequence = new KeyframeSequence (1,1,KeyframeSequence::STEP);
    AnimationTrack*   anim_track   = new AnimationTrack (key_sequence, AnimationTrack::ALPHA);
    Object3D* obj = new Node;
    obj->addAnimationTrack (anim_track);
    
    key_sequence->setUserID (100);
    anim_track->setUserID (101);
    obj->setUserID (102);
    
    CHECK_EQUAL (key_sequence, obj->find (100));
    CHECK_EQUAL (anim_track  , obj->find (101));
    CHECK_EQUAL (obj         , obj->find (102));
    
    delete obj;
    delete anim_track;
    delete key_sequence;
}

TEST (Object3D_duplicate)
{
    KeyframeSequence* key_seq    = new KeyframeSequence (10, 1, KeyframeSequence::LINEAR);
    AnimationTrack*   anim_track = new AnimationTrack   (key_seq, AnimationTrack::PICKABILITY);
    
    Object3D* obj0 = new Node;
    obj0->setUserID     (0x87654321);
    obj0->setUserObject ((void*)0x12345678);
    obj0->addAnimationTrack (anim_track);

    Object3D* obj1 = obj0->duplicate();
  
    CHECK_EQUAL (0x87654321, obj1->getUserID());
    CHECK_EQUAL ((void*)0x12345678, obj1->getUserObject());
    CHECK_EQUAL (anim_track, obj1->getAnimationTrack(0));
}
