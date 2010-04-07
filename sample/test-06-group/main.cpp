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
  glutInitDisplayMode(GLUT_RGB);
  glutCreateWindow(argv[0]);
  glewInit ();

  float scale = 1;
  float bias[3] = {0,0,0};

  VertexArray* pos_array = new VertexArray (4, 3, 2);
  pos_array->set (0, 4, vertices1);
  VertexBuffer* vbuf1 = new VertexBuffer;
  vbuf1->setPositions (pos_array, scale, bias);
  vbuf1->setDefaultColor (0xff4c4cb2);  // 0.3, 0.3, 0.7

  VertexBuffer* vbuf2 = new VertexBuffer;
  vbuf2->setPositions (pos_array, scale, bias);
  vbuf2->setDefaultColor (0xff4cb2b2);  // 0.3, 0.3, 0.7

  int strips[1] = {4};
  TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);
  Appearance* app = new Appearance;

  Mesh* mesh1 = new Mesh (vbuf1, tris, app);
  mesh1->translate (1,0,0);

  Mesh* mesh2 = new Mesh (vbuf2, tris, app);
  mesh2->translate (-1,0,0);
  
  Group* grp = new Group;
  grp->translate (0,0,-3);
  grp->addChild(mesh1);
  grp->addChild(mesh2);

  cout << "hello world\n";

  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (grp);
  //  wld->addChild (lig);

  cout << *wld << "\n";

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
