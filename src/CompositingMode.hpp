#ifndef __COMPOSITING_MODE_HPP__
#define __COMPOSITING_MODE_HPP__


#include <iosfwd>
#include "Object3D.hpp"

namespace m3g {

/**
 * ピクセルのコンポジットモードをカプセル化したアピアランスの構成要素.
 */
class CompositingMode : public Object3D
{
  friend class Appearance;  // for findByType

public:
  /**
   * アルファブレンドを表す定数.
   */
    static const int ALPHA        = 64;
  /**
   * アルファ加算ブレンドを表す定数.
   */
    static const int ALPHA_ADD    = 65;
  /**
   * モジュロ演算ブレンドを表す定数.
   */
    static const int MODULATE     = 66;
  /**
   * より明るいモジュロ演算ブレンドを表す定数
   */
    static const int MODULATE_X2  = 67;
  /**
   * リプレースを表す定数.
   */
    static const int REPLACE      = 68;

  struct DepthOffset {
    DepthOffset (float factor_, float units_) : factor(factor_), units(units_) {};
    float factor;
    float units;
  };

public:
    /**
     * コンストラクタ.
     */
    CompositingMode ();

    /**
     * デストラクタ.
     */
    virtual ~CompositingMode ();

    /**
     * カレントのαテストの閾値を取得する.
     */
    float getAlphaThreshold () const;

    /**
     * カレントのフレームバッファーのブレンディングモードを取得する.
     */
    int getBlending () const;

    /**
     * カレントの深度オフセットの勾配値を取得する.
     */
    float getDepthOffsetFactor () const;

    /**
     * カレントの固定深度オフセット値を取得する.
     */
    float getDepthOffsetUnits () const;

    /**
     * αチャンネルへの書き込みが有効かどうかの問い合わせ.
     */
    bool isAlphaWriteEnabled () const;

    /**
     * カラーチャンネルへの書き込みが有効かどうかの問い合わせ.
     */
    bool isColorWriteEnabled () const;

    /**
     * 深度テストが有効かどうかの問い合わせ.
     */
    bool isDepthTestEnabled () const;

    /**
     * 深度バッファーへの書き込みが有効かどうかの問い合わせ.
     */
    bool isDepthWriteEnabled () const;

    /**
     * αテスト閾値の設定.
     */
    void setAlphaThreshold (float threshold);

    /**
     * フラグメントのα成分をカラーバッファーへ書き込む事を許可もしくは不許可にする.
     */
    void setAlphaWriteEnable (bool enable);

    /**
     * フレームバッファーのピクセルとのブレンドモードの設定.
     */
    void setBlending (int mode);

    /**
     * カラーバッファーへのフラグメントのカラーの書き込みの許可もしくは不許可の設定.
     */
    void setColorWriteEnable (bool enable);

    /**
     * 深度テストと深度バッファーへの書き込みの直前にスクリーン座標のZ座標にある値を足す.
     */
    void setDepthOffset (float factor, float units);

    /**
     * 深度テストの有効、無効の設定.
     */
    void setDepthTestEnable (bool enable);

    /**
     * 深度バッファーへフラグメントの深度値を書き込みの許可もしくは不許可.
     */
    void setDepthWriteEnable (bool enable);

  /**
   * このCompositingModeの情報を表示する。デバッグ用.
   */
  std::ostream& print (std::ostream& out) const;

protected:
  /**
   * このCompositingModeノードをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;

private:
  int blending_mode;
  float alpha_threshold;
  DepthOffset depth_offset;
  bool depth_test;
  bool depth_write;
  bool color_write;
  bool alpha_write;

};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::CompositingMode& c);



#endif

