#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/Appearance.hpp"
#include "m3g/PolygonMode.hpp"
#include "m3g/CompositingMode.hpp"
#include "m3g/Image2D.hpp"
#include "m3g/Texture2D.hpp"
#include "m3g/Material.hpp"
#include "m3g/Fog.hpp"
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
    Appearance*      app0  = new Appearance;
    CompositingMode* cmode = new CompositingMode;
    Fog*             fog   = new Fog;
    Material*        mat   = new Material;
    PolygonMode*     pmode = new PolygonMode;
    Image2D*         img   = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D*       tex   = new Texture2D (img);

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


TEST (Appearance_find)
{
    Appearance*      app  = new Appearance;
    CompositingMode* cmode = new CompositingMode;
    Fog*             fog   = new Fog;
    Material*        mat   = new Material;
    PolygonMode*     pmode = new PolygonMode;
    Image2D*         img   = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D*       tex   = new Texture2D (img);

    app->setCompositingMode (cmode);
    app->setFog (fog);
    app->setLayer (1);
    app->setMaterial (mat);
    app->setPolygonMode (pmode);
    app->setTexture (1, tex);

    app  ->setUserID (100);
    cmode->setUserID (101);
    fog  ->setUserID (102);
    mat  ->setUserID (103);
    pmode->setUserID (104);
    img  ->setUserID (105);
    tex  ->setUserID (106);

    CHECK_EQUAL (app  , app->find (100));
    CHECK_EQUAL (cmode, app->find (101));
    CHECK_EQUAL (fog  , app->find (102));
    CHECK_EQUAL (mat  , app->find (103));
    CHECK_EQUAL (pmode, app->find (104));
    CHECK_EQUAL (img  , app->find (105));
    CHECK_EQUAL (tex  , app->find (106));

    delete img;
    delete tex;
    delete pmode;
    delete mat;
    delete fog;
    delete cmode;
    delete app;
}

TEST (Appearance_getReferences)
{
    Appearance*      app  = new Appearance;
    CompositingMode* cmode = new CompositingMode;
    Fog*             fog   = new Fog;
    Material*        mat   = new Material;
    PolygonMode*     pmode = new PolygonMode;
    Image2D*         img   = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D*       tex   = new Texture2D (img);

    app->setCompositingMode (cmode);
    app->setFog (fog);
    app->setLayer (1);
    app->setMaterial (mat);
    app->setPolygonMode (pmode);
    app->setTexture (1, tex);

    Object3D* objs[5];

    // 順番は無保証
    int n = app->getReferences(objs);
    CHECK_EQUAL (5    , n);
    CHECK_EQUAL (pmode, objs[0]);
    CHECK_EQUAL (cmode, objs[1]);
    CHECK_EQUAL (mat  , objs[2]);
    CHECK_EQUAL (tex  , objs[3]);
    CHECK_EQUAL (fog  , objs[4]);

    delete img;
    delete tex;
    delete pmode;
    delete mat;
    delete fog;
    delete cmode;
    delete app;
}


