#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Object3D.hpp"
#include "AnimationTrack.hpp"
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


// Not implemented, 

TEST (Object3D_defautlt_variables)
{
    Object3D* obj = new Object3D;

    CHECK_EQUAL (0, obj->getAnimationTrackCount());
    //CHECK_EQUAL (0, obj->getReferences(0,0));
    CHECK_EQUAL (0, obj->getUserID());
    //CHECK_EQUAL ((void*)0, obj->getUserObject());

    delete obj;
}

TEST (Object3D_set_variables)
{
    /*
      Object3D* obj = new Object3D;
      char buf[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

      obj->setUserID (100);
      obj->setUserObject ("test", buf);

      CHECK_EQUAL (100, obj->getUserID());
      CHECK_EQUAL ((void*)buf, obj->getUserObject());
    */
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
    Object3D* obj0 = new Object3D;
    Object3D* obj1 = obj0->duplicate();
  
    CHECK_EQUAL (obj0->getUserID(), obj1->getUserID());
    // 後でgetUserObject()のテストも追加
}
