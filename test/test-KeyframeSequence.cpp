#include <unittest++/UnitTest++.h>
#include <iostream>
#include "KeyframeSequence.hpp"
using namespace std;
using namespace m3g;


/**
 * M3G1.1ではなぜかデフォルト値が定義されてない。自分で適当に決めた。
 */
TEST (KeyframeSequence_default_variables)
{
  KeyframeSequence* keyframe = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);

  CHECK_EQUAL (10,   keyframe->getKeyframeCount());
  CHECK_EQUAL (3,    keyframe->getComponentCount());
  CHECK_EQUAL (KeyframeSequence::LINEAR, keyframe->getInterpolationType());
  CHECK_EQUAL (KeyframeSequence::CONSTANT,   keyframe->getRepeatMode());

  delete keyframe;
}

TEST (KeyframeSequence_set_variables)
{
  KeyframeSequence* keyframe = new KeyframeSequence (10, 3, KeyframeSequence::LINEAR);
  keyframe->setDuration (1000);
  keyframe->setRepeatMode (KeyframeSequence::LOOP);
  keyframe->setValidRange (5,9);

  CHECK_EQUAL (10,   keyframe->getKeyframeCount());
  CHECK_EQUAL (3,    keyframe->getComponentCount());
  CHECK_EQUAL (KeyframeSequence::LINEAR,   keyframe->getInterpolationType());
  CHECK_EQUAL (KeyframeSequence::LOOP, keyframe->getRepeatMode());
  CHECK_EQUAL (1000, keyframe->getDuration());
  CHECK_EQUAL (5,    keyframe->getValidRangeFirst());
  CHECK_EQUAL (9,   keyframe->getValidRangeLast());

  delete keyframe;
}

TEST (KeyframeSequence_interpolate_step)
{
  KeyframeSequence* keyframe = new KeyframeSequence (3, 1, KeyframeSequence::STEP);
  keyframe->setDuration  (1000);
  keyframe->setValidRange (0,2);

  float values[] = {0,1,3};
  keyframe->setKeyframe (0,   0, &values[0]);
  keyframe->setKeyframe (1, 100, &values[1]);
  keyframe->setKeyframe (2, 200, &values[2]);

  float value;

  keyframe->getFrame (-50, &value);
  CHECK_CLOSE (0, value, 0.00001);

  keyframe->getFrame (0, &value);
  CHECK_CLOSE (0, value, 0.00001);

  keyframe->getFrame (50, &value);
  CHECK_CLOSE (0, value, 0.00001);

  keyframe->getFrame (100, &value);
  CHECK_CLOSE (1, value, 0.00001);

  keyframe->getFrame (150, &value);
  CHECK_CLOSE (1, value, 0.00001);

  keyframe->getFrame (200, &value);
  CHECK_CLOSE (3, value, 0.00001);

  keyframe->getFrame (250, &value);
  CHECK_CLOSE (3, value, 0.00001);
}



TEST (KeyframeSequence_interpolate_linear_constant)
{
  KeyframeSequence* keyframe = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
  keyframe->setDuration  (1000);
  keyframe->setValidRange (0,2);

  float values[] = {0,1,3};
  keyframe->setKeyframe (0,   0, &values[0]);
  keyframe->setKeyframe (1, 100, &values[1]);
  keyframe->setKeyframe (2, 200, &values[2]);

  float value;

  keyframe->getFrame (-50, &value);
  CHECK_CLOSE (0, value, 0.00001);

  keyframe->getFrame (0, &value);
  CHECK_CLOSE (0, value, 0.00001);

  keyframe->getFrame (50, &value);
  CHECK_CLOSE (0.5, value, 0.00001);

  keyframe->getFrame (100, &value);
  CHECK_CLOSE (1, value, 0.00001);

  keyframe->getFrame (150, &value);
  CHECK_CLOSE (2, value, 0.00001);

  keyframe->getFrame (200, &value);
  CHECK_CLOSE (3, value, 0.00001);

  keyframe->getFrame (250, &value);
  CHECK_CLOSE (3, value, 0.00001);
}


TEST (KeyframeSequence_interpolate_linear_loop)
{
  KeyframeSequence* keyframe = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
  keyframe->setDuration  (1000);
  keyframe->setValidRange (0,2);
  keyframe->setRepeatMode (KeyframeSequence::LOOP);

  float values[] = {0,1,3};
  keyframe->setKeyframe (0,   0, &values[0]);
  keyframe->setKeyframe (1, 100, &values[1]);
  keyframe->setKeyframe (2, 200, &values[2]);

  float value;

  keyframe->getFrame (-50, &value);
  CHECK_CLOSE (0, value, 0.00001);

  keyframe->getFrame (0, &value);
  CHECK_CLOSE (0, value, 0.00001);

  keyframe->getFrame (50, &value);
  CHECK_CLOSE (0.5, value, 0.00001);

  keyframe->getFrame (100, &value);
  CHECK_CLOSE (1, value, 0.00001);

  keyframe->getFrame (150, &value);
  CHECK_CLOSE (2, value, 0.00001);

  keyframe->getFrame (200, &value);
  CHECK_CLOSE (3, value, 0.00001);

  keyframe->getFrame (250, &value);
  CHECK_CLOSE (3, value, 0.00001);
}



