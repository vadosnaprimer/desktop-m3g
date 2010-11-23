#include "m3g/m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
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
    Camera* cam = wld->getActiveCamera();
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

int world_time = 0;

static void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        quit ();
        break;
    case ' ':
        cout << "main: time = " << world_time << "\n";
        wld->animate (world_time);
        world_time += 2;
    default:
        break;
    }
    glutPostRedisplay();
}


int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow(argv[0]);

    AnimationController* controller = new AnimationController;

    KeyframeSequence* keyframe_fog_far = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
    float frame_fog_far[3][1] = {{10}, {4}, {10}};
    keyframe_fog_far->setKeyframe (0, 0,   frame_fog_far[0]);
    keyframe_fog_far->setKeyframe (1, 100, frame_fog_far[1]);
    keyframe_fog_far->setKeyframe (2, 200, frame_fog_far[2]);
    keyframe_fog_far->setRepeatMode (KeyframeSequence::LOOP);
    keyframe_fog_far->setValidRange (0, 2);
    keyframe_fog_far->setDuration (200);

    AnimationTrack* animation_fog_far = new AnimationTrack (keyframe_fog_far, AnimationTrack::FAR_DISTANCE);
    animation_fog_far->setController (controller);

    VertexArray* positions         = new VertexArray (4, 3, 2);
    short        position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    positions->set (0, 4, position_values);

    float scale   = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setDefaultColor (0xff0000ff);

    int strips[1] = {4};
    TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

    Fog* fog = new Fog;
    fog->setLinear (4, 10);
    fog->setColor (0x000000ff);
    fog->addAnimationTrack (animation_fog_far);
    fog->setMode (Fog::LINEAR);

    Appearance* app = new Appearance;
    app->setFog (fog);

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

    Group* grp = new Group;
    grp->addChild(mesh1);
    grp->addChild(mesh2);
    grp->addChild(mesh3);
    grp->addChild(mesh4);
    grp->addChild(mesh5);

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

    objs.push_back (controller);
    objs.push_back (keyframe_fog_far);
    objs.push_back (animation_fog_far);
    objs.push_back (positions);
    objs.push_back (vertices);
    objs.push_back (tris);
    objs.push_back (fog);
    objs.push_back (app);
    objs.push_back (mesh1);
    objs.push_back (mesh2);
    objs.push_back (mesh3);
    objs.push_back (mesh4);
    objs.push_back (mesh5);
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
