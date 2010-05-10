#ifndef __TEXTURE2D_HPP__
#define __TEXTURE2D_HPP__

#include <GL/glew.h>
#include "Transformable.hpp"
#include <iostream>

namespace m3g {

  class Image2D;

  /**
   * @~English  Constructs a new texture object with the given image.
   * @~Japanese 2Dテクスチャー画像とサブメッシュへの適応方法を指定する属性値をカプセル化したシーングラフノード.
   */
  class Texture2D : public Transformable
  {
    friend class Appearance;  // for rendere, setTextureUnit

    struct Wrapping {
      Wrapping(int s_, int t_) : s(s_), t(t_) {};
      int s;
      int t;
    };
    struct Filter {
      Filter (int l, int i) : level(l), image(i) {};
      int level;
      int image;
    };

  public:
    /**
     * @~English  A level filtering paramteer to setFiltering that selects the base lvevel image.
     * @~Japanese フィルタリングの基本レベルを表す定数値.
     */
    static const int FILTER_BASE_LEVEL = 208;
    /**
     * @~English  A parameter to setFiltering htat selects linear filtering.
     * @~Japanese 線形補間を表す定数値.
     */
    static const int FILTER_LINEAR     = 209;
    /**
     * @~English  A parameter to setFiltering that selects nearest neightbor filtering.
     * @~Japanese 最近傍補間を表す定数値.
     */
    static const int FILTER_NEAREST    = 210;
    /**
     * @~English  A paramter to setBlending, specifying that the texel color is to be added to the fragment.
     * @~Japanese テクスチャー関数を加算(add)に設定する定数値.
     */
    static const int FUNC_ADD          = 224;
    /**
     * @~English  A paramter to setBlending, specifying that 
     *            the texture blend color is to be blended into
     *            the fragment color in proportion to the texel RGB values.
     * @~Japanese テクスチャー関数をブレンド(blend)に設定する定数値.
     */
    static const int FUNC_BLEND        = 225;
    /**
     * @~English  A parameter to setBlending, specifying that the texel color is to be blended into the fragment color in proportion to the texel alpha.
     * @~Japanese テクスチャー関数をデカール(decal)に設定する定数値.
     */
    static const int FUNC_DECAL        = 226;
    /**
     * @~English  A parameter to setBlending , specifying that the texel color and/or alpha are to be multiplied with the fragment color and alpha.
     * @~Japanese テクスチャー関数をモジュレート(modulate)に設定する定数値.
     */
    static const int FUNC_MODULATE     = 227;
    /**
     * @~English  A parameter to setBlending, specifying that the texle color and/or alpha are to replace the fragment color and alpha.
     * @~Japanese テクスチャー関数を置換(replace)に設定する定数値.
     */
    static const int FUNC_REPLACE      = 228;
    /**
     * @~English  A parameter to setWrapping, specifying that the texture image i sto be repeated oly once.
     * @~Japanese ラップモードをクランプ(clamp)に設定する定数値.
     */
    static const int WRAP_CLAMP        = 240;
    /**
     * @~English  A parameter to setWrappping, specifying that the texture image is tto be repeated indefinitely.
     * @~Japanese ラップモードを繰り返し(repeat)に設定する定数値.
     */
    static const int WRAP_REPEAT       = 241;


  public:
    /**
     * @~English  Constructs a new texture object with the given image.
     * @~Japanese デフォルトの値で指定された画像のテクスチャーオブジェクトを作成する.
     */
    Texture2D (Image2D* image);

    /**
     * @~English  Destructs this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    virtual ~Texture2D ();

    /**
     * @~English  Creates a duplicate of this Object3D. 
     * @~Japanese このオブジェクトの複製の作成.
     */
    Texture2D* duplicate () const;

    virtual int animate (int world_time);

    virtual void addAnimationTrack (AnimationTrack* animation_track);



    /**
     * @~English  
     * @~Japanese カレントのテクスチャーブレンドカラーの取得.
     */
    int getBlendColor () const;

    /**
     * @~English  
     * @~Japanese このTexture2Dのブレンドモードの取得.
     */
    int getBlending () const;

    /**
     * @~English  Retrieves the current base level (full size) texture image.
     * @~Japanese カレントのベースレベル(最大サイズ)のテクスチャー画像の取得.
     */
    Image2D* getImage () const;


    /**
     * @~English  Returns the current texture image filter.
     * @~Japanese カレントの画像フィルターの取得.
     */
    int getImageFilter () const;

    /**
     * @~English  Returns the current texture level filter.
     * @~Japanese カレントのレベルフィルターの取得.
     */
    int getLevelFilter () const;

    /**
     * @~English  
     * @~Japanese S方向のテクスチャー座標系のカレントのラッピングモードの取得.
     */
    int getWrappingS () const;

    /**
     * @~English  
     * @~Japanese T方向のテクスチャー座標系のカレントのラッピングモードの取得.
     */
    int getWrappingT () const;
    
    /**
     * @~English  
     * @~Japanese このTexture2Dのブレンドカラーの取得.
     */
    void setBlendColor (int rgb);

    /**
     * @~English  
     * @~Japanese このTexute2Dで使用するテクスチャーブレンドモードやブレンド関数の選択.
     */
    void setBlending (int func);

    /**
     * @~English  Selects the filtering mode for this Texture2D.
     * @~Japanese このTexture2Dのフィルタリングモードの選択.
     */
    void setFiltering (int level_filter, int image_filter);

    /**
     * @~English  Sets the given Image2D as the texture image of this Texture2D.
     * @~Japanese 指定された2次元画像をこのTexute2Dのテクスチャー画像として設定する.
     */
    void setImage (Image2D* image);

    /**
     * @~English  Sets the wrapping mode for the S and T texture coordinates.
     * @~Japanese S,Tテクスチャー座標のラッピングモードの設定.
     */
    void setWrapping (int wrap_s, int wrap_t);

    /**
     * @~English  Print out information of this object, for debug only.
     * @~Japanese このTexture2Dクラスの情報を表示するデバッグ用の関数.
     */
    virtual std::ostream& print (std::ostream& out) const;

    /**
     * @~English  Render this object, for inner use.
     * @~Japanese このオブジェクトをレンダリングする内部使用の関数.
     */
    virtual void render (RenderState& state) const;


  private:
    /**
     * @~English  Render this object, for inner use.
     * @~Japanese デフォルトでレンダリングする内部使用の関数.
     */
    static void renderX ();


  private:
    Image2D* image;
    Wrapping wrapping;
    Filter   filter;
    int      blending_mode;
    int      blend_color;

    GLuint texobj;
  };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Texture2D& tex);



#endif
