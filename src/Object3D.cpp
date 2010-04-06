#include "Object3D.hpp"
#include "AnimationTrack.hpp"
#include "Exception.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

Object3D:: Object3D () : obj_type(OBJTYPE_OBJECT3D), user_id(0)
{
}

Object3D:: ~Object3D ()
{
}

/**
 * 
 */
void Object3D:: addAnimationTrack (AnimationTrack* animation_track)
{
  if (animation_track == NULL) {
    throw NullPointException (__FILE__, __func__, "Animation track is Null.");
  }

  anim_tracks.push_back (animation_track);
}

int Object3D:: animate (int world_time)
{
    return 0;
}

Object3D* Object3D:: duplicate () const
{
  Object3D* obj    = new Object3D;
  obj->user_id     = this->user_id;
  obj->anim_tracks = this->anim_tracks;
  return obj;
}

Object3D* Object3D:: find (int target_user_id) const
{
  if (user_id == target_user_id)
    return const_cast<Object3D*>(this);
  else 
    return 0;
}

AnimationTrack* Object3D:: getAnimationTrack (int index) const
{
  if (index < 0 || index > (int)anim_tracks.size()) {
    throw IllegalArgumentException (__FILE__, __func__, "Index is invalid, index=%d, max=%d.", index, anim_tracks.size());
  }
  return anim_tracks[index];
}

int Object3D:: getAnimationTrackCount () const
{
  return anim_tracks.size();
}

int Object3D:: getReferences (Object3D** references, int size) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, Reference is not implemented yet.");

  return 0;
}

int Object3D:: getUserID () const
{
    return user_id;
}

void* Object3D:: getUserObject () const
{
  throw NotImplementedException (__FILE__, __func__, "User Object is not implemnted, yet.");
  return 0;
}

void Object3D:: removeAnimationTrack (AnimationTrack* animation_track)
{
  vector<AnimationTrack*>::iterator it;
  vector<AnimationTrack*>::iterator it_end = anim_tracks.end();
  for (it = anim_tracks.begin(); it != it_end; it++) {
    if (*it == animation_track) {
      anim_tracks.erase (it);
      break;
    }
  }
}

void Object3D:: setUserID (int new_user_id)
{
  user_id = new_user_id;
}

void Object3D:: setUserObject (const char* name, void* value)
{
  throw NotImplementedException (__FILE__, __func__, "User Object is not implemented, yte");
}

void Object3D:: setObjectType (int type)
{
  obj_type = type;
}
int Object3D:: getObjectType () const
{
  return obj_type;
}

void Object3D:: findByObjectType (int type, std::vector<Object3D*>& objs) const
{
  if (obj_type == type) {
    objs.push_back (const_cast<Object3D*>(this));
  }
}

void Object3D:: render (int pass, int index) const
{
  // do nothing
}

std::ostream& Object3D:: print (std::ostream& out) const
{
  out << "Object3D: ";
  out << "  user_id=" << user_id;
  out << ", animation_tracks=" << anim_tracks.size();
  return out << "\n";
}

std::ostream& operator<< (std::ostream& out, const Object3D& obj)
{
  return obj.print(out);
}



