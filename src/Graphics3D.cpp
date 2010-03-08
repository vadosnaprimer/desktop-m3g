#include <iostream>
#include <unordered_map>
#include <cmath>
#include "Graphics3D.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Graphics.hpp"
#include "Transform.hpp"
#include "Light.hpp"
#include "m3gexcept.hpp"
using namespace m3g;
using namespace std;

Graphics3D:: Graphics3D () : 
  viewport(0,0,0,0), depth_buffer_enable(false), hints(0)
{
  // 今だけZテストを常時有効
  // 本当はbindTarget()の中で有効化すべき
  // bindTarget()自体消そうかどうしようか迷い中。
  glEnable (GL_DEPTH_TEST);
}

Graphics3D:: ~Graphics3D ()
{
}  

int Graphics3D:: addLight (Light* light, Transform& transform)
{
    return 0;
}

void Graphics3D:: bindTarget (Graphics* g, bool depth_buffer_enabled, int hints)
{
}

void Graphics3D:: bindTarget (Image2D* i, bool depth_buffer_enabled, int hints)
{
}

void Graphics3D:: clear (Background* background)
{
}

Camera* Graphics3D:: getCamera (const Transform& transform)
{
    return 0;
}

float Graphics3D:: getDepthRangeFar () const
{
    return 0;
}

float Graphics3D:: getDepthRangeNear () const
{
    return 0;
}

int Graphics3D:: getHints () const
{
    return 0;
}

Graphics3D* Graphics3D:: getInstance ()
{
  static Graphics3D* g3d = new Graphics3D;
  return g3d;
}

Light* Graphics3D:: getLight (int index, const Transform& transform) const
{
    return 0;
}

int Graphics3D:: getLightCount () const
{
    return 0;
}

std::unordered_map<const char*, int> Graphics3D:: getProperties () const
{
    unordered_map<const char*, int> m;
    return m;
}

void* Graphics3D:: getTarget () const
{
    return 0;
}

int Graphics3D:: getViewportHeight () const
{
    return viewport.height;
}

int Graphics3D:: getViewportWidth () const
{
    return viewport.width;
}

int Graphics3D:: getViewportX () const
{
    return viewport.x;
}

int Graphics3D:: getViewportY () const
{
    return viewport.y;
}

bool Graphics3D:: isDepthBufferEnabled () const
{
    return 0;
}

void Graphics3D:: releaseTarget () const
{
}

void Graphics3D:: render (Node* node, Transform* transform) const
{
  throw not_implemented_error ("Sorry, immediate render mode is not implemented.");
}

void Graphics3D:: render (VertexBuffer* vertices, IndexBuffer* triangles, Appearance* apperance, Transform& transform) const
{
  throw not_implemented_error ("Sorry, immediate render mode is not implemented.");
}

void Graphics3D:: render (VertexBuffer* vertices, IndexBuffer* triangles, Appearance* apperance, Transform& transform, int scope) const
{
  throw not_implemented_error ("Sorry, immediate render mode is not implemented.");
}

void Graphics3D:: render (World* world) const
{
  cout << "Graphics3D: レンダー " << world->getChildCount() << " ノード\n";

  // Camera should be first.
  world->render (0);

  //  Camera* cam = world->getActiveCamera();
  //  cam->render ();

    // Fist pass for Lights.
    //Light::resetGLIndex();
    world->render (1);

    // Second pass for Objects.
    world->render (2);

    /*
    // デバッグ用トライアングル。そのうち消す。
    glDisable (GL_LIGHTING);
    for (int i = 0; i < MAX_TEXTURE_UNITS; i++) {
      glActiveTexture (GL_TEXTURE0+i);
      glDisable (GL_TEXTURE_2D);
    }
    glActiveTexture (GL_TEXTURE0);

    glBegin (GL_TRIANGLES);
    glColor3f (1,1,0);
    glVertex3f (1,1,0);
    glVertex3f (0,0,0);
    glVertex3f (-1,1,0);
    glColor3f (1,1,1);
    glEnd();
    */
}

void Graphics3D:: resetLights ()
{
}

void Graphics3D:: setCamera (Camera* camera, const Transform& transform)
{
}

void Graphics3D:: setDepthRange (float near, float far)
{
}

void Graphics3D:: setLight (int index, Light* light, const Transform& transform)
{
}

void Graphics3D:: setViewport (int x, int y, int width, int height)
{
  viewport.x      = x;
  viewport.y      = y;
  viewport.width  = width;
  viewport.height = height;

  //cout << "Graphcs3D: Viewport = " << x << ", " << y << ", " << width << ", " << height << "\n";
  glViewport (viewport.x, viewport.y, viewport.width, viewport.height);
}

