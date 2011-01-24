#include <iostream>
#include "m3g/m3g-gl.hpp"
#include "m3g/Transformable.hpp"
#include "m3g/Transform.hpp"
#include "m3g/Exception.hpp"
#include "m3g/AnimationTrack.hpp"
#include "m3g/AnimationController.hpp"
#include "m3g/KeyframeSequence.hpp"
using namespace std;
using namespace m3g;

Transformable:: Transformable () :
    scaling(1,1,1), translation(0,0,0), orientation(0,0,0,1)
{
}

Transformable:: ~Transformable ()
{
}

Transformable* Transformable:: duplicate () const
{
    Transformable* trans = new Transformable;
    this->Object3D     :: copy (trans);
    this->Transformable:: copy (trans);
    return trans;
}

void Transformable:: copy (Transformable* trans) const
{
    if (trans == NULL) {
        throw NullPointerException (__FILE__, __func__, "Transformalbe is NULL.");
    }
    trans->scaling     = scaling;
    trans->translation = translation;
    trans->orientation = orientation;
    trans->transform   = transform;
}


void Transformable:: addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted)
{
    int property = animation_track->getTargetProperty();
    if (property == AnimationTrack::ORIENTATION ||
        property == AnimationTrack::SCALE       ||
        property == AnimationTrack::TRANSLATION) {
        accepted = true;
    }
    Object3D:: addAnimationTrack_xxx (animation_track, accepted);
}

int Transformable:: animate_xxx (int world_time)
{
    Object3D:: animate_xxx (world_time);

    bool        is_orientation_modefied = false;
    bool        is_scaling_modefied     = false;
    bool        is_translation_modefied = false;
    Scale       new_scaling       = Scale(0,0,0);
    Translation new_translation   = Translation(0,0,0);
    Quaternion  new_orientation   = Quaternion();
    new_orientation.setZero();

    for (int i = 0; i < getAnimationTrackCount(); i++) {
        AnimationTrack*      track      = getAnimationTrack (i);
        KeyframeSequence*    keyframe   = track->getKeyframeSequence();
        AnimationController* controller = track->getController();
        if (!controller || !controller->isActive(world_time)) {
            continue;
        }
        float weight        = controller->getWeight ();
        float sequence_time = controller->getPosition (world_time);
    
        switch (track->getTargetProperty()) {
        case AnimationTrack:: ORIENTATION: {
            float value[4] = {0,0,0,0};  // Quaternion(x,y,z,w)
            keyframe->getFrame (sequence_time, value);
            Quaternion q;
            q.set (value[0], value[1], value[2], value[3]);
            new_orientation = new_orientation + q * weight;
            is_orientation_modefied = true;
            //cout << "Transformable: orientation --> " << new_orientation << "\n";
            break;
        }
        case AnimationTrack:: SCALE: {
            float value[3] = {0,0,0};
            keyframe->getFrame (sequence_time, value);
            if (keyframe->getComponentCount() == 3) {
                new_scaling = Scale(value[0]*weight, value[1]*weight, value[2]*weight);
            }
            else {
                new_scaling = Scale(value[0]*weight, value[0]*weight, value[0]*weight);	
            }
            is_scaling_modefied = true;
            //cout << "Transformable: scale --> " << new_scaling.x << ", " << new_scaling.y << ", " << new_scaling.z << "\n";
            break;
        }
        case AnimationTrack:: TRANSLATION: {
            float value[3] = {0,0,0};
            keyframe->getFrame (sequence_time, value);
            new_translation = Translation (value[0]*weight, value[1]*weight, value[2]*weight);
            is_translation_modefied = true;
            //cout << "Transformable: translation --> " << new_translation.x << ", " << new_translation.y << ", " << new_translation.z << "\n";
            break;
        }
        default: {
            // Unknown target should be ignored.
            // animate() of Base class (of Derived class) retrieve it.
        }
        }
    }

    if (is_orientation_modefied) {
        orientation = new_orientation.normalize();
    }
    if (is_scaling_modefied) {
        scaling = new_scaling;
    }
    if (is_translation_modefied) {
        translation = new_translation;
    }

    return 0;
}

void Transformable:: getCompositeTransform (Transform* ctransform) const
{
    if (ctransform == NULL) {
        throw NullPointerException (__FILE__, __func__, "Tranform is NULL.");
    }

    ctransform->setIdentity ();
    ctransform->postTranslate (translation.x, translation.y, translation.z);
    ctransform->postRotateQuat (orientation.x, orientation.y, orientation.z, orientation.w);
    ctransform->postScale (scaling.x, scaling.y, scaling.z);
    ctransform->postMultiply (transform);
}

void Transformable:: getOrientation (float* angle_axis) const
{
    if (angle_axis == NULL) {
        throw NullPointerException (__FILE__, __func__, "Angle_axis is NULL.");
    }
  
    orientation.getAngleAxis (angle_axis);
}

void Transformable:: getScale (float* xyz) const
{
    if (xyz == NULL) {
        throw NullPointerException (__FILE__, __func__, "Scaling xyz is NULL.");
    }

    xyz[0] = scaling.x;
    xyz[1] = scaling.y;
    xyz[2] = scaling.z;
}

void Transformable:: getTransform (Transform* tra) const
{
    if (tra == NULL) {
        throw NullPointerException (__FILE__, __func__, "Transform is NULL.");
    }
    tra->set (&transform);
}

void Transformable:: getTranslation (float* xyz) const
{
    if (xyz == NULL) {
        throw NullPointerException (__FILE__, __func__, "Xyz is NULL.");
    }

    xyz[0] = translation.x;
    xyz[1] = translation.y;
    xyz[2] = translation.z;
}

void Transformable:: postRotate (float angle, float ax, float ay, float az)
{
    orientation = orientation * Quaternion (angle, ax,ay,az);
}

void Transformable:: preRotate (float angle, float ax, float ay, float az)
{
    orientation = Quaternion (angle, ax,ay,az) * orientation;
}

void Transformable:: scale (float sx, float sy, float sz)
{
    scaling.x *= sx;
    scaling.y *= sy;
    scaling.z *= sz;
}

void Transformable:: setOrientation (float angle, float ax, float ay, float az)
{
    if (angle != 0 && ax == 0 && ay == 0 && az == 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Rotation axis is 0,0,0.");
    }
    orientation = Quaternion (angle, ax, ay, az);
}

void Transformable:: setScale (float sx, float sy, float sz)
{
    scaling.x = sx;
    scaling.y = sy;
    scaling.z = sz;
}

void Transformable:: setTransform (const Transform* tra)
{
    transform.set (tra);
}

void Transformable:: setTranslation (float tx, float ty, float tz)
{
    translation.x = tx;
    translation.y = ty;
    translation.z = tz;
}

void Transformable:: translate (float tx, float ty, float tz)
{
    translation.x += tx;
    translation.y += ty;
    translation.z += tz;
}

void Transformable:: render (RenderState& state) const
{
    Transform trans;
    getCompositeTransform(&trans);
    trans.transpose();
    float m[16];
    trans.get (m);
    glMultMatrixf ((GLfloat*)&m);

}

std::ostream& Transformable:: print (std::ostream& out) const
{
    float angle_axis[4];
    orientation.getAngleAxis (angle_axis);

    out << "Transformable: ";
    out << "  translation=" << translation.x << "," << translation.y << "," << translation.z;
    out << ", scale="       << scaling.x     << "," << scaling.y     << "," << scaling.z;
    out << ", orientation=" << angle_axis[0] << ",(" << angle_axis[1] << "," << angle_axis[2] << "," << angle_axis[3] << ")";
    out << ", transform="   << transform;
    return out;
}

std::ostream& operator<< (std::ostream& out, const Transformable& t)
{
    return t.print(out);
}

