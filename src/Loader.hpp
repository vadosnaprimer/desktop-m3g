#ifndef __LOADER_HPP__
#define __LOADER_HPP__

#include <vector>
#include <iostream>

namespace m3g {

class Object3D;

/**
 * m3gファイルのローダー。インスタンス化不可.
 */
class Loader
{

public:
    /**
     * コンストラクタ.
     */
    Loader ();
    /**
     * コンストラクタ.
     */
    ~Loader ();

    /**
     * 与えられたバイトストリームのオフセット位置からObject3Dのインスタンスを生成する.
     */
    static std::vector<Object3D*> load (void* data, int offset);

    /**
     * 与えられた名前のリソースからObject3Dのインスタンスを生成する.
     */
    static std::vector<Object3D*> load (const char* name);
};


} // namespace m3g {

#endif






