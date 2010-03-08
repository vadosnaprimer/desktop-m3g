#ifndef __RAY_INTERSECTION_HPP__
#define __RAY_INTERSECTION_HPP__

#include <iosfwd>

namespace m3g {

class Node;

/**
 * Groupのpick関数によって生成され、交差点の情報を収納するクラス.
 */
class RayIntersection
{
public:
    /**
     * デフォルト値のコンストラクタ.
     */
    RayIntersection ();

    /**
     * デストラクタ.
     */
    ~RayIntersection ();

    /**
     * ピック光線の交差地点までの距離を取得する.
     */
    float getDistance () const;

    /**
     * ピックされたMeshまたはSprite3Dクラスを取得する.
     */
    Node* getIntersected () const;

    /**
     * 交差地点のサーフェス法線のXコンポーネントの取得.
     */
    float getNormalX () const;

    /**
     * 交差地点のサーフェス法線のYコンポーネントの取得.
     */
    float getNormalY () const;

    /**
     * 交差地点のサーフェス法線のZコンポーネントの取得.
     */
    float getNormalZ () const;

    /**
     * ピック光線の原点(ox,oy,oz)、方向(dx,dy,dz)を取得する。順番はこの順.
     */
    void getRay (float* ray) const;

    /**
     * メッシュの交差した地点のサブメッシュのインデックスを返す.
     */
    int getSubmeshIndex () const;

    /**
     * ピックしたMesh,Sprite3Dの交差地点のテクスチャー座標Sを返す.
     */
    float getTextureS (int index) const;

    /**
     * ピックしたMesh,Sprite3Dの交差地点のテクスチャー座標Tを返す.
     */
    float getTextureT (int index) const;

};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::RayIntersection& ri);

#endif
