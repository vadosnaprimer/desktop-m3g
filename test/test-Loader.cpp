#include <unittest++/UnitTest++.h>
#include <iostream>
#include "Loader.hpp"
using namespace std;
using namespace m3g;


TEST (Loader_load)
{
  std::vector<Object3D*> objs = Loader::load ("simple.m3g");

  CHECK_EQUAL (12, objs.size());

  // 注意：M3Gの仕様ではオブジェクトインデックスは１から始まる。
  // 0番はダミー(=0)、１番はヘッダーオブジェクト(=0),
  // 使用するのは２番から
  CHECK (objs[0] != NULL);
  
}

