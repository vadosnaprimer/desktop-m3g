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
    default:
        break;
    }
    glutPostRedisplay();
}


int main (int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(argv[0]);

    AnimationController* controller = new AnimationController;

    KeyframeSequence* keyframe_fovy = new KeyframeSequence (3, 1, KeyframeSequence::LINEAR);
    float frame_fovy[3][1] = {{45}, {90}, {45}};
    keyframe_fovy->setKeyframe (0, 0,   frame_fovy[0]);
    keyframe_fovy->setKeyframe (1, 100, frame_fovy[1]);
    keyframe_fovy->setKeyframe (2, 200, frame_fovy[2]);
    keyframe_fovy->setRepeatMode (KeyframeSequence::LOOP);
    keyframe_fovy->setValidRange (0, 2);
    keyframe_fovy->setDuration (200);

    AnimationTrack* animation_fovy = new AnimationTrack (keyframe_fovy, AnimationTrack::FIELD_OF_VIEW);
    animation_fovy->setController (controller);

    short        position_values[] = {10,-10,0, 10,10,0, -10,-10,0, -10,10,0};
    VertexArray* positions         = new VertexArray (4, 3, 2);
    positions->set (0, 4, position_values);

    float scale = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);

    //int strips[20] = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40};
    int strips[1] = {4};
    TriangleStripArray* tris = new TriangleStripArray (0, 1, strips);

    Material* mat = new Material;
    mat->setColor (Material::DIFFUSE, 0xff4c4cb2);  // 0.3, 0.3, 0.7

    Appearance* app = new Appearance;
    app->setMaterial (mat);

    Mesh* mesh = new Mesh (vertices, tris, app);
  

    Camera* cam = new Camera;
    //cam->translate (0,0,10);
    cam->lookAt (0,0,50,
                 0,0,0,
                 0.1,1,0);       
    //Light* lig = new Light;
    cam->addAnimationTrack (animation_fovy);

    wld = new World;
    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->addChild (mesh);
    //  wld->addChild (lig);

    cout << *wld << "\n";

    objs.push_back (controller);
    objs.push_back (keyframe_fovy);
    objs.push_back (animation_fovy);
    objs.push_back (positions);
    objs.push_back (vertices);
    objs.push_back (tris);
    objs.push_back (mat);
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
