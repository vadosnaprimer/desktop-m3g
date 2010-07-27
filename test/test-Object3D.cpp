#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Object3D.hpp"
#include "AnimationTrack.hpp"
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


TEST (Object3D_defautlt_variables)
{
    Object3D* obj = new Object3D;

    CHECK_EQUAL (0, obj->getAnimationTrackCount());
    //CHECK_EQUAL (0, obj->getReferences(0,0));
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

TEST (Object3D_animation_track) 
{
    KeyframeSequence* keyframe = new KeyframeSequence (1,1,KeyframeSequence::STEP);
    AnimationTrack* anim_track = new AnimationTrack (keyframe, AnimationTrack::ALPHA);

    Object3D* obj = new Object3D;
    obj->addAnimationTrack (anim_track);

    CHECK_EQUAL (1, obj->getAnimationTrackCount());
    CHECK_EQUAL (anim_track, obj->getAnimationTrack(0));

    obj->removeAnimationTrack (anim_track);
  
    CHECK_EQUAL (0, obj->getAnimationTrackCount());
}

TEST (Object3D_find)
{
    Object3D* obj = new Object3D;
    obj->setUserID (100);
    CHECK_EQUAL (obj, obj->find (100));

    delete obj;
}

TEST (Object3D_duplicate)
{
    KeyframeSequence* key_seq    = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
    AnimationTrack*   anim_track = new AnimationTrack   (key_seq, AnimationTrack::COLOR);
    
    Object3D* obj0 = new Object3D;
    obj0->setUserID     (0x87654321);
    obj0->setUserObject ((void*)0x12345678);
    obj0->addAnimationTrack (anim_track);

    Object3D* obj1 = obj0->duplicate();
  
    CHECK_EQUAL (0x87654321, obj1->getUserID());
    CHECK_EQUAL ((void*)0x12345678, obj1->getUserObject());
    CHECK_EQUAL (anim_track, obj1->getAnimationTrack(0));
}
