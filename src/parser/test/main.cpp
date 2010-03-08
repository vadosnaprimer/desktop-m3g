#include "M3GParser.hpp"
#include "m3g.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace m3g;
using namespace std;
const char* file_name = "untitled.m3g";

World* wld = NULL;

void display ()
{
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->render (wld);
  glutSwapBuffers ();
}

void resize (int w, int h)
{
  Graphics3D* g3d = Graphics3D::getInstance();
  g3d->setViewport (0,0,w,h);
  Camera* cam = wld->getActiveCamera();
  cam->setPerspective (60, w/(float)h, 0.1, 100);
}

static int world_time = 0;

static
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
  case 'Q':
  case '\033':
    exit(0);
  case ' ':
    world_time += 33;
    cout << "world_time = " << world_time << "\n";
    wld->animate (world_time);
    break;
  default:
    break;
  }
  glutPostRedisplay ();
}

int main (int argc, char** argv)
{
  if (argc >= 2) {
    file_name = (char*)argv[1];
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutCreateWindow(argv[0]);
  glewInit ();

  vector<Object3D*> objs;

  M3GParser parser (file_name);
  objs = parser.parse ();

  for (int i = 0; i < (int)objs.size(); i++) {
    wld = dynamic_cast<World*>(objs[i]);
    if (wld) {
      break;
    }
  }

  if (!wld) {
    cout << "World is NULL!\n";
    return 0;
  }

cout << "--------------------------\n";
cout << *wld;
cout << "--------------------------\n";

  glutDisplayFunc (display);
  glutReshapeFunc (resize);
  glutKeyboardFunc(keyboard);
  glutMainLoop ();
  return 0;
}
