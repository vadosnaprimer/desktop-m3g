#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/SkinnedMesh.hpp"
#include "m3g/VertexArray.hpp"
#include "m3g/VertexBuffer.hpp"
#include "m3g/TriangleStripArray.hpp"
#include "m3g/Appearance.hpp"
#include "m3g/Group.hpp"
#include "m3g/Exception.hpp"
using namespace std;
using namespace m3g;

TEST (SkinnedMesh_default_variables)
{
    VertexArray*  varry       = new VertexArray (16, 3, 2);
    VertexBuffer* vbuf        = new VertexBuffer;
    int           indices[]   = {0,1,2};
    int           strips[]    = {3};
    TriangleStripArray* tris  = new TriangleStripArray (3, indices, 1, strips);
    Appearance*   app         = new Appearance;
    Group*        skeleton    = new Group;
    Group*        bone        = new Group;

    float scale  = 1;
    float bias[] = {0,0,0};
    vbuf->setPositions (varry, scale, bias);

    skeleton->addChild (bone);

    SkinnedMesh*  mesh = new SkinnedMesh (vbuf, 
                                          1, (IndexBuffer**)&tris, 
                                          1, &app,
                                          skeleton);

    CHECK_EQUAL (skeleton, mesh->getSkeleton());
    CHECK_EQUAL (mesh    , mesh->getSkeleton()->getParent());
    CHECK_THROW (skeleton->removeChild (bone), IllegalArgumentException);

    delete vbuf;
    delete tris;
    delete app;
    delete skeleton;
    delete mesh;
}




TEST (SkinnedMesh_addTransform_getBoneVertices)
{
    VertexArray*  varry       = new VertexArray (10, 3, 2);
    VertexBuffer* vbuf        = new VertexBuffer;
    int           indices[]   = {0,1,2};
    int           strips[]    = {3};
    TriangleStripArray* tris  = new TriangleStripArray (3, indices, 1, strips);
    Appearance*   app         = new Appearance;

    // bone0 --> bone1 --> bone2
    //             |-----> bone3
    Group*        bone0    = new Group;
    Group*        bone1    = new Group;
    Group*        bone2    = new Group;
    Group*        bone3    = new Group;
    bone1->translate (0,1,0);
    bone2->translate (1,0,0);
    bone3->translate (1,0,0);
    bone0->addChild (bone1);
    bone1->addChild (bone2);
    bone1->addChild (bone3);
  
    float scale  = 1;
    float bias[] = {0,0,0};
    vbuf->setPositions (varry, scale, bias);

    SkinnedMesh*  mesh = new SkinnedMesh (vbuf, 
                                          1, (IndexBuffer**)&tris, 
                                          1, &app                ,
                                          bone0);

    // vertices 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    // bone0    ----------        ----
    // bone1          ----------
    // bone2          ----                   
    // bone3                      ----------                     
    mesh->addTransform (bone0, 100, 0, 4);
    mesh->addTransform (bone0, 100, 6, 2);
    mesh->addTransform (bone1, 100, 2, 4);
    mesh->addTransform (bone2, 200, 2, 2);
    mesh->addTransform (bone3, 200, 6, 4);
  
    int vertex_indices[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    float weights[10] = {0,0,0,0,0,0,0,0,0,0};
    int num = 0;

    num = mesh->getBoneVertices (bone0, vertex_indices, weights);
    CHECK_EQUAL (6, num);
    CHECK_EQUAL (0, vertex_indices[0]);
    CHECK_EQUAL (1, vertex_indices[1]);
    CHECK_EQUAL (2, vertex_indices[2]);
    CHECK_EQUAL (3, vertex_indices[3]);
    CHECK_EQUAL (6, vertex_indices[4]);
    CHECK_EQUAL (7, vertex_indices[5]);
    CHECK_CLOSE (1,   weights[0], 0.00001);
    CHECK_CLOSE (1,   weights[1], 0.00001);
    CHECK_CLOSE (0.25, weights[2], 0.00001);
    CHECK_CLOSE (0.25, weights[3], 0.00001);
    CHECK_CLOSE (0.333333,   weights[4], 0.00001);
    CHECK_CLOSE (0.333333,   weights[5], 0.00001);

    num = mesh->getBoneVertices (bone1, vertex_indices, weights);
    CHECK_EQUAL (4, num);
    CHECK_EQUAL (2, vertex_indices[0]);
    CHECK_EQUAL (3, vertex_indices[1]);
    CHECK_EQUAL (4, vertex_indices[2]);
    CHECK_EQUAL (5, vertex_indices[3]);
    CHECK_CLOSE (0.25, weights[0], 0.00001);
    CHECK_CLOSE (0.25, weights[1], 0.00001);
    CHECK_CLOSE (1,   weights[2], 0.00001);
    CHECK_CLOSE (1,   weights[3], 0.00001);

    num = mesh->getBoneVertices (bone2, vertex_indices, weights);
    CHECK_EQUAL (2, num);
    CHECK_EQUAL (2, vertex_indices[0]);
    CHECK_EQUAL (3, vertex_indices[1]);
    CHECK_CLOSE (0.5, weights[0], 0.00001);
    CHECK_CLOSE (0.5, weights[1], 0.00001);

    num = mesh->getBoneVertices (bone3, vertex_indices, weights);
    CHECK_EQUAL (4, num);
    CHECK_EQUAL (6, vertex_indices[0]);
    CHECK_EQUAL (7, vertex_indices[1]);
    CHECK_EQUAL (8, vertex_indices[2]);
    CHECK_EQUAL (9, vertex_indices[3]);
    CHECK_CLOSE (0.666667, weights[0], 0.00001);
    CHECK_CLOSE (0.666667, weights[1], 0.00001);
    CHECK_CLOSE (1, weights[2], 0.00001);
    CHECK_CLOSE (1, weights[3], 0.00001);


}

TEST (SkinnedMesh_getBoneTransform)
{
    VertexArray*  varry       = new VertexArray (10, 3, 2);
    VertexBuffer* vbuf        = new VertexBuffer;
    int           indices[]   = {0,1,2};
    int           strips[]    = {3};
    TriangleStripArray* tris  = new TriangleStripArray (3, indices, 1, strips);
    Appearance*   app         = new Appearance;

    Group*        bone0    = new Group;
    Group*        bone1    = new Group;
    Group*        bone2    = new Group;
    bone1->translate (0,1,0);
    bone2->translate (1,0,0);
    bone0->addChild (bone1);
    bone0->addChild (bone2);

    float scale  = 1;
    float bias[] = {0,0,0};
    vbuf->setPositions (varry, scale, bias);

    SkinnedMesh*  mesh = new SkinnedMesh (vbuf, 
                                          1, (IndexBuffer**)&tris,
                                          1, &app,
                                          bone0);

    // vertices 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    // bone0    ----------        ----
    // bone1          ----------
    // bone2          ----                   
    mesh->addTransform (bone0, 100, 0, 4);
    mesh->addTransform (bone0, 100, 6, 2);
    mesh->addTransform (bone1, 100, 2, 4);
    mesh->addTransform (bone2, 20,  2, 2);  // ウェイトの小さな3つ目のボーンは無視

    Transform trns;
    float m[16];

    mesh->getBoneTransform (bone1, &trns);
    trns.get (m);
    CHECK_CLOSE (-1, m[7], 0.00001);   // m[1][3] = ty

    mesh->getBoneTransform (bone2, &trns);
    trns.get (m);
    CHECK_CLOSE (-1, m[3], 0.00001);   // m[0][3] = tx

}

TEST (SkinnedMesh_duplicate)
{
    VertexArray*  varry       = new VertexArray (10, 3, 2);
    VertexBuffer* vbuf        = new VertexBuffer;
    int           indices[]   = {0,1,2};
    int           strips[]    = {3};
    TriangleStripArray* tris  = new TriangleStripArray (3, indices, 1, strips);
    Appearance*   app         = new Appearance;

    Group*        bone0    = new Group;
    Group*        bone1    = new Group;
    Group*        bone2    = new Group;
    bone1->translate (0,1,0);
    bone2->translate (1,0,0);
    bone0->addChild (bone1);
    bone0->addChild (bone2);

    float scale  = 1;
    float bias[] = {0,0,0};
    vbuf->setPositions (varry, scale, bias);

    SkinnedMesh* mesh0 = new SkinnedMesh (vbuf,
                                          1, (IndexBuffer**)&tris,
                                          1, &app,
                                          bone0);

    // vertices 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    // bone0    ----------        ----
    // bone1          ----------
    // bone2          ----                   
    mesh0->addTransform (bone0, 100, 0, 4);
    mesh0->addTransform (bone0, 100, 6, 2);
    mesh0->addTransform (bone1, 100, 2, 4);
    mesh0->addTransform (bone2, 20,  2, 2);  // ウェイトの小さな3つ目のボーンは無視


    SkinnedMesh* mesh1  = mesh0->duplicate();

    CHECK (mesh0->getSkeleton() != mesh1->getSkeleton());

    // 注意: mesh1はduplicateされたボーンを持つので、
    // 古い方のボーンでgetBoneVertices()すると例外を発生するのが正しい。
    CHECK_THROW (mesh1->getBoneVertices (bone0,0,0), IllegalArgumentException);
    CHECK_THROW (mesh1->getBoneVertices (bone1,0,0), IllegalArgumentException);
    CHECK_THROW (mesh1->getBoneVertices (bone2,0,0), IllegalArgumentException);

    // bone0が影響を持つ頂点は6つ
    int   vertex_indices0[6], vertex_indices1[6];
    float weights0[6], weights1[6];
    
    mesh0->getBoneVertices (bone0, vertex_indices0, weights0);
    mesh1->getBoneVertices (mesh1->getSkeleton(), vertex_indices1, weights1);

    // ルート・ボーンしかチェックしてないけどまず大丈夫だろう。
    CHECK_ARRAY_EQUAL (vertex_indices0, vertex_indices1, 6);
    CHECK_ARRAY_EQUAL (weights0, weights1, 6);
    
    delete varry;
    delete vbuf;
    delete tris;
    delete app;
    delete bone0;
    delete bone1;
    delete bone2;
    delete mesh0;
    delete mesh1;
}

TEST (SkinnedMesh_find)
{
    VertexArray*  varry       = new VertexArray (16, 3, 2);
    VertexBuffer* vbuf        = new VertexBuffer;
    int           indices[]   = {0,1,2};
    int           strips[]    = {3};
    TriangleStripArray* tris  = new TriangleStripArray (3, indices, 1, strips);
    Appearance*   app         = new Appearance;
    Group*        skeleton    = new Group;

    float scale  = 1;
    float bias[] = {0,0,0};
    vbuf->setPositions (varry, scale, bias);

    SkinnedMesh*  mesh        = new SkinnedMesh (vbuf, 
                                                 1, (IndexBuffer**)&tris,
                                                 1, &app,
                                                 skeleton);

    varry->setUserID (100);
    vbuf ->setUserID (101);
    tris ->setUserID (102);
    app  ->setUserID (103);
    skeleton->setUserID (104);
    mesh->setUserID  (105);

    CHECK_EQUAL (vbuf    , mesh->find(101));
    CHECK_EQUAL (tris    , mesh->find(102));
    CHECK_EQUAL (app     , mesh->find(103));
    CHECK_EQUAL (skeleton, mesh->find(104));
    CHECK_EQUAL (mesh    , mesh->find(105));

    delete varry;
    delete vbuf;
    delete tris;
    delete app;
    delete skeleton;
    delete mesh;
}

TEST (SkinnedMesh_getReferences)
{
    VertexArray*  varry       = new VertexArray (16, 3, 2);
    VertexBuffer* vbuf        = new VertexBuffer;
    int           indices[]   = {0,1,2};
    int           strips[]    = {3};
    TriangleStripArray* tris  = new TriangleStripArray (3, indices, 1, strips);
    Appearance*   app         = new Appearance;
    Group*        skeleton    = new Group;

    float scale  = 1;
    float bias[] = {0,0,0};
    vbuf->setPositions (varry, scale, bias);

    SkinnedMesh*  mesh = new SkinnedMesh (vbuf                   ,
                                          1, (IndexBuffer**)&tris,
                                          1, &app                , 
                                          skeleton);

    int n;
    Object3D* objs[4];

    n = mesh->getReferences (objs);

    CHECK_EQUAL (4, n);
    CHECK_EQUAL (vbuf    , objs[0]);
    CHECK_EQUAL (tris    , objs[1]);
    CHECK_EQUAL (app     , objs[2]);
    CHECK_EQUAL (skeleton, objs[3]);

    delete vbuf;
    delete tris;
    delete app;
    delete skeleton;
    delete mesh;
}
