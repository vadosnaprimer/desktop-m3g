#include "m3g/RayIntersection.hpp"
#include "m3g/Exception.hpp"
#include "m3g/VertexBuffer.hpp"
#include "m3g/VertexArray.hpp"
#include "m3g/Mesh.hpp"
#include "m3g/Sprite3D.hpp"
#include "m3g/Node.hpp"
#include <iostream>
#include <typeinfo>
#include <cmath>
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
    //cout << "u = " << u << "\n";
    //cout << "v = " << v << "\n";
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

void RayIntersection:: computeNormal ()
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
            float normal_values[3][3];
            normals->get (0, 1, scale, bias, normal_values[0]);
            normals->get (vertices[0], 1, scale, bias, normal_values[0]);
            normals->get (vertices[1], 1, scale, bias, normal_values[1]);
            normals->get (vertices[2], 1, scale, bias, normal_values[2]);
            Vector n0 = Vector(normal_values[0]);
            Vector n1 = Vector(normal_values[1]);
            Vector n2 = Vector(normal_values[2]);
            *normal = lerp (u, v, n0, n1, n2);
            if (normal->length() > 0)
                normal->normalize();

        }
        return; 
    }
    

}

float RayIntersection:: getNormalX () const
{
    if (!normal) {
        const_cast<RayIntersection*>(this)->computeNormal();
    }
    return normal->x;
}

float RayIntersection:: getNormalY () const
{
    if (!normal) {
        const_cast<RayIntersection*>(this)->computeNormal();
    }
    return normal->y;
}

float RayIntersection:: getNormalZ () const
{
    if (!normal) {
        const_cast<RayIntersection*>(this)->computeNormal();
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

void RayIntersection:: computeTexCoord (int index)
{
    tex_coord[index] = new Vector(0,0,0);

    Sprite3D* spr = dynamic_cast<Sprite3D*>(node);
    if (spr) {
        if (vertices[0] == 2 && vertices[1] == 1 && vertices[2] == 0) {
            tex_coord[index]->x = u+v;
            tex_coord[index]->y = 1-u*sinf(45);
        } else if (vertices[0] == 2 && vertices[1] == 3 && vertices[2] == 1) {
            tex_coord[index]->x = v;
            tex_coord[index]->y = 1-(u+v*sinf(45));
        } else {
            throw InternalException (__FILE__, __func__, "Unknown winding.");
        }
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
    if (index < 0 || index >= MAX_TEXTURE_UNITS) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d.", index);
    }

    if (!tex_coord[index]) {
        const_cast<RayIntersection*>(this)->computeTexCoord(index);
    }
    return tex_coord[index]->x;
}

float RayIntersection:: getTextureT (int index) const
{
    if (index < 0 || index >= MAX_TEXTURE_UNITS) {
        throw IndexOutOfBoundsException (__FILE__, __func__, "Index is invalid, index=%d.", index);
    }

    if (!tex_coord[index]) {
        const_cast<RayIntersection*>(this)->computeTexCoord(index);
    }
    return tex_coord[index]->y;
}

void RayIntersection:: transformRay (const Transform& trans)
{
    if (ray.dir.length() == 0) {
        throw InternalException (__FILE__, __func__, "Ray dir is 0. this never happen.");
    }

    Vector org  = ray.org;
    Vector dst0 = ray.org + ray.dir;
    Vector dst1 = ray.org + ray.dir * ray.t;
    org     = trans.transform (org) .divided_by_w ();
    dst0    = trans.transform (dst0).divided_by_w ();
    dst1    = trans.transform (dst1).divided_by_w ();

    ray.org = org;
    ray.dir = dst0-org;
    ray.t  = (dst1-org).length() / (dst0-org).length();
}

void RayIntersection:: normalizeRay ()
{
    ray.t *= ray.dir.length();
    ray.dir.normalize();
}



std::ostream& RayIntersection:: print (std::ostream& out) const
{
    out << "RayIntersection:";
    out << "  hit="      << (node ? "yes" : "no");
    out << ", ray.org=(" << ray.org << ")";
    out << ", ray.dir=(" << ray.dir << ")";
    out << ", ray.t="    << ray.t;
    out << ", node="     << (node ? typeid(*node).name() : "none");
    out << ", u,v=("     << u << "," << v << ")";
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


