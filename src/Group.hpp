#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include "Node.hpp"
#include <iosfwd>
#include <vector>


namespace m3g {

class RayIntersection;


/**
 * 未ソートの複数の子ノードを持つシーングラフのノード.
 */
class Group : public Node
{
public:
    /**
     * 子ノードを持たないGroupノードの作成.
     */
    Group ();

    /**
     * デストラクタ.
     */
    virtual ~Group ();

    /** 
     * 指定されたノードを追加する。以前に追加されていた子ノードの順番とインデックスは変更される可能性がある.
     */
    void addChild (Node* child);

    /**
     * このノードと子ノードをアニメーションする.
     */
  virtual int animate (int world_time);

    /**
     * インデックスを指定して子ノードを取得する.
     */
    Node* getChild (int index) const;

    /**
     * このグループの子ノードの数を取得する.
     */
    int getChildCount () const;

    /**
     * このグループのピッキング可能なMesh,scaled Sprite3Dのうち同じスコープで、指定されたピッキング光線で最初にヒットしたノードを返す.
     */
    bool pick (int scope, float ox, float oy, float oz, float dx, float dy, float dz, RayIntersection* ri) const;

    /**
     * このグループから指定されたノードを削除する。以前に追加されていた子ノードの順番とインデックスは変更される可能性がある.
     */
    void removeChild (Node* child);

  /**
   * このGroupクラスの情報を表示する。デバッグ用.
   */
  virtual std::ostream& print (std::ostream& out) const;

PROTECTED:
    virtual void findByObjectType (int obj_type, std::vector<Object3D*>& objs) const;

protected:
  /**
   * このGroupをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;
  
private:
  std::vector<Node*> children;
};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Group& g);




#endif
