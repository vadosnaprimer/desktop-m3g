#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Loader.hpp"
using namespace std;
using namespace m3g;


TEST (Loader_load_m3g)
{
    std::vector<Object3D*> objs = Loader::load ("simple.m3g");

    CHECK_EQUAL (12, objs.size());

    // 注意：M3Gの仕様ではオブジェクトインデックスは１から始まる。
    // 内部的に0番はNULLが入っているので、それを正しく除去している事を確認している。
    CHECK (objs[0] != NULL);
}

TEST (Loader_load_png)
{
    Image2D* img1 = dynamic_cast<Image2D*>(Loader::load ("indexed.png")[0]);

    CHECK (img1 != NULL);
    CHECK_EQUAL (Image2D::RGB, img1->getFormat());
    CHECK_EQUAL (32          , img1->getWidth());
    CHECK_EQUAL (32          , img1->getHeight());

    img1->writePNG ("output.png");
    Image2D* img2 = dynamic_cast<Image2D*>(Loader::load ("output.png")[0]);

    CHECK (img2 != NULL);
    CHECK_EQUAL (Image2D::RGB, img2->getFormat());
    CHECK_EQUAL (32          , img2->getWidth());
    CHECK_EQUAL (32          , img2->getHeight());
}


