#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Image2D.hpp"
#include "Exception.hpp"
#include "Loader.hpp"
using namespace std;
using namespace m3g;


TEST (Image2D_default_variables_0)
{
    Image2D* img = new Image2D (Image2D::RGB, 64, 48);

    CHECK_EQUAL (true        , img->isMutable());
    CHECK_EQUAL (64          , img->getWidth());
    CHECK_EQUAL (48          , img->getHeight());
    CHECK_EQUAL (Image2D::RGB, img->getFormat());
  
    delete img;
}

TEST (Image2D_default_variables_1)
{
    unsigned char pixels[64*48*3]; 
    for (int y = 0; y < 48; y++) {
        for (int x = 0; x < 64; x++) {
            pixels[(y*64+x)*3+0] = 255-x*4;   // R
            pixels[(y*64+x)*3+1] = 0;   // G
            pixels[(y*64+x)*3+2] = x*4; // B
        }
    }

    Image2D* img = new Image2D (Image2D::RGB, 64, 48, pixels);

    CHECK_EQUAL (false       , img->isMutable());
    CHECK_EQUAL (64          , img->getWidth());
    CHECK_EQUAL (48          , img->getHeight());
    CHECK_EQUAL (Image2D::RGB, img->getFormat());

    // 目で見て確認
    img->writePNG ("new-image-1.png");

    delete img;
}

TEST (Image2D_default_variables_2)
{
    unsigned char palette_index[64*48]; 
    unsigned char palette      [256*3];

    for (int y = 0; y < 48; y++) {
        for (int x = 0; x < 64; x++) {
            palette_index[y*64+x] = x*4;
        }
    }
    for (int i = 0; i < 256; i++) {
        palette[i*3+0] = 255-i;  // R
        palette[i*3+1] = 0;  // G
        palette[i*3+2] = i;  // B
    }

    Image2D* img = new Image2D (Image2D::RGB, 64, 48, palette_index, palette);

    CHECK_EQUAL (false       , img->isMutable());
    CHECK_EQUAL (64          , img->getWidth());
    CHECK_EQUAL (48          , img->getHeight());
    CHECK_EQUAL (Image2D::RGB, img->getFormat());

    // 目で見て確認
    img->writePNG ("new-image-2.png");

    delete img;
}

TEST (Image2D_set)
{
    Image2D* img = new Image2D (Image2D::RGB, 64, 48);

    unsigned char buf[10*10*3];
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            buf[(y*10+x)*3+0] = x*25;
            buf[(y*10+x)*3+1] = x*25;
            buf[(y*10+x)*3+2] = 255;
        }
    }

    // 目で見て確認
    img->writePNG ("set-image-before.png");

    img->set (10,10,10,10,buf);

    // 目で見て確認
    img->writePNG ("set-image-after.png");

    delete img;
}

TEST (Image2D_writePng)
{
    Image2D* img = dynamic_cast<Image2D*>(Loader::load ("simple.png")[0]);
    CHECK (img != NULL);

    // 目で見て確認
    img->writePNG ("output-simple.png");
}

TEST (Image2D_duplicate)
{
    Image2D* img0 = new Image2D (Image2D::RGB, 64, 48);
    Image2D* img1 = img0->duplicate();

    CHECK_EQUAL (img0->isMutable(), img1->isMutable());
    CHECK_EQUAL (img0->getWidth() , img1->getWidth());
    CHECK_EQUAL (img0->getHeight(), img1->getHeight());
    CHECK_EQUAL (img0->getFormat(), img1->getFormat());
    // duplicate()は深いコピーなので
    CHECK (img0->getOpenGLPointer() != img1->getOpenGLPointer());
}
