#include <cstdlib>
#include "parse-Object3D.hpp"
#include "../Object3D.hpp"
#include "../AnimationTrack.hpp"
#include "../Exception.hpp"
using namespace std;
using namespace m3g;

void parse_Object3D (istrstream& iss, vector<Object3D*>& objs, Object3D* obj)
{
  if (obj == NULL) {
    throw NullPointException (__FILE__, __func__, "Object3D is NULL.");
  }

  unsigned int user_id;
  iss.read ((char*)&user_id, 4);
  obj->setUserID (user_id);

  unsigned int animation_tracks_count;
  unsigned int animation_tracks_index;
  iss.read ((char*)&animation_tracks_count, 4);
  for (int i = 0; i < (int)animation_tracks_count; i++) {
    iss.read ((char*)&animation_tracks_index, 4);
    AnimationTrack* atrack = dynamic_cast<AnimationTrack*>(objs[animation_tracks_index]);
    obj->addAnimationTrack (atrack);
  }

  unsigned int user_parameter_count;
  unsigned int user_parameter_id;
  unsigned int user_parameter_value_count;
  char* user_parameter_value;
  iss.read ((char*)&user_parameter_count, 4);
  for (int i = 0; i < (int)user_parameter_count; i++) {
    iss.read ((char*)&user_parameter_id, 4);
    iss.read ((char*)&user_parameter_value_count, 4);
    user_parameter_value = (char*)malloc(user_parameter_value_count);
    iss.read ((char*)user_parameter_value, user_parameter_value_count);

    // 本当はユーザーデータはkey,valueのペアでなければならない。
    // 今の実装だとvalueだけ。あとで修整する。
    obj->setUserObject (user_parameter_value);
  }

}
