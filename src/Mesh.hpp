#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "Node.hpp"
#include <iosfwd>
#include <vector>


namespace m3g {

class VertexBuffer;
class IndexBuffer;
class Appearance;

/**
 * ポリ後なるサーフェスを定義するシーングラフのノード.
 */
class Mesh : public Node
{
public:
    /**
     * 指定された頂点バッファーとサブメッシュから新しいメッシュを作成する.
     */
  Mesh (VertexBuffer* vertices,
	int num_submesh, IndexBuffer** submeshes,
	int num_appearance, Appearance** appearances);

    /**
     * サブメッシュ1つからなる新しいメッシュを作成する.
     */
    Mesh (VertexBuffer* vertices, 
	  IndexBuffer* submesh,
	  Appearance* appearance);

    /**
     * デストラクタ
     */
    virtual ~Mesh ();

    /**
     * アニメーション.
     */
    virtual int animate (int time);

    /**
     * 指定されたサブメッシュのカレントのアピアランスを取得.
     */
    Appearance* getAppearance (int index) const;

    /**
     * 指定されたインデックスのサブメッシュを取得.
     */
    IndexBuffer* getIndexBuffer (int index) const;

    /**
     * このメッシュのサブメッシュ数を取得.
     */
    int getSubmeshCount () const;

    /**
     * このメッシュの頂点バッファーの取得.
     */
    VertexBuffer* getVertexBuffer () const;

    /**
     * 指定されたサブメッシュのアピアランスを設定.
     */
    void setAppearance (int index, Appearance* appearance);

    /**
     * このMeshクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

protected:

  /**
   * このノードをレンダリングする内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;

protected:
  VertexBuffer* vertices;
  std::vector<IndexBuffer*> indices;
  std::vector<Appearance*>  appearances;

};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Mesh& mesh);


#endif
