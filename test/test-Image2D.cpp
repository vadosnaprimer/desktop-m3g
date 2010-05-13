#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Image2D.hpp"
#include "Exception.hpp"
using namespace std;
using namespace m3g;


TEST (Image2D_default_variables_0)
{
    Image2D* img = new Image2D (Image2D::RGB, 64, 48);

    CHECK_EQUAL (true, img->isMutable());
    CHECK_EQUAL (64, img->getWidth());
    CHECK_EQUAL (48, img->getHeight());
    CHECK_EQUAL (Image2D::RGB, img->getFormat());
  
    delete img;
}

TEST (Image2D_default_variables_1)
{
    unsigned char buf[64*48*3]; 
    for (int y = 0; y < 48; y++) {
        for (int x = 0; x < 64; x++) {
            buf[(y*64+x)*3+0] = (y*64+x)*3+0; // R
            buf[(y*64+x)*3+1] = (y*64+x)*3+1; // G
            buf[(y*64+x)*3+2] = (y*64+x)*3+2; // B
        }
    }

    Image2D* img = new Image2D (Image2D::RGB, 64, 48, buf);

    CHECK_EQUAL (false, img->isMutable());
    CHECK_EQUAL (64, img->getWidth());
    CHECK_EQUAL (48, img->getHeight());
    CHECK_EQUAL (Image2D::RGB, img->getFormat());

    //CHECK_EQUAL (0x00020100, img->get(0,0));
    //CHECK_EQUAL (0x009f9e9d, img->get(31,23));
    //CHECK_EQUAL (0x00fffefd, img->get(63,47));

}

TEST (Image2D_default_variables_2)
{
    try {
        unsigned char buf[64*48*3]; 
        unsigned char pallet[256];
        Image2D* img = new Image2D (Image2D::ALPHA, 64, 48, buf, pallet);
        img->getWidth();
    } 
    catch (NotImplementedException& e) {
        // Palleted image is not supported.
        // it will raise NotImplementedException
    }
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

    img->write_ppm ("before.ppm");
    img->set (10,10,10,10,buf);
    img->write_ppm ("after.ppm");
    //CHECK_EQUAL (0x00020100, img->get(10,10));
    //CHECK_EQUAL (0x002b2a29, img->get(19,19));

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
    CHECK (img0->getOpenGLData() != img1->getOpenGLData());
}
