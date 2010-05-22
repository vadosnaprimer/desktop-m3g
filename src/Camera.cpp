#include <iostream>
#include <cmath>
#include "Camera.hpp"
#include "Vector.hpp"
#include "Transform.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include "Exception.hpp"
#include "RenderState.hpp"
using namespace std;
using namespace m3g;

const int Camera:: GENERIC;
const int Camera:: PARALLEL;
const int Camera:: PERSPECTIVE;

Camera:: Camera () :
    type(GENERIC), fovy(0), aspect_ratio(0), near(0), far(0)
{
}

Camera:: ~Camera ()
{
}

Camera* Camera:: duplicate () const
{
    Node*   node = Node::duplicate();
    Camera* cam  = new Camera(*this);
    *(Node*)cam  = *node;
    delete node;
    return cam;
}

void Camera:: addAnimationTrack (AnimationTrack* animation_track)
{
    if (animation_track == NULL) {
        throw NullPointerException (__FILE__, __func__, "Animation track is NULL.");
    }
    int property = animation_track->getTargetProperty();
    if (property != AnimationTrack::FAR_DISTANCE  &&
        property != AnimationTrack::FIELD_OF_VIEW &&
        property != AnimationTrack::NEAR_DISTANCE &&
        property != AnimationTrack::ALPHA         &&
        property != AnimationTrack::PICKABILITY   &&
        property != AnimationTrack::VISIBILITY    &&
        property != AnimationTrack::ORIENTATION   &&
        property != AnimationTrack::SCALE         &&
        property != AnimationTrack::TRANSLATION) {
        throw IllegalArgumentException (__FILE__, __func__, "Animation track target is invalid for this Camera, property=%d.", property);
    }
 
    Object3D:: addAnimationTrack (animation_track);
}

int Camera:: animate (int world_time)
{
    //cout << "Camera: animate, time=" << world_time << "\n";

    Object3D:: animate (world_time);

    bool  is_far_modefied  = false;
    bool  is_fovy_modefied = false;
    bool  is_near_modefied = false;
    float new_far   = 0;
    float new_fovy  = 0;
    float new_near  = 0;
  
    for (int i = 0; i < getAnimationTrackCount(); i++) {
        AnimationTrack*      track      = getAnimationTrack (i);
        KeyframeSequence*    keyframe   = track->getKeyframeSequence();
        AnimationController* controller = track->getController();
        if (controller == NULL) {
            //cout << "Node: missing controller, this animation track is ignored.\n";
            continue;
        }
        if (!controller->isActiveInterval(world_time)) {
            continue;
        }
        float weight     = controller->getWeight ();
        float sequence_time = controller->getPosition (world_time);
    
        switch (track->getTargetProperty()) {
        case AnimationTrack:: FAR_DISTANCE: {
            float value[1] = {1};
            keyframe->getFrame (sequence_time, value);
            new_far += value[0] * weight;
            is_far_modefied = true;
            //cout << "Camera: far --> " << new_far << "\n";
            break;
        }
        case AnimationTrack::FIELD_OF_VIEW: {
            float value[1] = {1};
            keyframe->getFrame (sequence_time, value);
            new_fovy += value[0] * weight;
            is_fovy_modefied = true;
            //cout << "Fog: fovy --> " << new_fovy << "\n";
            break;
        }
        case AnimationTrack:: NEAR_DISTANCE: {
            float value[1] = {1};
            keyframe->getFrame (sequence_time, value);
            new_near += value[0] * weight;
            is_near_modefied = true;
            //cout << "Camera: near --> " << new_near << "\n";
            break;
        }
        default: {
            // Unknwon target should be ignored.
            // animate() of Base class (of Derived class) retrieve it.
        }
        }
    }

    if (is_near_modefied) {
        if (type == PERSPECTIVE) {
            near = max (M3G_EPSILON, new_near);
        } else {
            near = new_near;
        }
    }
    if (is_far_modefied) {
        if (type == PERSPECTIVE) {
            far = max (M3G_EPSILON, new_far);
        } else {
            far = new_far;
        }
    }
    if (is_fovy_modefied) {
        if (type == PERSPECTIVE) {
            fovy = clamp (M3G_EPSILON, 180-M3G_EPSILON, new_fovy);
        } else {
            fovy = max (M3G_EPSILON, new_fovy);
        }
    }

    // don't permit this condition.
    if (near == far) {
        throw IllegalArgumentException (__FILE__, __func__, "Near equals far, n,f=%f.", near);
    }

  
    return 0;
}


int Camera:: getProjection (float* params) const
{
    if (params) {
        params[0] = fovy;
        params[1] = aspect_ratio;
        params[2] = near;
        params[3] = far;
    }
    return type;
}

int Camera:: getProjection (Transform* transform) const
{
    if (transform) {
        transform->set (proj_trans);
    }
    return type;
}

void Camera:: setGeneric (const Transform& transform)
{
    type = GENERIC;
    proj_trans.set (transform);

    // ここで逆行列が計算できる事をチェックするべき？
}

void Camera:: setParallel (float height_, float aspect_ratio_, float near_, float far_)
{
    if (height_ <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Height is invalid, h=%f,", height_);
    }
    if (aspect_ratio_ <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Aspect ratio is invalid, ratio=%f,", aspect_ratio_);
    }
    if (near_ == far_) {
        throw IllegalArgumentException (__FILE__, __func__, "Near and far are invalid, near=%f, far=%f.", near_, far_);
    }

    type         = PARALLEL;
    fovy         = height_;
    aspect_ratio = aspect_ratio_;
    near         = near_;
    far          = far_;

    Matrix proj = make_parallel_projection_matrix (fovy, aspect_ratio, near, far);
    proj_trans.set (proj);
}

void Camera:: setPerspective (float fovy_, float aspect_ratio_, float near_, float far_)
{
    if (fovy_ <= 0 || fovy_ >= 180) {
        throw IllegalArgumentException (__FILE__, __func__, "Fov is invalid, fov=%f.", fovy_);
    }
    if (aspect_ratio_ <= 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Aspect ratio is invalid, ratio=%f.", aspect_ratio);
    }
    if (near_ <= 0 || far_ <= 0 || near_ == far_) {
        throw IllegalArgumentException (__FILE__, __func__, "Near and far are invalid, near=%f, far=%f.", near_, far_);
    }

    type         = PERSPECTIVE;
    fovy         = fovy_;
    aspect_ratio = aspect_ratio_;
    near         = near_;
    far          = far_;

    Matrix proj = make_perspective_projection_matrix (fovy, aspect_ratio, near, far);
    proj_trans.set (proj);
}

/**
 * Note: Camera should be rendered only at 0th rendering pass(pass=0).
 * In other cases, do nothing.
 */
void Camera:: render (RenderState& state) const
{
    if (state.pass != 0) {
        return;
    }

    //cout << "Camera: render, " << *this << "\n";
    Matrix mat;

    glMatrixMode(GL_PROJECTION);
    proj_trans.get (&mat);
    mat.transpose();
    glMultMatrixf (mat.m);

    glMatrixMode (GL_MODELVIEW);
    mat = getGlobalPose ();
    mat.invert ();
    mat.transpose ();
    glMultMatrixf (mat.m);

    //    gluLookAt (0, 0, 5, // from
    //	0, 0, 0, // to
    //	0, 1, 0);  // up

}

void Camera:: lookAt  (float from_x, float from_y, float from_z,
                       float to_x, float to_y, float to_z, 
                       float up_x, float up_y, float up_z)
{
    Vector from (from_x, from_y, from_z);
    Vector view (to_x-from_x, to_y-from_y, to_z-from_z);
    Vector up   (up_x, up_y, up_z);

    view.normalize();
    up.normalize();
    Vector right = cross(view, up);
    up = cross(right, view);

    float m[16] = { right.x, up.x, -view.x, from.x,
                    right.y, up.y, -view.y, from.y,
                    right.z, up.z, -view.z, from.z,
                    0,    0,       0,      1 };
    Transform trans;
    trans.set (m);   

    setTransform (trans);
}


std::ostream& Camera:: print (std::ostream& out) const
{
    out << "Camera: ";
    switch (type) {
    case PARALLEL:
        out << "  type=\"PARALLEL\"";
        out << ", height="       << fovy;
        out << ", aspect_ratio=" << aspect_ratio;
        out << ", near="         << near;
        out << ", far="          << far;
    case PERSPECTIVE:
        out << "  type=\"PERSPECTIVE\"";
        out << ", fovy="         << fovy;
        out << ", aspect_ratio=" << aspect_ratio;
        out << ", near="         << near;
        out << ", far="          << far;
        break;
    default:
        Transform trns;
        getTransform (&trns);
        out << "  type=\"GENERIC\"";
        out << ", matrix=" << trns;
    }
    return out;
}


std::ostream& operator<< (std::ostream& out, const Camera& cam)
{
    return cam.print(out);
}
