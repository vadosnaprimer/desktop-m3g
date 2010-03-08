#include <unittest++/UnitTest++.h>
#include <iostream>
#include <fstream>
#include "Keyframe.hpp"
using namespace std;
using namespace m3g;


TEST (Keyframe_step)
{
  float value0[] = {0,0};
  float value1[] = {1,1};
  Keyframe key0 (0, value0);
  Keyframe key1 (1, value1);

  float value[2];

  step (0, key0, key1, 2, value);
  CHECK_CLOSE (0, value[0], 0.00001);
  CHECK_CLOSE (0, value[1], 0.00001);

  step (0.5, key0, key1, 2, value);
  CHECK_CLOSE (0, value[0], 0.00001);
  CHECK_CLOSE (0, value[1], 0.00001);

  step (1, key0, key1, 2, value);
  CHECK_CLOSE (1, value[0], 0.00001);
  CHECK_CLOSE (1, value[1], 0.00001);
}

TEST (Keyframe_linear)
{
  float value0[] = {0,0};
  float value1[] = {1,1};
  Keyframe key0 (0, value0);
  Keyframe key1 (1, value1);

  float value[2];

  linear (0, key0, key1, 2, value);
  CHECK_CLOSE (0, value[0], 0.00001);
  CHECK_CLOSE (0, value[1], 0.00001);

  linear (0.5, key0, key1, 2, value);
  CHECK_CLOSE (0.5, value[0], 0.00001);
  CHECK_CLOSE (0.5, value[1], 0.00001);

  linear (1, key0, key1, 2, value);
  CHECK_CLOSE (1, value[0], 0.00001);
  CHECK_CLOSE (1, value[1], 0.00001);
}


TEST (Keyframe_spline)
{
  float value0[] = {0,0};
  float value1[] = {1,1};
  float value2[] = {2,1};
  float value3[] = {3,0};
  Keyframe key0 (0, value0);
  Keyframe key1 (10, value1);
  Keyframe key2 (20, value2);
  Keyframe key3 (25, value3);

  float value[2];
  
  ofstream ofs ("log");

  for (int time = key0.time; time <= key3.time; time++) {
    if (time < key1.time) {
      float s = (time - key0.time) / (float)(key1.time - key0.time);
      spline (s, Keyframe(-1,0), key0, key1, key2, 2, value);
      //cout << "s = " << s << "\n";
    }
    else if (time < key2.time) {
      float s = (time - key1.time) / (float)(key2.time - key1.time);
      spline (s, key0, key1, key2, key3, 2, value);
      //cout << "s = " << s << "\n";
    }
    else if (time <= key3.time) {
      float s = (time - key2.time) / (float)(key3.time - key2.time);
      spline (s, key1, key2, key3, Keyframe(-1,0), 2, value);
      //cout << "s = " << s << "\n";
    }
    ofs << value[0] << ", " << value[1] << "\n";
  }

  // logをプロットして確認する
}

