#include <unittest++/UnitTest++.h>
#include <iostream>
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


TEST (AnimationTrack_default_variables)
{
  KeyframeSequence* keyframe = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
  AnimationTrack*   track    = new AnimationTrack   (keyframe, AnimationTrack::COLOR);

  CHECK_EQUAL ((AnimationController*)0, track->getController());
  CHECK_EQUAL (keyframe,                track->getKeyframeSequence());
  CHECK_EQUAL (AnimationTrack::COLOR,   track->getTargetProperty());
}

TEST (AnimationTrack_set_variables)
{
  AnimationController* controller = new AnimationController;
  KeyframeSequence* keyframe = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
  AnimationTrack* track      = new AnimationTrack   (keyframe, AnimationTrack::COLOR);
  track->setController (controller);

  CHECK_EQUAL ((AnimationController*)controller,    track->getController());
  CHECK_EQUAL (keyframe,                   track->getKeyframeSequence());
  CHECK_EQUAL (AnimationTrack::COLOR, track->getTargetProperty());

  delete keyframe;
}




