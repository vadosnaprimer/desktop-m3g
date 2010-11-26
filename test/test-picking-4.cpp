#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/m3g.hpp"
using namespace std;
using namespace m3g;

// -----------------------------------------------------------------
// Meshの前後関係をピックするテスト
// -----------------------------------------------------------------


// ----------------------------------------------------------------------------------------
// 座標はすべてsample/test-01-simpleと同じ
// Cameraは(0,0,5)でnear=0.1,far=1000
// Meshは(0,0,0)を中心に左上(-1,1)、右下(1,-1)
// 内部的にピックはMeshのローカル座標で行われる。
// レイ光線の方向ベクトルは正規化されて帰ってくるが、M3Gの要件では定義されていない独自仕様。
// ----------------------------------------------------------------------------------------
TEST (Group_pick_meshs)
{
    VertexArray* positions_0         = new VertexArray (4, 3, 2);
    short        positions_value_0[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    positions_0->set (0, 4, positions_value_0);

    VertexArray* positions_1         = new VertexArray (4, 3, 2);
    short        positions_value_1[] = {1,-1,-1, 1,1,-1, -1,-1,-1, -1,1,-1};
    positions_1->set (0, 4, positions_value_1);

    VertexArray* normals         = new VertexArray (4, 3, 1);
    char         normals_value[] = {0,0,127, 0,0,127, 0,0,127, 0,0,127};
    normals->set (0, 4, normals_value);

    float         scale    = 1;
    float         bias[3]  = {0,0,0};
    VertexBuffer* vertices_0 = new VertexBuffer;
    vertices_0->setPositions (positions_0, scale, bias);
    vertices_0->setNormals   (normals);

    VertexBuffer* vertices_1 = new VertexBuffer;
    vertices_1->setPositions (positions_1, scale, bias);
    vertices_1->setNormals   (normals);

    int           indices[] = {0,1,2,3};
    int           strips[]  = {4};
    TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);
    Appearance*         app  = new Appearance;

    Mesh*               mesh_0 = new Mesh (vertices_0, tris, app);
    Mesh*               mesh_1 = new Mesh (vertices_1, tris, app);

    Camera* cam = new Camera;
    cam->setPerspective (45, 1, 0.1, 100);
    cam->lookAt (0,0,5,
                 0,0,0,
                 0,1,0);

    World* wld = new World;
    wld->addChild (mesh_0);
    wld->addChild (mesh_1);
    wld->addChild (cam);
    wld->setActiveCamera (cam);


    RayIntersection ri;
    bool hit;
    
    // ど真ん中のピック.
    hit = wld->pick (-1, 0.5, 0.5, cam, &ri);

    // mesh_1.z = -1
    // mesh_0.z =  0   // hit!
    CHECK_EQUAL (true, hit);
    CHECK_EQUAL (mesh_0, ri.getIntersected());


    mesh_1->translate (0,0,2);

    // ど真ん中のピック.
    hit = wld->pick (-1, 0.5, 0.5, cam, &ri);

    // mesh_0.z =  0
    // mesh_1.z =  1   // hit!
    CHECK_EQUAL (true, hit);
    CHECK_EQUAL (mesh_1, ri.getIntersected());


    delete wld;
    delete cam;
    delete mesh_0;
    delete mesh_1;
    delete vertices_0;
    delete vertices_1;
    delete tris;
    delete app;
    delete positions_0;
    delete positions_1;
    delete normals;
}

