#ifndef __M3G_MESH_HPP__
#define __M3G_MESH_HPP__

#include "m3g/Node.hpp"
#include <iosfwd>
#include <vector>


namespace m3g {

    class VertexBuffer;
    class IndexBuffer;
    class Appearance;
    class RayIntersection;

    /**
     * @~English  A scene graph node that represents a 3D object defined as a polygonal surface.
     * @~Japanese ポリゴナルサーフェスを定義するシーングラフのノード.
     */
    class Mesh : public Node
    {
    public:
        /**
         * @~English  Constructs a new Mesh with the given VertexBuffer and submeshes.
         * @~Japanese 指定された頂点バッファーとサブメッシュから新しいメッシュを作成する.
         */
        Mesh (VertexBuffer* vertices,
              int           num_submesh,
              IndexBuffer** submeshes,
              Appearance**  appearances);

        /**
         * @~English Constructs a new Mesh consisting of only one submesh. 
         * @~Japanese サブメッシュ1つからなる新しいメッシュを作成する.
         */
        Mesh (VertexBuffer* vertices, 
              IndexBuffer*  submesh,
              Appearance*   appearance);

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~Mesh ();


        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual Mesh* duplicate () const;


        /**
         * @~English  Copy this Object3D to specified Object3D, not defined by M3G. 
         * @~Japanese このオブジェクトのデータを引数で指定されたオブジェクトにコピーするM3G非標準の関数.
         */
        void copy (Mesh* mesh) const;

        /**
         * @~English  Updates all animated properties in this Object3D and all Object3Ds that are reachable from this Object3D.
         * @~Japanese このObject3D自身とここから到達できるObject3Dのアニメーテッドプロパティを更新する.
         */
        virtual int animate (int world_time);

        
        /**
         * @~English  Gets the current Appearance of the specified submesh.
         * @~Japanese 指定されたサブメッシュのカレントのアピアランスを取得.
         */
        Appearance* getAppearance (int index) const;

        /**
         * @~English  Retrieves tthe submesh at the given index.
         * @~Japanese 指定されたインデックスのサブメッシュを取得.
         */
        IndexBuffer* getIndexBuffer (int index) const;

        /**
         * @~English  Gets the number of submeshes in this Mesh.
         * @~Japanese このメッシュのサブメッシュ数を取得.
         */
        int getSubmeshCount () const;

        /**
         * @~English  Gets the vertex buffer of this Mesh.
         * @~Japanese このメッシュの頂点バッファーの取得.
         */
        VertexBuffer* getVertexBuffer () const;

        /**
         * @~English  Sets the Appearance ofr the specified submesh.
         * @~Japanese 指定されたサブメッシュのアピアランスを設定.
         */
        void setAppearance (int index, Appearance* appearance);


        /**
         * 座標は全てこのメッシュのローカル座標系で指定する.
         */
        virtual bool intersect (const Vector& org, const Vector& dir, RayIntersection* ri) const;

        /**
         * @~English  Print out information of this object, for only debug.
         * @~Japanese このMeshクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Render this object, for inner use.
         * @~Japanese このノードをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;

    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int getReferences_xxx (Object3D** references) const;

    private:
        Mesh (const Mesh& mesh);
        Mesh operator= (const Mesh& mesh);

        /**
         * @~English   
         * @~Japanese  共通初期化処理
         */
        void initialize (VertexBuffer* vertices, int num_submesh, IndexBuffer** submeshes, Appearance** appearances);


    protected:
        VertexBuffer*             vertices;
        std::vector<IndexBuffer*> indices;
        std::vector<Appearance*>  appearances;

    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Mesh& mesh);


#endif
