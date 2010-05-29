#include "Node.hpp"
#include "Exception.hpp"
#include "AnimationTrack.hpp"
#include "AnimationController.hpp"
#include "KeyframeSequence.hpp"
#include "RenderState.hpp"
#include "Vector.hpp"
#include <iostream>
#include <cmath>
using namespace std;
using namespace m3g;

const int Node:: NONE;
const int Node:: ORIGIN;
const int Node:: X_AXIS;
const int Node:: Y_AXIS;
const int Node:: Z_AXIS;

Node:: Node () : 
    parent(0), rendering_enable(true), picking_enable(true),
    alpha_factor(1), scope(-1),
    z_alignment(NONE, 0), y_alignment(NONE, 0)
{
}

Node:: ~Node ()
{
}

Node* Node:: duplicate () const
{
    // 注意：Nodeクラスを継承する全てのクラスはduplicate()する時に
    // この関数を呼ばなければならない。
    Node* node = new Node (*this);
    node->parent = NULL;
    return node;
}

void Node:: addAnimationTrack (AnimationTrack* animation_track)
{
    if (animation_track == NULL) {
        throw NullPointerException (__FILE__, __func__, "Animation track is NULL.");
    }
    int property = animation_track->getTargetProperty();
    if (property != AnimationTrack::ALPHA       &&
        property != AnimationTrack::PICKABILITY &&
        property != AnimationTrack::VISIBILITY  &&
        property != AnimationTrack::ORIENTATION &&
        property != AnimationTrack::SCALE       &&
        property != AnimationTrack::TRANSLATION &&
        property != AnimationTrack::MORPH_WEIGHTS ) {
        throw IllegalArgumentException (__FILE__, __func__, "Annimation target is invlid for this Node, property=%d.", property);
    }

    Object3D:: addAnimationTrack (animation_track);
}

void Node:: align (Node* reference)
{
    //cout << "Node: align, z_target = " << z_alignment.target << ", y_target = " << y_alignment.target << "\n";
    Matrix Rz, Ry;
    Vector tz(0,0,1), ty(0,1,0);


    if (z_alignment.target == ORIGIN) {

        Node* z_reference = (z_alignment.reference != NULL) ? z_alignment.reference : reference;
        if (z_reference != NULL) {
            Transform t;
            //cout << "z_reference's transform = " << z_reference->Transformable::print (cout) << "\n";
            z_reference->getCompositeTransform (&t);
            float m[16];
            t.get (m);
            tz = Vector(m[2], m[6], m[10]).normalize();
            //cout << "tz = " << tz << "\n";
            Vector axis_z  = cross (Vector(0,0,1), tz);
            //cout << "axis_z = " << axis_z << "\n";
            axis_z = (axis_z.length() > 0) ? axis_z.normalize() : Vector(0,1,0);
            //cout << "dot = " << dot (Vector(0,0,1), tz) << "\n";
            float  angle_z = acosf (dot(Vector(0,0,1),tz)) * 360/(2*M_PI);
            //cout << "angle_z = " << angle_z << "\n";
            //cout << "axis_z  = " << axis_z << "\n";
            Rz.setRotate (angle_z, axis_z.x, axis_z.y, axis_z.z);
        }

        if (y_alignment.target == ORIGIN) {

            //cout << "==================================in======================================\n";         
            Node* y_reference = (y_alignment.reference != NULL) ? y_alignment.reference : reference;
            if (y_reference != NULL) {
                Transform t;
                //cout << "\ny_reference's transform = " << y_reference->Transformable::print (cout) << "\n";
                y_reference->getCompositeTransform (&t);
                float m[16];
                t.get (m);
                //cout << "t = " << t << "\n";
                ty = Vector(m[1], m[5], m[9]).normalize();
                //cout << "ty = " << ty << "\n";
                Vector ty2 = Rz.getInverse() * ty;
                //cout << "ty2 = " << ty2 << "\n";
                ty2[2] = 0;
                //cout << "ty2 = " << ty2 << "\n";
                ty2 = (ty2.length() > 0) ? ty2.normalize() : Vector(0,1,0);
                //cout << "ty2 = " << ty2 << "\n";
                Vector axis_y  = (ty2[0] > 0) ? tz*-1 : tz;
                axis_y = (axis_y.length() > 0) ? axis_y.normalize() : tz;
                float  angle_y = acosf(dot(Vector(0,1,0),ty2)) * 360/(2*M_PI);
                //cout << "angle_y = " << angle_y << "\n";
                //cout << "axis_y  = " << axis_y << "\n";
                Ry.setRotate (angle_y, axis_y.x, axis_y.y, axis_y.z);
            }
            //cout << "==================================out=====================================\n";
        }

    } else if (y_alignment.target == ORIGIN) {

        Node* y_reference = (y_alignment.reference != NULL) ? y_alignment.reference : reference;
        if (y_reference != NULL) {
            Transform t;
            //cout << "y_reference's transform = " << y_reference->Transformable::print (cout) << "\n";
            y_reference->getCompositeTransform (&t);
            float m[16];
            t.get (m);
            ty = Vector(m[1], m[5], m[9]).normalize();
            //cout << "ty = " << ty << "\n";
            Vector axis_y  = cross (Vector(0,1,0), ty);
            //cout << "axis_y = " << axis_y << "\n";
            axis_y = (axis_y.length() > 0) ? axis_y.normalize() : Vector(0,0,1);
            //cout << "axis_y = " << axis_y << "\n";
            //cout << "dot = " << dot (Vector(0,1,0), ty) << "\n";
            float  angle_y = acosf (dot (Vector(0,1,0), ty)) * 360/(2*M_PI);
            //cout << "angle_y = " << angle_y << "\n";
            Ry.setRotate (angle_y, axis_y.x, axis_y.y, axis_y.z);
        }
    }


    if (z_alignment.target == ORIGIN || y_alignment.target == ORIGIN) {
        //cout << "A(matrix) = " << Ry*Rz << "\n";
        Quaternion A = matrix2quat (Ry*Rz);
        //cout << "A(quaternion) = " << A << "\n";
        float angle_axis[4];
        A.getAngleAxis (angle_axis);
        //cout << "angle=" << angle_axis[0] << ", axis=" << angle_axis[1] << ", " <<  angle_axis[2] << ", " <<  angle_axis[3] << "\n";
        setOrientation (angle_axis[0], angle_axis[1], angle_axis[2], angle_axis[3]);
    }

}

int Node:: animate (int world_time)
{
    //cout << "Node: animate, time=" << world_time << "\n";

    Transformable:: animate (world_time);

    bool  is_alpha_modefied            = false;
    bool  is_picking_enable_modefied   = false;
    bool  is_rendering_enable_modefied = false;
    float new_alpha            = 0;
    bool  new_picking_enable   = false;
    bool  new_rendering_enable = false;
  
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
        float weight        = controller->getWeight ();
        float sequence_time = controller->getPosition (world_time);
    
        switch (track->getTargetProperty()) {
        case AnimationTrack:: ALPHA: {
            float value[1] = {1};
            keyframe->getFrame (sequence_time, value);
            new_alpha += value[0] * weight;
            is_alpha_modefied = true;
            //cout << "Node: alpha --> " << alpha << "\n";
            break;
        }
        case AnimationTrack:: PICKABILITY: {
            float value[1] = {1};
            keyframe->getFrame (sequence_time, value);
            new_picking_enable = new_picking_enable || ((value[0] != 0) ? true : false);
            is_picking_enable_modefied = true;
            //cout << "Node: picking_enable --> " << new_picking_enable << "\n";
            break;
        }
        case AnimationTrack:: VISIBILITY: {
            float value[1] = {1};
            keyframe->getFrame (sequence_time, value);
            new_rendering_enable = new_rendering_enable || ((value[0] != 0) ? true : false);
            is_rendering_enable_modefied = true;
            //cout << "Node: rendering_enable --> " << new_rendering_enable << "\n";
            break;
        }
        default: {
            // Unknwon target should be ignored.
            // animate() of Base class (of Derived class) retrieve it.
        }
        }
    }

    if (is_alpha_modefied) {
        alpha_factor = clamp (0, 1, new_alpha);
    }
    if (is_picking_enable_modefied) {
        picking_enable = new_picking_enable;
    }
    if (is_rendering_enable_modefied) {
        rendering_enable = new_rendering_enable;
    }

    //cout << *this << "\n";

    return 0;
}



Node* Node:: getAlignmentReference (int axis) const
{
    switch (axis) {
    case Z_AXIS: return z_alignment.reference;
    case Y_AXIS: return y_alignment.reference;
    default: throw IllegalArgumentException (__FILE__, __func__, "Axis is invalid, axis=%d.", axis);
    }
}

int Node:: getAlignmentTarget (int axis) const
{
    switch (axis) {
    case Z_AXIS: return z_alignment.target;
    case Y_AXIS: return y_alignment.target;
    default: throw IllegalArgumentException (__FILE__, __func__, "Axis is invalid, axis=%d.", axis);
    }
}

float Node:: getAlphaFactor () const
{
    return alpha_factor;
}

float Node:: getGlobalAlphaFactor () const
{
    const Node* node  = this;
    float alpha = 1;
    do {
        alpha *= node->getAlphaFactor () ;
    } while ((node = node->getParent()) != NULL);
    return alpha;
}

Matrix Node:: getGlobalPose () const
{
    const Node* node = this;
    Matrix global_pose;
    do {
        Transform trans;
        node->getCompositeTransform (&trans);
        float m[16];
        trans.get (m);
        global_pose = Matrix(m) * global_pose;
    } while ((node = node->getParent()));

    return global_pose;
}

Node* Node:: getParent () const
{
    return parent;
}

Node* Node:: getGlobalParent () const
{
    Node* node = const_cast<Node*>(this);
    if (node->getParent() == NULL)
        return NULL;

    while (node->getParent() != NULL)
        node = node->getParent();

    return node;
}

bool Node:: isGlobalPickingEnabled () const
{
    const Node* node = this;
    do {
        if (!node->isPickingEnabled())
            return false;
    } while ((node = node->getParent()) != NULL);

    return true;
}

bool Node:: isGlobalRenderingEnabled () const
{
    const Node* node = this;
    do {
        if (!node->isRenderingEnabled())
            return false;
    } while ((node = node->getParent()) != NULL);

    return true;

}



int Node:: getScope () const
{
    return scope;
}

bool Node:: getTransformTo (const Node* target, Transform* transform) const
{
    if (target == NULL) {
        throw NullPointerException (__FILE__, __func__, "Target is NULL.");
    }
    if (transform == NULL) {
        throw NullPointerException (__FILE__, __func__, "Transform is NULL.");
    }

    const Node *root_a, *root_b, *node;
  
    node = this;
    do {
        root_a = node;
    } while ((node = node->parent));

    node = target;
    do {
        root_b = node;
    } while ((node = node->parent));

    if (root_a != root_b) {
        cout << "Node: can't getTransformTo\n";
        return false;
    }

    Matrix global_pose_a = this->getGlobalPose ();
    Matrix global_pose_b = target->getGlobalPose ();

    Matrix transform_matrix = global_pose_b.getInverse() * global_pose_a;
    transform->set (transform_matrix.m);

    return true;
}

bool Node:: isPickingEnabled () const
{
    return picking_enable;
}

bool Node:: isRenderingEnabled () const
{
    return rendering_enable;
}


void Node:: setAlignment (Node* z_reference, int z_target, Node* y_reference, int y_target)
{
    z_alignment.target    = z_target;
    z_alignment.reference = z_reference;
    y_alignment.target    = y_target;
    y_alignment.reference = y_reference;
}


void Node:: setAlphaFactor (float alpha)
{
    if (alpha < 0 || alpha > 1.0) {
        throw IllegalArgumentException (__FILE__, __func__, "Alpha is invalid, alph=%f.", alpha);
    }

    alpha_factor = alpha;
}


void Node:: setPickingEnable (bool enable)
{
    picking_enable = enable;
}

void Node:: setRenderingEnable (bool enable)
{
    rendering_enable = enable;
}

void Node:: setScope (int s)
{
    scope = s;
}

void Node:: setParent (Node* node)
{
    parent = node;
}

/**
 * Note: Node should be rendered via all rendering pass.
 */
void Node:: render (RenderState& state) const
{
    if (!isGlobalRenderingEnabled()) {
        return;
    }

    Transformable::render (state);
  
    state.alpha = getGlobalAlphaFactor();
}

std::ostream& Node:: print (std::ostream& out) const
{
    out << "Node: ";
    out << "  scope=" << scope;
    out << ", rendering_enable=" << rendering_enable;
    out << ", picking_enable=" << picking_enable;
    out << ", alpha_factor=" << alpha_factor;
    return out;
}

std::ostream& operator<< (std::ostream& out, const Node& node)
{
    return node.print(out);
}
