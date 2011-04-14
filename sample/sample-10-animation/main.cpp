#include "m3g/m3g.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
World* wld = NULL;
AnimationController* controller_translation = NULL;
AnimationController* controller_orientation = NULL;

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

    draw_string (10, 287, "u : speed up");
    draw_string (10, 274, "d : speed down");
    draw_string (10, 261, "space : animate");

    glutSwapBuffers();
}

static
void reshape (int w, int h)
{
    Graphics3D* g3d = Graphics3D::getInstance();
    g3d->setViewport (0,0,w,h);
    Camera* cam = wld->getActiveCamera();
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

int   world_time = 0;
float speed      = 1;

static
void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
    case 'u':
        speed = (++speed < 10) ? speed : 10;
        controller_orientation->setSpeed (speed, world_time);
        cout << "main: speed = " << speed << "\n";
        break;
    case 'd':
        speed = (--speed > 0) ? speed : 1;
        controller_orientation->setSpeed (speed, world_time);
        cout << "main: speed = " << speed << "\n";
        break;
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
    glutInit            (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow    (argv[0]);
    glutInitWindowSize  (300, 300);
    glewInit            ();

    controller_translation = new AnimationController;
    controller_translation->setSpeed (1, 0);
    controller_orientation = new AnimationController;
    controller_orientation->setSpeed (2, 0);
  
    //        x,y,z, w  or angle, axis(x,y,z)
    // q0 = [ 0,0,0, 1  or 0 ,0,0,0 ]
    // q1 = [ 0,1,0, 0  or 180 ,0,1,0 ]
    // q2 = [ 0,0,0, -1 or 360 ,0,1,0 ]

    //Quaternion q0 (0, 0,1,0);
    //Quaternion q1 (180, 0,1,0);
    //Quaternion q2 (360, 0,1,0);
    //cout << "q0 = " << q0 << "\n";
    //cout << "q1 = " << q1 << "\n";
    //cout << "q2 = " << q2 << "\n";
    KeyframeSequence* keyframe_mesh_translate   = new KeyframeSequence (4, 3, KeyframeSequence::LINEAR);
    KeyframeSequence* keyframe_mesh_orientation = new KeyframeSequence (3, 4, KeyframeSequence::SLERP);
    float frame_mesh_translate[3][3]= {{0,0,0},
                                       {4,0,0},
                                       {-4,0,0}};
    float frame_mesh_orientation[3][4]= {{0,0,0, 1},
                                         {0,1,0, 0},
                                         {0,0,0, -1}};
    keyframe_mesh_translate->setKeyframe     (0, 0,   frame_mesh_translate[0]);
    keyframe_mesh_translate->setKeyframe     (1, 100, frame_mesh_translate[1]);
    keyframe_mesh_translate->setKeyframe     (2, 300, frame_mesh_translate[2]);
    keyframe_mesh_translate->setKeyframe     (3, 400, frame_mesh_translate[0]);
    keyframe_mesh_translate->setRepeatMode   (KeyframeSequence::LOOP);
    keyframe_mesh_translate->setValidRange   (0, 3);
    keyframe_mesh_translate->setDuration     (400);
    keyframe_mesh_orientation->setKeyframe   (0, 0,   frame_mesh_orientation[0]);
    keyframe_mesh_orientation->setKeyframe   (1, 100, frame_mesh_orientation[1]);
    keyframe_mesh_orientation->setKeyframe   (2, 200, frame_mesh_orientation[2]);
    keyframe_mesh_orientation->setRepeatMode (KeyframeSequence::LOOP);
    keyframe_mesh_orientation->setValidRange (0, 2);
    keyframe_mesh_orientation->setDuration   (200);

    AnimationTrack* animation_mesh_translation = new AnimationTrack (keyframe_mesh_translate, AnimationTrack::TRANSLATION);
    animation_mesh_translation->setController (controller_translation);
    AnimationTrack* animation_mesh_orientation = new AnimationTrack (keyframe_mesh_orientation, AnimationTrack::ORIENTATION);
    animation_mesh_orientation->setController (controller_orientation);

    Background* bg = new Background;
    bg->setColor (0xff7f7f7f);

    Camera* cam = new Camera;
    cam->lookAt (0,0,10,
                 0,0,0,
                 0,1,0);

    VertexArray* positions         = new VertexArray (4, 3, 2);
    short        position_values[] = {1,-1,0, 1,1,0, -1,-1,0, -1,1,0};
    positions->set (0, 4, position_values);

    float scale = 1;
    float bias[3] = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer;
    vertices->setPositions (positions, scale, bias);

    int strips[1]  = {4};
    int indices[4] = {0,1,2,3};
    TriangleStripArray* tris = new TriangleStripArray (indices, 1, strips);

    Material* mat = new Material;
    mat->setColor (Material::DIFFUSE, 0xff0000ff);

    PolygonMode* pmode = new PolygonMode;
    pmode->setCulling (PolygonMode::CULL_NONE);

    Appearance* app = new Appearance;
    app->setMaterial (mat);
    app->setPolygonMode (pmode);

    Mesh* mesh = new Mesh (vertices, tris, app);
    mesh->addAnimationTrack (animation_mesh_translation);
    mesh->addAnimationTrack (animation_mesh_orientation);

    wld = new World;
    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->setBackground (bg);
    wld->addChild (mesh);

    cout << *wld << "\n";

    objs.push_back (controller_translation);
    objs.push_back (controller_orientation);
    objs.push_back (keyframe_mesh_translate);
    objs.push_back (keyframe_mesh_orientation);
    objs.push_back (animation_mesh_translation);
    objs.push_back (animation_mesh_orientation);
    objs.push_back (bg);
    objs.push_back (cam);
    objs.push_back (positions);
    objs.push_back (vertices);
    objs.push_back (tris);
    objs.push_back (mat);
    objs.push_back (pmode);
    objs.push_back (app);
    objs.push_back (mesh);
    objs.push_back (wld);

    glutKeyboardFunc (keyboard);
    glutDisplayFunc  (display);
    glutReshapeFunc  (reshape);
    glutMainLoop     ();

    return 0;
}
