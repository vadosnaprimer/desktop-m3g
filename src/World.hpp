#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include "Group.hpp"
#include <iosfwd>
#include <vector>



namespace m3g {

class Camera;
class Background;

/**
 * シーングラフを保持する最上位の特殊グループノード.
 */
class World : public Group
{
  friend class Graphics3D;

public:
    /**
     * デフォルト値のWorldオブジェクトの作成.
     */
    World ();

    /**
     * デストラクタ.
     */
    virtual ~World ();

    /**
     * このノードと子ノードをアニメーションする.
     */
  virtual int animate (int world_time);

    /**
     * カレントのアクティブカメラの取得.
     */
    Camera* getActiveCamera () const;

    /**
     * このWorldのバックグラウンド設定の取得.
     */
    Background* getBackground () const;

    /**
     * このWorldをレンダリングするときに使われるカメラの設定.
     */
    void setActiveCamera (Camera* camera);

    /**
     * このWorldのバックグラウンドオブジェ区の設定.
     */
    void setBackground (Background* background);

  /**
   * このWorldクラスの情報を表示する。デバッグ用.
   */
  virtual std::ostream& print (std::ostream& out) const;

protected:
  /**
   * このノードをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;

private:
  Background* background;
  Camera*     camera;
};


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::World& wld);


#endif
