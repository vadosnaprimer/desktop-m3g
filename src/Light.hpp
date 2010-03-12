#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include "Node.hpp"
#include <iosfwd>

namespace m3g {

  /**
   * @~English  
   * @~Japanese ライトを表すシーングラフノード.
   */
  class Light : public Node
  {
    friend class Graphics3D;  // for render
    friend class World;  // for resetGLIndex

    /**
     * @~English  
     * @~Japanese 放射照度の計算式のパラメーターを保持する内部使用の構造体.
     */
    struct Attenuation {
      Attenuation (float c, float l, float q) : constant(c), linear(l), quadratic(q) {};
      float constant;
      float linear;
      float quadratic;
    };

    /**
     * @~English  
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
     * @~Japanese デフォルト値のLightオブジェクトを作成するコンストラクタ..
     */
    Light ();

    /**
     * @~English  Destruct this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    virtual ~Light ();

    /**
     * @~English  
     * @~Japanese アニメーショントラックの追加。
     *            既存のトラックの順番とインデックスは変更されるかもしれない.
     */
    virtual void addAnimationTrack (AnimationTrack* animation_track);

    /**
     * @~English  
     * @~Japanese アニメーションの更新.
     */
    virtual int animate (int world_time);

    /**
     * @~English  Retrieves the curent color fo this Light.
     * @~Japanese このライトのカレントのカラーの取得.
     */
    int getColor () const;

    /**
     * @~English  Retrieves the current constant attenuation coefficient for this Light.
     * @~Japanese このライトのカレントのコンスタントの減衰率の取得.
     */
    float getConstantAttenuation () const;

    /**
     * @~English  Retrieves the current intensity of this Light.
     * @~Japanese このライトのカレントの強度の取得.
     */
    float getIntensity () const;

    /**
     * @~English  Retrieves the current linear attenuation coefficient for this Light.
     * @~Japanese このライトのリニアの減衰率の取得.
     */
    float getLinearAttenuation () const;

    /**
     * @~English  Retrieves the current type of this Light.
     * @~Japanese このライトのカレントの種類の取得.
     */
    int getMode () const;

    /**
     * @~English  Retrieves the current quadratic attenuation coefficient for this Light.
     * @~Japanese このライトの2乗の減衰率の取得.
     */
    float getQuadraticAttenuation () const;

    /**
     * @~English  Retrieves the current spot angle of this Light.
     * @~Japanese このライトのカレントのスポット角度の取得.
     */
    float getSpotAngle () const;

    /**
     * @~English  Sets the spot exponent for this Light.
     * @~Japanese このライトのカレントのスポットexponential減衰率の取得.
     */
    float getSpotExponent () const;

    /**
     * @~English  Sets the attenuation coeffieicients for this Light.
     * @~Japanese このライトの減衰係数の取得.
     */
    void setAttenuation (float constant, float linear, float quadratic);

    /**
     * @~English  Sets the color of this Light.
     * @~Japanese このライトのカラーの設定.
     */
    void setColor (int rgb);

    /**
     * @~English  Sets the intensity of this Light.
     * @~Japanese このライトの強度の設定.
     */
    void setIntensity (float intensity);

    /**
     * @~English  Sets the type of this Light.
     * @~Japanese このライトの種類の設置.
     */
    void setMode (int mode);

    /**
     * @~English  Sets the spot cone angle for this Light.
     * @~Japanese このライトのスポットコーン角度の設定.
     */
    void setSpotAngle (float angle);

    /**
     * @~English  
     * @~Japanese このライトのスポットexponentの設定.
     */
    void setSpotExponent (float exponent);

    /**
     * @~English  Print out information of this object, for debug only.
     * @~Japanese このLightクラスの情報を表示する。デバッグ用.
     */
    virtual std::ostream& print (std::ostream& out) const;

  private:
    /**
     * @~English  Render this object, for inner use.
     * @~Japanese このLightをレンダリングする内部使用の関数.
     */
    virtual void render (int pass, int index=0) const;

    /**
     * @~English  Reset opengl index, for inner use.
     * @~Japanese OpenGLのライト番号をリセットする内部使用の関数. 
     */
    static void resetGLIndex ();

    /**
     * @~English  Retrieves current opengl index, for inner use.
     * @~Japanese OpenGLのライト番号を取得する内部使用の関数.
     */
    static int getGLIndex ();

  private:
    int         mode;
    int         color;
    int         intensity;
    Attenuation attenuation;
    Spot        spot;

    static int gl_light_index; ///< OpenGLのライトのインデックス
  };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Light& l);


#endif