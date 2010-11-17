#ifndef __SPRITE3D_HPP__
#define __SPRITE3D_HPP__

#include "m3g/Node.hpp"
#include <iosfwd>


namespace m3g {

    class Image2D;
    class Appearance;
    class RayIntersection;
    class Camera;

    /**
     * @~English  A scene graph node that represents a 2-dimensional image with a 3D position.
     * @~Japanese 3Dの位置情報を持った2D画像を表すシーングラフノード.
     */
    class Sprite3D : public Node
    {

        /**
         * @~English  Structure of defining crop region, for inner use.
         * @~Japanese クロップ領域を定義する内部使用の構造体.
         */
        struct CropRect
        {
            CropRect (float x_, float y_, float width_, float height_) : x(x_), y(y_), width(width_), height(height_) {};
            float x;
            float y;
            float width;
            float height;
        };

    public:

        /**
         * @~English  A scene graph node that represents a 2-dimensional image with a 3D position.
         * @~Japanese 指定されたスケーリングモード、画像、アピアランスを持ったSprite3Dの作成.
         */
        Sprite3D (bool scaled, Image2D* image, Appearance* appearance);

        /**
         * @~English  Destructs this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~Sprite3D ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual Sprite3D* duplicate () const;


        virtual void mark (void(*func)(void*)) const;

        /**
         * @~English  Copy this Object3D to specified Object3D, not defined by M3G. 
         * @~Japanese このオブジェクトのデータを引数で指定されたオブジェクトにコピーするM3G非標準の関数.
         */
        void copy (Sprite3D* spr) const;

        /**
         * @~English  Adds the given AnimationTrack to this Object3D, 
         *            potentially changing the order and indices of the previously added tracks.
         * @~Japanese このObject3Dに指定されたアニメーショントラックを追加する。
         *            既存のトラックの順番とインデックスは変更されるかもしれない.
         */
        virtual void addAnimationTrack (AnimationTrack* animation_track);

        /**
         * @~English  Updates all animated properties in this Object3D and all Object3Ds that are reachable from this Object3D.
         * @~Japanese このObject3D自身とここから到達できるObject3Dのアニメーテッドプロパティを更新する.
         */
        virtual int animate (int world_time);

        /**
         * @~English  Gets the current Appearance of this Sprite3D.
         * @~Japanese このSprite3Dのカレントのアピアランスを取得.
         */
        Appearance* getAppearance () const;

        /**
         * @~English  Gets the current cropping rectangle height within the source image.
         * @~Japanese ソース画像のカレントのクロップ領域の高さの取得.
         */
        int getCropHeight () const;

        /**
         * @~English  Gets the current cropping rectangle width within the source image.
         * @~Japanese ソース画像のカレントのクロップ領域の高さの取得.
         */
        int getCropWidth () const;

        /**
         * @~English  Retrieves the current cropping rectangle X offset relative to the source image top left corner.
         * @~Japanese クロップ矩形のソース画像の左上からのX方向の相対オフセット.
         */
        int getCropX () const;

        /** 
         * @~English  Retrieves the current cropping rectangle Y offset relative to the source image top left corner.
         * @~Japanese クロップ矩形のソース画像の左上からのY方向の相対オフセット.
         */
        int getCropY () const;

        /**
         * @~English  Gets the current Sprite3D image.
         * @~Japanese カレントのSprite3D画像の取得.
         */
        Image2D* getImage () const;

        /**
         * 座標は全てNDC座標で渡す.
         */
        bool intersect (const Vector& org, const Vector& dir, const Camera* cam, RayIntersection* ri) const;

        /**
         * @~English  Returns the automatic scaling status of this Sprite3D.
         * @~Japanese このSprite3Dの自動スケーリングの状態を返す.
         */
        bool isScaled () const;

        /**
         * @~English  Sets the Appearancce of this Sprite3D.
         * @~Japanese このSprite3Dのアピアランスの設定.
         */
        void setAppearance (Appearance* appearance);

        /**
         * @~English  Sets a cropping rectangle within the source image.
         * @~Japanese ソース画像のクロッピング矩形の設定.
         */
        void setCrop (int crop_x, int crop_y, int crop_width, int crop_height);

        /**
         * @~English  Sets the sprite image to display.
         * @~Japanese 表示するスプライト画像の設定.
         */
        void setImage (Image2D* image);


        /**
         * @~English  Rrint out information of this object, for only debug.
         * @~Japanese このSprite3Dクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Render this object, for inner use.
         * @~Japanese このノードをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;


    private:
        
        /**
         * @~English  Retrieves center of scaled sprite in NDC coordinate.
         * @~Japanese スケールドスプライトのNDC座標での中心点を取得.
         */
        Vector getCenterPoint (const Camera* cam) const;

        /**
         * @~English  Retrieves width of scaled sprite in NDC coordinate.
         * @~Japanese スケールドスプライトのNDC座標での横幅を取得.
         */
        float getScaledWidth (const Camera* cam) const;

        /**
         * @~English  Retrieves height of scaled sprite in NDC coordinate.
         * @~Japanese スケールドスプライトのNDC座標での立て幅を取得.
         */
        float getScaledHeight (const Camera* cam) const;


        /**
         * @~English  Retrieves width of unscaled sprite in NDC coordinate.
         * @~Japanese アンスケールドスプライトのNDC座標での横幅を取得.
         */
        float getUnscaledWidth () const;

        /**
         * @~English  Retrieves height of unscaled sprite in NDC coordinate.
         * @~Japanese アンスケールドスプライトのNDC座標での立て幅を取得.
         */
        float getUnscaledHeight () const;

        /**
         * @~English  Retrieves tex coord(bottom-left) of sprite.
         * @~Japanese 左下のテクスチャー座標を計算して取得.
         */
        Vector getTexCoord0 () const;

        /**
         * @~English  Retrieves tex coord(top-right) of sprite.
         * @~Japanese 右上のテクスチャー座標を計算して取得.
         */
        Vector getTexCoord1 () const;

    private:
        Sprite3D (const Sprite3D& spr);
        Sprite3D& operator= (const Sprite3D& spr);

    private:
        bool        scaled;
        Image2D*    image;
        Appearance* appearance;
        CropRect    crop;

        unsigned int      texobj;
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Sprite3D& s);


#endif
