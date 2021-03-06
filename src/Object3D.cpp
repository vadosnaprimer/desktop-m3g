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
    addAnimationTrack_xxx (animation_track, false);
}

void Object3D:: addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted)
{
    if (!accepted) {
        throw IllegalArgumentException (__FILE__, __func__, "AnimationTrack property is invalid, pro=%d\n", animation_track->getTargetProperty());
    }

    anim_tracks.push_back (animation_track);
}

int Object3D:: animate (int world_time)
{
    return animate_xxx (world_time);
}

int Object3D:: animate_xxx (int world_time)
{
    return 0;
}



Object3D* Object3D:: duplicate () const
{
    return duplicate_xxx (NULL);
}

Object3D* Object3D:: duplicate_xxx (Object3D* obj) const
{
    if (obj == NULL) {
        obj = new Object3D;
    }

    obj->user_id     = user_id;
    obj->user_object = user_object;
    obj->anim_tracks = anim_tracks;

    return obj;
}


Object3D* Object3D:: find (int id) const
{
    if (id == user_id) {
        return const_cast<Object3D*>(this);
    }

    int n = getReferences (NULL);
    Object3D** objs = new Object3D* [n];
    getReferences (objs);
    for (int i = 0; i < n; i++) {
        if (Object3D* obj = objs[i]->find (id)) {
            delete [] objs;
            return obj;
        }
    }
    delete [] objs;

    return NULL;
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
    return getReferences_xxx (references);
}

int Object3D:: getReferences_xxx (Object3D** references) const
{
    int n = anim_tracks.size();
    if (references) {
        for (int i = 0; i < (int)anim_tracks.size(); i++)
            references[i] = anim_tracks[i];
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
    render_xxx (state);
}

void Object3D:: render_xxx (RenderState& state) const
{
    // nothing to do
    // メモ：この関数をオーバーライドしたら、呼ぶ必要がなければ
    // 基底クラスのrender_xxx()を呼ばなくてもいい。
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



