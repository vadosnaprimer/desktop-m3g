#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cmath>
#include "m3g/Intersect.hpp"
#include "m3g/VertexArray.hpp"
#include "m3g/VertexBuffer.hpp"
#include "m3g/TriangleStripArray.hpp"
#include "m3g/Appearance.hpp"
#include "m3g/Mesh.hpp"
#include "m3g/Vector.hpp"
#include "m3g/RayIntersection.hpp"
using namespace std;
using namespace m3g;

TEST (RayIntersect_set_variable)
{
    float        position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    VertexArray* positions         = new VertexArray (4, 3, 4);
    positions->set (0, 4, position_values);

    float        normal_values[] = {0,0,1, 0,0,1, 0,0,1, 0,0,1};
    VertexArray* normals         = new VertexArray (4, 3, 4);
    normals->set (0, 4, normal_values);

    float scale   = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setNormals (normals);

    int indices[] = {0,1,2,3};
    int strips[]  = {4};
    IndexBuffer* submesh = new TriangleStripArray (indices, 1, strips);
    Appearance*  app     = new Appearance;
    Mesh*        mesh    = new Mesh (vertices, submesh, app);

    int vertex_indices[] = {0,1,2};
    int submesh_index    = 0;
    RayIntersection ri (mesh, 
                        Vector(0,0,1), Vector(0,0,-1), 1,
                        0.5, 0.5,
                        3, vertex_indices,
                        submesh_index);
    //normals->print_raw_data (cout) << "\n";
    //cout << ri << "\n";

    CHECK_EQUAL ((Node*)mesh, ri.getIntersected());
    CHECK_CLOSE (1.f,  ri.getDistance(), 0.00001f);
    CHECK_EQUAL (0,    ri.getSubmeshIndex());

    float ray[6];
    ri.getRay (ray);
    CHECK_CLOSE (0.f,  ray[0], 0.00001f);
    CHECK_CLOSE (0.f,  ray[1], 0.00001f);
    CHECK_CLOSE (1.f,  ray[2], 0.00001f);
    CHECK_CLOSE (0.f,  ray[3], 0.00001f);
    CHECK_CLOSE (0.f,  ray[4], 0.00001f);
    CHECK_CLOSE (-1.f, ray[5], 0.00001f);
    
    CHECK_CLOSE (0.f, ri.getNormalX(), 0.00001f);
    CHECK_CLOSE (0.f, ri.getNormalY(), 0.00001f);
    CHECK_CLOSE (1.f, ri.getNormalZ(), 0.00001f);

    //normals->print_raw_data (cout) << "\n";
}


TEST (RayIntersection_transformRay)
{
    Node*  node              = new Node;
    Vector org               = Vector(1,2,3);
    Vector dir               = Vector(-1,-3,-2);
    float  t                 = 100;
    int    vertex_indices[3] = {0,1,2};
    float  u                 = 0.5;
    float  v                 = 0.5;
    int    submesh_index     = 0;
    RayIntersection ri (node, 
                        org, dir, t,
                        u, v,
                        3, vertex_indices,
                        submesh_index);

    float ray[6];
    ri.getRay (ray);
    CHECK_CLOSE (1.f,  ray[0], 0.00001f);  // ox
    CHECK_CLOSE (2.f,  ray[1], 0.00001f);  // oy
    CHECK_CLOSE (3.f,  ray[2], 0.00001f);  // oz
    CHECK_CLOSE (-1.f, ray[3], 0.00001f);  // dx
    CHECK_CLOSE (-3.f, ray[4], 0.00001f);  // dy
    CHECK_CLOSE (-2.f, ray[5], 0.00001f);  // dz
    
    Matrix mat;
    
    Transform trans;


    // 単位行列
    trans.set (mat);
    ri.transformRay (trans);
    ri.getRay (ray);
    CHECK_CLOSE (1.f,  ray[0], 0.00001f);  // ox
    CHECK_CLOSE (2.f,  ray[1], 0.00001f);  // oy
    CHECK_CLOSE (3.f,  ray[2], 0.00001f);  // oz
    CHECK_CLOSE (-1.f, ray[3], 0.00001f);  // dx
    CHECK_CLOSE (-3.f, ray[4], 0.00001f);  // dy
    CHECK_CLOSE (-2.f, ray[5], 0.00001f);  // dz
    CHECK_CLOSE (100.f, ri.getDistance(), 0.00001f); // t

    // 平行移動&スケール
    mat.setTranslate (1,2,3);
    mat.setScale     (2,4,6);

    trans.set (mat);
    ri.transformRay (trans);
    ri.getRay (ray);
    CHECK_CLOSE (3.f,   ray[0], 0.00001f);  // ox
    CHECK_CLOSE (10.f,  ray[1], 0.00001f);  // oy
    CHECK_CLOSE (21.f,  ray[2], 0.00001f);  // oz
    CHECK_CLOSE (-2.f,  ray[3], 0.00001f);  // dx
    CHECK_CLOSE (-12.f, ray[4], 0.00001f);  // dy
    CHECK_CLOSE (-12.f,  ray[5], 0.00001f);  // dz
    CHECK_CLOSE (100.f, ri.getDistance(), 0.00001f); // t
}
