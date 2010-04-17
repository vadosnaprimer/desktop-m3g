#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include "libpng.hpp"
#include "data.hpp"
using namespace std;
using namespace m3g;


World* wld = 0;

void display(void)
{
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->render (wld);
  glutSwapBuffers();
}

void resize(int w, int h)
{
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->setViewport (0,0,w,h);
  Camera* cam = wld->getActiveCamera();
  cam->setPerspective (45, w/(float)h, 0.1, 100);
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glewInit ();

  VertexArray* pos_array = new VertexArray (4, 3, 2);
  pos_array->set (0, 4, vertices1);

  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vbuf = new VertexBuffer;
  vbuf->setPositions (pos_array, scale, bias);
  //vbuf->setDefaultColor (0x3f7f7fff);
  vbuf->setDefaultColor (0xcf7f7fff);

  int strips[1] = {4};
  TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

  CompositingMode* cmp = new CompositingMode;
  cmp->setBlending (CompositingMode::ALPHA);
  cmp->setDepthTestEnable (false);
  cmp->setDepthWriteEnable (false);
  cmp->setAlphaThreshold (0.0);

  Appearance* app = new Appearance;
  app->setCompositingMode (cmp);

  Mesh* mesh1 = new Mesh (vbuf, tris, app);
  mesh1->translate (0,0,-1);

  Mesh* mesh2 = new Mesh (vbuf, tris, app);
  mesh2->translate (0,0,-2);

  Mesh* mesh3 = new Mesh (vbuf, tris, app);
  mesh3->translate (0,0,-3);

  Mesh* mesh4 = new Mesh (vbuf, tris, app);
  mesh4->translate (0,0,-4);

  Mesh* mesh5 = new Mesh (vbuf, tris, app);
  mesh5->translate (0,0,-5);

  Group* grp = new Group;
  grp->addChild(mesh1);
  grp->addChild(mesh2);
  grp->addChild(mesh3);
  grp->addChild(mesh4);
  grp->addChild(mesh5);

  Camera* cam = new Camera;
  cam->lookAt (3,0,3, 0,0,-2, 0,1,0);

  Background* bg = new Background;
  bg->setColor (0xff3f3f3f);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (grp);
  wld->setBackground (bg);


  cout << *wld << "\n";

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
