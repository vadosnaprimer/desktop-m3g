#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
World* wld = 0;
Mesh* mesh = 0;

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

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        quit ();
    default:
        break;
    }
    glutPostRedisplay();
}

void mouse (int button, int state, int x, int y)
{
    cout << "state = " << state << "\n";
}

void idle ()
{
    mesh->postRotate (1, 0,1,0);

    glutPostRedisplay();
}

int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow(argv[0]);

    short        position_values[] =  { 1,-1,1,  1,1,1,  -1,-1,1,  -1,1,1,
                                        -1,-1,-1,  -1,1,-1,  1,-1,-1,  1,1,-1,
                                        -1,1,1,  -1,1,-1,  -1,-1,1,  -1,-1,-1};
    VertexArray* positions         = new VertexArray (12, 3, 2);
    positions->set (0, 12, position_values);

    short        tex_coord_values[] = {1,0, 1,1, 0,0, 0,1,
                                       1,0, 1,1, 0,0, 0,1,
                                       1,0, 0,0, 1,1, 0,1};
    VertexArray* tex_coords         = new VertexArray (12, 2, 2);
    tex_coords->set (0, 12, tex_coord_values);

    float scale   = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setTexCoords (0, tex_coords, scale, bias);
    vertices->setDefaultColor (0xffffffff);
  
    int indices[24] = {0,1,2,3, 2,3,4,5, 4,5,6,7, 6,7,0,1, 1,7,8,9, 0,10,6,11};
    int strips [6]  = {4,4,4,4,4,4};
    TriangleStripArray* tris = new TriangleStripArray (indices, 6, strips);


    Image2D*    img = dynamic_cast<Image2D*>(Loader::load("yumemi.png")[0]);
    Texture2D*  tex = new Texture2D (img);
    Appearance* app = new Appearance;
    app->setTexture (0, tex);


    mesh = new Mesh (vertices, tris, app);
    mesh->translate (0,0,2);
  
    Camera* cam = new Camera;
    cam->lookAt (0,0,10,
                 0,0,0,
                 0,1,0);

    wld = new World;
    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->addChild (mesh);

    cout << *wld << "\n";

    objs.push_back (positions);
    objs.push_back (tex_coords);
    objs.push_back (vertices);
    objs.push_back (tris);
    objs.push_back (img);
    objs.push_back (tex);
    objs.push_back (app);
    objs.push_back (mesh);
    objs.push_back (cam);
    objs.push_back (wld);

    glutKeyboardFunc (keyboard);
    glutMouseFunc    (mouse);
    glutIdleFunc     (idle);
    glutDisplayFunc  (display);
    glutReshapeFunc  (resize);
    glutMainLoop     ();

    return 0;
}
