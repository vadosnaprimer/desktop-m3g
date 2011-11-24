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
     * @~Japanese メッシュ（ポリゴンからなるサーフェス）を定義するシーングラフのノード.
     */
    class Mesh : public Node
    {
    public:
        /**
         * @~English  Constructs a new Mesh with the given VertexBuffer and submeshes.
         * @~Japanese 指定された頂点バッファーとサブメッシュから新しいメッシュを作成する.
         * @param[in] vertices        頂点バッファーデータ.
         * @param[in] num_submesh     頂点インデックスの配列の個数.
         * @param[in] submeshes       頂点インデックスの配列.
         * @param[in] num_appearance  アピアランスの配列の個数.
         * @param[in] appearances     アピアランスの配列.
         */
        Mesh (VertexBuffer* vertices,
              int           num_submesh,
              IndexBuffer** submeshes,
              int           num_appearance,
              Appearance**  appearances);

        /**
         * @~English Constructs a new Mesh consisting of only one submesh. 
         * @~Japanese サブメッシュ1つからなる新しいメッシュを作成する.
         * @param[in] vertices      頂点バッファーデータ.
         * @param[in] submesh       頂点インデックス.
         * @param[in] appearance    アピアランス.
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
         * @return  複製されたMeshオブジェクト.
         */
        Mesh* duplicate () const;

        /**
         * @~English  Gets the current Appearance of the specified submesh.
         * @~Japanese 指定された番号のサブメッシュのアピアランスを取得.
         * @param[in] index サブメッシュの番号.
         * @return  アピアランス.
         */
        Appearance* getAppearance (int index) const;

        /**
         * @~English  Retrieves the submesh at the given index.
         * @~Japanese 指定された番号ののサブメッシュの頂点デックスを取得.
         * @param[in] index   サブメッシュの番号.
         * @return  頂点インデックスバッファー.
         */
        IndexBuffer* getIndexBuffer (int index) const;

        /**
         * @~English  Gets the number of submeshes in this Mesh.
         * @~Japanese このメッシュのサブメッシュ数を取得.
         * @return サブメッシュの総数.
         */
        int getSubmeshCount () const;

        /**
         * @~English  Gets the vertex buffer of this Mesh.
         * @~Japanese このメッシュの頂点バッファーの取得.
         * @return 頂点バッファー.
         */
        VertexBuffer* getVertexBuffer () const;

        /**
         * @~English  Sets the Appearance ofr the specified submesh.
         * @~Japanese 指定された番号のサブメッシュのアピアランスを設定.
         * @param[in] index        サブメッシュの番号.
         * @param[in] appearance   アピアランス.
         */
        void setAppearance (int index, Appearance* appearance);


        /**
         * @~English   Not in M3G specification.
         * @~Japanese  内部使用の関数.
         * 座標は全てこのメッシュのローカル座標系で指定する.
         */
        virtual bool intersect (const Vector& org, const Vector& dir, RayIntersection* ri) const;

        /**
         * @~English  Print out information of this object, for only debug.
         * @~Japanese このMeshクラスの情報を表示する。デバッグ用.
         * @param[in] out  表示先のストリーム
         */
        virtual std::ostream& print (std::ostream& out) const;


    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int animate_xxx (int world_time);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual Mesh* duplicate_xxx (Object3D* obj) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int getReferences_xxx (Object3D** references) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void render_xxx (RenderState& state) const;

    private:
        Mesh (const Mesh& mesh);
        Mesh operator= (const Mesh& mesh);

        /**
         * @~English   
         * @~Japanese  共通初期化処理
         */
        void initialize (VertexBuffer* vertices, int num_submesh, IndexBuffer** submeshes, int num_appearance, Appearance** appearances);


    protected:
        VertexBuffer*             vertices;
        std::vector<IndexBuffer*> indices;
        std::vector<Appearance*>  appearances;

    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Mesh& mesh);


#endif
