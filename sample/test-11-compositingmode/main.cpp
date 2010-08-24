#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;
using namespace m3g;

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
    Camera* cam = wld->getActiveCamera();
    cam->setPerspective (45, w/(float)h, 1, 1000);
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

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        quit ();
        break;
    case ' ':
        cout << "main: time = " << world_time << "\n";
        wld->animate (world_time);
        world_time += 2;
        break;
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

    AnimationController* controller = new AnimationController;

    KeyframeSequence* keyframe_sequence = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
    float values[3][3] = {{0,0,0}, {0,0,-6}, {0,0,0}};
    keyframe_sequence->setKeyframe (0, 0,   values[0]);
    keyframe_sequence->setKeyframe (1, 100, values[1]);
    keyframe_sequence->setKeyframe (2, 200, values[2]);
    keyframe_sequence->setRepeatMode (KeyframeSequence::LOOP);
    keyframe_sequence->setValidRange (0, 2);
    keyframe_sequence->setDuration (200);

    AnimationTrack* animation_track = new AnimationTrack (keyframe_sequence, AnimationTrack::TRANSLATION);
    animation_track->setController (controller);

    VertexArray* positions         = new VertexArray (4, 3, 2);
    short        position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    positions->set (0, 4, position_values);

    float scale   = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setDefaultColor (0x3f7f7fff);

    int strips[1] = {4};
    TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

    CompositingMode* cmp = new CompositingMode;
    cmp->setBlending (CompositingMode::ALPHA);
    //cmp->setDepthTestEnable (false);
    cmp->setDepthWriteEnable (false);
    cmp->setAlphaThreshold (0.0);

    Material* mat = new Material;
    mat->setColor (Material::DIFFUSE, 0x4f7f7fff);

    Appearance* app = new Appearance;
    app->setCompositingMode (cmp);
    app->setMaterial (mat);

    Mesh* mesh1 = new Mesh (vertices, tris, app);
    mesh1->translate (0,0,-1);

    Mesh* mesh2 = new Mesh (vertices, tris, app);
    mesh2->translate (0,0,-2);

    Mesh* mesh3 = new Mesh (vertices, tris, app);
    mesh3->translate (0,0,-3);

    Mesh* mesh4 = new Mesh (vertices, tris, app);
    mesh4->translate (0,0,-4);

    Mesh* mesh5 = new Mesh (vertices, tris, app);
    mesh5->translate (0,0,-5);


    CompositingMode* cmp2 = new CompositingMode;
    cmp2->setBlending (CompositingMode::REPLACE);
    //cmp2->setDepthTestEnable (false);
    //cmp2->setDepthWriteEnable (false);

    Material* mat2 = new Material;
    mat2->setColor (Material::DIFFUSE, 0xff7f7f7f);

    Appearance* app2 = new Appearance;
    app2->setCompositingMode (cmp2);
    app2->setMaterial (mat2);

    Mesh* mesh10 = new Mesh (vertices, tris, app2);
    mesh10->addAnimationTrack (animation_track);


    Group* grp = new Group;
    grp->addChild(mesh1);
    grp->addChild(mesh2);
    grp->addChild(mesh3);
    grp->addChild(mesh4);
    grp->addChild(mesh5);
    grp->addChild(mesh10);

    Camera* cam = new Camera;
    cam->lookAt (3,0,3, 0,0,-2, 0,1,0);

    Background* bg = new Background;
    bg->setColor (0xff3f3f3f);

    wld = new World;
    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->addChild (grp);
    wld->setBackground (bg);

    cout << *wld << "\n";

    objs.push_back (positions);
    objs.push_back (vertices);
    objs.push_back (tris);
    objs.push_back (cmp);
    objs.push_back (mat);
    objs.push_back (app);
    objs.push_back (cmp2);
    objs.push_back (mat2);
    objs.push_back (app2);
    objs.push_back (mesh1);
    objs.push_back (mesh2);
    objs.push_back (mesh3);
    objs.push_back (mesh4);
    objs.push_back (mesh5);
    objs.push_back (mesh10);
    objs.push_back (grp);
    objs.push_back (cam);
    objs.push_back (bg);
    objs.push_back (wld);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop ();

    return 0;
}
