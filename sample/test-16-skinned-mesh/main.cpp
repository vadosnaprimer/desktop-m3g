#include "m3g.hpp"
#include "data.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cmath>
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
  cam->setPerspective (45, w/(float)w, 0.1, 100);
  glutPostRedisplay();
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glewInit ();

  VertexArray* positions = new VertexArray (42, 3, 2);
  positions->set (0, 42, (short*)xyz);

  float scale = 0.001;
  float bias[3] = {0,0,0};
  VertexBuffer* vbuf = new VertexBuffer;
  vbuf->setPositions (positions, scale, bias);
  
  int strips[1] = {42};
  TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

  Appearance* app = new Appearance;

  Group* bone0 = new Group;
  Group* bone1 = new Group;
  bone1->translate (0,10,0);
  bone0->addChild (bone1);
  
  SkinnedMesh* mesh = new SkinnedMesh (vbuf, tris, app, bone0);
  //mesh->addTransform (bone0, 1, 0, 21);
  //mesh->addTransform (bone1, 1, 21, 21);
  mesh->addTransform (bone0, 1, 0, 26);
  mesh->addTransform (bone1, 1, 16, 26);
  
  //bone0->translate (10,0,0);
  bone1->postRotate (-20, 0,0,1);

  Camera* cam = new Camera;
  cam->translate (0,10,50);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (mesh);

  cout << *wld << "\n";

  mesh->animate (0);


  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
