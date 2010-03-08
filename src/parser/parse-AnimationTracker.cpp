#include <strstream>
#include <iostream>
#include <vector>
#include "../AnimationController.hpp"
#include "../AnimationTrack.hpp"
#include "../KeyframeSequence.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;


void parse_AnimationTrack (istrstream& iss, std::vector<Object3D*>& objs)
{
  Object3D* dummy = new Object3D;
  parse_Object3D (iss, objs, dummy);

  unsigned int keyframe_sequence_index;
  unsigned int animation_controller_index;
  unsigned int property_id;
    
  iss.read ((char*)&keyframe_sequence_index, 4);
  iss.read ((char*)&animation_controller_index, 4);
  iss.read ((char*)&property_id, 4);

  KeyframeSequence* keyframe_sequence = 0;
  if (keyframe_sequence_index > 0) {
    keyframe_sequence = dynamic_cast<KeyframeSequence*>(objs.at(keyframe_sequence_index));
  }
  
  AnimationTrack* atrack = new AnimationTrack (keyframe_sequence, property_id);
  *(Object3D*)atrack = *dummy;
  
  AnimationController* acon = 0;
  if (animation_controller_index > 0) {
    acon = dynamic_cast<AnimationController*>(objs.at(animation_controller_index));
    atrack->setController (acon);
  }

  atrack->print (cout);

  objs.push_back (atrack);
}
