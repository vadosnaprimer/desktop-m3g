#ifndef __GROUP_HPP__
#define __GROUP_HPP__

#include "Node.hpp"
#include <iosfwd>
#include <vector>


namespace m3g {

    class RayIntersection;
    class Camera;

    /**
     * @~Enslish  A scene graph node that stores an unordered set of nodes as its children.
     * @~Japanese 未ソートの複数の子ノードを持つシーングラフのノード.
     */
    class Group : public Node
    {

    public:
        /**
         * @~Enslish  Constructs a new Group node and initializes it with an empty list of children.
         * @~Japanese 子ノードを持たないGroupノードを作成するコンストラクタ.
         */
        Group ();

        /**
         * @~Enslish  Destruct a this Group node.
         * @~Japanese デストラクタ.
         */
        virtual ~Group ();

        /**
         *
         */
        virtual void align (Node* reference);

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual Group* duplicate () const;

        /**
         * @~English  Copy this Object3D to specified Object3D, not defined by M3G. 
         * @~Japanese このオブジェクトのデータを引数で指定されたオブジェクトにコピーするM3G非標準の関数.
         */
        void copy (Group* grp) const;

        /** 
         * @~Enslish  Adds the given node to this Group, potentially changing the order and indices of the previously added children.
         * @~Japanese 指定されたノードを追加する。以前に追加されていた子ノードの順番とインデックスは変更される可能性がある.
         */
        void addChild (Node* child);

        /**
         * @~Enslish  Update animatable property, for inner use.
         * @~Japanese このノードと子ノードをアニメーションする.
         */
        virtual int animate (int world_time);

        /**
         * @~Enslish  Gets a child by index.
         * @~Japanese インデックスを指定して子ノードを取得する.
         */
        Node* getChild (int index) const;

        /**
         * @~Enslish  Gets the number of children in this Group.
         * @~Japanese このグループの子ノードの数を取得する.
         */
        int getChildCount () const;

        /**
         * @~Enslish  Picks the first Mesh or scaled Sprite3D in this Group that is enabled for picking,
         *            is intercepted by the given pick ray, and is in the specified scope.
         * @~Japanese このグループのMeshのうち同じスコープでピッキング可能な最初にヒットしたMeshを返す.
         */
        bool pick (int scope, float x, float y, const Camera* camera, RayIntersection* ri) const;

        /**
         * @~Enslish  Picks the first Mesh or scaled Sprite3D in this Group that is enabled for picking,
         *            is intercepted by the given pick ray, and is in the specified scope.
         * @~Japanese このグループのピッキング可能なMesh,scaled Sprite3Dのうち同じスコープで、指定されたピッキング光線で最初にヒットしたノードを返す.
         */
        bool pick (int scope, float ox, float oy, float oz, float dx, float dy, float dz, RayIntersection* ri) const;


        /**
         * @~Enslish  Picks the first Mesh in this Group that is itercepted by the given pick ray and is in the specified scope.
         * @~Japanese このグループから指定されたノードを削除する。以前に追加されていた子ノードの順番とインデックスは変更される可能性がある.
         */
        void removeChild (Node* child);

        /**
         * @~Enslish  Print out information of this object, for debug only.
         * @~Japanese このGroupクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

        /**
         * @~Enslish  Renderr this object, for inner use.
         * @~Japanese このGroupをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;

    private:
        Group (const Group& grp);
        Group& operator= (const Group& grp);

    protected:
        std::vector<Node*> children;
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Group& g);




#endif
