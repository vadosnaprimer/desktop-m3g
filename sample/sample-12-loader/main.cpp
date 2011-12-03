#include "m3g/m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
World* wld = NULL;
int fovy;
float near;
float far;

static
void draw_string (int x, int y, const char* s)
{
    while (*s) {
        glWindowPos2i (x+=8, y);
        glutBitmapCharacter (GLUT_BITMAP_8_BY_13, *s++);
    }
}

static
void display (void)
{
    Graphics3D* g3d = Graphics3D::getInstance();
    g3d->render (wld);

    draw_string (10, 287, "space : pause/resume");
    glutSwapBuffers();
}

static
void reshape (int width, int height)
{
    Graphics3D* g3d = Graphics3D::getInstance();
    g3d->setViewport (0,0,width,height);
    Camera* cam = wld->getActiveCamera ();
    cam->setPerspective (45, width/(float)height, 0.1, 1000);
}

static
void quit ()
{
    for (int i = 0; i < (int)objs.size(); i++) {
        delete objs[i];
    }
    Graphics3D* g3d = Graphics3D::getInstance();
    delete g3d;
    exit (0);
}


int   world_time = 0;
bool  stopped    = true;
float angle      = 0;

float rad (float degree) 
{
    return degree/(180.0/M_PI);
}

static int frame = 0;

void idle ()
{
    if (stopped)
        return;

    cout << "frame = " << frame++ << "\n";

    world_time = world_time + 20;
    wld->animate (world_time);

    //float from_x = 0;
    //float from_y = 10*sin(rad(angle));
    //float from_z = 10*cos(rad(angle));
    //cam->lookAt (from_x, from_y, from_z,
    //             0, 0, 0,
    //             0, 1, 0);

    glutPostRedisplay ();
}

static
void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        quit();
        break;
    case ' ':
        stopped = !stopped;
        cout << (stopped ? "stopped" : "running") << "\n";;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

static
void mouse (int button, int state, int x, int y)
{
    Graphics3D* g3d    = Graphics3D::getInstance ();
    float       width  = g3d->getViewportWidth ();
    float       height = g3d->getViewportHeight ();
    Camera*     cam    = wld->getActiveCamera();
    if (state == 0) {
        RayIntersection ri;
        bool hit = wld->pick (-1, x/width, y/height, cam, &ri);
        cout << ((hit) ? "HIT!" : "miss") << "\n";
    }
}


int main (int argc, char** argv)
{
    glutInit            (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow    (argv[0]);
    glutInitWindowSize  (300, 300);

    //objs = Loader::load ("../simple.m3g");
    //objs = Loader::load ("../checker-board.m3g");
    objs = Loader::load ("../kitune-miko.m3g");
    //objs = Loader::load ("../mahosyojo-with-sexy-walking.m3g");

    for (int i = 0; i < (int)objs.size(); i++) {
        wld = dynamic_cast<World*>(objs[i]);
        if (wld) {
            cout << *wld << "\n";
            break;
        }
    }

    for (int i = 0; i < (int)objs.size(); i++) {
        cout << i << " : " << *objs[i] << "\n";
        VertexArray* varry = dynamic_cast<VertexArray*>(objs[i]);
        if (varry) {
            varry->print_raw_data (cout) << "\n";
        }
    }

    Camera* cam = wld->getActiveCamera ();
    float params[4];
    cam->getProjection (params);
    fovy = params[0];
    near = params[2];
    far  = params[3];
    cout << "fovy = " << fovy << "\n";
    cout << "near = " << near << "\n";

    Background* bg = wld->getBackground ();
    if (bg == NULL) {
        bg = new Background ();
        wld->setBackground (bg);
    }
    bg->setColor (0xff3f7fff);

    glutKeyboardFunc (keyboard);
    glutIdleFunc     (idle);
    glutMouseFunc    (mouse);
    glutDisplayFunc  (display);
    glutReshapeFunc  (reshape);
    glutMainLoop     ();

    return 0;
}
