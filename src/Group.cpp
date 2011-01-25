#include <iostream>
#include <algorithm>
#include "m3g/m3g-gl.hpp"
#include "m3g/Group.hpp"
#include "m3g/RayIntersection.hpp"
#include "m3g/Exception.hpp"
#include "m3g/World.hpp"
#include "m3g/Vector.hpp"
#include "m3g/Camera.hpp"
#include "m3g/Mesh.hpp"
#include "m3g/SkinnedMesh.hpp"
#include "m3g/Sprite3D.hpp"
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
    Group* grp = new Group;
    this->Object3D      :: copy (grp);
    this->Transformable :: copy (grp);
    this->Node          :: copy (grp);
    this->Group         :: copy (grp);
    return grp;
}



int Group:: getReferences_xxx (Object3D** references) const
{
    int n = Node:: getReferences_xxx (references);
    for (int i = 0; i < (int)children.size(); i++) {
        references ? references[n] = children[i], n++ : n++;
    }

    return n;
}


void Group:: copy (Group* grp) const
{
    if (grp == NULL) {
        throw NullPointerException (__FILE__, __func__, "Group is NULL.");
    }
    grp->children.resize (this->children.size());
    for (int i = 0; i < (int)children.size(); i++) {
        grp->children[i] = this->children[i]->duplicate();
        grp->children[i]->setParent (grp);
    }
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

int Group:: animate_xxx (int world_time)
{
    Node:: animate_xxx (world_time);

    for (int i = 0; i < (int)children.size(); i++) {
        children[i]->animate (world_time);
    }
    return 0;
}

Node* Group:: getChild (int index) const
{
    if (index < 0 || index >= (int)children.size()) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Children index is invalid, index=%d.", index);
    }

    return children[index];
}

int Group:: getChildCount () const
{
    return children.size();
}

bool Group:: isDescendant (const Node* node) const
{
    if (node == NULL) {
        throw NullPointerException (__FILE__, __func__, "Node is null.");
    }
    if (node == this) {
        return true;
    }

    for (int i = 0; i < (int)children.size(); i++) {
        if (children[i] == node) {
            return true;
        }
        Group* grp = dynamic_cast<Group*>(children[i]);
        if (grp && grp->isDescendant (node)) {
            return true;
        }
    }

    return false;
}

/**
 * 注意1: (x,y)はウィンドウ座標を左上が(0,0)右下を(1,1)で指定する。視野垂台以外も指定可。
 * 注意2: ピック可能なのはMeshとscaledなSprite3Dのみ。unscaledなSprite3Dはピック対象外。
 */
bool Group:: pick (int scope, float x, float y, const Camera* camera, RayIntersection* ri_out) const
{
    if (camera == NULL) {
        throw NullPointerException (__FILE__, __func__, "Camera is NULL.");
    }
    if (!isGlobalPickingEnabled()) {
        return false;
    }
    if (this->getGlobalParent() != camera->getGlobalParent()) {
        throw IllegalStateException (__FILE__, __func__, "Can't translate from Group coordinate to given Camera coordinate.");
    }

    //cout << "Group: pick\n";

    // NDC
    Vector p0_ndc = Vector(2*x-1, 1-2*y, -1);
    Vector p1_ndc = Vector(2*x-1, 1-2*y,  1);
    //cout << "p0(ndc) = " << p0_ndc << "\n";
    //cout << "p1(ndc) = " << p1_ndc << "\n";

    // Camera
    Transform proj_inv;
    camera->getProjection (&proj_inv);
    proj_inv.invert();
    Vector p0_cam = proj_inv.transform (p0_ndc);
    Vector p1_cam = proj_inv.transform (p1_ndc);
    //cout << "p0(cam) = " << p0_cam << "\n";
    //cout << "p1(cam) = " << p1_cam << "\n";
    p0_cam.divided_by_w ();
    p1_cam.divided_by_w ();
    
    RayIntersection min_ri;

    for (int i = 0; i < (int)children.size(); i++) {
        RayIntersection ri;
        Transform       trans;

        Group* grp = dynamic_cast<Group*>(children[i]);
        if (grp) {
            // 再帰呼び出し
            grp->pick (scope, x, y, camera, &ri);
            // レイはこのGroupの座標系で格納する
            grp->getTransformTo (this, &trans);
            ri.transformRay (trans);
        }
        Mesh* mesh = dynamic_cast<Mesh*>(children[i]);
        if (mesh && (mesh->getScope() & scope)) {
            // 交差判定はMeshのモデル座標系で行う
            camera->getTransformTo (mesh, &trans);
            Vector p0_mesh = trans.transform (p0_cam);
            Vector p1_mesh = trans.transform (p1_cam);
            Vector org = p0_mesh;
            Vector dir = p1_mesh - p0_mesh;
            mesh->intersect (org, dir, &ri);
            // レイはこのGroupの座標系で格納する
            mesh->getTransformTo (this, &trans);
            ri.transformRay (trans);
            ri.normalizeRay ();
        }
        Sprite3D* spr = dynamic_cast<Sprite3D*>(children[i]);
        if (spr && spr->isScaled() && (spr->getScope() & scope)) {
            // 交差判定はNDC座標系で行う
            Vector org = p0_ndc;
            Vector dir = p1_ndc - p0_ndc;
            spr->intersect (org, dir, camera, &ri);
            // レイはこのGroupの座標系で格納する
            ri.transformRay (proj_inv);
            camera->getTransformTo (this, &trans);
            ri.transformRay (trans);
            ri.normalizeRay ();
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
 * 注意1: レイ光線はこのGroupの座標系で指定する。
 *        方向ベクトルの長さが１である必要はない。
 * 注意2: ピック可能なのはMeshとscaledなSprite3Dのみ。unscaledなSprite3Dはピック対象外。
 */
bool Group:: pick (int scope, float ox, float oy, float oz, float dx, float dy, float dz, RayIntersection* ri_out) const
{
    if (dx == 0 && dy == 0 && dz == 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Given ray Direction is 0.");
    }

    Vector p0_grp (ox,oy,oz);
    Vector p1_grp (ox+dx,oy+dy,oz+dz);

    RayIntersection min_ri;

    for (int i = 0; i < (int)children.size(); i++) {
        RayIntersection ri;
        Transform       trans;
        Group* grp2 = dynamic_cast<Group*>(children[i]);
        if (grp2) {
            // 座標系を子ノードのGroupに変換して再帰呼び出し
            this->getTransformTo (grp2, &trans);
            Vector p0_grp2 = trans.transform (p0_grp);
            Vector p1_grp2 = trans.transform (p1_grp);
            Vector org     = p0_grp2;
            Vector dir     = p1_grp2 - p0_grp2;
            grp2-> pick (scope, 
                        org.x, org.y, org.z,
                        dir.x, dir.y, dir.z,
                        &ri);
            // レイはこのGroupの座標系で格納する
            trans.invert();
            ri.transformRay (trans);
        }
        Mesh* mesh = dynamic_cast<Mesh*>(children[i]);
        if (mesh && (mesh->getScope() & scope)) {
            // 交差判定はMeshのモデル座標系で行う
            this->getTransformTo (mesh, &trans);
            Vector p0_mesh = trans.transform (p0_grp);
            Vector p1_mesh = trans.transform (p1_grp);
            Vector org     = p0_mesh;
            Vector dir     = p1_mesh - p0_mesh;
            mesh->intersect (org, dir, &ri);
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
    Node* node = this;
    while ((node = node->getParent()) != NULL) {
        if (dynamic_cast<SkinnedMesh*>(node)) {
            throw IllegalArgumentException (__FILE__, __func__, "Skeleton node is not removed.");
        }
    }

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
void Group:: render_xxx (RenderState& state) const
{
    if (!isGlobalRenderingEnabled()) {
        return;
    }

    //cout << "Group: render\n";
    glPushMatrix ();
    Node::render_xxx (state);

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
    for (int i = 0; i < (int)children.size(); i++) {
        out << "  [" << i << "] : ";
        children[i]->print(out) << "\n";
    }
    return out;
}

std::ostream& operator<< (std::ostream& out, const Group& grp)
{
    return grp.print (out);
}



