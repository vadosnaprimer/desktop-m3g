#ifndef __M3G_SKINNED_MESH_HPP__
#define __M3G_SKINNED_MESH_HPP__

#include "m3g/Mesh.hpp"
#include "m3g/BoneWeight.hpp"
#include <iosfwd>
#include <vector>


namespace m3g {

    class Group;
    class VertexBuffer;
    class IndexBuffer;
    class RayIntersection;
    class Vector;
  

    /**
     * @~English  A scene graph node that represents a skeletally animated polygon mesh.
     * @~Japanese スケレタルアニメーションつきのポリゴンメッシュを表すシーングラフノード.
     */
    class SkinnedMesh : public Mesh
    {
    public:

        /**
         * @~English  Constructs a new SkinnedMesh witdh the given vertices, submeshes and skeleton.
         * @~Japanese 指定された頂点、サブメッシュ、スケルトンを持つSkinnedMeshを新しく作成する.
         * @param[in] vertices        頂点バッファーデータ.
         * @param[in] num_submesh     頂点インデックスの配列の個数.
         * @param[in] submeshes       頂点インデックスの配列.
         * @param[in] num_appearance  アピアランスの配列の個数.
         * @param[in] appearances     アピアランスの配列.
         * @param[in] skeleton        スケルトン.
         */
        SkinnedMesh (VertexBuffer* vertices      ,
                     int           num_submesh   ,
                     IndexBuffer** submeshes     ,
                     int           num_appearance,
                     Appearance**  apperarances  ,
                     Group*        skeleton       );

        /**
         * @~English  Constructs a new SkinnedMesh witdh the given vertices, submeshes and skeleton.
         * @~Japanese 指定された頂点、サブメッシュ、スケルトンを持つSkinnedMeshを新しく作成する.
         * @param[in] vertices      頂点バッファーデータ.
         * @param[in] submesh       頂点インデックス.
         * @param[in] appearance    アピアランス.
         * @param[in] skeleton      スケルトン.
         */
        SkinnedMesh (VertexBuffer* vertices    , 
                     IndexBuffer*  submesh     , 
                     Appearance*   apperarance ,
                     Group*        skeleton     );

        /**
         * @~English  Destructs this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~SkinnedMesh ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         * @return  複製されたSkinnedMeshオブジェクト.
         */
        SkinnedMesh* duplicate () const;


        /**
         * @~English  Associates a weighted transformation, or "bone", with a range of vertices int this SkinnedMesh.
         * @~Japanese このスキンメッシュの持つ頂点配列に対してボーンによる変形を設定する.
         * @param[in] bone          変形の元になるボーンノード.
         * @param[in] weight        ウェイト値.
         * @param[in] first_vertex  変形を設定する最初の頂点番号.
         * @param[in] num_vertices  変形を設定する頂点の個数.
         */
        void addTransform (Node* bone, int weight, int first_vertex, int num_vertices);

        /**
         * @~English  Returns the at-rest tarnsformation (from local coordinate to bone coordinate)  for a bone node.
         * @~Japanese ボーンノードの基本姿勢の変形(ローカル座標系からボーン座標系への変換行列)を返す.
         * @param[in]  bone          変形行列を求めたいボーンノード.
         * @param[out] tranform     結果を書き込むTransformオブジェクト.
         */
        void getBoneTransform (Node* bone, Transform* transform) const;

        /**
         * @~English Returns the number of vertices influenced by the given bone, filling in the vertices and their weights to given arrays. 
         * @~Japanese 指定されたボーンに影響を受ける頂点の数を返す。与えられた配列に頂点のインデックスとウェイト値が入る.
         * @param[in]  bone            変形行列を求めたいボーンノード.
         * @param[out] vertex_indices  結果を書き込む頂点インデックス配列.
         * @param[out] weights         結果を書き込むウェイト値の配列.

         */
        int getBoneVertices (Node* bone, int* vertex_indices, float* weights) const;

        /**
         * @~English  Returns the skeleton Group of this SkinnedMesh.
         * @~Japanese このスキンメッシュのスケルトンGroupを返す.
         * @return  スケルトンとしてセットされたGroupノード.
         */
        Group* getSkeleton () const;


        /**
         * @~English  
         * @~Japanese 
         */
        virtual bool intersect (const Vector& org, const Vector& dir, RayIntersection* ri) const;

        /**
         * @~English  Print out information of this class, for debug only.
         * @~Japanese このSkinnedMeshクラスの情報を表示する。デバッグ用.
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
        virtual SkinnedMesh* duplicate_xxx (Object3D* obj) const;

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

        /**
         * @~English   Register bone and retriev it's index.
         * @~Japanese  ボーンの登録とそのインデックスの取得.
         */
        int addBoneIndex (Node* bone);

        /**
         * @~English   Retriev bone index.
         * @~Japanese  ボーンインデックスの取得.
         */
        int getBoneIndex (Node* bone) const;

    
        /**
         * @~English   Update skin vertices.
         * @~Japanese  スキンの頂点を更新する.
         */
        void updateSkinnedVertices ();

    private:
        /**
         * @~English   
         * @~Japanese  共通初期化処理.
         */
        void initialize ();

        SkinnedMesh (const SkinnedMesh& mesh);
        SkinnedMesh& operator= (const SkinnedMesh& mesh);

    private:
        Group*        skeleton;
        VertexBuffer* skinned_vertices;

        std::vector<std::vector<BoneWeight> > bone_weights;
        std::vector<BindPose>                 bind_poses;
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::SkinnedMesh& mesh);


#endif
