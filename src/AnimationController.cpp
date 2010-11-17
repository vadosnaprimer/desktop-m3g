#include <iostream>
#include "m3g/AnimationController.hpp"
#include "m3g/Exception.hpp"
using namespace std;
using namespace m3g;


AnimationController:: AnimationController () : 
    active_interval(0,0), blending_weight(1), speed(1),
    reference_world_time(0), reference_sequence_time(0)
{
}

AnimationController:: ~AnimationController ()
{
}

AnimationController* AnimationController:: duplicate () const
{
    AnimationController* anim_ctr = new AnimationController;
    this->Object3D           :: copy (anim_ctr);
    this->AnimationController:: copy (anim_ctr);
    return anim_ctr;
}

void AnimationController:: copy (AnimationController* anim_ctr) const
{
    if (anim_ctr == NULL) {
        throw NullPointerException (__FILE__, __func__, "AnimationController is NULL.");
    }
    anim_ctr->active_interval          = active_interval;
    anim_ctr->blending_weight          = blending_weight;
    anim_ctr->speed                    = speed;
    anim_ctr->reference_world_time    = reference_world_time;
    anim_ctr->reference_sequence_time = reference_sequence_time;
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
    return reference_sequence_time + speed*(world_time - reference_world_time);
}

int AnimationController:: getRefWorldTime () const
{
    return reference_world_time;
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
    reference_world_time    = world_time;
    reference_sequence_time = sequence_time;
}

void AnimationController:: setSpeed (float new_speed, int world_time)
{
    reference_sequence_time = getPosition (world_time);
    reference_world_time    = world_time;
    speed                   = new_speed;
}

void AnimationController:: setWeight (float weight)
{
    blending_weight = weight;
}

bool AnimationController:: isActive (int world_time) const
{
    if (blending_weight == 0)
        return false;
    else if (active_interval.start == active_interval.end)
        return true;
    else if (world_time >= active_interval.start && world_time < active_interval.end)
        return true;
    else
        return false;
}

std::ostream& AnimationController:: print (std::ostream& out) const
{
    out << "AnimationController: ";
    out << "  active_interval="         << active_interval.start << "," << active_interval.end;
    out << ", blending_weight="         << blending_weight;
    out << ", speed="                   << speed;
    out << ", reference_world_time="    << reference_world_time;
    out << ", reference_sequence_time=" << reference_sequence_time;
    return out;
}

std::ostream& operator<< (std::ostream& out, const AnimationController& a)
{
    return a.print(out);
}
