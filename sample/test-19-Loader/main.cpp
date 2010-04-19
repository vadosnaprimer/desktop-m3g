#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>
#include <cstdlib>
using namespace std;
using namespace m3g;
#include <typeinfo>

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
  Camera* cam = wld->getActiveCamera ();
  cam->setPerspective (45, w/(float)h, 0.1, 10000);
}


int animation_time = 0;

static void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'q':
    exit(0);
  case ' ':
    wld->animate (animation_time);
    animation_time += 100;
    cout << "animation time = " << animation_time << "\n";
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
  glewInit ();

  //std::vector<Object3D*> objs = Loader::load ("blocklow.m3g");
  //std::vector<Object3D*> objs = Loader::load ("simple.m3g");
  //std::vector<Object3D*> objs = Loader::load ("test.m3g");
  std::vector<Object3D*> objs = Loader::load ("test.m3g");

  for (int i = 0; i < (int)objs.size(); i++) {
    wld = dynamic_cast<World*>(objs[i]);
    if (wld) {
      cout << *wld << "\n";
      break;
    }
  }
  assert (wld != 0);

  vector<Mesh*> meshs;
  vector<Group*> groups;

  int only_once = 1;
  for (int i = 0; i < (int)objs.size(); i++) {
    Group* grp = dynamic_cast<Group*>(objs[i]);
    if (grp != 0) {
      for (int j = 0; j < grp->getChildCount(); j++) {
	  //cout << *grp->getChild (j);
	  Mesh* m = dynamic_cast<Mesh*>(grp->getChild(j));
	  if (m) {
	    if (only_once == 1) {
	       Node* node = m;
	       while ((node = node->getParent())) {
		 cout << "node = "<< node << ", " << typeid(*node).name() << ", ";
		 node->Transformable:: print (cout);
		 groups.push_back (dynamic_cast<Group*>(node));
	       } 
	       only_once = 0;
	       cout << "Group: ";
	       grp->Transformable:: print (cout);
	       cout << "Mesh:  ";
	       m->Transformable:: print (cout);
	       //grp->removeChild (m);
	       //grp->addChild (m);
      	       meshs.push_back (m);
	    } else {
	      //grp->removeChild (m);
      	       meshs.push_back (m);
	    }
	  }

	}
	     //wld->removeChild (grp);
    }
  }
  
    cout << "--------------\n";
    cout << "groups.size() = " << groups.size() << "\n";
    //groups[6]->addChild (meshs[0]);

    //wld->addChild (meshs[0]);

  Camera* cam = wld->getActiveCamera ();
  if (cam == 0) {
    cam = new Camera;
    cam->translate (0,20,80);
    wld->addChild (cam);
    wld->setActiveCamera (cam);
  }
  // cam->lookAt (0,100,300,
  //             0,100,0,
  //             0,1,0);

  Background* bg = new Background;
  bg->setColor (0xff3f7fff);
  wld->setBackground (bg);

  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutMainLoop ();

  return 0;
}
