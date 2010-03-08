#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Appearance.hpp"
#include "PolygonMode.hpp"
#include "CompositingMode.hpp"
#include "Image2D.hpp"
#include "Texture2D.hpp"
#include "Material.hpp"
#include "Fog.hpp"
using namespace std;
using namespace m3g;


TEST (Appearance_default_variables)
{
  Appearance* app = new Appearance;

  CHECK_EQUAL (OBJTYPE_APPEARANCE, app->getObjectType());
  CHECK_EQUAL (0, app->getLayer());
  CHECK_EQUAL ((PolygonMode*)0, app->getPolygonMode());
  CHECK_EQUAL ((CompositingMode*)0, app->getCompositingMode());
  CHECK_EQUAL ((Texture2D*)0, app->getTexture(0));  // うちのGF9500だと4つ
  CHECK_EQUAL ((Texture2D*)0, app->getTexture(1));  // うちのGF9500だと4つ
  CHECK_EQUAL ((Material*)0, app->getMaterial());
  CHECK_EQUAL ((Fog*)0, app->getFog());

  delete app;
}

TEST (Appearance_set_variables)
{
  Appearance*  app   = new Appearance;
  CompositingMode* cmode = new CompositingMode;
  Fog*         fog   = new Fog;
  Material*    mat   = new Material;
  PolygonMode* pmode = new PolygonMode;
  Image2D*     img   = new Image2D (Image2D::RGBA, 64, 48);
  Texture2D*   tex   = new Texture2D (img);

  app->setCompositingMode (cmode);
  app->setFog (fog);
  app->setLayer (1);
  app->setMaterial (mat);
  app->setPolygonMode (pmode);
  app->setTexture (1, tex);

  CHECK_EQUAL (1, app->getLayer());
  CHECK_EQUAL (pmode, app->getPolygonMode());
  CHECK_EQUAL (cmode, app->getCompositingMode());
  CHECK_EQUAL ((Texture2D*)0, app->getTexture(0));  // うちのGF9500だと4つ
  CHECK_EQUAL (tex, app->getTexture(1));            // うちのGF9500だと4つ
  CHECK_EQUAL (mat, app->getMaterial());
  CHECK_EQUAL (fog, app->getFog());

  delete img;
  delete tex;
  delete pmode;
  delete mat;
  delete fog;
  delete cmode;
  delete app;
}
