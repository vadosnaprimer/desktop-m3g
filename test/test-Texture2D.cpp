#include <unittest++/UnitTest++.h>
#include <iostream>
#include "m3g/Texture2D.hpp"
#include "m3g/Image2D.hpp"
using namespace std;
using namespace m3g;


TEST (Texture2D_default_variables)
{
    Image2D*   img = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D* tex = new Texture2D (img);

    CHECK_EQUAL (img, tex->getImage());
    CHECK_EQUAL (Texture2D::WRAP_REPEAT,       tex->getWrappingS());
    CHECK_EQUAL (Texture2D::WRAP_REPEAT,       tex->getWrappingT());
    CHECK_EQUAL (Texture2D::FILTER_BASE_LEVEL, tex->getLevelFilter());
    CHECK_EQUAL (Texture2D::FILTER_NEAREST,    tex->getImageFilter());
    CHECK_EQUAL (Texture2D::FUNC_MODULATE,     tex->getBlending());

    delete img;
    delete tex;
}

TEST (Texure2D_set_variables)
{
    Image2D*   img  = new Image2D(Image2D::RGBA, 64, 64);
    Image2D*   img2 = new Image2D(Image2D::RGBA, 64, 64);
    Texture2D* tex  = new Texture2D (img);

    tex->setBlendColor (0x12345678);
    tex->setBlending (Texture2D::FUNC_BLEND);
    tex->setFiltering (Texture2D::FILTER_LINEAR, Texture2D::FILTER_LINEAR);
    tex->setImage (img2);
    tex->setWrapping (Texture2D::WRAP_CLAMP, Texture2D::WRAP_CLAMP);

    CHECK_EQUAL (img2, tex->getImage());
    CHECK_EQUAL (Texture2D::WRAP_CLAMP,    tex->getWrappingS());
    CHECK_EQUAL (Texture2D::WRAP_CLAMP,    tex->getWrappingT());
    CHECK_EQUAL (Texture2D::FILTER_LINEAR, tex->getLevelFilter());
    CHECK_EQUAL (Texture2D::FILTER_LINEAR, tex->getImageFilter());
    CHECK_EQUAL (Texture2D::FUNC_BLEND,    tex->getBlending());

    delete img2;
    delete img;
    delete tex;
}

TEST (Texure2D_duplicate)
{
    Image2D*   img  = new Image2D(Image2D::RGBA, 64, 64);
    Texture2D* tex0 = new Texture2D (img);

    tex0->setBlendColor (0x12345678);
    tex0->setBlending (Texture2D::FUNC_BLEND);
    tex0->setFiltering (Texture2D::FILTER_LINEAR, Texture2D::FILTER_LINEAR);
    tex0->setImage (img);
    tex0->setWrapping (Texture2D::WRAP_CLAMP, Texture2D::WRAP_CLAMP);

    Texture2D* tex1 = tex0->duplicate();

    CHECK_EQUAL (tex0->getImage()      , tex1->getImage());
    CHECK_EQUAL (tex0->getWrappingS()  , tex1->getWrappingS());
    CHECK_EQUAL (tex0->getWrappingT()  , tex1->getWrappingT());
    CHECK_EQUAL (tex0->getLevelFilter(), tex1->getLevelFilter());
    CHECK_EQUAL (tex0->getImageFilter(), tex1->getImageFilter());
    CHECK_EQUAL (tex0->getBlending()   , tex1->getBlending());

    delete img;
    delete tex0;
    delete tex1;
}

TEST (Texture2D_find)
{
    Image2D*   img = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D* tex = new Texture2D (img);
    
    img->setUserID (100);
    tex->setUserID (101);

    CHECK_EQUAL (img, img->find(100));
    CHECK_EQUAL (tex, tex->find(101));

    delete img;
    delete tex;
}

TEST (Texture2D_getReferences)
{
    Image2D*   img = new Image2D (Image2D::RGBA, 64, 64);
    Texture2D* tex = new Texture2D (img);

    int n;
    Object3D* objs[1];
    
    n = tex->getReferences (objs);

    CHECK_EQUAL (1, n);
    CHECK_EQUAL (img, objs[0]);

    delete img;
    delete tex;
}

