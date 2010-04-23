#include <iostream>
#include "AnimationController.hpp"
using namespace std;
using namespace m3g;


AnimationController:: AnimationController () : 
  active_interval(0,0), blending_weight(1), speed(1),
  refference_world_time(0), refference_sequence_time(0)
{
  setObjectType(OBJTYPE_ANIMATION_CONTROLLER);
}

AnimationController:: ~AnimationController ()
{
}

AnimationController* AnimationController:: duplicate () const
{
  return new AnimationController(*this);
}

int AnimationController:: getActiveIntervalEnd () const
{
    return active_interval.end;
}

int AnimationController:: getActiveIntervalStart () const
{
    return active_interval.start;
}

float AnimationController:: getPosition (int world_time) const
{
  return refference_sequence_time + speed*(world_time - refference_world_time);
}

int AnimationController:: getRefWorldTime () const
{
    return refference_world_time;
}

float AnimationController:: getSpeed () const
{
    return speed;
}

float AnimationController:: getWeight () const
{
    return blending_weight;
}

void AnimationController:: setActiveInterval (int start, int end)
{
  active_interval = ActiveInterval(start,end);
}

void AnimationController:: setPosition (float sequence_time, int world_time)
{
  refference_world_time    = world_time;
  refference_sequence_time = sequence_time;
}

void AnimationController:: setSpeed (float new_speed, int world_time)
{
  refference_sequence_time = getPosition (world_time);
  refference_world_time    = world_time;
  speed                    = new_speed;
}

void AnimationController:: setWeight (float weight)
{
  blending_weight = weight;
}

bool AnimationController:: isActiveInterval (int world_time) const
{
  if (active_interval.start == active_interval.end)
    return true;
  else if (world_time >= active_interval.start && world_time < active_interval.end)
    return true;
  else
    return false;
}

std::ostream& AnimationController:: print (std::ostream& out) const
{
  out << "AnimationController: ";
  out << "  active_interval=" << active_interval.start << "," << active_interval.end;
  out << ", blending_weight=" << blending_weight;
  out << ", speed=" << speed;
  out << ", refference_world_time=" << refference_world_time;
  out << ", refference_sequence_time=" << refference_sequence_time;
  return out;
}

std::ostream& operator<< (std::ostream& out, const AnimationController& a)
{
  return a.print(out);
}
