#ifndef __M3G_NODE_HPP__
#define __M3G_NODE_HPP__

#include "m3g/Transformable.hpp"
#include "m3g/m3ginternal.hpp"
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
        Node* duplicate () const;

        /**
         * @~English   Applies alignments to this Node and its descendants.
         * @~Japanese このノードと子孫ノードにアライメントを適応する.
         */
        void align (const Node* reference);


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
         * @~Japanese このノードと先祖のα値を全て乗算した値の取得, M3G非標準.
         */
        float getGlobalAlphaFactor () const;

        /**
         * @~English   Retrieves the transformation matrix from this to target, not in M3G.
         * @~Japanese  このノードから指定のノードまでの変換行列を返すM3G非標準の関数.
         */
        Matrix getGlobalPose (const Node* target) const;

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
         * @~Japanese  このノードから指定されたノードへの座標変換の取得.
         */
        bool getTransformTo (const Node* target, Transform* transform) const;

 
        /**
         * @~English   Retrieves the all ascendant picking enable flag of this Node, not in M3G.
         * @~Japanese このノードの先祖まで遡ったピッキング可能フラグを返す, M3G非標準.
         */
       bool isGlobalPickingEnabled () const;


        /**
         * @~English   Retrieves the all ascendant rendering enable flag of this Node, Not in M3G.
         * @~Japanese このノードの先祖まで遡ったレンダリング可能フラグを返す, M3G非標準.
         */
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
         * @~English  Sets this node to align with the given other nodes(s), or disables alignment.
         * @~Japanese このノードを指定されたノードに整列させる。もしくはアライメントを無効にする.
         */
        void setAlignment (Node* z_ref, int z_target, Node* y_ref, int y_target);


        /**
         * @~English  Sets the alpha factor for this Node.
         * @~Japanese このノードのノードαを設定.
         */
        void setAlphaFactor (float alpha);

        /**
         * @~English  Sets the picking enable flag of this Node.
         * @~Japanese このノードのピッキング可能フラグの設定.
         */
        void setPickingEnable (bool enable);

        /**
         * @~English  Sets the rendering enable flag of this Node.
         * @~Japanese このノードのレンダリング可能フラグの設定.
         */
        void setRenderingEnable (bool enable);

        /**
         * @~English  Sets the scope of this node.
         * @~Japanese このノードのスコープを設定する.
         */
        void setScope (int scope);

        /**
         * @~English  Print out information of this object.
         * @~Japanese このNodeクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~English  Sets parent of this node, not in M3G.
         * @~Japanese このノードの親ノードを設定するM3G非標準の関数.
         */
        void setParent (Node* node);

        /**
         * @~English   Retrieve duplicated node from this node, for inner use.
         * @~Japanese  このノードから複製されたNodeを取得する内部仕様の関数.
         */
        Node* getDuplicatedNode () const;

    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted);

        /**
         * @~English  Implement align().
         * @~Japanese アライメントを実行するalign()関数の実装.
         * @param[in] reference  実行時にアライメント対象を指定する時のノード.
         */
        virtual void align_xxx (const Node* reference);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int animate_xxx (int world_time);

        /**
         * @~English  
         * @~Japanese 
         */
        virtual Node* duplicate_xxx (Object3D* obj) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual void render_xxx (RenderState& state) const;




    private:
        Node (const Node& node);
        Node& operator= (const Node& node);


    private:
        Node*     parent;
        bool      rendering_enable;
        bool      picking_enable;
        float     alpha_factor;
        int       scope;
        Alignment z_alignment;
        Alignment y_alignment;

        Node* duplicated;
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Node& n);



#endif
