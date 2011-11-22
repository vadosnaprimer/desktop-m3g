#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/m3g.hpp"
using namespace std;
using namespace m3g;

// -----------------------------------------------------------------
// シーングラフのピッキングのテスト.
// test-picking-1.cpp, test-picking-2.cpp は
// 階層構造を持ったシーンのテストを実施していない。
// -----------------------------------------------------------------

// ----------------------------------------------------------------------------------------
// 座標はすべてsample/test-01-simpleと同じ
// Cameraは(0,0,5)でnear=0.1,far=1000
// Meshは(0,0,0)を中心に左上(-1,1)、右下(1,-1)
// これをGroupノードが右へ2ずらす(画面外)。
// ----------------------------------------------------------------------------------------
TEST (Group_pick_mesh_from_screen_with_group)
{
    VertexArray* positions         = new VertexArray (4, 3, 2);
    short        positions_value[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    positions->set (0, 4, positions_value);

    VertexArray* normals         = new VertexArray (4, 3, 1);
    char         normals_value[] = {0,0,127, 0,0,127, 0,0,127, 0,0,127};
    normals->set (0, 4, normals_value);

    float         scale    = 1;
    float         bias[3]  = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setNormals   (normals);

    int           indices[] = {0,1,2,3};
    int           strips [] = {4};
    TriangleStripArray* tris = new TriangleStripArray (4, indices, 1, strips);
    Appearance*         app  = new Appearance;
    Mesh*               mesh = new Mesh (vertices, tris, app);

    Camera* cam = new Camera;
    cam->setPerspective (45, 1, 0.1, 100);
    cam->lookAt (0,0,5,
                 0,0,0,
                 0,1,0);

    Group* grp = new Group;
    grp->addChild (mesh);
    grp->translate (2,0,0);

    World* wld = new World;
    wld->addChild (grp);
    wld->addChild (cam);
    wld->setActiveCamera (cam);


    RayIntersection ri;
    bool hit;
    
    // ど真ん中のピック.
    // MeshはGroupによって右に2ずれているので、
    // これはヒットしない。
    hit = wld->pick (-1, 
                     0.5, 0.5, cam,  //  center of screen
                     &ri);
    CHECK_EQUAL (false, hit);


    // 端っこのピック
    // MeshはGroupによって右に2ずれているので、
    // これはヒットする。
    // ピック光線はカメラが透視変換なので斜め前方方向に飛ぶ。
    hit = wld->pick (-1,
                     1, 0.5, cam,   // right edge of screen
                     &ri);

    CHECK_EQUAL (true, hit);

    CHECK_EQUAL (mesh, ri.getIntersected());

    // near面からメッシュまでの距離 = 約5.3f  (4.9よりより少し大きい)
    CHECK_CLOSE (5.30372f, ri.getDistance(), 0.0001f);

    float ray[6];
    ri.getRay (ray);

    // レイはorg=(0.04,0,4.9),dir=(0.38,0,-0.92)
    // 起点はnear面から。
    CHECK_CLOSE (0.0414214f, ray[0], 0.0001f);  // ox
    CHECK_CLOSE (0.f,        ray[1], 0.0001f);  // oy
    CHECK_CLOSE (4.9f,       ray[2], 0.0001f);  // oz
    CHECK_CLOSE (0.382684f,  ray[3], 0.0001f);  // dx
    CHECK_CLOSE (0.f,        ray[4], 0.0001f);  // dy
    CHECK_CLOSE (-0.92388f,  ray[5], 0.0001f);  // dz

    // 法線は(0,0,1)
    // (法線はchar型で保存しているので誤差が大きい)
    CHECK_CLOSE (0.f,  ri.getNormalX(), 0.01f);  // nx
    CHECK_CLOSE (0.f,  ri.getNormalY(), 0.01f);  // ny
    CHECK_CLOSE (1.f,  ri.getNormalZ(), 0.01f);  // nz

    // サブメッシュは0
    CHECK_EQUAL (0, ri.getSubmeshIndex());

    // テクスチャーはundefined.
    // (の時は0を返す実装)
    CHECK_CLOSE (0.f, ri.getTextureS(0), 0.0001f);  // s
    CHECK_CLOSE (0.f, ri.getTextureT(0), 0.0001f);  // t


    delete wld;
    delete cam;
    delete mesh;
    delete vertices;
    delete tris;
    delete app;
    delete positions;
    delete normals;
}


// ----------------------------------------------------------------------------------------
// 座標はすべてsample/test-01-simpleと同じ
// Cameraは(0,0,5)でnear=0.1,far=1000
// Meshは(0,0,0)を中心に左上(-1,1)、右下(1,-1)
// これがGroupによって右に2ずれる。
// 内部的にピックはMeshのローカル座標で行われる。
// レイ光線の方向ベクトルはユーザーが指定した値で、org + dir*t が衝突地点。
// ----------------------------------------------------------------------------------------
TEST (Group_pick_mesh_by_user_with_group)
{
    VertexArray* positions         = new VertexArray (4, 3, 2);
    short        positions_value[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    positions->set (0, 4, positions_value);

    VertexArray* normals         = new VertexArray (4, 3, 1);
    char        normals_value[] = {0,0,127, 0,0,127, 0,0,127, 0,0,127};
    normals->set (0, 4, normals_value);

    float         scale    = 1;
    float         bias[3]  = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setNormals   (normals);

    int           indices[] = {0,1,2,3};
    int           strips [] = {4};
    TriangleStripArray* tris = new TriangleStripArray (4, indices, 1, strips);
    Appearance*         app  = new Appearance;
    Mesh*               mesh = new Mesh (vertices, tris, app);

    Camera* cam = new Camera;
    cam->setPerspective (45, 1, 0.1, 100);
    cam->lookAt (0,0,5,
                 0,0,0,
                 0,1,0);

    Group* grp = new Group;
    grp->addChild (mesh);
    grp->translate (2,0,0);

    World* wld = new World;
    wld->addChild (grp);
    wld->addChild (cam);
    wld->setActiveCamera (cam);


    RayIntersection ri;
    bool hit;
    
    // レイ光線をユーザーが指定するピック.
    // これはヒットしない。
    hit = wld->pick (-1, 
                     0, 0, 5,    // ox, oy, oz
                     0, 0, -0.5,  // dx, dy, dz
                     &ri);

    CHECK_EQUAL (false, hit);



    // レイ光線をユーザーが指定するピック.
    // これはヒットする
    hit = wld->pick (-1, 
                     2, 0, 5,     // ox, oy, oz
                     0, 0, -0.5,  // dx, dy, dz
                     &ri);

    CHECK_EQUAL (hit, hit);
    CHECK_EQUAL (mesh, ri.getIntersected());

    // near面からメッシュまでの距離 = 10 (=5*2)
    CHECK_CLOSE (10.0f, ri.getDistance(), 0.0001f);

    float ray[6];
    ri.getRay (ray);

    // レイはユーザー指定の値そのもの
    // org=(2,0,5),dir=(0,0,-0.5)
    CHECK_CLOSE (2.f,   ray[0], 0.0001f);  // ox
    CHECK_CLOSE (0.f,   ray[1], 0.0001f);  // oy
    CHECK_CLOSE (5.f,   ray[2], 0.0001f);  // oz
    CHECK_CLOSE (0.f,   ray[3], 0.0001f);  // dx
    CHECK_CLOSE (0.f,   ray[4], 0.0001f);  // dy
    CHECK_CLOSE (-0.5f, ray[5], 0.0001f);  // dz

    // 法線は(0,0,1)
    // (法線はchar型で保存しているので誤差が大きい)
    CHECK_CLOSE (0.f,  ri.getNormalX(), 0.01f);  // nx
    CHECK_CLOSE (0.f,  ri.getNormalY(), 0.01f);  // ny
    CHECK_CLOSE (1.f,  ri.getNormalZ(), 0.01f);  // nz

    // サブメッシュは0
    CHECK_EQUAL (0, ri.getSubmeshIndex());

    // テクスチャーはundefined.
    // (の時は0を返す実装)
    CHECK_CLOSE (0.f, ri.getTextureS(0), 0.0001f);  // s
    CHECK_CLOSE (0.f, ri.getTextureT(0), 0.0001f);  // t

    delete wld;
    delete cam;
    delete mesh;
    delete vertices;
    delete tris;
    delete app;
    delete positions;
    delete normals;
}
