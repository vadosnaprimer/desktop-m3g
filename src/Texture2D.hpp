#ifndef __TEXTURE2D_HPP__
#define __TEXTURE2D_HPP__

#include <GL/glew.h>
#include "Transformable.hpp"
#include "TextureCoord2D.hpp"
#include <iostream>

namespace m3g {

class Image2D;

/**
 * 2Dテクスチャー画像とサブメッシュへの適応方法を指定する属性値をカプセル化したシーングラフノード.
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
   * フィルタリングの基本レベルを表す定数値.
   */
    static const int FILTER_BASE_LEVEL = 208;
  /**
   * バイリニア補完を表す定数値.
   */
    static const int FILTER_LINEAR     = 209;
  /**
   * ニアレストネイバーを表す定数値.
   */
    static const int FILTER_NEAREST    = 210;
  /**
   * テクスチャー関数を加算(add)に設定する定数値.
   */
    static const int FUNC_ADD          = 224;
  /**
   * テクスチャー関数をブレンド(blend)に設定する定数値.
   */
    static const int FUNC_BLEND        = 225;
  /**
   * テクスチャー関数をデカール(decal)に設定する定数値.
   */
    static const int FUNC_DECAL        = 226;
  /**
   * テクスチャー関数をモジュレート(modulate)に設定する定数値.
   */
    static const int FUNC_MODULATE     = 227;
  /**
   * テクスチャー関数を置換(replace)に設定する定数値.
   */
    static const int FUNC_REPLACE      = 228;
  /**
   * ラップモードをクランプ(clamp)に設定する定数値.
   */
    static const int WRAP_CLAMP        = 240;
  /**
   * ラップモードを繰り返し(repeat)に設定する定数値.
   */
    static const int WRAP_REPEAT       = 241;


public:
    /**
     * デフォルトの値で指定された画像のテクスチャーオブジェクトを作成する.
     */
    Texture2D (Image2D* image);

    /**
     * デストラクタ.
     */
    virtual ~Texture2D ();

    /**
     * アニメーショントラックの追加。
     * 既存のトラックの順番とインデックスは変更されるかもしれない.
     */
    virtual void addAnimationTrack (AnimationTrack* animation_track);

    /**
     * アニメーションの更新.
y     */
    virtual int animate (int time);

    /**
     * カレントのテクスチャーブレンドカラーの取得.
     */
    int getBlendColor () const;

    /**
     * このTexture2Dのブレンドモードの取得.
     */
    int getBlending () const;

    /**
     * カレントのベースレベル(最大サイズ)のテクスチャー画像の取得.
     */
    Image2D* getImage () const;


    /**
     * カレントの画像フィルターの取得.
     */
    int getImageFilter () const;

    /**
     * カレントのレベルフィルターの取得.
     */
    int getLevelFilter () const;

    /**
     * S方向のテクスチャー座標系のカレントのラッピングモードの取得.
     */
    int getWrappingS () const;

    /**
     * T方向のテクスチャー座標系のカレントのラッピングモードの取得.
     */
    int getWrappingT () const;
    
    /**
     * このTexture2Dのブレンドカラーの取得.
     */
    void setBlendColor (int rgb);

    /**
     * このTexute2Dで使用するテクスチャーブレンドモードやブレンド関数の選択.
     */
    void setBlending (int func);

    /**
     * このTexture2Dのフィルタリングモードの選択.
     */
    void setFiltering (int level_filter, int image_filter);

    /**
     * 指定された2次元画像をこのTexute2Dのテクスチャー画像として設定する.
     */
    void setImage (Image2D* image);

    /**
     * S,Tテクスチャー座標のラッピングモードの設定.
     */
    void setWrapping (int wrap_s, int wrap_t);

  /**
   * このTexture2Dクラスの情報を表示するデバッグ用の関数.
   */
  virtual std::ostream& print (std::ostream& out) const;

protected:
  virtual void findByObjectType (int obj_type, std::vector<Object3D*>& objs) const;

private:
  /**
   * テクスチャーユニットにセットする内部使用の関数.
   */
  //void setTextureUnit (int index);

private:
  /**
   * このTexture2Dをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;


private:
  Image2D* image;
  Wrapping wrapping;
  Filter filter;
  int blending_mode;
  int blend_color;

private:
  GLuint texobj;
  //int texunit;
};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Texture2D& tex);



#endif
