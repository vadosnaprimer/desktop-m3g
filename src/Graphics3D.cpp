#include <iostream>
#include <cmath>
#include "Graphics3D.hpp"
#include "World.hpp"
#include "Camera.hpp"
#include "Graphics.hpp"
#include "Transform.hpp"
#include "Light.hpp"
#include "Exception.hpp"
#include "Property.hpp"
using namespace m3g;
using namespace std;

Graphics3D:: Graphics3D () : 
  viewport(0,0,0,0), depth_buffer_enable(false), hints(0)
{
  // 今だけZテストを常時有効
  glEnable (GL_DEPTH_TEST);

  // プロパティは決めうち
  properties.push_back (new Property("supportAntialiasing"         , 1));
  properties.push_back (new Property("supportTrueColor"            , 1));
  properties.push_back (new Property("supportDithering"            , 1));
  properties.push_back (new Property("supportMipmapping"           , 1));
  properties.push_back (new Property("supportPerspectiveCorrection", 1));
  properties.push_back (new Property("supportLocalCameraLighting"  , 1));
  properties.push_back (new Property("maxLights"                   , 8));
  properties.push_back (new Property("maxViewportWith"             , 2048));
  properties.push_back (new Property("maxViewportHeight"           , 2048));
  properties.push_back (new Property("maxViewportDimension"        , 2048));
  properties.push_back (new Property("maxTextureDimension"         , 2048));
  properties.push_back (new Property("maxSpriteCropDimension"      , 2048));
  properties.push_back (new Property("maxTransformsPerVertex"      , 2));
  properties.push_back (new Property("numTextureUnits"             , 4));
}

Graphics3D:: ~Graphics3D ()
{
}  

int Graphics3D:: addLight (Light* light, Transform& transform)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, addLight is not implemented.");
  return 0;
}

void Graphics3D:: bindTarget (Graphics* g, bool depth_buffer_enabled, int hints)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, bindTarget is not implemented.");
}


void Graphics3D:: clear (Background* background)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, clear is not implemented.");
}

Camera* Graphics3D:: getCamera (const Transform& transform)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, getCamera is not implemented.");
  return 0;
}

float Graphics3D:: getDepthRangeFar () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, getDepthRangeFar is not implemented.");
  return 0;
}

float Graphics3D:: getDepthRangeNear () const
{
  throw NotImplementedException (__FILE__, __func__, "Soryy, getDepthNear is not implemented.");
  return 0;
}

int Graphics3D:: getHints () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, getHints is not implemented.");
  return 0;
}

Graphics3D* Graphics3D:: getInstance ()
{
  static Graphics3D* g3d = new Graphics3D;
  return g3d;
}

Light* Graphics3D:: getLight (int index, const Transform& transform) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, getLight is not implemented.");

  return 0;
}

int Graphics3D:: getLightCount () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, getLightCount is not implemented.");

  return 0;
}

std::vector<Property*> Graphics3D:: getProperties () const
{
  return properties;
}

void* Graphics3D:: getTarget () const
{
  throw NotImplementedException (__FILE__, __func__, "getTarget is not implemented.");

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
  throw NotImplementedException (__FILE__, __func__, "Sorry, isDepthBufferEnabled() is not implemented.");
  return 0;
}

void Graphics3D:: releaseTarget () const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, releaseTraget() is not implemented.");
}

void Graphics3D:: render (Node* node, Transform* transform) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, immediate render mode is not implemented.");
}

void Graphics3D:: render (VertexBuffer* vertices, IndexBuffer* triangles, Appearance* apperance, Transform& transform) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, immediate render mode is not implemented.");
}

void Graphics3D:: render (VertexBuffer* vertices, IndexBuffer* triangles, Appearance* apperance, Transform& transform, int scope) const
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, immediate render mode is not implemented.");
}

void Graphics3D:: render (World* world) const
{
  cout << "Graphics3D: レンダー " << world->getChildCount() << " ノード\n";

  // pass 0 for Background, Camera.
  world->render (0);

  // pass 1 for Lights.
  world->render (1);

  // pass 2 for Scene nodes.
  world->render (2);

  /*
  // This is for Debug.
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
  throw NotImplementedException (__FILE__, __func__, "Sorry, resetLights is not implemented.");
}

void Graphics3D:: setCamera (Camera* camera, const Transform& transform)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, setCamera is not implemented.");
}

void Graphics3D:: setDepthRange (float near, float far)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry setDepthRange is not implemented.");
}

void Graphics3D:: setLight (int index, Light* light, const Transform& transform)
{
  throw NotImplementedException (__FILE__, __func__, "Sorry, setLight is not implemented.");
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

