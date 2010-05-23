#include <iostream>
#include <algorithm>
#include "m3g-gl.hpp"
#include "Group.hpp"
#include "RayIntersection.hpp"
#include "Exception.hpp"
#include "World.hpp"
#include "Vector.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
using namespace m3g;
using namespace std;

#include <typeinfo>


Group:: Group ()
{
}

Group:: ~Group ()
{
}

Group* Group:: duplicate () const
{
    Group* grp  = new Group (*this);
    Node*  node = Node::duplicate();
    *(Node*)grp = *node;
    delete node;

    for (int i = 0; i < (int)children.size(); i++) {
        grp->children[i] = this->children[i]->duplicate();
        grp->children[i]->setParent (grp);
    }
    return grp;
}


void Group:: addChild (Node* child)
{
    if (child == NULL) {
        throw NullPointerException (__FILE__, __func__, "Child is NULL.");
    }
    if (child == this) {
        throw IllegalArgumentException (__FILE__, __func__, "Can't add myself.");
    }
    if (dynamic_cast<World*>(child)) {
        throw IllegalArgumentException (__FILE__, __func__, "Child is invalid, World.");
    }
    if (child->getParent() != NULL && child->getParent() != this) {
        throw IllegalArgumentException (__FILE__, __func__, "Added child is already a member of other group.");
    }

    child->setParent (this);
    children.push_back (child);
}

void Group:: align (Node* reference)
{
    //cout << "Group: align, ref=0x" << reference << "\n";

    Node:: align (reference);
    for (int i = 0; i < (int)children.size(); i++) {
        children[i]->align (reference);
    }
}

int Group:: animate (int world_time)
{
    //cout << "Group: animate, time=" << world_time << "\n";

    Node:: animate (world_time);

    for (int i = 0; i < (int)children.size(); i++) {
        children[i]->animate (world_time);
    }
    return 0;
}

Node* Group:: getChild (int index) const
{
    if (index < 0 || index >= (int)children.size()) {
        throw IllegalArgumentException (__FILE__, __func__, "Chldren index is invalid, index=%d.", index);
    }

    return children[index];
}

int Group:: getChildCount () const
{
    return children.size();
}

// min_riはNULLも可.
bool Group:: pick (int scope, float x, float y, const Camera* camera, RayIntersection* ri_out) const
{
    if (camera == NULL) {
        throw NullPointerException (__FILE__, __func__, "Camera is NULL.");
    }

    // NDC
    Vector p0_ndc = Vector(2*x-1, 1-2*y, -1);
    Vector p1_ndc = Vector(2*x-1, 1-2*y,  1);
    //cout << "p0(ndc) = " << p0_ndc << "\n";
    //cout << "p1(ndc) = " << p1_ndc << "\n";

    // Camera
    Transform proj;
    camera->getProjection (&proj);
    proj.invert();
    Vector p0_cam = proj.transform (p0_ndc);
    Vector p1_cam = proj.transform (p1_ndc);
    //cout << "p0(cam) = " << p0_cam << "\n";
    //cout << "p1(cam) = " << p1_cam << "\n";
    p0_cam.divided_by_w ();
    p1_cam.divided_by_w ();
    
    RayIntersection min_ri;

    for (int i = 0; i < (int)children.size(); i++) {
        RayIntersection ri;
        Transform trans;
        Group* grp = dynamic_cast<Group*>(children[i]);
        if (grp) {
            camera->getTransformTo (grp, &trans);
            Vector p0_grp = trans.transform (p0_cam);
            Vector p1_grp = trans.transform (p1_cam);
            Vector org = p0_grp;
            Vector dir = (p1_grp-p0_grp).normalize();
            grp-> pick (scope, 
                        org.x, org.y, org.z,
                        dir.x, dir.y, dir.z, &ri);
        }
        Mesh* mesh = dynamic_cast<Mesh*>(children[i]);
        if (mesh) {
            // 交差判定はMeshの座標系で行う
            camera->getTransformTo (mesh, &trans);
            Vector p0_mesh = trans.transform (p0_cam);
            Vector p1_mesh = trans.transform (p1_cam);
            //cout << "p0(mesh) = " << p0_mesh << "\n";
            //cout << "p1(mesh) = " << p1_mesh << "\n";
            Vector org = p0_mesh;
            Vector dir = (p1_mesh-p0_mesh).normalize();
            mesh->intersect (org, dir, &ri);
            // レイはGroupの座標系で格納する
            mesh->getTransformTo (this, &trans);
            ri.transformRay (trans);
        }
        if (ri.getIntersected()) {
            if (min_ri.getIntersected() == NULL ||
                ri.getDistance() < min_ri.getDistance()) {
                min_ri = ri;
            }
        }
    }

    if (ri_out)
        *ri_out = min_ri;

    return min_ri.getIntersected();
}



bool Group:: pick (int scope, float ox, float oy, float oz, float dx, float dy, float dz, RayIntersection* ri) const
{
    throw NotImplementedException (__FILE__, __func__, "Sorry, pick is not implemented.");
    return false;
}

void Group:: removeChild (Node* child)
{
    std::vector<Node*>::iterator it;
    for (it = children.begin(); it < children.end(); it++) {
        if (*it == child) {
            children.erase (it);
            child->setParent (NULL);
            break;
        }
    }

    // SkinnedMeshの場合特殊な処理が必要。
    // 仕様書を見よ。
}

/**
 * Note: Group should be rendered via all rendering pass.
 */
void Group:: render (RenderState& state) const
{
    //cout << "Group: render\n";
    glPushMatrix ();
    Node::render (state);

    for (int i = 0; i < (int)children.size(); i++) {
        glPushMatrix ();
        children[i]->render (state);
        glPopMatrix ();
    }

    glPopMatrix ();

}
  


std::ostream& Group:: print (std::ostream& out) const
{
    out << "Group: " << children.size() << " nodes";
    //for (int i = 0; i < (int)children.size(); i++) {
    //  out << "  [" << i << "] : ";
    //  children[i]->print(out);
    //}
    return out;
}

std::ostream& operator<< (std::ostream& out, const Group& grp)
{
    return grp.print (out);
}



