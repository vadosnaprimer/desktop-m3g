#include <unittest++/UnitTest++.h>
#include <iostream>
#include <cmath>
#include "Intersect.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "TriangleStripArray.hpp"
#include "Appearance.hpp"
#include "Mesh.hpp"
#include "Vector.hpp"
#include "RayIntersection.hpp"
using namespace std;
using namespace m3g;

TEST (RayIntersect_set_variable)
{
    float position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    VertexArray* positions = new VertexArray (4, 3, 4);
    positions->set (0, 4, position_values);
    float normal_values[] = {0,0,1, 0,0,1, 0,0,1, 0,0,1};
    VertexArray* normals = new VertexArray (4, 3, 4);
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

    cout << ri << "\n";

    CHECK_EQUAL ((Node*)mesh, ri.getIntersected());
    CHECK_CLOSE (1.f,  ri.getDistance(), 0.00001f);
    CHECK_EQUAL (0,    ri.getSubmeshIndex());

    float ray[6];
    ri.getRay (ray);
    CHECK_CLOSE (0.f, ray[0], 0.00001f);
    CHECK_CLOSE (0.f, ray[1], 0.00001f);
    CHECK_CLOSE (1.f, ray[2], 0.00001f);
    CHECK_CLOSE (0.f, ray[3], 0.00001f);
    CHECK_CLOSE (0.f, ray[4], 0.00001f);
    CHECK_CLOSE (-1.f, ray[5], 0.00001f);
    
    CHECK_CLOSE (0.f, ri.getNormalX(), 0.00001f);
//    CHECK_CLOSE (0.f, ri.getNormalY(), 0.00001f);
//    CHECK_CLOSE (1.f, ri.getNormalZ(), 0.00001f);

}


#if 0
TEST (RayIntersect_Mesh_intersect)
{
    float position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    VertexArray* positions = new VertexArray (4, 3, 4);
    positions->set (0, 4, position_values);
    float scale   = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vbuf = new VertexBuffer;
    vbuf->setPositions (positions, scale, bias);
    IndexBuffer* submesh[2];
    int indices0[] = {0,1,2};
    int strips0[]  = {3};
    submesh[0] = new TriangleStripArray (indices0, 1, strips0);
    int indices1[] = {1,2,3};
    int strips1[]  = {3};
    submesh[1] = new TriangleStripArray (indices1, 1, strips1);
    Appearance* app[2];
    app[0] = new Appearance;
    app[1] = new Appearance;
    Mesh* mesh = new Mesh (vbuf, 2, submesh, app);
    
    RayIntersection ri;
    mesh->intersect (Vector(-0.9,0,1), Vector(0,0,-1), &ri);

    cout << ri << "\n";
}
#endif
