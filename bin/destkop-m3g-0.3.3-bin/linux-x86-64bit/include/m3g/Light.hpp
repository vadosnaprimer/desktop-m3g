#ifndef __M3G_LIGHT_HPP__
#define __M3G_LIGHT_HPP__

#include "m3g/Node.hpp"
#include <iosfwd>

namespace m3g {

    /**
     * @~English  A scene graph node that represents different kinds of light sources.
     * @~Japanese ライトを表すシーングラフ・ノード.
     */
    class Light : public Node
    {

        /**
         * @~English  Attenuation parameters, for inner use.
         * @~Japanese 放射照度の計算式のパラメーターを保持する内部使用の構造体.
         */
        struct Attenuation {
            Attenuation (float c, float l, float q) : constant(c), linear(l), quadratic(q) {};
            float constant;
            float linear;
            float quadratic;
        };

        /**
         * @~English  Spot light parameters, for inner use.
         * @~Japanese スポットライトの放射照度の計算に使うパラメーターを保持する内部使用の構造体.
         */
        struct Spot {
            Spot (float a, float e) : angle(a), exponent(e) {};
            float angle;
            float exponent;
        };

    public:
        /**
         * @~English  A paramter to setMode, specifying an amibent light source.
         * @~Japanese 環境光を表す定数.
         */
        static const int AMBIENT     = 128;
        /**
         * @~English  A paramter to setMode, specifying an directional light source.
         * @~Japanese 平行光源を表す定数.
         */
        static const int DIRECTIONAL = 129;
        /**
         * @~English  A paramter to setMode, specifying an omnidirectional light source.
         * @~Japanese 点光源を表す定数.
         */
        static const int OMNI        = 130;
        /**
         * @~English  A paramter to setMode, specifying an spot light source.
         * @~Japanese スポットライトを表す定数.
         */
        static const int SPOT        = 131;

    public:
        /**
         * @~English  Consturct a new Light witdh default values.
         * @~Japanese デフォルト値のLightオブジェクトを作成するコンストラクタ.
         */
        Light ();

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~Light ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         * @return 複製されたライト.
         */
        Light* duplicate () const;

        /**
         * @~English  Retrieves the curent color fo this Light.
         * @~Japanese 現在のライトの色の取得.
         * @return 現在設定されているのライトの色
         */
        int getColor () const;

        /**
         * @~English  Retrieves the current constant attenuation coefficient for this Light.
         * @~Japanese ライトの減衰定数の１つである定数減衰パラメーターの取得.
         * @return 減衰定数のconstantパラメーター
         */
        float getConstantAttenuation () const;

        /**
         * @~English  Retrieves the current intensity of this Light.
         * @~Japanese このライトの発光強度の取得.
         * @return 現在設定されている発光強度
         */
        float getIntensity () const;

        /**
         * @~English  Retrieves the current linear attenuation coefficient for this Light.
         * @~Japanese ライトの減衰定数の１つである線形減衰パラメーターの取得.
         */
        float getLinearAttenuation () const;

        /**
         * @~English  Retrieves the current type of this Light.
         * @~Japanese ライトの種類の取得.
         * @return ライトの種類。AMBIENT, DIRECTIONAL, OMNI, SPOTのいずれか。
         */
        int getMode () const;

        /**
         * @~English  Retrieves the current quadratic attenuation coefficient for this Light.
         * @~Japanese ライトの減衰定数の１つである自乗減衰パラメーターの取得.
         * @return 自乗減衰パラメーター
         */
        float getQuadraticAttenuation () const;

        /**
         * @~English  Retrieves the current spot angle of this Light.
         * @~Japanese このライトのスポット角度の取得.　ライトの種類がスポットライトの時のみ有効。
         * @return スポット角度.
         */
        float getSpotAngle () const;

        /**
         * @~English  Sets the spot exponent for this Light.
         * @~Japanese このライトのスポット指数係数の取得. ライトの種類がスポットライトの時のみ有効。
         * @return スポット指数定数.
         */
        float getSpotExponent () const;

        /**
         * @~English  Sets the attenuation coeffieicients for this Light.
         * @~Japanese このライトの減衰係数を変更する.
         * @param[in] constant  定数パラメーター
         * @param[in] linear    線形パラメーター
         * @param[in] quadratic 自乗パラメーター
         */
        void setAttenuation (float constant, float linear, float quadratic);

        /**
         * @~English  Sets the color of this Light.
         * @~Japanese このライトの色の設定.
         * @param[in] rgb このライトの色
         */
        void setColor (int rgb);

        /**
         * @~English  Sets the intensity of this Light.
         * @~Japanese このライトの強度の設定.
         * @pramra[in] intensity ライトの強度.
         */
        void setIntensity (float intensity);

        /**
         * @~English  Sets the type of this Light.
         * @~Japanese このライトの種類の設定.
         * @param[in] mode  ライトの種類。AMBIENT, DIRECTIONAL, OMNI, SPOTのいずれか。
         */
        void setMode (int mode);

        /**
         * @~English  Sets the spot cone angle for this Light.
         * @~Japanese このライトのスポット角度の設定. ライトの種類がスポットの時のみ有効。
         * @param[in] angle スポット角度[0,90]
         */
        void setSpotAngle (float angle);

        /**
         * @~English  Sets the spot exponent for this Light.
         * @~Japanese このライトのスポットライト指数の設定.ライトの種類がスポットの時のみ有効。
         * @param[in] exponent  スポットライトの指数係数
         */
        void setSpotExponent (float exponent);

        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このLightクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int animate_xxx (int world_time);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual Light* duplicate_xxx (Object3D* obj) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void render_xxx (RenderState& state) const;


    private:
        Light (const Light& lgh);
        Light& operator= (const Light& lgh);

    private:
        int         mode;
        int         color;
        int         intensity;
        Attenuation attenuation;
        Spot        spot;
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Light& l);


#endif
