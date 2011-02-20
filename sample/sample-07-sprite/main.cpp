#include "m3g/m3g.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
World* wld = NULL;
float width;
float height;

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

    draw_string (10, 287, "8 : move forward");
    draw_string (10, 274, "2 : move back");
    draw_string (10, 261, "mouse : pick up");

    glutSwapBuffers();
}

static
void reshape (int w, int h)
{
    Graphics3D* g3d = Graphics3D::getInstance();
    g3d->setViewport (0,0,w,h);
    Camera* cam = wld->getActiveCamera();
    width  = w;
    height = h;
    cam->setPerspective (45, width/height, 1, 100);
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

static 
void keyboard (unsigned char key, int x, int y)
{
    Camera* cam = wld->getActiveCamera();
    switch (key) {
    case '2':
        cam->translate (0,0,1);
        break;
    case '8':
        cam->translate (0,0,-1);
        break;
    case 'q':
        quit ();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

static
void mouse (int button, int state, int x, int y)
{
    Camera* cam = wld->getActiveCamera();
    RayIntersection ri;
    bool hit = wld->pick (-1, x/width, y/height, cam, &ri);
    cout << ((hit) ? "HIT!" : "miss") << "\n";
    //if (hit) {
    //    cout << ri << "\n";
    //}
}


int main (int argc, char** argv)
{
    glutInit            (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow    (argv[0]);
    glutInitWindowSize  (300, 300);
    glewInit            ();

    Camera* cam = new Camera;
    cam->lookAt (0,0,5,
                 0,0,0,
                 0,1,0);

    Background* bg = new Background;
    bg->setColor (0xff1f1f7f);

    Image2D* img    = dynamic_cast<Image2D*>(Loader::load ("moe-small.png")[0]);
    int      width  = img->getWidth ();
    int      height = img->getHeight ();

    CompositingMode* cmp = new CompositingMode;
    cmp->setDepthTestEnable (true);

    Appearance* app1 = new Appearance;
    app1->setCompositingMode (cmp);

    Sprite3D*   spr1 = new Sprite3D (true, img, app1);
    spr1->translate (1,0,0);
    spr1->setCrop (0, 0, -width, height);

    Appearance* app2 = new Appearance;
    app2->setCompositingMode (cmp);

    Sprite3D*   spr2 = new Sprite3D (false, img, app2);
    spr2->translate (-1,0,0);
    spr2->setCrop (0, 0, width, height);

    wld = new World;
    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->setBackground (bg);
    wld->addChild (spr1);
    wld->addChild (spr2);

    cout << *wld << "\n";

    objs.push_back (cam);
    objs.push_back (bg);
    objs.push_back (img);
    objs.push_back (cmp);
    objs.push_back (app1);
    objs.push_back (spr1);
    objs.push_back (app2);
    objs.push_back (spr2);
    objs.push_back (wld);

    glutKeyboardFunc (keyboard);
    glutMouseFunc    (mouse);
    glutDisplayFunc  (display);
    glutReshapeFunc  (reshape);
    glutMainLoop     ();

    return 0;
}
