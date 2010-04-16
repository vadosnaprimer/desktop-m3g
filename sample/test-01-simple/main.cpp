#include "m3g.hpp"
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
  cam->setPerspective (45, h/(float)w, 0.1, 100);
}

int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glewInit ();

  VertexArray* poss = new VertexArray (4, 3, 1);
  char vertices[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
  poss->set (0, 4, vertices);

  VertexArray* cols = new VertexArray (4, 3, 1);
  unsigned char colors[] = {255,0,0, 0,255,0, 0,0,255, 255,255,255};
  cols->set (0, 4, (char*)colors);

  float scale = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vbuf = new VertexBuffer;
  vbuf->setPositions (poss, scale, bias);
  vbuf->setColors (cols);
  
  int strips[1] = {4};
  int indices[] = {0,1,2,3};

  TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);

  Appearance* app = new Appearance;

  Mesh* mesh = new Mesh (vbuf, tris, app);
  
  
  cout << "hello world\n";

  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (mesh);

  cout << *wld << "\n";




  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
