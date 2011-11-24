#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/Mesh.hpp"
#include "m3g/VertexArray.hpp"
#include "m3g/VertexBuffer.hpp"
#include "m3g/TriangleStripArray.hpp"
#include "m3g/Appearance.hpp"
#include "m3g/RayIntersection.hpp"
using namespace std;
using namespace m3g;


TEST (Mesh_default_variables_1)
{
    VertexBuffer* vbuf = new VertexBuffer;
    int indices[] = {0,1,2};
    int strips [] = {3};
    TriangleStripArray* tris[2] = {new TriangleStripArray (3, indices, 1, strips),
                                   new TriangleStripArray (3, indices, 1, strips)};
    Appearance*  app[2]  = {new Appearance, new Appearance};
    Mesh* mesh = new Mesh (vbuf, 2, (IndexBuffer**)tris, 2, app);

    CHECK_EQUAL (vbuf,    mesh->getVertexBuffer());
    CHECK_EQUAL (2,       mesh->getSubmeshCount());
    CHECK_EQUAL (tris[0], mesh->getIndexBuffer(0));
    CHECK_EQUAL (tris[1], mesh->getIndexBuffer(1));
    CHECK_EQUAL (app[0],  mesh->getAppearance(0));
    CHECK_EQUAL (app[1],  mesh->getAppearance(1));

    delete vbuf;
    delete tris[0];
    delete tris[1];
    delete app[0];
    delete app[1];
    delete mesh;
}


TEST (Mesh_default_variables_2)
{
    VertexBuffer* vbuf = new VertexBuffer;
    int indices[] = {0,1,2};
    int strips [] = {3};
    TriangleStripArray* tris = new TriangleStripArray (3, indices, 1, strips);
    Appearance* app = new Appearance;
    Mesh* mesh = new Mesh (vbuf, tris, app);

    CHECK_EQUAL (vbuf, mesh->getVertexBuffer());
    CHECK_EQUAL (1,    mesh->getSubmeshCount());
    CHECK_EQUAL (tris, mesh->getIndexBuffer(0));
    CHECK_EQUAL (app,  mesh->getAppearance(0));


    delete vbuf;
    delete tris;
    delete app;
    delete mesh;
}

TEST (Mesh_setAppearance)
{
    VertexBuffer* vbuf = new VertexBuffer;
    int indices[] = {0,1,2};
    int strips [] = {3};
    TriangleStripArray* tris[2] = {new TriangleStripArray (3, indices, 1, strips),
                                   new TriangleStripArray (3, indices, 1, strips)};
    Appearance* apps[2] = {new Appearance,
                           new Appearance};
    Mesh* mesh = new Mesh (vbuf, 2, (IndexBuffer**)tris, 2, apps);

    Appearance* app2 = new Appearance;
    mesh->setAppearance (0, NULL);
    mesh->setAppearance (1, app2);
    CHECK_EQUAL ((Appearance*)NULL, mesh->getAppearance(0));
    CHECK_EQUAL (app2             , mesh->getAppearance(1));

    delete vbuf;
    delete tris[0];
    delete tris[1];
    delete apps[0];
    delete apps[1];
    delete app2;
    delete mesh;
}


TEST (Mesh_duplicate)
{
    VertexBuffer* vbuf = new VertexBuffer;
    int indices[] = {0,1,2};
    int strips [] = {3};
    TriangleStripArray* tris = new TriangleStripArray (3, indices, 1, strips);
    Appearance* app = new Appearance;
    Mesh* mesh0 = new Mesh (vbuf, tris, app);

    CHECK_EQUAL (vbuf, mesh0->getVertexBuffer());
    CHECK_EQUAL (1,    mesh0->getSubmeshCount());
    CHECK_EQUAL (tris, mesh0->getIndexBuffer(0));
    CHECK_EQUAL (app,  mesh0->getAppearance(0));

    // duplicate()されるのはMesh本体だけ。
    // VertexBufferやIndexBufferは同じ物が使われる。
    Mesh* mesh1 = mesh0->duplicate();

    CHECK_EQUAL (mesh0->getSubmeshCount(), mesh1->getSubmeshCount());
    CHECK_EQUAL (mesh0->getVertexBuffer(), mesh1->getVertexBuffer());
    CHECK_EQUAL (mesh0->getIndexBuffer(0), mesh1->getIndexBuffer(0));
    CHECK_EQUAL (mesh0->getAppearance(0) , mesh1->getAppearance(0));

    delete vbuf;
    delete tris;
    delete app;
    delete mesh0;
    delete mesh1;
}

TEST (Mesh_getReferences)
{
    VertexBuffer* vbuf = new VertexBuffer;
    int indices[] = {0,1,2};
    int strips [] = {3};
    TriangleStripArray* tris = new TriangleStripArray (3, indices, 1, strips);
    Appearance*         app  = new Appearance;
    Mesh*               mesh = new Mesh (vbuf, tris, app);

    int n;
    Object3D* objs[3];

    n = mesh->getReferences (objs);

    CHECK_EQUAL (3, n);
    CHECK_EQUAL (vbuf, objs[0]);
    CHECK_EQUAL (tris, objs[1]);
    CHECK_EQUAL (app , objs[2]);

    delete vbuf;
    delete tris;
    delete app;
    delete mesh;
}

TEST (Mesh_find)
{
    VertexBuffer* vbuf = new VertexBuffer;
    int indices[] = {0,1,2};
    int strips [] = {3};
    TriangleStripArray* tris = new TriangleStripArray (3, indices, 1, strips);
    Appearance*         app  = new Appearance;
    Mesh*               mesh = new Mesh (vbuf, tris, app);

    vbuf->setUserID (100);
    tris->setUserID (101);
    app ->setUserID (102);
    mesh->setUserID (103);

    CHECK_EQUAL (vbuf, mesh->find(100));
    CHECK_EQUAL (tris, mesh->find(101));
    CHECK_EQUAL (app , mesh->find(102));
    CHECK_EQUAL (mesh, mesh->find(103));

    delete vbuf;
    delete tris;
    delete app;
    delete mesh;
}


