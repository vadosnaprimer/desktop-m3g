#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
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

void quit ()
{
  for (int i = 0; i < (int)objs.size(); i++) {
    delete objs[i];
  }
  Graphics3D* g3d = Graphics3D::getInstance();
  delete g3d;

  exit (0);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    quit ();
    break;
  default:
    break;
  }
  glutPostRedisplay();
}


int main (int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);

  VertexArray* positions         = new VertexArray (4, 3, 2);
  short        positions_value[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
  positions->set (0, 4, positions_value);

  float scale   = 1;
  float bias[3] = {0,0,0};
  VertexBuffer* vertices = new VertexBuffer;
  vertices->setPositions (positions, scale, bias);
  
  int strips[1] = {4};
  int indices[] = {0,1,2,3};

  TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);

  Material* mat = new Material;
  mat->setColor (Material::DIFFUSE, 0xff7f7fff);

  Appearance* app = new Appearance;
  app->setMaterial (mat);

  Mesh* mesh = new Mesh (vertices, tris, app);
  
  Camera* cam = new Camera;
  cam->translate (0,0,5);

  wld = new World;
  wld->addChild (cam);
  wld->setActiveCamera (cam);
  wld->addChild (mesh);

  cout << *wld << "\n";


  objs.push_back (positions);
  objs.push_back (vertices);
  objs.push_back (tris);
  objs.push_back (mat);
  objs.push_back (app);
  objs.push_back (cam);
  objs.push_back (mesh);
  objs.push_back (wld);

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
