#include "m3g/m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
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
    Camera* cam = wld->getActiveCamera ();
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

static float alpha = 1;

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        quit ();
        break;
    case ' ':
        cout << "main: node_alpha = " << alpha << "\n";
        wld->setAlphaFactor (alpha);
        alpha *= 0.95;
        if (alpha < 0.2)
            alpha = 1;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow (argv[0]);

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
