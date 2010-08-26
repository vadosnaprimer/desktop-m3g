#include "m3g.hpp"
#include <GL/glut.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include "data.hpp"
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
World* wld = 0;
Light* lgh = 0;

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

int animation_time = 0;

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q': {
        quit ();
        break;
    }
    case 's': {
        lgh->setMode (Light::SPOT);
        cout << "Swith to SPOT light.";
        break;
    }
    case 'o': {
        lgh->setMode (Light::OMNI);
        cout << "Swith to OMNI light.";
        break;
    }
    case 'd': {
        lgh->setMode (Light::DIRECTIONAL);
        cout << "Swith to OMNI light.";
        break;
    }
    case ' ':
        cout << "glut: Space, time = " << animation_time << "\n";
        wld->animate (animation_time);
        animation_time += 2;
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

    KeyframeSequence* keyframe_light_color = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
    float frame_light_color[4][3] = {{1,1,0}, {0,1,0}, {1,1,0}, {1,0,0}};
    keyframe_light_color->setKeyframe (0, 0,   frame_light_color[0]);
    keyframe_light_color->setKeyframe (1, 100, frame_light_color[1]);
    keyframe_light_color->setKeyframe (2, 200, frame_light_color[2]);
    keyframe_light_color->setRepeatMode (KeyframeSequence::LOOP);
    keyframe_light_color->setValidRange (0, 2);
    keyframe_light_color->setDuration (200);

    AnimationTrack* animation_light_color = new AnimationTrack (keyframe_light_color, AnimationTrack::COLOR);
    animation_light_color->setController (controller);


    cout << "positions_values.size = " << sizeof(position_values)/sizeof(position_values[0]) << "\n";
    cout << "normals_values.size = " << sizeof(normal_values)/sizeof(normal_values[0]) << "\n";

    VertexArray*  positions = new VertexArray (840, 3, 2);
    VertexArray*  normals   = new VertexArray (840, 3, 1);
    positions->set (0, 840, position_values);
    normals->set (0, 840, normal_values);

    float         scale    = 1;
    float         bias[3]  = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);
    vertices->setNormals (normals);

    int strips[20] = {42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42};
    TriangleStripArray* tris = new TriangleStripArray (0, 20, strips);

    Material* mat = new Material;
    mat->setColor (Material::DIFFUSE, 0xffffffff);

    Appearance* app = new Appearance;
    app->setMaterial (mat);

    Mesh* mesh = new Mesh (vertices, tris, app);

    Camera* cam = new Camera;
    cam->lookAt (0,20,20,
                 0,0,0,
                 0,1,0);

    // メッシュは(x,z)平面
    lgh = new Light;
    lgh->setColor (0xffffff00);   // yellow
    lgh->setIntensity (1);
    lgh->setMode (Light::OMNI);
    lgh->translate (0,2,0);
    lgh->postRotate (-90, 1,0,0);
    lgh->setSpotAngle (60);
    lgh->addAnimationTrack (animation_light_color);

    wld = new World;
    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->addChild (lgh);
    wld->addChild (mesh);


    cout << *wld << "\n";

    objs.push_back (controller);
    objs.push_back (keyframe_light_color);
    objs.push_back (animation_light_color);
    objs.push_back (positions);
    objs.push_back (normals);
    objs.push_back (vertices);
    objs.push_back (tris);
    objs.push_back (mat);
    objs.push_back (app);
    objs.push_back (mesh);
    objs.push_back (cam);
    objs.push_back (lgh);
    objs.push_back (wld);

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMainLoop ();

    return 0;
}
