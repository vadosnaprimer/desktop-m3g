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

    CHECK_EQUAL (0, app->getLayer());
    CHECK_EQUAL (0, app->getLayer2());
    CHECK_EQUAL ((PolygonMode*)0,    app->getPolygonMode());
    CHECK_EQUAL ((CompositingMode*)0,app->getCompositingMode());
    CHECK_EQUAL ((Texture2D*)0,      app->getTexture(0));  // うちのGF9500だと4つ
    CHECK_EQUAL ((Texture2D*)0,      app->getTexture(1));  // うちのGF9500だと4つ
    CHECK_EQUAL ((Material*)0,       app->getMaterial());
    CHECK_EQUAL ((Fog*)0,            app->getFog());

    delete app;
}

TEST (Appearance_set_variables)
{
    Appearance*  app   = new Appearance;
    CompositingMode* cmode = new CompositingMode;
    Fog*         fog   = new Fog;
    Material*    mat   = new Material;
    PolygonMode* pmode = new PolygonMode;
    Image2D*     img   = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D*   tex   = new Texture2D (img);

    app->setCompositingMode (cmode);
    app->setFog (fog);
    app->setLayer (1);
    app->setMaterial (mat);
    app->setPolygonMode (pmode);
    app->setTexture (1, tex);

    CHECK_EQUAL (1,             app->getLayer());
    CHECK_EQUAL (2,             app->getLayer2());
    CHECK_EQUAL (pmode,         app->getPolygonMode());
    CHECK_EQUAL (cmode,         app->getCompositingMode());
    CHECK_EQUAL ((Texture2D*)0, app->getTexture(0));         // うちのGF9500だと4つ
    CHECK_EQUAL (tex,           app->getTexture(1));         // うちのGF9500だと4つ
    CHECK_EQUAL (mat,           app->getMaterial());
    CHECK_EQUAL (fog,           app->getFog());


    cmode->setBlending (CompositingMode::ALPHA);
    CHECK_EQUAL (1,             app->getLayer());
    CHECK_EQUAL (3,             app->getLayer2());

    delete img;
    delete tex;
    delete pmode;
    delete mat;
    delete fog;
    delete cmode;
    delete app;
}

TEST (Appearance_duplicate)
{
    Appearance*  app0   = new Appearance;
    CompositingMode* cmode = new CompositingMode;
    Fog*         fog   = new Fog;
    Material*    mat   = new Material;
    PolygonMode* pmode = new PolygonMode;
    Image2D*     img   = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D*   tex   = new Texture2D (img);

    app0->setCompositingMode (cmode);
    app0->setFog (fog);
    app0->setLayer (1);
    app0->setMaterial (mat);
    app0->setPolygonMode (pmode);
    app0->setTexture (1, tex);

    Appearance* app1 = app0->duplicate();


    CHECK_EQUAL (app0->getLayer()          , app1->getLayer());
    CHECK_EQUAL (app0->getPolygonMode()    , app1->getPolygonMode());
    CHECK_EQUAL (app0->getCompositingMode(), app1->getCompositingMode());
    CHECK_EQUAL (app0->getTexture(0)       , app1->getTexture(0));
    CHECK_EQUAL (app0->getTexture(1)       , app1->getTexture(1));
    CHECK_EQUAL (app0->getMaterial()       , app1->getMaterial());
    CHECK_EQUAL (app0->getFog()            , app1->getFog());

    delete img;
    delete tex;
    delete pmode;
    delete mat;
    delete fog;
    delete cmode;
    delete app0;
    delete app1;

}

static int count = 0;
static void func (void* p)
{
    count++;
}

TEST (Appearance_mark)
{
    Appearance*  app   = new Appearance;
    CompositingMode* cmode = new CompositingMode;
    Fog*         fog   = new Fog;
    Material*    mat   = new Material;
    PolygonMode* pmode = new PolygonMode;
    Image2D*     img   = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D*   tex   = new Texture2D (img);

    app->setCompositingMode (cmode);
    app->setFog (fog);
    app->setMaterial (mat);
    app->setPolygonMode (pmode);
    app->setTexture (0, tex);

    app->mark (func);

    CHECK_EQUAL (7, count);

    delete app;
    delete cmode;
    delete fog;
    delete mat;
    delete pmode;
    delete img;
    delete tex;
}
