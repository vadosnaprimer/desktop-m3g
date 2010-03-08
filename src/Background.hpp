#ifndef __BACKGROUND_HPP__
#define __BACKGROUND_HPP__

#include <iosfwd>
#include "Object3D.hpp"


namespace m3g {

class Image2D;

/**
 * ビューポートのクリアとその設定.
 */
class Background : public Object3D
{
  friend class World;

  /**
   * 画像処理モードを定義する内部使用の構造体.
   */
  struct ImageMode {
    ImageMode (int mode_x, int mode_y) : x(mode_x), y(mode_y) {};
    int x;
    int y;
  };

  /**
   * クロップ領域を定義する内部使用の構造体.
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
   * 背景画像の領域外を指定した場合、ボーダー境界色を返す設定を表す定数.
   */
    static const int BORDER = 32;
  /**
   * 背景画像の領域外を指定した場合、画像をリピートして返す設定を表す定数.
   */
    static const int REPEAT = 33;

public:
    /**
     * コンストラクタ.
     */
    Background ();

    /**
     * デストラクタ.
     */
    virtual ~Background ();

  /**
   *
   */
  virtual void addAnimationTrack (AnimationTrack* animation_track);

    /**
     * このBackgroundをアニメーションする.
     */
  virtual int animate (int world_time);

    /**
     * カレントの背景色の取得
     */
    int getColor () const;

    /**
     * カレントのソースイメージのクロップ領域の高さの取得.
     */
    int getCropHeight () const;

    /** 
     * カレントのソースイメージのクロップ領域の幅の取得
     */
    int getCropWidth () const;
    
    /**
     * クロップ領域のソースイメージ左上からのX方向の相対オフセットの取得.
     */
    int getCropX () const;

    /**
     *  クロップ領域のソースイメージ左上からのY方向の相対オフセットの取得.
     */
    int getCropY () const;

    /**
     * カレントのバックグラウンドイメージの取得.
     */
    Image2D* getImage () const;

    /**
     * カレントのバックグラウンドイメージのX方向のリピートモードの取得.
     */
    int getImageModeX () const;

    /**
     *  カレントのバックグラウンドイメージのY方向のリピートモードの取得.
     */
    int getImageModeY () const;

    /**
     * カラーバッファーのクリアが有効かどうかの問い合わせ.
     */
    bool isColorClearEnabled () const;

    /**
     * デプスバッファーのクリアが有効かどうかの問い合わせ.
     */
    bool isDepthClearEnabled () const;

    /**
     * バックグラウンドカラーの設定.
     */
    void setColor (int argb);

    /**
     * カラーバッファーのクリアの有効化または無効化.
     */
    void setColorClearEnable (bool enable);

    /**
     * バックグラウンドイメージのクロップ領域の設定.
     */
    void setCrop (int crop_x, int rop_y, int width, int height);

    /**
     * デブ婦バッファーのクリアの有効化または無効化.
     */
    void setDepthClearEnable (bool enable);

    /**
     * 背景画像の設定、または背景画像モードと背景色モードの切り替え.
     */
    void setImage (Image2D* image);

    /**
     * 背景画像のX方向およびY方向のリピートモードの設定.
     */
    void setImageMode (int mode_x, int mode_y);

    /**
     * このBackgroundクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

private:
  /**
   * このBackgroundをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;

private:
  bool color_clear_enable;
  bool depth_clear_enable;
  int  background_color;
  Image2D* background_image;
  ImageMode image_mode;
  CropRect crop_rectangle;
  
  int background_width;
  int background_height;

private:
  GLuint texobj;
};

} //namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Background& bg);



#endif
