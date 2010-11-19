#include "m3g/Mesh.hpp"
#include "m3g/VertexBuffer.hpp"
#include "m3g/VertexArray.hpp"
#include "m3g/IndexBuffer.hpp"
#include "m3g/Appearance.hpp"
#include "m3g/Exception.hpp"
#include "m3g/RayIntersection.hpp"
#include "m3g/RenderState.hpp"
#include "m3g/Intersect.hpp"
#include "m3g/Vector.hpp"
#include <iostream>
#include <cassert>
#include <limits>
#include <cstring>
using namespace std;
using namespace m3g;

Mesh:: Mesh (VertexBuffer* vertices_, int num_submesh,
             IndexBuffer** submeshes, Appearance** appearances_) : vertices(0)
{
    if (vertices_ == NULL) {
        throw NullPointerException (__FILE__, __func__, "VertexBuffer is NULL.");
    }
    if (num_submesh == 0) {
        throw IllegalArgumentException (__FILE__, __func__, "Number of submesh is invalid, num_submesh=%d.", num_submesh);
    }
    if (submeshes == NULL) {
        throw NullPointerException (__FILE__, __func__, "IndexBuffer is NULL.");
    }
    if (appearances_ == NULL) {
        throw NullPointerException (__FILE__, __func__, "Appearances is NULL.");
    }

    initialize (vertices_, num_submesh, submeshes, appearances_);
}

Mesh:: Mesh (VertexBuffer* vertices_, IndexBuffer* submesh, Appearance* appearance_)
{
    if (vertices_ == NULL) {
        throw NullPointerException (__FILE__, __func__, "VertexBuffer is NULL.");
    }
    if (submesh == NULL) {
        throw NullPointerException (__FILE__, __func__, "IndexBuffer is NULL.");
    }
    if (appearance_ == NULL) {
        throw NullPointerException (__FILE__, __func__, "Appearance is NULL.");
    }

    initialize (vertices_, 1, &submesh, &appearance_);
}

//Mesh:: Mesh () : vertices(0)
//{
//}

void Mesh:: initialize (VertexBuffer* vertices_, int num_submesh, IndexBuffer** submeshes, Appearance** appearances_)
{
    vertices = vertices_;

    // 1行でかける
    indices.reserve (num_submesh);
    for (int i = 0; i < num_submesh; i++ ) {
        indices.push_back (*submeshes++);
    }

    // 1行でかける
    appearances.reserve (num_submesh);
    for (int i = 0; i < num_submesh; i++ ) {
        appearances.push_back (*appearances_++);
    }

}

Mesh:: ~Mesh ()
{
}

Mesh* Mesh:: duplicate () const
{
    Mesh* mesh = new Mesh (vertices, indices.size(), (IndexBuffer**)&indices[0], (Appearance**)&appearances[0]);
    this->Object3D     :: copy (mesh);
    this->Node         :: copy (mesh);
    this->Transformable:: copy (mesh);
    this->Mesh         :: copy (mesh);
    return mesh;
}

int Mesh:: getReferences (Object3D** references) const
{
    int n = 0;
    if (vertices)
        n++;
    for (int i = 0; i < (int)indices.size(); i++) {
        if (indices[i])
            n++;
    }
    for (int i = 0; i < (int)appearances.size(); i++) {
        if (appearances[i])
            n++;
    }

    if (references) {
        int i = 0;
        if (vertices)
            references[i++] = vertices;
        for (int j = 0; j < (int)indices.size(); j++) {
            if (indices[j])
                references[i++] = indices[j];
        }
        for (int j = 0; j < (int)appearances.size(); j++) {
            if (appearances[j])
                references[i++] = appearances[j];
        }
    }

    return n;  
}

void Mesh:: mark (void(*func)(void*)) const
{
    if (func == NULL)
        return;

    Object::mark (func);
    if (vertices) {
        vertices->mark (func);
    }
    for (int i = 0; i < (int)indices.size(); i++) {
        if (indices[i]) {
            indices[i]->mark (func);
        }
        if (appearances[i]) {
            appearances[i]->mark (func);
        }
    }
}


void Mesh:: copy (Mesh* mesh) const
{
    if (mesh == NULL) {
        throw NullPointerException (__FILE__, __func__, "Mesh is NULL.");
    }
    // vertices, indices, appearancesはコンストラクタで設定済み
}

int Mesh:: animate (int world_time)
{
    //cout << "Mesh: animate time=" << world_time << "\n";

    Node::animate (world_time);

    if (vertices) {
        vertices->animate (world_time);
    }

    for (int i = 0; i < (int)appearances.size(); i++) {
        appearances[i]->animate (world_time);
    }

    return 0;
}


Appearance* Mesh:: getAppearance (int index) const
{
    if (index < 0 || index >= (int)appearances.size()) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d, max=%d.", index, appearances.size());
    }
    return appearances[index];
}

IndexBuffer* Mesh:: getIndexBuffer (int index) const
{
    if (index < 0 || index >= (int)indices.size()) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d, max=%d.", index, indices.size());
    }
    return indices[index];
}

int Mesh:: getSubmeshCount () const
{
    return indices.size();
}

VertexBuffer* Mesh:: getVertexBuffer () const
{
    return vertices;
}

void Mesh:: setAppearance (int index, Appearance* appearance)
{
    if (index < 0 || index >= (int)appearances.size()) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d, max=%d.", index, appearances.size());
    }
  
    if (appearance) {
        appearances[index] = appearance;
    }
    else {
        std::vector<Appearance*>::iterator it = appearances.begin();
        it += index;
        appearances.erase (it);
    }

}

bool Mesh:: intersect (const Vector& org, const Vector& dir, RayIntersection* ri_out) const
{
    if (org.w != 1 || dir.w != 1) {
        throw IllegalArgumentException (__FILE__, __func__, "W must be 1. org.w=%f, dir.w=%f.", org.w, dir.w);
    }
    if (ri_out == NULL) {
        throw NullPointerException (__FILE__, __func__, "RayIntersection is NULL.");
    }
    if (!isGlobalPickingEnabled()) {
        return false;
    }

    float  scale_bias[4];
    float& scale = scale_bias[0];
    float* bias  = &scale_bias[1];

    VertexArray* positions = vertices->getPositions(scale_bias);
    bool         ri_hit   = false;
    float        ri_u, ri_v, ri_t = numeric_limits<float>::max();
    int          ri_index_values[3];
    int          ri_submesh_index;

    //cout << "indices.size() = " << indices.size() << "\n";

    for (int i = 0; i < (int)indices.size(); i++) {
        int   face_vertex_count = indices[i]->getFaceVertexCount();
        assert (face_vertex_count == 3);

        int   face_count        = indices[i]->getFaceCount();
        float position_values[3][3];
        int   index_values[3];

        for (int f = 0; f < face_count; f++) {
            indices[i]->getFaceVertexIndex (f, index_values);
            positions->get (index_values[0], 1, scale, bias, &position_values[0][0]);
            positions->get (index_values[1], 1, scale, bias, &position_values[1][0]);
            positions->get (index_values[2], 1, scale, bias, &position_values[2][0]);
            Vector v0 = Vector(position_values[0]);
            Vector v1 = Vector(position_values[1]);
            Vector v2 = Vector(position_values[2]);
            float u, v, t;
            bool hit = triangle_intersect (org, dir, v0, v1, v2, &u, &v, &t);
            //cout << "triangle-intersect : " << hit << "\n";
            if (hit && t < ri_t) {
                ri_hit = true;
                ri_u = u;
                ri_v = v;
                ri_t = t;
                ri_submesh_index = i;
                memcpy (ri_index_values, index_values, sizeof(int)*3);
            }
        }

    }

    if (ri_hit) {
        //cout << "ri_hit = " << ri_hit << "\n";
        if (ri_out) {
            *ri_out = RayIntersection (const_cast<Mesh*>(this),
                                       org, dir, ri_t,
                                       ri_u, ri_v,
                                       3, ri_index_values,
                                       ri_submesh_index);
        }
        return true;
    }
        
    return false;
}



/**
 * Note: Mesh should be rendered only at second rendering pass(pass=2).
 *       In other cases, do nothing.
 */
void Mesh:: render (RenderState& state) const
{
    if (!isGlobalRenderingEnabled()) {
        return;
    }

    if (state.pass == -1) {
        for (int i = 0; i < (int)appearances.size(); i++) {
            state.valid_layers.push_back (appearances[i]->getLayer2());
        }
    }
    if (state.pass != 2) {
        return;
    }

    //cout << "Mesh: render " << indices.size() << "メッシュ\n";

    // 注意：下の３つは厳密にこの順番でなければならない。変更不可

    // ノードαの設定
    Node::render (state);

    // 頂点データの指定
    vertices->render (state);


    // マテリアルとインデックスの指定
    for (int i = 0; i < (int)appearances.size(); i++) {
        if (appearances[i] && appearances[i]->getLayer2() == state.layer) {
            appearances[i]->render (state);
            indices[i]->render (state);
        }
    }

}

std::ostream& Mesh:: print (std::ostream& out) const
{
    out << "Mesh: ";
    out << "  " << indices.size() << " submesh";
    VertexArray* vary = vertices->getPositions(0);
    if (vary)
        out << ",  " << vary->getVertexCount() << " vertices";
    else
        out << ",  0 vertices";
    out << ", node_alpha=" << getAlphaFactor();
    //for (int i = 0; i < (int)appearances.size(); i++) {
    //  out << *appearances[i];
    //}

    return out;
}


std::ostream& operator<< (std::ostream& out, const Mesh& mesh)
{
    return mesh.print (out);
}

