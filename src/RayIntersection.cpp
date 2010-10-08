#include "RayIntersection.hpp"
#include "Exception.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Mesh.hpp"
#include "Sprite3D.hpp"
#include "Node.hpp"
#include <iostream>
#include <typeinfo>
#include "Node.hpp"
using namespace std;
using namespace m3g;

RayIntersection:: RayIntersection () :
    ray(Vector(0,0,0),Vector(0,0,1),0), node(0), u(0), v(0), submesh_index(0),
    normal(0)
{
    tex_coord.reserve (MAX_TEXTURE_UNITS);
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        tex_coord[i] = 0;
    }
}

RayIntersection:: RayIntersection (Node* node_,
                                   const Vector& org, const Vector& dir, float t,
                                   float u_, float v_,
                                   int vertex_num, int* vertex_indices,
                                   int submesh_index_) :
    ray(Vector(0,0,0),Vector(0,0,1),0), node(0), u(0), v(0), submesh_index(0),
    normal(0)
{
    ray.org = org;
    ray.dir = dir;
    ray.t   = t;
    node    = node_;
    u       = u_;
    v       = v_;
    submesh_index = submesh_index_;

    vertices.reserve (vertex_num);
    for (int i = 0; i < vertex_num; i++) {
        vertices.push_back (vertex_indices[i]);
    }

    tex_coord.reserve (MAX_TEXTURE_UNITS);
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
        tex_coord[i] = 0;
    }
}

RayIntersection:: ~RayIntersection ()
{
    if (normal)
        delete normal;
}


float RayIntersection:: getDistance () const
{
    return ray.t;
}

Node* RayIntersection:: getIntersected () const
{
    return node;
}

void RayIntersection:: setNormal ()
{
    normal = new Vector(0,0,0);

    Sprite3D* spr = dynamic_cast<Sprite3D*>(node);
    if (spr) {
        *normal = Vector(0,0,1);
        return;
    }

    Mesh* mesh = dynamic_cast<Mesh*>(node);
    if (mesh) {
        float  scale_bias[4];
        VertexArray* normals = mesh->getVertexBuffer()->getNormals(scale_bias);
        if (normals) {
            float scale    = scale_bias[0];
            float bias[3]  = {scale_bias[1], scale_bias[2], scale_bias[3]};
            //cout << "RI: scale = " << scale << ", bias[] = " << bias[0] << ", " << bias[1] << ", " << bias[2] << "\n";
            //cout << "vertex_indices = " << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << "\n";
            float normal_values[3][3];
            normals->get (0, 1, scale, bias, normal_values[0]);
            normals->get (vertices[0], 1, scale, bias, normal_values[0]);
            normals->get (vertices[1], 1, scale, bias, normal_values[1]);
            normals->get (vertices[2], 1, scale, bias, normal_values[2]);
            Vector n0 = Vector(normal_values[0]);
            Vector n1 = Vector(normal_values[1]);
            Vector n2 = Vector(normal_values[2]);
            //cout << "n0 = " << n0 << "\n";
            //cout << "n1 = " << n1 << "\n";
            //cout << "n2 = " << n2 << "\n";
            //cout << "(u,v) = " << u << ", " << v << "\n";
            *normal = lerp (u, v, n0, n1, n2);
            //cout << "normal = " << *normal << "\n";
            if (normal->length() > 0)
                normal->normalize();

        }
        return; 
    }
    

}

float RayIntersection:: getNormalX () const
{
    if (!normal) {
        const_cast<RayIntersection*>(this)->setNormal();
    }
    return normal->x;
}

float RayIntersection:: getNormalY () const
{
    if (!normal) {
        const_cast<RayIntersection*>(this)->setNormal();
    }
    return normal->y;
}

float RayIntersection:: getNormalZ () const
{
    if (!normal) {
        const_cast<RayIntersection*>(this)->setNormal();
    }
    return normal->z;
}

void RayIntersection:: getRay (float* ray_) const
{
    if (ray_ == NULL) {
        throw NullPointerException (__FILE__, __func__, "Ray is NULL.");
    }
    ray_[0] = ray.org.x;
    ray_[1] = ray.org.y;
    ray_[2] = ray.org.z;
    ray_[3] = ray.dir.x;
    ray_[4] = ray.dir.y;
    ray_[5] = ray.dir.z;
}

int RayIntersection:: getSubmeshIndex () const
{
    return submesh_index;
}

void RayIntersection:: setTexCoord (int index)
{
    tex_coord[index] = new Vector(0,0,0);

    Sprite3D* spr = dynamic_cast<Sprite3D*>(node);
    if (spr) {
        // 後で実装する
        return;
    }

    Mesh* mesh = dynamic_cast<Mesh*>(node);
    if (mesh) {
        float scale_bias[4];
        VertexArray* tex_coords = mesh->getVertexBuffer()->getTexCoords (index, scale_bias);
        if (tex_coords) {
            float scale   = scale_bias[0];
            float bias[3] = {scale_bias[0], scale_bias[1], scale_bias[2]};
            float tex_coord_values[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
            tex_coords->get (vertices[0], 1, scale, bias, tex_coord_values[0]);
            tex_coords->get (vertices[1], 1, scale, bias, tex_coord_values[1]);
            tex_coords->get (vertices[2], 1, scale, bias, tex_coord_values[2]);
            Vector tex_coord0 = Vector(tex_coord_values[0]);
            Vector tex_coord1 = Vector(tex_coord_values[1]);
            Vector tex_coord2 = Vector(tex_coord_values[2]);
            *tex_coord[index] = lerp (u, v, tex_coord0, tex_coord1, tex_coord2);
        }
        return;
    }
    
}

float RayIntersection:: getTextureS (int index) const
{
    if (!tex_coord[index]) {
        const_cast<RayIntersection*>(this)->setTexCoord(index);
    }
    return tex_coord[index]->x;
}

float RayIntersection:: getTextureT (int index) const
{
    if (!tex_coord[index]) {
        const_cast<RayIntersection*>(this)->setTexCoord(index);
    }
    return tex_coord[index]->y;
}

void RayIntersection:: transformRay (const Transform& trans)
{
    ray.org = trans.transform (ray.org);
    ray.dir.w = 0;
    ray.dir = trans.transform (ray.dir);
    ray.dir.w = 1;
}

std::ostream& RayIntersection:: print (std::ostream& out) const
{
    out << "RayIntersection: " << (node ? "hit" : "not hit");
    out << ", ray.org=" << ray.org;
    out << ", ray.dir=" << ray.dir;
    out << ", ray.t=" << ray.t;
    out << ", node=" << (node ? typeid(*node).name() : "none");
    out << ", u=" << u << ",v=" << v;
    out << ", vertices=[";
    for (int i = 0; i < (int)vertices.size(); i++) {
        out << vertices[i] << ",";
    }
    out << "]";
    out << ", submesh_index=" << submesh_index;
    return out;
}

std::ostream& operator<< (std::ostream& out, const RayIntersection& ri)
{
    return ri.print (out);
}


