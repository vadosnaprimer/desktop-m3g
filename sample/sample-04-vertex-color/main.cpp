#include "m3g/m3g.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
World* wld = NULL;

static
void draw_string (int x, int y, const char* s)
{
    while (*s) {
        glWindowPos2i (x+=8, y);
        glutBitmapCharacter (GLUT_BITMAP_8_BY_13, *s++);
    }
}

static
void display(void)
{
    Graphics3D* g3d = Graphics3D::getInstance();
    g3d->render (wld);

    draw_string (10, 287, "4 : decrease alpha");
    draw_string (10, 274, "6 : increase alpha");

    glutSwapBuffers();
}

static
void resize(int w, int h)
{
    Graphics3D* g3d = Graphics3D::getInstance();
    g3d->setViewport (0,0,w,h);
    Camera* cam = wld->getActiveCamera ();
    cam->setPerspective (45, w/(float)h, 0.1, 100);
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

static float alpha = 1;

static
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        quit ();
        break;
    case '4':
        alpha *= 0.95;
        if (alpha < 0.4)
            alpha = 0.4;
        cout << "main: node_alpha = " << alpha << "\n";
        wld->setAlphaFactor (alpha);
        break;
    case '6':
        alpha *= 1.05;
        if (alpha > 1.0)
            alpha = 1.0;
        cout << "main: node_alpha = " << alpha << "\n";
        wld->setAlphaFactor (alpha);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main (int argc, char** argv)
{
    glutInit            (&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow    (argv[0]);
    glutInitWindowSize  (300, 300);
    glewInit            ();

    VertexArray* positions         = new VertexArray (4, 3, 2);
    short        position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    positions->set (0, 4, position_values);

    VertexArray*  colors           = new VertexArray (4, 4, 1);
    unsigned char color_values[]   = {255,0,0,255,  0,255,0,255,  0,0,255,255,  255,255,255,255};
    colors->set (0, 4, (char*)color_values);

    float scale   = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setColors    (colors);

    int indices[] = {0,1,2,3};
    int strips[]  = {4};
    TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);

    CompositingMode* cmp = new CompositingMode;
    cmp->setBlending (CompositingMode::ALPHA);

    Material* mat = new Material;
    mat->setVertexColorTrackingEnable (true);

    Appearance* app = new Appearance;
    app->setMaterial (mat);
    app->setCompositingMode (cmp);

    Mesh* mesh  = new Mesh (vertices, tris, app);

    Camera* cam = new Camera;
    cam->translate (0,0,5);

    wld = new World;
    wld->setActiveCamera (cam);
    wld->addChild (cam);
    wld->addChild (mesh);

    cout << *wld << "\n";

    objs.push_back (positions);
    objs.push_back (colors);
    objs.push_back (vertices);
    objs.push_back (tris);
    objs.push_back (mat);
    objs.push_back (cmp);
    objs.push_back (app);
    objs.push_back (mesh);
    objs.push_back (cam);
    objs.push_back (wld);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop ();

    return 0;
}
