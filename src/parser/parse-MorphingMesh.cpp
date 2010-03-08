#include <strstream>
#include <iostream>
#include <cstdlib>
#include "../MorphingMesh.hpp"
using namespace std;
using namespace m3g;

void parse_MorphingMesh (istrstream& iss, vector<Object3D*>& objs)
{
  unsigned int morph_target_count;
  int morph_target_index;
  float initial_weight;

  iss.read ((char*)&morph_target_count, 4);

 IndexBuffer** ibufs = (IndexBuffer**)malloc(sizeof(IndexBuffer*)*morph_target_count);
 Appearance** apps   = (Appearance**)malloc(sizeof(Appearance*)*morph_target_count);

 for (int i = 0; i < (int)morph_target_count; i++ ) {
    iss.read ((char*)&morph_target_index, 4);
    iss.read ((char*)&initial_weight, 4);
    
  }

  // 注意：基底クラスのMeshをデコードしないと作れない。
}
