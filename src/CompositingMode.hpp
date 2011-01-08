#ifndef __M3G_COMPOSITING_MODE_HPP__
#define __M3G_COMPOSITING_MODE_HPP__


#include <iosfwd>
#include "m3g/Object3D.hpp"

namespace m3g {

    /**
     * @~English  An Appearance component encapsulating per-pixel comositing attributes.
     * @~Japanese ピクセル単位のコンポジット方法をカプセル化したアピアランスの構成要素.
     */
    class CompositingMode : public Object3D
    {

        /**
         * @~English  Structure of depth offset, for inner use.
         * @~Japanese デプスオフセット情報を持つ内部使用の構造体.
         */
        struct DepthOffset {
            DepthOffset (float factor_, float units_) : factor(factor_), units(units_) {};
            float factor;
            float units;
        };

    public:

        /**
         * @~English  Selects the alpha blend mode.
         * @~Japanese アルファブレンドを表す定数.
         */
        static const int ALPHA        = 64;
        /**
         * @~English  Selects the additive blend mode.
         * @~Japanese アルファ加算ブレンドを表す定数.
         */
        static const int ALPHA_ADD    = 65;
        /**
         * @~English  Selects the basic modulating blending mode.
         * @~Japanese モジュロ演算ブレンドを表す定数.
         */
        static const int MODULATE     = 66;
        /**
         * @~English  Selects the brighter modulating blending mode.
         * @~Japanese より明るいモジュロ演算ブレンドを表す定数
         */
        static const int MODULATE_X2  = 67;
        /**
         * @~English  Selects the replace mode.
         * @~Japanese リプレースを表す定数.
         */
        static const int REPLACE      = 68;

    public:
        /**
         * @~English  Constructs a CompositingMode object with default values.
         * @~Japanese CompositingModeオブジェクトを作成するコンストラクタ.
         */
        CompositingMode ();

        /**
         * @~English  Destuct a CompositingMode object.
         * @~Japanese このCompositingModeオブジェクトのデストラクタ.
         */
        virtual ~CompositingMode ();


        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual CompositingMode* duplicate () const;


        /**
         * @~English  Copy this Object3D to specified Object3D, not defined by M3G. 
         * @~Japanese このオブジェクトのデータを引数で指定されたオブジェクトにコピーするM3G非標準の関数.
         */
        void copy (CompositingMode* cmode) const;

        /**
         * @~English  Retrieves the current alpha testing threashold.
         * @~Japanese カレントのαテストの閾値を取得する.
         */
        float getAlphaThreshold () const;

        /**
         * @~English  Retrieves the current frame buffer blending mode.
         * @~Japanese カレントのフレームバッファーのブレンディングモードを取得する.
         */
        int getBlending () const;

        /**
         * @~English  Retrieves the current depth offset slope factor.
         * @~Japanese カレントの深度オフセットの勾配値を取得する.
         */
        float getDepthOffsetFactor () const;

        /**
         * @~English  Retrieves the current constant depth offset.
         * @~Japanese カレントの固定深度オフセット値を取得する.
         */
        float getDepthOffsetUnits () const;

        /**
         * @~English  Queries whether alpha writing is enabled.
         * @~Japanese αチャンネルへの書き込みが有効かどうかの問い合わせ.
         */
        bool isAlphaWriteEnabled () const;

        /**
         * @~English  Queries whether color writing is enabled.
         * @~Japanese カラーチャンネルへの書き込みが有効かどうかの問い合わせ.
         */
        bool isColorWriteEnabled () const;

        /**
         * @~English  Queries whether depth writing is enabled.
         * @~Japanese 深度テストが有効かどうかの問い合わせ.
         */
        bool isDepthTestEnabled () const;

        /**
         * @~English  Enables or disables writing of fragment depth values into the depth buffer.
         * @~Japanese 深度バッファーへの書き込みが有効かどうかの問い合わせ.
         */
        bool isDepthWriteEnabled () const;

        /**
         * @~English  Sets the threshold value for alpha testing.
         * @~Japanese αテスト閾値の設定.
         */
        void setAlphaThreshold (float threshold);

        /**
         * @~English  Enables or disables writing of fragment alpha values into the color buffer.
         * @~Japanese フラグメントのα成分をカラーバッファーへ書き込む事を許可もしくは不許可にする.
         */
        void setAlphaWriteEnable (bool enable);

        /**
         * @~English  Selects a method of combindinnnng the pixel to be rendered with the pixel already inthe frame buffer.
         * @~Japanese フレームバッファーのピクセルとのブレンドモードの設定.
         */
        void setBlending (int mode);

        /**
         * @~English  Enables or disables writing of fragment coor values into the color buffer.
         * @~Japanese カラーバッファーへのフラグメントのカラーの書き込みの許可もしくは不許可の設定.
         */
        void setColorWriteEnable (bool enable);

        /**
         * @~English Defines a value that is added to the screen space Z coordinate of a pixel immediately.
         * @~Japanese 深度テストと深度バッファーへの書き込みの直前にスクリーン座標のZ座標にある値を足す.
         */
        void setDepthOffset (float factor, float units);

        /**
         * @~English  Enables or disables depth testing.
         * @~Japanese 深度テストの有効、無効の設定.
         */
        void setDepthTestEnable (bool enable);

        /**
         * @~English  Queries whether depth writing is enabled.
         * @~Japanese 深度バッファーへフラグメントの深度値を書き込みの許可もしくは不許可.
         */
        void setDepthWriteEnable (bool enable);

        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このCompositingModeの情報を表示する。デバッグ用.
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
        CompositingMode (const CompositingMode& cmode);
        CompositingMode& operator= (const CompositingMode& cmode);

    private:
        int         blending_mode;
        float       alpha_threshold;
        DepthOffset depth_offset;
        bool        depth_test;
        bool        depth_write;
        bool        color_write;
        bool        alpha_write;
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::CompositingMode& c);



#endif

