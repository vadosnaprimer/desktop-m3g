#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
World* wld = 0;
float width;
float height;

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
    cam->setPerspective (90, w/(float)h, 1, 100);
    //cam->setPerspective (30, w/(float)h, 1, 100);
    //cam->setParallel (2, w/(float)h, 1, 100);
    cout << "camera = " << *cam << "\n";
    width  = w;
    height = h;
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

void mouse (int button, int state, int x, int y)
{
    cout << "mouse, button=" << button;
    cout << ", state=" << state;
    cout << ", x=" << x << ", y=" << y << "\n";
    Camera* cam = wld->getActiveCamera();
    RayIntersection ri;
    bool hit = wld->pick (-1, x/width, y/height, cam, &ri);
    cout << ((hit) ? "HIT!" : "miss") << "\n";
    if (hit) {
        float nx = ri.getNormalX();
        float ny = ri.getNormalY();
        float nz = ri.getNormalZ();
        int   submesh_index = ri.getSubmeshIndex();
        cout << "normal = " << Vector(nx,ny,nz) << "\n";
        cout << "submesh index = " << submesh_index << "\n";
    }
}

void keyboard (unsigned char key, int x, int y)
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
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
    glutCreateWindow(argv[0]);
    glewInit ();

    VertexArray* positions         = new VertexArray (4, 3, 2);
    short        position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    positions->set (0, 4, position_values);

    VertexArray* normals           = new VertexArray (4, 3, 1);
    char         normal_values[]   = {0,0,127, 0,127,0, 0,0,127, 0,127,0};
    normals->set (0, 4, normal_values);

    VertexArray* tex_coords         = new VertexArray (4, 2, 4);
    float        tex_coord_values[] = {1,0, 1,1, 0,0, 0,1};
    tex_coords->set (0, 4, tex_coord_values);

    float scale   = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setNormals   (normals);
    vertices->setTexCoords (0, tex_coords, scale, bias);
  
    int strips[2][1]  = {{3}, {3}};
    int indices[2][3] = {{0,1,2}, {1,2,3}};

    IndexBuffer* submesh[2];
    submesh[0] = new TriangleStripArray (indices[0], 1, strips[0]);
    submesh[1] = new TriangleStripArray (indices[1], 1, strips[1]);

    Appearance* app[2];
    app[0]     = new Appearance;
    app[1]     = new Appearance;

    Mesh* mesh = new Mesh (vertices, 2, submesh, app);
  
    Background* bg = new Background;
    //bg->setColor (0xff0000ff);
    bg->setColor (0xff66380e);

    Camera* cam = new Camera;
    cam->translate (0,0,2);

    wld = new World;
    wld->setBackground (bg);
    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->addChild (mesh);

    wld->translate (0,0,-20);

    cout << *wld << "\n";

    objs.push_back (positions);
    objs.push_back (vertices);
    objs.push_back (submesh[0]);
    objs.push_back (submesh[1]);
    objs.push_back (app[0]);
    objs.push_back (app[1]);
    objs.push_back (mesh);
    objs.push_back (bg);
    objs.push_back (cam);
    objs.push_back (wld);

    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop ();

    return 0;
}
