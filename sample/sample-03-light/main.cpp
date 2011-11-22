#include "m3g/m3g.hpp"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include "data.hpp"
using namespace std;
using namespace m3g;

std::vector<Object3D*> objs;
World* wld  = NULL;
Mesh*  mesh = NULL;
Light* lgh  = NULL;
Texture2D* tex = NULL;

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

    draw_string (10, 287, "t : Texture on/off");
    draw_string (10, 274, "s : Switch to spot light");
    draw_string (10, 261, "d : Switch to directional light");
    draw_string (10, 248, "o : Switch to omni light");
    draw_string (10, 235, "space : change intensity");

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

static int t = 0;

static
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q': {
        quit ();
        break;
    }
    case 's': {
        lgh->setMode (Light::SPOT);
        cout << "Swith to SPOT light.\n";
        break;
    }
    case 'o': {
        lgh->setMode (Light::OMNI);
        cout << "Swith to OMNI light.\n";
        break;
    }
    case 'd': {
        lgh->setMode (Light::DIRECTIONAL);
        cout << "Swith to OMNI light.\n";
        break;
    }
    case 't': {
        Appearance* app = mesh->getAppearance(0);
        if (app->getTexture(0)) {
            app->setTexture (0, NULL);
            cout << "Texture off.\n";
        } else {
            app->setTexture (0, tex);
            cout << "Texture on.\n";
        }
        break;
    }
    case ' ':
        cout << "main: time = " << t << "\n";
        wld->animate (t);
        t += 2;
        break;
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

    AnimationController* ctrl = new AnimationController ();

    KeyframeSequence* keyframe_light_color = new KeyframeSequence (3, 3, KeyframeSequence::LINEAR);
    float light_color[3][3] = {{1,1,1}, {0.5,0.5,0.5}, {1,1,1}};
    keyframe_light_color->setKeyframe   (0, 0,   light_color[0]);
    keyframe_light_color->setKeyframe   (1, 100, light_color[1]);
    keyframe_light_color->setKeyframe   (2, 200, light_color[2]);
    keyframe_light_color->setRepeatMode (KeyframeSequence::LOOP);
    keyframe_light_color->setValidRange (0, 2);
    keyframe_light_color->setDuration   (200);

    AnimationTrack* animation_light_color = new AnimationTrack (keyframe_light_color, AnimationTrack::COLOR);
    animation_light_color->setController (ctrl);

    cout << "positions_values.size = " << sizeof(position_values)/sizeof(position_values[0]) << "\n";
    cout << "normals_values.size   = " << sizeof(normal_values  )/sizeof(normal_values[0])   << "\n";
    cout << "texcoord_values.size  = " << sizeof(texcoord_values)/sizeof(texcoord_values[0]) << "\n";

    VertexArray*  positions = new VertexArray (840, 3, 2);
    VertexArray*  normals   = new VertexArray (840, 3, 1);
    VertexArray*  texcoords = new VertexArray (840, 2, 4);
    positions->set (0, 840, position_values);
    normals->set   (0, 840, normal_values);
    texcoords->set (0, 840, texcoord_values);

    float         scale    = 1;
    float         bias[3]  = {0,0,0};
    VertexBuffer* vertices = new VertexBuffer ();
    vertices->setPositions (positions, scale, bias);
    vertices->setNormals   (normals);
    vertices->setTexCoords (0, texcoords, scale, bias);

    int strips[20] = {42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42};
    TriangleStripArray* tris = new TriangleStripArray (0, 20, strips);
    Material* mat = new Material ();
    mat->setColor (Material::DIFFUSE, 0xffffffff);

    Appearance* app = new Appearance ();
    app->setMaterial (mat);

    Image2D* img = dynamic_cast<Image2D*>(Loader::load ("../kingyo.png")[0]);
    tex = new Texture2D (img);
    app->setTexture (0, tex);

    mesh = new Mesh (vertices, tris, app);

    Camera* cam = new Camera ();
    cam->lookAt (0,20,20,
                 0,0,0,
                 0,1,0);

    // メッシュは(x,z)平面
    lgh = new Light ();
    lgh->setColor     (0x00ffffff);   // white
    lgh->setIntensity (2);            // 少し強め
    lgh->setMode      (Light::OMNI);
    lgh->translate    (0,2,0);
    lgh->postRotate   (-90, 1,0,0);
    lgh->setSpotAngle (60);
    lgh->addAnimationTrack (animation_light_color);

    wld = new World ();
    wld->addChild (cam);
    wld->setActiveCamera (cam);
    wld->addChild (lgh);
    wld->addChild (mesh);

    cout << *wld << "\n";

    objs.push_back (ctrl);
    objs.push_back (keyframe_light_color);
    objs.push_back (animation_light_color);
    objs.push_back (positions);
    objs.push_back (normals);
    objs.push_back (texcoords);
    objs.push_back (vertices);
    objs.push_back (tris);
    objs.push_back (mat);
    objs.push_back (tex);
    objs.push_back (img);
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
