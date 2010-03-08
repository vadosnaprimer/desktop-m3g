#include "Keyframe.hpp"
#include "Quaternion.hpp"
#include "m3gexcept.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

Keyframe:: Keyframe () : time(-1), value(0)
{
}


Keyframe:: Keyframe (int t, float* v) : time(t), value(v)
{
}

Keyframe:: ~Keyframe ()
{
}

void m3g::step   (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value)
{
  if (value == NULL) {
    throw null_point_error ("Value is NULL.");
  }
  if (s < 0 || s > 1) {
    throw invalid_argument ("S is invalid.");
  }

  for (int i = 0; i < component_count; i++) {
    value[i] = (s < 1) ? k0.value[i] : k1.value[i];
    }
}

void m3g::linear (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value)
{
  if (value == NULL) {
    throw null_point_error ("Value is NULL.");
  }
  if (s < 0 || s > 1) {
    throw invalid_argument ("S is invalid.");
  }

  for (int i = 0; i < component_count; i++) {
    value[i] = k0.value[i]*(1-s) + k1.value[i]*(s);
  }
}

void m3g::slerp  (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value)
{
  if (value == NULL) {
    throw null_point_error ("Value is NULL.");
  }
  if (s < 0 || s > 1) {
    throw invalid_argument ("S is invalid.");
  }

  Quaternion q0, q1, q2;
  q0.set (k0.value[0], k0.value[1], k0.value[2], k0.value[3]);
  q1.set (k1.value[0], k1.value[1], k1.value[2], k1.value[3]);
  q2 = slerp (q0, q1, s);
  value[0] = q2.x;
  value[1] = q2.y;
  value[2] = q2.z;
  value[3] = q2.w;
  //cout << "a = " << a << "\n";
  //cout << "Quaternion q0 = " << q0 << "\n";
  //cout << "Quaternion q1 = " << q1 << "\n";
  //cout << "Quaternion by SLEPR = " << q2 << "\n";
}

void m3g::squad  (float s, const Keyframe& k0, const Keyframe& k1, int component_count, float* value)
{
  throw not_implemented_error ("Squad is not implemented.");
}

void m3g::spline (float s, const Keyframe& k0, const Keyframe& k1, const Keyframe& k2, const Keyframe& k3, int component_count, float* value)
{
  if (value == NULL) {
    throw null_point_error ("Value is NULL.");
  }
  if (s < 0 || s > 1) {
    throw invalid_argument ("S is invalid.");
  }

  float sh0 = 2*s*s*s - 3*s*s + 1;
  float sh1 = -2*s*s*s + 3*s*s;
  float sh2 = s*s*s - 2*s*s + s;
  float sh3 = s*s*s - s*s;

  for (int i = 0; i < component_count; i++) {
    float tan1 = (k0.time == -1) ? 0 : (k2.time-k1.time)/(float)(k2.time-k0.time)*(k2.value[i] - k0.value[i]);
    float tan2 = (k3.time == -1) ? 0 : (k2.time-k1.time)/(float)(k3.time-k1.time)*(k3.value[i] - k1.value[i]);

    value[i] = sh0*k1.value[i] + sh1*k2.value[i] + sh2*tan1 + sh3*tan2;
  }
}

std::ostream& operator<< (std::ostream& out, const m3g::Keyframe& key)
{
  out << "time=" << key.time << ",value=";
  if (key.value == NULL)
    out << "0";
  else
    out << key.value[0] << "," << key.value[1] << "," << key.value[2];
  return out;
}
