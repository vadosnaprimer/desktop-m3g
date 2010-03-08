#ifndef __POLYGON_MODE_HPP__
#define __POLYGON_MODE_HPP__

#include "Object3D.hpp"
#include <iosfwd>

namespace m3g {

/**
 * ポリゴンレベルの属性値をカプセル化したアピアランスの構成要素.
 */
class PolygonMode : public Object3D
{
  friend class Appearance;  // for findByType

public:
  /**
   * 背面のカリングを表す定数.
   */
    static const int CULL_BACK    = 160;
  /**
   * 前面のカリングを表す定数.
   */
    static const int CULL_FRONT   = 161;
  /**
   * カリングなしを表す定数.
   */
    static const int CULL_NONE    = 162;
  /**
   * フラットシェーディングを表す定数.
   */
    static const int SHADE_FLAT   = 164;
  /**
   * スムースシェーディングを表す定数.
   */
    static const int SHADE_SMOOTH = 165;
  /**
   * 反時計回りの頂点の並び順を前面と規定する定数.
   */
    static const int WINDING_CCW  = 168;
  /**
   * 時計回りの頂点の並び順を前面と規定する定数.
   */
    static const int WINDING_CW   = 169;

public:

    /**
     * デフォルト値でPolygonModeオブジェクトの作成.
     */
    PolygonMode ();

    /**
     * デストラクタ.
     */
    virtual ~PolygonMode ();

    /**
     * ポリゴンのカリングモードの取得.
     */
    int getCulling () const;

    /**
     * ポリゴンのシェーディングモードの取得.
     */
    int getShading () const;

    /**
     * ポリゴンのワインでぃんぐもーどの取得.
     */
    int getWinding () const;

    /**
     * ローカルカメラライティングの有効、無効の取得.
     */
    bool isLocalCameraLightingEnabled () const;

    /**
     * 透視変換補正の有効、無効の問い合わせ.
     */
    bool isPerspectiveCorrectionEnabled () const;

    /**
     * 両面ライティングの有効、無効の問い合わせ.
     */
    bool isTwoSidedLightingEnabled () const;

    /**
     * ポリゴンのカリングモードの設定.
     */
    void setCulling (int mode);

    /**
     * ローカルカメラライティングの有効化、無効化.
     */
    void setLocalCameraLightingEnable (bool enable);

    /**
     * 透視変換補正の有効化、無効化.
     */
    void setPerspectiveCorrectionEnable (bool enable);

    /**
     * ポリゴンのシェーディングモードの設定.
     */
    void setShading (int mode);

    /**
     * 両面ライティングの有効化、無効化.
     */
    void setTwoSidedLightingEnable (bool enable);

    /**
     * ポリゴンのワインディングモードを時計回りか、反時計回りに設定する.
     */
    void setWinding (int mode);

  /**
   * このPolygoModeの情報を表示する。デバッグ用.
   */
  virtual std::ostream& print (std::ostream& out) const;

protected:
  /**
   *
   */
  virtual void render (int pass, int index=0) const;

private:
  int culling;
  int winding;
  int shading;
  bool two_sided_lighting;
  bool local_camera_lighting;
  bool perspective_correction;
};

} // namespace m3g {


std::ostream& operator<< (std::ostream& out, const m3g::PolygonMode& pm);

#endif
