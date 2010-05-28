#ifndef __NODE_HPP__
#define __NODE_HPP__

#include "Transformable.hpp"
#include "m3ginternal.hpp"
#include <iosfwd>

namespace m3g {

    class Transform;
    class Matrix;

    /**
     * @~English  An abstract base class for all scene graph nodes.
     * @~Japanese シーングラフのノードを表す抽象クラス.
     */
    class Node : public Transformable
    {
        friend class Group;      // for ???
        friend class World;      // for ???
        friend class Graphics3D; // for render
        friend class Mesh;       // for node

        /**
         * @~English  Structure of aliment property, for inner use.
         * @~Japanese アライメントを保持する内部使用の構造体.
         */
        struct Alignment {
            Alignment (int t, Node* r) : target(t), reference(r) {};
            int   target;
            Node* reference;
        };

    public:

        /**
         * @~English  Specifies for the setAlignment method that no alignment should be done for the specified axis.
         * @~Japanese setAlignment()関数で指定された軸に対するアライメントがない事を示す定数.
         */
        static const int NONE   = 144;
        /**
         * @~English  Specifies the origin of the reference node as an orientation reference for the setAlighnment method.
         * @~Japanese setAlignment()関数でアライメントがリファレンスノードの原点である事を示す定数.
         */
        static const int ORIGIN = 145;
        /**
         * @~English  Specifies the X axis of the reference node as an orientation reference for the setAlignement method.
         * @~Japanese setAlignment()関数でアライメントがリファレンスノードのX軸である事を示す定数.
         */
        static const int X_AXIS = 146;
        /**
         * @~English  Specifieds the Y axis of the reference node as an orientation reference for the setAlignment mehotd.
         * @~Japanese setAlignment()関数でアライメントがリファレンスノードのY軸である事を示す定数.
         */
        static const int Y_AXIS = 147;
        /**
         * @~English  Specifieds the Z axis of the reference node as an orientation reference for the setAlignment mehotd.
         * @~Japanese setAlignment()関数でアライメントがリファレンスノードのZ軸である事を示す定数.
         */
        static const int Z_AXIS = 148;

        /**
         * @~English   Construct a new Node object. 
         * @~Japanese Nodeオブジェクトを作成するコンストラクタ.
         */
        Node ();

        /**
         * @~English   Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~Node ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual Node* duplicate () const;

        /**
         * @~English   Applies alignments to this Node and its descendants.
         * @~Japanese このノードと子孫ノードにアライメントを適応する.
         */
        virtual void align (Node* reference);

        /**
         * @~English  Adds the given AnimationTrack to this Object3D, 
         *            potentially changing the order and indices of the previously added tracks.
         * @~Japanese このObject3Dに指定されたアニメーショントラックを追加する。
         *            既存のトラックの順番とインデックスは変更されるかもしれない.
         */
        virtual void addAnimationTrack (AnimationTrack* animation_track);

        /**
         * @~English  Updates all animated properties in this Object3D and all Object3Ds that are reachable from this Object3D.
         * @~Japanese このObject3D自身とここから到達できるObject3Dのアニメーテッドプロパティを更新する.
         */
        virtual int animate (int world_time);



        /**
         * @~English   Returns the alignment reference node for the given axis.
         * @~Japanese 指定された軸にアライメントされた参照ノードを返す.
         */
        Node* getAlignmentReference (int axis) const;

        /**
         * @~English   Returns tthe alignment target for the given axis.
         * @~Japanese 指定された軸に対するアライメントターゲットを返す.
         */
        int getAlignmentTarget (int axis) const;

        /**
         * @~English   Retrieves the alpha factor of this Node.
         * @~Japanese このノードのα値の取得.
         */
        float getAlphaFactor () const;

        /**
         * @~English   Retrieves the alpha factor of this Node and all ancestors, not in M3G.
         * @~Japanese このノードと先祖のα値を全て乗算した値の取得, M3G未定義.
         */
        float getGlobalAlphaFactor () const;

        /**
         * @~English   Get global pose matrix (bone coordinate to local coordinate), for inner use.
         * @~Japanese  グローバルポーズ（ボーン座標からローカル座標）を計算するM3G非標準の関数.
         */
        Matrix getGlobalPose () const;

        /**
         * @~English   Returns the scene graph parent of this node.
         * @~Japanese このノードの親ノードの取得.
         */
        Node* getParent () const;

        /**
         * @~English   Returns the top scene graph parent of this node.
         * @~Japanese  このノードの一番上の親ノードの取得.
         */
        Node* getGlobalParent () const;

        

        /**
         * @~English  Retrieves the scope of this Node. 
         * @~Japanese このノードのスコープの取得.
         */
        int getScope () const;

        /**
         * @~English   Gets the composite transfformation from this node to the given node.
         * @~Japanese このノードから指定されたノードへの座標変換の取得.
         */
        bool getTransformTo (const Node* target, Transform* transform) const;

 
       bool isGlobalPickingEnabled () const;


        bool isGlobalRenderingEnabled () const;

        /**
         * @~English   Retrieves the picking enable flag of this Node.
         * @~Japanese このノードのピッキング可能フラグを返す.
         */
        bool isPickingEnabled () const;

        /** 
         * @~English   Retrieves the rendering neble flag of this Node.
         * @~Japanese このノードのレンダリング可能フラグを返す.
         */
        bool isRenderingEnabled () const;


        /**
         * @~English   Sts this node to align with the given other nodes(s), or disables alignment.
         * @~Japanese このノードを指定されたノードに整列させる。もしくはアライメントを無効にする.
         */
        void setAlignment (Node* z_ref, int z_target, Node* y_ref, int y_target);


        /**
         * @~English   Sets the alpha factor for this Node.
         * @~Japanese このノードのα値を設定.
         */
        void setAlphaFactor (float alpha_factor);

        /**
         * @~English   Sets the picking enable flag of this Node.
         * @~Japanese このノードのピッキング可能フラグの設定.
         */
        void setPickingEnable (bool enable);

        /**
         * @~English   Sets the rendering enable flag of this Node.
         * @~Japanese このノードのレンダリング可能フラグの設定.
         */
        void setRenderingEnable (bool enable);

        /**
         * @~English   Sets the scope of this node.
         * @~Japanese このノードのスコープを設定する.
         */
        void setScope (int scope);

        /**
         * @~English   Print out information of this object.
         * @~Japanese このNodeクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English   Sets parent of this node.
         * @~Japanese このノードの親ノードを設定する. 
         */
        void setParent (Node* node);

        /**
         * @~English  Render this object, for inner use.
         * @~Japanese このNodeをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;

    private:
        Node*     parent;
        bool      rendering_enable;
        bool      picking_enable;
        float     alpha_factor;
        int       scope;
        Alignment z_alignment;
        Alignment y_alignment;

    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Node& n);



#endif
