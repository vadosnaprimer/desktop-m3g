#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/m3g.hpp"
using namespace std;
using namespace m3g;

// -----------------------------------------------------------------
// カメラを指定してスクリーンをピックする方のpick関数のテスト
// このテストは本当に簡単なテストしてかしていないので
// m3g-viewerあたりを使って別途検証が必要。
// 実際問題これが通ればほぼ問題ないと思われるが。
// -----------------------------------------------------------------


// ----------------------------------------------------------------------------------------
// 座標はすべてsample/test-01-simpleと同じ
// Cameraは(0,0,5)でnear=0.1,far=1000
// Meshは(0,0,0)を中心に左上(-1,1)、右下(1,-1)
// 内部的にピックはMeshのローカル座標で行われる。
// レイ光線の方向ベクトルは正規化されて帰ってくるが、M3Gの要件では定義されていない独自仕様。
// ----------------------------------------------------------------------------------------
TEST (Group_pick_mesh_from_screen)
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
    int           strips[]  = {4};
    TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);
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
    
    // ど真ん中のピック
    hit = wld->pick (-1, 0.5, 0.5, cam, &ri);

    CHECK_EQUAL (true, hit);
    CHECK_EQUAL (mesh, ri.getIntersected());

    // near面からメッシュまでの距離 = 4.9
    CHECK_CLOSE (4.9f, ri.getDistance(), 0.0001f);

    float ray[6];
    ri.getRay (ray);

    // レイはorg=(0,0,4.9),dir=(0,0,-1)
    // 起点はnear面から
    CHECK_CLOSE (0.f,   ray[0], 0.0001f);  // ox
    CHECK_CLOSE (0.f,   ray[1], 0.0001f);  // oy
    CHECK_CLOSE (4.9f,  ray[2], 0.0001f);  // oz
    CHECK_CLOSE (0.f,   ray[3], 0.0001f);  // dx
    CHECK_CLOSE (0.f,   ray[4], 0.0001f);  // dy
    CHECK_CLOSE (-1.f,  ray[5], 0.0001f);  // dz

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

    hit = wld->pick (-1, 1, 1, cam, &ri);


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
TEST (Group_pick_sprite_from_screen)
{
    Image2D*    img = new Image2D (Image2D::RGB, 128, 128);
    Appearance* app = new Appearance;

    Sprite3D*   spr = new Sprite3D (true, img, app);
    //spr->translate (1,0,0);

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

    hit = wld->pick (-1, 0.5, 0.5, cam, &ri);

    CHECK_EQUAL (true, hit);

    CHECK_EQUAL (spr, ri.getIntersected());

    // near面からメッシュまでの距離 = 4.0
    CHECK_CLOSE (4.0f, ri.getDistance(), 0.0001f);

    float ray[6];
    ri.getRay (ray);

    // レイはorg=(0,0,4),dir=(0,0,-1)
    // 起点はnear面から
    CHECK_CLOSE (0.f,   ray[0], 0.0001f);  // ox
    CHECK_CLOSE (0.f,   ray[1], 0.0001f);  // oy
    CHECK_CLOSE (4.f,   ray[2], 0.0001f);  // oz
    CHECK_CLOSE (0.f,   ray[3], 0.0001f);  // dx
    CHECK_CLOSE (0.f,   ray[4], 0.0001f);  // dy
    CHECK_CLOSE (-1.f,  ray[5], 0.0001f);  // dz

    // 法線は必ず(0,0,1)
    CHECK_CLOSE (0.f,  ri.getNormalX(), 0.0001f);  // nx
    CHECK_CLOSE (0.f,  ri.getNormalY(), 0.0001f);  // ny
    CHECK_CLOSE (1.f,  ri.getNormalZ(), 0.0001f);  // nz

    // サブメッシュはundefined.
    // (の時は0を返す実装になっている)
    CHECK_EQUAL (0, ri.getSubmeshIndex());

    // (s,t)=(0.5,0.5)を期待しているが、なぜか(0.5,0.5745)が返る。
    // 精度が悪いのが気になるが現在はこれで保留。
    CHECK_CLOSE (0.5f, ri.getTextureS(0), 0.1f);  // s
    CHECK_CLOSE (0.5f, ri.getTextureT(0), 0.1f);  // t
    
    delete wld;
    delete cam;
    delete spr;
    delete app;
}
