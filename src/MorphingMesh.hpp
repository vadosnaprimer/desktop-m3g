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
     * @~Japanese 頂点モーフィングメッシュを表すシーングラフのノード.
     */
    class MorphingMesh : public Mesh
    {
    public:
        /**
         * @~English  Construct a new MorphingMesh with the given base mesh and morph targets.
         * @~Japanese 指定されたベースメッシュとモーフターゲットを持つ新しいモーフィングメッシュを作成.
         */
        MorphingMesh (VertexBuffer*  base,
                      int            num_targets,
                      VertexBuffer** targets,
                      int            num_submesh,
                      IndexBuffer**  submeshes,
                      Appearance**   appearances);

        /**
         * @~English  Constructs a new MorphingMesh with the given base mesh and morph targets.
         * @~Japanese 指定されたベースメッシュとモーフターゲットを持つ新しいモーフィングメッシュを作成.
         */
        MorphingMesh (VertexBuffer*  base, 
                      int            num_targets, 
                      VertexBuffer** targets,
                      IndexBuffer*   submesh,
                      Appearance*    appearance);

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~MorphingMesh ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual MorphingMesh* duplicate () const;



        /**
         * @~English  Copy this Object3D to specified Object3D, not defined by M3G. 
         * @~Japanese このオブジェクトのデータを引数で指定されたオブジェクトにコピーするM3G非標準の関数.
         */
        void copy (MorphingMesh* mesh) const;


        /**
         * @~English  Returns the morph target VertxBuffer at the given index.
         * @~Japanese 指定されたインデックスのモーフターゲット頂点バッファーの取得.
         */
        VertexBuffer* getMorphTarget (int index) const;

        /**
         * @~English  Returns the number of morph targets in this MorphingMesh.
         * @~Japanese このモーフィングメッシュのモーフターゲット数の取得.
         */
        int getMorphTargetCount () const;

        /**
         * @~English  Gets the current morph target weights for this mesh.
         * @~Japanese このメッシュのカレントのモーフターゲットのウェイトの取得.
         */
        void getWeights (float* weights) const;

        /**
         * @~English  Sets the weights for all morph targets in this mesh.
         * @~Japanese このメッシュの全てのモーフターゲットのウエイトの設定.
         */
        void setWeights (int num_weights, float* weights);

        /**
         * @~English  Print out information of this object.
         * @~Japanese このオブジェクトの情報を表示。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Render this object, for inner use.
         * @~Japanese このMorphingMeshをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;

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
        virtual int getReferences_xxx (Object3D** references) const;

    private:

        MorphingMesh (const MorphingMesh& mesh);
        MorphingMesh& operator= (const MorphingMesh& mesh);


        /**
         * @~English  Morph skin, inner use.
         * @~Japanese スキンを変形させる内部仕様の関数.
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
