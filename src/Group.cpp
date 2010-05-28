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
#include "Sprite3D.hpp"
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

/**
 * 注意1: (x,y)にはウィンドウ座標をピクセル数で指定する。
 *        左上が(0,0)、右下(width,height)
 * 注意2: ピック可能＝Mesh,Sprite3D
 */
bool Group:: pick (int scope, float x, float y, const Camera* camera, RayIntersection* ri_out) const
{
    if (camera == NULL) {
        throw NullPointerException (__FILE__, __func__, "Camera is NULL.");
    }

    //cout << "Group: pick\n";

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
        if (mesh && (mesh->getScope() & scope)) {
            // 交差判定はMeshのモデル座標系で行う
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
        Sprite3D* spr = dynamic_cast<Sprite3D*>(children[i]);
        if (spr && (spr->getScope() & scope)) {
            // 交差判定はNDC座標系で行う
            Vector org = p0_ndc;
            Vector dir = (p1_ndc-p0_ndc).normalize();
            spr->intersect (org, dir, camera, &ri);
            // レイはGroupの座標系で格納する
            ri.transformRay (proj);
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



/**
 * 注意1: レイの原点と方向はこのGroupのモデル座標系で表す。
 *        左上が(0,0)、右下(width,height)
 *        方向ベクトルの長さは１である必要はない。
 * 注意2: ピック可能＝Meshのみ
 */
bool Group:: pick (int scope, float ox, float oy, float oz, float dx, float dy, float dz, RayIntersection* ri_out) const
{
    if (dx == 0 && dy == 0 && dz == 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Direction is 0.");
    }

    Vector org_mdl (ox,oy,oz);
    Vector dir_mdl (dx,dy,dz);

    RayIntersection min_ri;

    for (int i = 0; i < (int)children.size(); i++) {
        RayIntersection ri;
        Transform trans;
        Group* grp = dynamic_cast<Group*>(children[i]);
        if (grp) {
            getTransformTo (grp, &trans);
            Vector org_grp = trans.transform (org_mdl).divided_by_w();
            Vector dir_grp = trans.transform3x3 (dir_mdl).divided_by_w();
            grp-> pick (scope, 
                        org_grp.x, org_grp.y, org_grp.z,
                        dir_grp.x, dir_grp.y, dir_grp.z, &ri);
        }
        Mesh* mesh = dynamic_cast<Mesh*>(children[i]);
        if (mesh && (mesh->getScope() & scope)) {
            // 交差判定はMeshのモデル座標系で行う
            getTransformTo (mesh, &trans);
            Vector org_mesh = trans.transform (org_mdl).divided_by_w();
            Vector dir_mesh = trans.transform (dir_mdl).divided_by_w();
            mesh->intersect (org_mesh, dir_mesh, &ri);
            // レイはこのGroupの座標系で格納する
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



