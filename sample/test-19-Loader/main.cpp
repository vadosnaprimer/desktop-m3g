#include "m3g/m3g.hpp"
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
bool stopped = false;
float angle = 0;

float rad (float degree) 
{
    return degree/(180.0/M_PI);
}

void idle ()
{
    if (stopped)
        return;
    world_time = (world_time + 20) % 6000;
    wld->animate (world_time);

    Camera* cam = wld->getActiveCamera ();
    float from_x = 0;
    float from_y = 10*sin(rad(angle));
    float from_z = 10*cos(rad(angle));
    cam->lookAt (from_x, from_y, from_z,
                 0, 0, 0,
                 0, 1, 0);

    glutPostRedisplay ();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        quit();
        break;
    case ' ':
        stopped = !stopped;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void mouse (int button, int state, int x, int y)
{
    Graphics3D* g3d    = Graphics3D::getInstance ();
    float       width  = g3d->getViewportWidth ();
    float       height = g3d->getViewportHeight ();
    Camera*     cam    = wld->getActiveCamera();
    if (state == 0) {
        cout << "mouse, button=" << button << ", state=" << state << ", x=" << x << ", y=" << y << "\n";
        RayIntersection ri;
        bool hit = wld->pick (-1, x/width, y/height, cam, &ri);
        cout << ((hit) ? "HIT!" : "miss") << "\n";
    }
}


int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (512,512);
    glutCreateWindow(argv[0]);

    //objs = Loader::load ("test.m3g");
    //objs = Loader::load ("checker-board.m3g");
    objs = Loader::load ("kitune-miko.m3g");

    for (int i = 0; i < (int)objs.size(); i++) {
        wld = dynamic_cast<World*>(objs[i]);
        if (wld) {
            cout << *wld << "\n";
            break;
        }
    }
    assert (wld != 0);

    for (int i = 0; i < (int)objs.size(); i++) {
        cout << "i = " << i << " : " << *objs[i] << "\n";
    }

    Camera* cam = wld->getActiveCamera ();
    cam->setTranslation (0, 10, 100);
    cam->setOrientation (0, 0,0,0);
    cam->Transformable:: print (cout) << "\n";
    
    Background* bg = wld->getBackground ();
    if (bg == 0) {
        bg = new Background;
        wld->setBackground (bg);
    }
    bg->setColor (0xff3f7fff);

    glutKeyboardFunc(keyboard);
    glutIdleFunc (idle);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop ();

    return 0;
}
