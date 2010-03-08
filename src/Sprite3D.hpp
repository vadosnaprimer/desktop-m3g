#ifndef __SPRITE3D_HPP__
#define __SPRITE3D_HPP__

#include "Node.hpp"
#include <iosfwd>


namespace m3g {

    class Image2D;
    class Appearance;

/**
 * 3Dの位置情報を持った2D画像を表すシーングラフノード.
 */
class Sprite3D : public Node
{
  friend class Group;   // for sort_by_layer

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
     * 指定されたスケーリングモード、画像、アピアランスを持ったSprite3Dの作成.
     */
    Sprite3D (bool scaled, Image2D* image, Appearance* appearance);

    /**
     * デストラクタ.
     */
    virtual ~Sprite3D ();

  /**
   *
   */
  virtual void addAnimationTrack (AnimationTrack* animation_track);

    /**
     * このBackgroundをアニメーションする.
     */
  virtual int animate (int world_time);

    /**
     * このSprite3Dのカレントのアピアランスを取得.
     */
    Appearance* getAppearance () const;

    /**
     * ソース画像のカレントのクロップ領域の高さの取得.
     */
    int getCropHeight () const;

    /**
     * ソース画像のカレントのクロップ領域の高さの取得.
     */
    int getCropWidth () const;

    /**
     * クロップ矩形のソース画像の左上からのX方向の相対オフセット.
     */
    int getCropX () const;

    /**
     * クロップ矩形のソース画像の左上からのY方向の相対オフセット.
     */
    int getCropY () const;

    /**
     * カレントのSprite3D画像の取得.
     */
    Image2D* getImage () const;

    /**
     * このSprite3Dの自動スケーリングの状態を返す.
     */
    bool isScaled () const;

    /**
     * このSprite3Dのアピアランスの設定.
     */
    void setAppearance (Appearance* appearance);

    /**
     * ソース画像のクロッピング矩形の設定.
     */
    void setCrop (int cropX, int cropY, int width, int height);

    /**
     * 表示するスプライト画像の設定.
     */
    void setImage (Image2D* image);


    /**
     * このSprite3Dクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

protected:
  /**
   * このノードをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;


private:
  int getLayer () const;
  static bool sort_by_layer (const Sprite3D* lhs, const Sprite3D* rhs);

private:
  bool        scaled;
  Image2D*    image;
  Appearance* appearance;
  CropRect    crop;

  GLuint      texobj;
};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Sprite3D& s);


#endif
