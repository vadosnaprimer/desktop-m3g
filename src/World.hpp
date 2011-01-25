#ifndef __M3G_WORLD_HPP__
#define __M3G_WORLD_HPP__

#include "m3g/Group.hpp"
#include <iosfwd>
#include <vector>



namespace m3g {

    class Camera;
    class Background;

    /**
     * @~English  A special Group node that is a top-level container for scene graphs.
     * @~Japanese シーングラフを保持する最上位の特殊グループノード.
     */
    class World : public Group
    {

    public:
        /**
         * @~English  Creates an empty World with default values.
         * @~Japanese デフォルト値のWorldオブジェクトの作成.
         */
        World ();

        /**
         * @~English  Destructs this objects.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~World ();

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        World* duplicate () const;


        /**
         * @~English  Gets the currently active cameara.
         * @~Japanese カレントのアクティブカメラの取得.
         */
        Camera* getActiveCamera () const;

        /**
         * @~English  Retrieves the background settings of this World.
         * @~Japanese このWorldのバックグラウンド設定の取得.
         */
        Background* getBackground () const;

        /**
         * @~English  Sets the Camera to use when rendering this World.
         * @~Japanese このWorldをレンダリングするときに使われるカメラの設定.
         */
        void setActiveCamera (Camera* camera);

        /**
         * @~English  Sets the Background object for this World.
         * @~Japanese このWorldのバックグラウンドオブジェクトの設定.
         */
        void setBackground (Background* background);

        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このWorldクラスの情報を表示する。デバッグ用.
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
        virtual World* duplicate_xxx (Object3D* obj) const;

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
        World (const World& wld);
        World& operator= (const World& wld);

    private:
        Background* background;
        Camera*     active_camera;
    };


} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::World& wld);


#endif
