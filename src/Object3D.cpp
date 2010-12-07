#include "m3g/Object3D.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/Exception.hpp"
#include <iostream>
using namespace std;
using namespace m3g;

Object3D:: Object3D () : user_id(0), user_object(0)
{
}

Object3D:: ~Object3D ()
{
}

void Object3D:: addAnimationTrack (AnimationTrack* animation_track)
{
    if (animation_track == NULL) {
        throw NullPointerException (__FILE__, __func__, "Animation track is Null.");
    }

    anim_tracks.push_back (animation_track);
}

int Object3D:: animate (int world_time)
{
    return 0;
}

void Object3D:: mark (void(*func)(void*)) const
{
    if (func == NULL) {
        return;
    }

    Object:: mark (func);
    for (int i = 0; i < (int)anim_tracks.size(); i++) {
        anim_tracks[i]->mark (func);
    }
}

Object3D* Object3D:: duplicate () const
{
    Object3D* obj = new Object3D;
    this->Object3D:: copy (obj);
    return obj;
}

void Object3D:: copy (Object3D* obj) const
{
    obj->user_id     = user_id;
    obj->user_object = user_object;
    obj->anim_tracks = anim_tracks;
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
    if (index < 0 || index >= (int)anim_tracks.size()) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d, max=%d.", index, anim_tracks.size());
    }

    return anim_tracks[index];
}

int Object3D:: getAnimationTrackCount () const
{
    return anim_tracks.size();
}

int Object3D:: getReferences (Object3D** references) const
{
    int n = anim_tracks.size();

    if (references) {
        for (int i = 0; i < (int)anim_tracks.size(); i++) {
            references[i] = anim_tracks[i];
        }
    }

    return n;
}

int Object3D:: getUserID () const
{
    return user_id;
}

void* Object3D:: getUserObject () const
{
    return user_object;
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

void Object3D:: setUserObject (void* new_user_object)
{
    user_object = new_user_object;
}



void Object3D:: render (RenderState& state) const
{
    // nothing to do
}

std::ostream& Object3D:: print (std::ostream& out) const
{
    out << "Object3D: ";
    out << "  user_id=" << user_id;
    out << "  user_object=0x" << user_object;
    out << ", animation_tracks=" << anim_tracks.size();
    return out;
}

std::ostream& operator<< (std::ostream& out, const Object3D& obj)
{
    return obj.print(out);
}



