#ifndef __RAY_INTERSECTION_HPP__
#define __RAY_INTERSECTION_HPP__

#include <iosfwd>
#include "m3g/Object.hpp"
#include "m3g/Vector.hpp"

#include <vector>

namespace m3g {

    class Node;
    class Transform;

    /**
     * @~English  A RayInersection objet is filled in by the pick methods in Group.
     *            RayIntersection stores a reference to the intersected Mesh or Sprite3D and information about the intersection point. 
     * @~Japanese Groupのpick関数によって生成され、交差点の情報を収納するクラス.
     */
    class RayIntersection : public Object
    {
        struct Ray {
            Ray (const Vector& o, const Vector& d, float t_) : org(o), dir(d), t(t_) {};
            Vector org;
            Vector dir;
            float  t;
        };

    public:
        /**
         * @~English  Construct sa new RayIntersection object with default values.
         * @~Japanese デフォルト値のコンストラクタ.
         */
        RayIntersection ();

        /**
         * M3G未定義.
         * 第１引数はNodeではなくMeshの方が良いか？
         */
        RayIntersection (Node* node,
                         const Vector& org, const Vector& dir, float t,
                         float u, float v,
                         int vertex_num, int* vertices,
                         int submesh_index);

        /**
         * @~English  Destructs this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        ~RayIntersection ();

        /**
         * @~English  Retrieves the distance from the pick ray origin to the intersection point.
         * @~Japanese ピック光線の交差地点までの距離を取得する.
         */
        float getDistance () const;

        /**
         * @~English  Retrieves the picked Mesh or Sprite 3D object.
         * @~Japanese ピックされたMeshまたはSprite3Dクラスを取得する.
         */
        Node* getIntersected () const;

        /**
         * @~English  Retrieves the X component of the surface normal at the intersection point.
         * @~Japanese 交差地点のサーフェス法線のXコンポーネントの取得.
         */
        float getNormalX () const;

        /**
         * @~English  Retrieves the Y component of the surface normal at the intersection point.
         * @~Japanese 交差地点のサーフェス法線のYコンポーネントの取得.
         */
        float getNormalY () const;

        /**
         * @~English  Retrieves the Z component of the surface normal at the intersection point.
         * @~Japanese 交差地点のサーフェス法線のZコンポーネントの取得.
         */
        float getNormalZ () const;

        /**
         * @~English  Retieves the origin (ox oy oz) and direction(dx dy dz) of the pick ray, inthat order.
         * @~Japanese ピック光線の原点(ox,oy,oz)、方向(dx,dy,dz)を取得する。順番はこの順.
         */
        void getRay (float* ray) const;

        /**
         * @~English  Retrieves the index of the submesh where the intersection point is located within the intersected Mesh.
         * @~Japanese メッシュの交差した地点のサブメッシュのインデックスを返す.
         */
        int getSubmeshIndex () const;

        /**
         * @~English Retrives the S texture coordinate at the intersection point on the picked Mesh or Sprite3D. 
         * @~Japanese ピックしたMesh,Sprite3Dの交差地点のテクスチャー座標Sを返す.
         */
        float getTextureS (int index) const;

        /**
         * @~English Retrives the T texture coordinate at the intersection point on the picked Mesh or Sprite3D. 
         * @~Japanese ピックしたMesh,Sprite3Dの交差地点のテクスチャー座標Tを返す.
         */
        float getTextureT (int index) const;


        /**
         *  レイの座標変換を行うM3G未定義
         */
        void transformRay (const Transform& trans);

        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このオブジェクトの情報を表示する。デバッグ用.
         */
        std::ostream& print (std::ostream& out) const;

    private:

        void setNormal ();
        void setTexCoord (int index);

    private:

        Ray    ray;
        Node*  node;
        float  u, v;
        std::vector<int> vertices;        
        int    submesh_index;

        Vector* normal;
        std::vector<Vector*> tex_coord;
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::RayIntersection& ri);

#endif
