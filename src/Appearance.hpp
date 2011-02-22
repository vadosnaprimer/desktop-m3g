#ifndef __M3G_APPEARANCE_HPP__
#define __M3G_APPEARANCE_HPP__

#include "m3g/Object3D.hpp"
#include "m3g/m3gdef.hpp"
#include <iosfwd>
#include <vector>

namespace m3g {

    class CompositingMode;
    class Fog;
    class Material;
    class PolygonMode;
    class Texture2D;


    /**
     * @~English  set of component objects that define the rendering attributes of a Mesh or Sprite3D.
     * @~Japanese MeshやSprite3Dなどの”見え方”を定義するレンダリング属性値を保持するオブジェクト要素を保持するコンテナクラス.
     */

    class Appearance : public Object3D
    {

    public:
        /** 
         * @~English  Constructs an Appearance object with default values.
         * @~Japanese Appearanceオブジェクトの作成.
         */
        Appearance ();

        /**
         * @~English  Destruct an Appearance object.
         * @~Japanese このオブジェクトを破壊するデストラクタ.
         */
        virtual ~Appearance ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         * @return 複製されたAppearanceオブジェクト.
         */
        Appearance* duplicate () const;


        /**
         * @~English  Returns the current CompostingMode for this Appearance.
         * @~Japanese このアピアランスのCompositingModeの取得.
         * @return コンポジティングモード要素.
         */
        CompositingMode* getCompositingMode () const;

        /**
         * @~English  Returns the current foggin attributes for this Appearance.
         * @~Japanese このアピアランスのフォグ要素の取得.
         * @return フォグ要素
         */
        Fog* getFog () const;

        /**
         * @~English  Gets the current rendering layer for this Appearance.
         * @~Japanese このアピアランスのレンダリングレイヤーの取得.
         * @return このアピアランスのレンダリングレイヤー番号
         */
        int getLayer () const;

        /**
         * @~English  Gets the current rendering layer including tranceparency for this Appearance, for inner use.
         * @~Japanese このアピアランスの透明度を考慮したレンダリングレイヤーの取得。内部使用専用.
         * @return このアピアランスの透明度を考慮したレンダリングレイヤー番号.
         */
        int getLayer2 () const;

        /**
         * @~English  Returns the current Material for this Appearance.
         * @~Japanese このアピアランスのマテリアル要素の取得.
         * @return マテリアル要素.
         */
        Material* getMaterial () const;

        /**
         * @~English  Returns the current PolygonMode for this Appearance.
         * @~Japanese このアピアランスのポリゴンモード要素の取得.
         * @return ポリゴン要素.
         */
        PolygonMode* getPolygonMode () const;

        /**
         * @~English  Retrieves the current texture image and its attributes for the given texturing unit.
         * @~Japanese 指定されたテクスチャーユニットのテクスチャオブジェクトの取得.
         * @return テクスチャー要素
         */
        Texture2D* getTexture (int index) const;

        /**
         * @~English  Sets the CompositingMode to user for this Appearance.
         * @~Japanese このアピアランスで使用するコンポジティングモードの設定.
         * @param[in] compositing_mode  セットするコンポジティングモード・オブジェクト.
         */
        void setCompositingMode (CompositingMode* compositing_mode);

        /**
         * @~English  Sets the fogging attributes to use for this Appearance.
         * @~Japanese このアピアランスで使用するFogの設定.
         * @param[in] fog セットするフォグ要素.
         */
        void setFog (Fog* fog);

        /**
         * @~English  Sets the rendering layer for this Appearance.
         * @~Japanese このアピアランスのレンダリングレイヤーの設定.
         * @param[in] layer  レイヤー番号の取得
         */
        void setLayer (int layer);

        /**
         * @~English  Sets the Material to use when lighting this Appearance.
         * @~Japanese このアピアランスのMaterialの設定.
         * @param[in] material  マテリアルを表すMaterialオブジェクト.
         */
        void setMaterial (Material* material);

        /**
         * @~English  Sets the PolygonMode to use for this Appearance.
         * @~Japanese このアピアランスのPolygonModeの設定
         */
        void setPolygonMode (PolygonMode* polygon_mode);

        /**
         * @~English  Sets the texture image and its attributes for the given textureing unit.
         * @~Japanese 指定されたテクスチャーユニットのテクスチャーイメージとその属性値の設定. NULLでテクスチャーの無効化.
         * @param[in] index   テクスチャーユニット番号.
         * @param[in] texture テクスチャーを表すTexture2Dオブジェクト.
         */
        void setTexture (int index, Texture2D* texture);

        /**
         * @~English  Print out information of this class, for debug only.
         * @~Japanese このAppearanceクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

  
        /**
         * @~English  Render this object, inner use only.
         * @~Japanese このノードをレンダリングする内部使用の関数.
         */
        static void renderX ();

    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int animate_xxx (int world_time);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual Appearance* duplicate_xxx (Object3D* obj) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int getReferences_xxx (Object3D** references) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void render_xxx (RenderState& state) const;



    private:
        Appearance (const Appearance& app);
        Appearance& operator= (const Appearance& app);

    private:
        int                     layer;
        PolygonMode*            polygon_mode;
        CompositingMode*        compositing_mode;
        Material*               material;
        Fog*                    fog;
        std::vector<Texture2D*> textures;
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Appearance& app);

#endif
