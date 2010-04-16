#ifndef __IMAGE2D_HPP__
#define __IMAGE2D_HPP__

#include "Object3D.hpp"
#include <iosfwd>

namespace m3g {

  /**
   * @~English  A two-dimensional image that can be used as a textur, backgoround or sprite image.
   * @~Japanese テクスチャー、バックグラウンド、スプライト画像として使う2D画像クラス.
   */
  class Image2D : public Object3D
  {
    friend class Texture2D;
    friend class Background;  // for getImage
    friend class Sprite3D;   // for getImage

  public:
    /**
     * @~English  A constructor parameter specifying that this Image2D has an alpha component only.
     * @~Japanese A（アルファ）のみを持つ画像を表す定数.
     */
    static const int ALPHA           = 96;
    /**
     * @~English  A constructor parameter specifying that this Image2D has a luminance component only.
     * @~Japanese L（ルミナンス）のみを持つ画像を表す定数.
     */
    static const int LUMINANCE       = 97;
    /**
     * @~English  A constructor parameter specifying that this Image2D has luminance and an alpha component only.
     * @~Japanese AとLを持つ画像を表す定数.
     */
    static const int LUMINANCE_ALPHA = 98;
    /**
     * @~English  A constructor parameter specifying that this Image2D has red, green and blue color components.
     * @~Japanese R,G,Bを持つ画像を表す定数.
     */
    static const int RGB             = 99;
    /**
     * @~English  A constructor parameter specifying that this Image2D has red, green, blue and alpha color components.
     * @~Japanese R,G,B,Aを持つ画像を表す定数.
     */
    static const int RGBA            = 100;

  public:
    /**
     * @~English  Construct an empty, mutable Image2D with the given dimensions.
     * @~Japanese 指定された寸法の空の変更可能なImage2Dオブジェクトの作成.
     */
    Image2D (int format, int width, int height);

    /**
     * @~English  Costrucsts an immutable Image2D by copying pixels from a byte array.
     * @~Japanese バイト配列からピクセル値をコピーしての変更不可のImage2Dオブジェクトの作成.
     *            バイト順は例えばRGBAフォーマットならR,G,B,Aの順番で格納されていなければならない。
     */
    Image2D (int format, int width, int height, void* image);

    /**
     * @~English  Constructs an immutable Image2D by copying palette indices from a byte array, and the palette enttries from another byte array.
     * @~Japanese パレットの配列とそのパレットインデックスの配列から変更不可のImage2Dオブジェクトの作成.
     */
    Image2D (int format, int width, int height, void* image, void* palette);

    /**
     * @~English  Destruct this object.
     * @~Japanese このオブジェクトを削除するデストラクタ.
     */
    virtual ~Image2D ();

    /**
     * @~English  Creates a duplicate of this Object3D. 
     * @~Japanese このオブジェクトの複製の作成.
     */
    virtual Image2D* duplicate () const;

    /**
     * @~English  Gets the internal format of this Image2D.
     * @~Japanese このImage2Dクラスの内部フォーマットを取得.
     */
    int getFormat () const;

    /**
     * @~English  Gets the hieght of this Image2D.
     * @~Japanese このImage2Dクラスの高さをピクセル数で取得.
     */
    int getHeight () const;

    /**
     * @~English  Gets the width of this Image2D.
     * @~Japanese このImage2Dクラスの幅をピクセル数で取得.
     */
    int getWidth () const;

    /**
     * @~English  Qeries wheter this Image2D is mutable.
     * @~Japanese このImage2Dクラスがミュータブルかどうかの問い合わせ.
     */
    bool isMutable () const;

    /**
     * @~English  Updates a rectangular area of this Image2D by copying pixels from a byte array.
     * @~Japanese バイト配列からピクセルをコピーしてこのImage2Dクラスの矩形領域を更新する.
     */
    void set (int x, int y, int width, int height, void* image);


    /**
     * @~English  Write image as ppm file(alpha component is ignored), for only debug .
     * @~Japanese ppm画像として出力するM3G非標準の関数。
     *            この関数はデバッグ用でありリリースに含まれていてはならない.
     */
    void write_ppm (const char* file_name) const;

    /**
     * @~English  Print out information of this class, for only debug.
     * @~Japanese このImage2Dクラスの情報を表示する。デバッグ用.
     */
    virtual std::ostream& print (std::ostream& out) const;

    /**
     * @~English  Return OpenGL format, for inner use.
     * @~Japanese OpenGLの画像形式を返すM3G未定義の関数.
     */
    GLenum getOpenGLFormat () const;

    /**
     * @~English  Return pointer to raw data, for inner use.
     * @~Japanese 内部データへのポインターを返すM3G未定義の関数.
     */
    void* getOpenGLData () const;


  private:
    int   format;
    int   width;
    int   height;
    char* image;
    bool  immutable;

  };

  int format_to_bpp (int format);

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Image2D& img);


#endif
