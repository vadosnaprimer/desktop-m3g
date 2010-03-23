#include <strstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "../KeyframeSequence.hpp"
#include "../Exception.hpp"
#include "parse-Object3D.hpp"
using namespace std;
using namespace m3g;
#include <cstdlib>


void parse_KeyframeSequence (istrstream& iss, vector<Object3D*>& objs)
{
  Object3D* dummy = new Object3D;
  parse_Object3D (iss, objs, dummy);

  unsigned char interpolation;
  unsigned char repeat_mode;
  unsigned char encoding;
  unsigned int  duration;
  unsigned int  valid_range_first;
  unsigned int  valid_range_last;
  unsigned int  component_count;
  unsigned int  keyframe_count;
  iss.read ((char*)&interpolation, 1);
  iss.read ((char*)&repeat_mode, 1);
  iss.read ((char*)&encoding, 1);
  iss.read ((char*)&duration, 4);
  iss.read ((char*)&valid_range_first, 4);
  iss.read ((char*)&valid_range_last, 4);
  iss.read ((char*)&component_count, 4);
  iss.read ((char*)&keyframe_count, 4);

  //cout << "keyframe_count = " << keyframe_count << "\n";
  //cout << "component_count = " << component_count << "\n";

  KeyframeSequence* keys = new KeyframeSequence (keyframe_count, component_count, interpolation);
  *(Object3D*)keys = *dummy;

  keys->setDuration   (duration);
  keys->setRepeatMode (repeat_mode);
  keys->setValidRange (valid_range_first, valid_range_last);

  unsigned int time;
  float* vector_value = new float[component_count];
 
  switch (encoding) {
  case 0: {
    for (int i = 0; i < (int)keyframe_count; i++) {
      iss.read ((char*)&time, 4);
      iss.read ((char*)vector_value, 4*component_count);
      keys->setKeyframe (i, time, vector_value);
      cout << "keyframe: " << i << ": (" << time << ") ";
      for (int j = 0; j < (int)component_count; j++) {
	cout << vector_value[j] << ","; 
      }
      cout << "\n";
    }
    break;
  }
  case 1: {
    float*          vector_bias          = new float[component_count];
    float*          vector_scale         = new float[component_count];
    unsigned char*  vector_encoded_value = new unsigned char[component_count];
    iss.read ((char*)vector_bias,  4*component_count);
    iss.read ((char*)vector_scale, 4*component_count);
    for (int i = 0; i < (int)keyframe_count; i++) {
      iss.read ((char*)&time, 4);
      iss.read ((char*)vector_encoded_value, 1*component_count);
      for (int j = 0; j < (int)component_count; j++) {
	vector_value[j] = (vector_encoded_value[j] - vector_bias[j]) / vector_scale[j] * 255;
      }
      keys->setKeyframe (i, time, vector_value);
    }
    delete [] vector_encoded_value;
    delete [] vector_bias;
    delete [] vector_scale;
    break;
  }
  case 2: {
    float*          vector_bias          = new float[component_count];
    float*          vector_scale         = new float[component_count];
    unsigned short* vector_encoded_value = new unsigned short[component_count];
    iss.read ((char*)vector_bias,  4*component_count);
    iss.read ((char*)vector_scale, 4*component_count);
    for (int i = 0; i < (int)keyframe_count; i++) {
      iss.read ((char*)&time, 4);
      iss.read ((char*)vector_encoded_value, 2*component_count);
      for (int j = 0; j < (int)component_count; j++) {
	vector_value[j] = (vector_encoded_value[j] - vector_bias[j]) / vector_scale[j] * 65535;
      }
      keys->setKeyframe (i, time, vector_value);
    }
    delete [] vector_encoded_value;
    delete [] vector_bias;
    delete [] vector_scale;
    break;
  }
  default: {
    throw InternalException (__FILE__, __func__, "Invalid encoding of KeyframeSequence.");
  }
  }

  delete [] vector_value;

  keys->print (cout);

  objs.push_back (keys);

}
