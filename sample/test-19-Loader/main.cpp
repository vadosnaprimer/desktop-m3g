#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cassert>
#include <cstdlib>
using namespace std;
using namespace m3g;
#include <typeinfo>

std::vector<Object3D*> objs;
World* wld = 0;
int file_index = 1;

void display(void)
{
  Graphics3D* g3d = Graphics3D::getInstance();

  //char name[256];
  //sprintf (name, "%03d.png", file_index++);
  //int width  = glutGet (GLUT_WINDOW_WIDTH);
  //int height = glutGet (GLUT_WINDOW_HEIGHT);
  //Image2D* img = new Image2D (Image2D::RGBA, width, height);
  //g3d->bindTarget (img);

  g3d->render (wld);

  //g3d->releaseTarget ();
  //img->writePNG (name);
  //delete img;

  glutSwapBuffers();
}

void resize(int w, int h)
{
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->setViewport (0,0,w,h);
  Camera* cam = wld->getActiveCamera ();
  cam->setPerspective (45, w/(float)h, 0.1, 10000);
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

int world_time = 0;

static void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    quit();
    break;
  case ' ':
    wld->animate (world_time);
    world_time += 33;
    cout << "main: time = " << world_time << "\n";
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

  //objs = Loader::load ("simple.m3g");
  objs = Loader::load ("test.m3g");

  for (int i = 0; i < (int)objs.size(); i++) {
    wld = dynamic_cast<World*>(objs[i]);
    if (wld) {
      cout << *wld << "\n";
      break;
    }
  }
  assert (wld != 0);

  for (int i = 0; i < (int)objs.size(); i++) {
    Node* node = dynamic_cast<Node*>(objs[i]);
    if (node) {
      node->setAlphaFactor(1);
    }
    //cout << *objs[i] << "\n";
  }


  Background* bg = wld->getBackground ();
  if (bg == 0) {
    bg = new Background;
    wld->setBackground (bg);
  }
  bg->setColor (0xff3f7fff);

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
