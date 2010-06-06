#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__

#include "Object3D.hpp"
#include <iosfwd>

namespace m3g {

    /**
     * @~English  An Appearance component encapsulating material attributes for lighting computations.
     * @~Japanese ライティング計算のためのマテリアル属性をカプセル化したアピアランスの構成要素.
     */
    class Material : public Object3D
    {

    public:
        /**
         * @~English  A parameter to setColor and getColor, specifying that the ambient color component.
         * @~Japanese 環境光(アンビエント)を表す定数.
         */
        static const int AMBIENT  = 1<<10;
        /**
         * @~English  A parameter to setColor and getColor, specifying that the diffuse color component.
         * @~Japanese 拡散反射光(ディフューズ)を表す定数.
         */
        static const int DIFFUSE  = 1<<11;
        /**
         * @~English  A parameter to setColor and getColor, specifying that the emissive color component.
         * @~Japanese 発光を表す定数.
         */
        static const int EMISSIVE = 1<<12;
        /**
         * @~English  A parameter to setColor and getColor, specifying that the specular color component.
         * @~Japanese 鏡面反射光(スペキュラー)を表す定数.
         */
        static const int SPECULAR = 1<<13;

    public:
        /**
         * @~English  Creates a Material object with default values.
         * @~Japanese デフォルト値のコンストラクタ.
         */
        Material ();

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~Material ();


        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual Material* duplicate () const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void addAnimationTrack (AnimationTrack* animation_track);

        /**
         * @~English  Update animatable property.
         * @~Japanese このMaterialをアニメーションする.
         */
        virtual int animate (int world_time);

        /**
         * @~English  Gets the value of the specified color component of this Material.
         * @~Japanese このマテリアルの指定されたカラーコンポーネントの取得.
         */
        int getColor (int target) const;

        /**
         * @~English  Sets the shininess of this Material.
         * @~Japanese このマテリアルのカレントのshininessパラメーターの取得.
         */
        float getShininess () const;

        /**
         * @~English  
         * @~Japanese 頂点カラートラッキングの有効、無効の問い合わせ.
         */
        bool isVertexColorTrackingEnabled () const;

        /**
         * @~English  Sets the given value to the specified color component(s) of this Material.
         * @~Japanese このマテリアルの指定されたカラーコンポーネントの設定.
         */
        void setColor (int target, int argb);


        /**
         * @~English  
         * @~Japanese このマテリアルのshinessパラメーターの設定.
         */
        void setShininess (float shininess);

    
        /**
         * @~English  Enables or disables vertex color tracking.
         * @~Japanese 頂点カラートラッキングの有効化、無効化.
         */
        void setVertexColorTrackingEnable (bool enable);

        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このオブジェクトの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Render this object, for inner use.
         * @~Japanese このオブジェクトをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;

        /**
         * @~English  Render this object, for inner use.
         * @~Japanese このオブジェクトをレンダリングする内部使用の関数.
         */
        static void renderX ();

    private:
        bool  vertex_color_tracking;
        int   ambient_color;
        int   diffuse_color;
        int   emissive_color;
        int   specular_color;
        float shininess;
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Material& m);


#endif
