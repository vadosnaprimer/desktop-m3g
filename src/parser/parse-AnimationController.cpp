#include <strstream>
#include <iostream>
#include "../AnimationController.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;



void parse_AnimationController (istrstream& iss, vector<Object3D*>& objs)
{
  AnimationController* ac = new AnimationController;

  parse_Object3D (iss, objs, ac);

  float speed;
  float weight;
  int   active_interval_start;
  int   active_interval_end;
  float reference_sequence_time;
  int   reference_world_time;

  iss.read ((char*)&speed, 4);
  iss.read ((char*)&weight, 4);
  iss.read ((char*)&active_interval_start, 4);
  iss.read ((char*)&active_interval_end, 4);
  iss.read ((char*)&reference_sequence_time, 4);
  iss.read ((char*)&reference_world_time, 4);
  
  ac->setSpeed (speed, reference_world_time);
  ac->setWeight (weight);
  ac->setActiveInterval (active_interval_start, active_interval_end);
  ac->setPosition (reference_sequence_time, reference_world_time);
  
  ac->print (cout);

  objs.push_back (ac);
}
