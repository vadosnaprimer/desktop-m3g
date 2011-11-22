#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/m3g.hpp"
using namespace std;
using namespace m3g;

// -----------------------------------------------------------------
// レイ光線をユーザーが指定する方のpick関数のテスト
// このテストは本当に簡単なテストしてかしていないので
// m3g-viewerあたりを使って別途検証が必要。
// 実際問題これが通ればほぼ問題ないと思われるが。
// -----------------------------------------------------------------

// ----------------------------------------------------------------------------------------
// 座標はすべてsample/test-01-simpleと同じ
// Cameraは(0,0,5)でnear=0.1,far=1000
// Meshは(0,0,0)を中心に左上(-1,1)、右下(1,-1)
// 内部的にピックはMeshのローカル座標で行われる。
// レイ光線の方向ベクトルはユーザーが指定した値で、org + dir*t が衝突地点。
// ----------------------------------------------------------------------------------------
TEST (Group_pick_mesh_by_user)
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

    World* wld = new World;
    wld->addChild (mesh);
    wld->addChild (cam);
    wld->setActiveCamera (cam);


    RayIntersection ri;
    bool hit;
    
    // レイ光線をユーザーが指定するピック.
    // 方向ベクトルの長さが0.5であることに注意.
    hit = wld->pick (-1, 
                     0, 0, 5,    // ox, oy, oz
                     0, 0, -0.5,  // dx, dy, dz
                     &ri);

    CHECK_EQUAL (true, hit);
    CHECK_EQUAL (mesh, ri.getIntersected());

    // near面からメッシュまでの距離 = 10 (=5*2)
    CHECK_CLOSE (10.0f, ri.getDistance(), 0.0001f);

    float ray[6];
    ri.getRay (ray);

    // レイはユーザー指定の値そのもの
    // org=(0,0,5),dir=(0,0,-0.5)
    CHECK_CLOSE (0.f,   ray[0], 0.0001f);  // ox
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

    // 端っこのピック
    // これはヒットしない
    ri = RayIntersection();

    hit = wld->pick (-1,
                     10, 0, 0,   //  ox, oy, oz
                     0,  0, -1,   //  dx, dy, dz
                     &ri);


    CHECK_EQUAL (false, hit);

    delete wld;
    delete cam;
    delete mesh;
    delete vertices;
    delete tris;
    delete app;
    delete positions;
    delete normals;
}


// ---------------------------------------------------------------------------------------
// 座標は上と若干異なる。sample/test-12-spriteに準拠
// Cameraは(0,0,5)でnear=1,far=100
// Sprite3Dは(0,0,0)を中心にscaled.
// 内部的にピックはNDC座標で行われる。
// レイ光線の方向ベクトルは正規化されて帰ってくるが、M3Gの要件では定義されていない独自仕様。
// ----------------------------------------------------------------------------------------
// -----------------------------------------------------
// 
// 
// 
// -----------------------------------------------------
TEST (Group_pick_sprite_by_user)
{
    Image2D*    img = new Image2D (Image2D::RGB, 128, 128);
    Appearance* app = new Appearance;
    Sprite3D*   spr = new Sprite3D (true, img, app);

    Camera* cam = new Camera;
    cam->setPerspective (45, 1, 1, 100);
    cam->lookAt (0,0,5,
                 0,0,0,
                 0,1,0);

    World* wld = new World;
    wld->addChild (spr);
    wld->addChild (cam);
    wld->setActiveCamera (cam);

    RayIntersection ri;
    bool hit;

    // レイ光線をユーザーが指定するピック.
    // 方向ベクトルの長さが0.5であることに注意.
    hit = wld->pick (-1, 
                     0, 0, 5,     // ox, oy, oz
                     0, 0, -0.5,  // dx, dy, dz
                     &ri);

    // この形式のpick()はSprite3Dをピックしない
    CHECK_EQUAL (false, hit);


    
    delete wld;
    delete cam;
    delete spr;
    delete app;
}


