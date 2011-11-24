#ifndef __M3G_MORPHING_MESH_HPP__
#define __M3G_MORPHING_MESH_HPP__

#include "m3g/Mesh.hpp"
#include <iosfwd>


namespace m3g {

    class VertexBuffer;
    class IndexBuffer;
    class Appearance;
    class AnimationTrack;

    /**
     * @~English  A scene graph node that represents a vertex morphing polygon mesh.
     * @~Japanese モーフィングメッシュを表すシーングラフのノード.
     */
    class MorphingMesh : public Mesh
    {
    public:
        /**
         * @~English  Construct a new MorphingMesh with the given base mesh and morph targets.
         * @~Japanese 指定されたベースメッシュとモーフターゲットを持つ新しいモーフィングメッシュを作成.
         * @param[in] vertices        頂点バッファーデータ.
         * @param[in] num_targets     モーフターゲットの個数
         * @param[in] targets         モーフターゲットの配列
         * @param[in] num_submesh     頂点インデックスの配列の個数.
         * @param[in] submeshes       頂点インデックスの配列.
         * @param[in] num_appearance  アピアランスの配列の個数.
         * @param[in] appearances     アピアランスの配列.
         */
        MorphingMesh (VertexBuffer*  base          ,
                      int            num_targets   ,
                      VertexBuffer** targets       ,
                      int            num_submesh   ,
                      IndexBuffer**  submeshes     ,
                      int            num_appearance,
                      Appearance**   appearances   );

        /**
         * @~English  Constructs a new MorphingMesh with the given base mesh and morph targets.
         * @~Japanese 指定されたベースメッシュとモーフターゲットを持つ新しいモーフィングメッシュを作成.
         * @param[in] num_targets     モーフターゲットの個数
         * @param[in] targets         モーフターゲットの配列
         * @param[in] submesh       頂点インデックス.
         * @param[in] appearance    アピアランス.
         */
        MorphingMesh (VertexBuffer*  base       , 
                      int            num_targets, 
                      VertexBuffer** targets    ,
                      IndexBuffer*   submesh    ,
                      Appearance*    appearance  );

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~MorphingMesh ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         * @return 複製したMorphingMeshオブジェクト.
         */
        MorphingMesh* duplicate () const;



        /**
         * @~English  Returns the morph target VertxBuffer at the given index.
         * @~Japanese 指定されたインデックスのモーフターゲット頂点バッファーの取得.
         * @param[in] index  サブメッシュ番号.
         * @return  サブメッシュ番号で指定された頂点インデックスバッファー.
         */
        VertexBuffer* getMorphTarget (int index) const;

        /**
         * @~English  Returns the number of morph targets in this MorphingMesh.
         * @~Japanese このモーフィングメッシュのモーフターゲット数の取得.
         ＊@return  ターゲット数.
         */
        int getMorphTargetCount () const;

        /**
         * @~English  Gets the current morph target weights for this mesh.
         * @~Japanese このメッシュのカレントのモーフターゲットのウェイトの取得.
         * @param[out] weights  結果を書き込むウェイト値の配列.
         */
        void getWeights (float* weights) const;

        /**
         * @~English  Sets the weights for all morph targets in this mesh.
         * @~Japanese このメッシュの全てのモーフターゲットのウエイトの設定.
         * param[in] num_weights  ウェイト値の配列の総数.
         * param[in] weights      ウェイト値の配列.
         */
        void setWeights (int num_weights, float* weights);

        /**
         * @~English  Print out information of this object.
         * @~Japanese このオブジェクトの情報を表示。デバッグ用.
         * @param[in] out  表示先のストリーム
         */
        virtual std::ostream& print (std::ostream& out) const;


    protected:
        /**
         * @~English  
         * @~Japanese 
         */
        virtual void addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int animate_xxx (int world_time);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual MorphingMesh* duplicate_xxx (Object3D* obj) const;

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

        MorphingMesh (const MorphingMesh& mesh);
        MorphingMesh& operator= (const MorphingMesh& mesh);


        /**
         * @~English  Morph skin, inner use.
         * @~Japanese スキンを変形させる内部使用の関数.
         */
        void updateMorphedVertices ();

        /**
         * @~Japanesse  共通初期化処理.
         */
        void initialize (int num_targets, VertexBuffer** targets);


    private:

        VertexBuffer*              morphed_vertices;
        std::vector<VertexBuffer*> morph_targets;
        std::vector<float>         morph_weights;
    
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::MorphingMesh& m);



#endif
