#ifndef __M3G_OBJECT3D_HPP__
#define __M3G_OBJECT3D_HPP__


#include <iosfwd>
#include <vector>
#include "m3g/m3gdef.hpp"
#include "m3g/m3ginternal.hpp"
#include "m3g/Object.hpp"

namespace m3g {

    class AnimationTrack;
    class Graphics3D;
    struct RenderState;

    /**
     * @~English  An abstract base class for all objects that can be part of a 3D world.
     * @~Japanese 3Dワールドに存在する全てのオブジェクトの基底となる抽象クラス.
     */
    class Object3D : public Object
    {
  
    public:
        /**
         * @~English  Construct a new Objec3D object.
         * @~Japanese このオブジェクトを作成するコンストラクタ.
         */
        Object3D ();

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを削除するデストラクタ.
         */
        virtual ~Object3D ();

        /**
         * @~English  Adds the given AnimationTrack to this Object3D, 
         *            potentially changing the order and indices of the previously added tracks.
         * @~Japanese このObject3Dに指定されたアニメーショントラックを追加する。
         *            既存のトラックの順番とインデックスは変更されるかもしれない.
         */
        void addAnimationTrack (AnimationTrack* animation_track);

        /**
         * @~English  Updates all animated properties in this Object3D and all Object3Ds that are reachable from this Object3D.
         * @~Japanese このObject3D自身とここから到達できるObject3Dのアニメーテッドプロパティを更新する.
         */
        virtual int animate (int world_time);

        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        virtual Object3D* duplicate () const;

        /**
         * @~English  Copy this Object3D to specified Object3D, not defined by M3G. 
         * @~Japanese このオブジェクトのデータを引数で指定されたオブジェクトにコピーするM3G非標準の関数.
         */
        void copy (Object3D* obj) const;

        /**
         * @~English  Retrieves an object that has the given uer ID and is reachable from this object.
         * @~Japanese このオブジェクトと到達できるオブジェクトから指定のユーザーIDのオブジェクトを見つける.
         */
        Object3D* find (int user_id) const;


        /** 
         * @~English  Gets an AnimationTrack by index.
         * @~Japanese 指定のインデックスのアニメーショントラックを取得する.
         */
        AnimationTrack* getAnimationTrack (int index) const;

        /**
         * @~English  Gets the number of AnimationTracks currently associated with this Object3D.
         * @~Japanese このObject3Dに関連づけられているアニメーショントラックの数の取得.
         */
        int getAnimationTrackCount () const;

        /**
         * @~English  Returns the number of direct Object3D references in this object, and fills in the objects to the given array.
         * @~Japanese このオブジェクトから参照されているObject3Dの数を返し、
         *            引数の配列をそのポインターで埋める.
         */
        int getReferences (Object3D** references) const;

        /**
         * @~English  Gets the user ID of this object.
         * @~Japanese このオブジェクトのユーザーIDを返す.
         */
        int getUserID () const;

        /**
         * @~English  Rerieves the user object that is currently associated with this Object3D.
         * @~Japanese このオブジェクトに現在関連づけられているユーザーオブジェクトを取得する.
         */
        void* getUserObject () const;

        /**
         * @~English  Removves the given AnimationTrack from this Objet3D, potentially changing the order and indices.of the remaining tracks.
         * @~Japanese このObject3Dから指定されたアニメーショントラックを削除する。
         *            既存のトラックの順番やインデックスは変更されるかもしれない.
         */
        void removeAnimationTrack (AnimationTrack* animation_track);

        /**
         * @~English  Sets the user ID for this object.
         * @~Japanese このオブジェクトのユーザーIDを設定する.
         */
        void setUserID (int user_id);

        /**
         * @~English  Associates an arbitrary, application specific Object wth this Object3D.
         * @~Japanese このObject3Dに任意のアプリケーション固有のオブジェクトを関連づける。
         *            ユーザーオブジェクトはコピーされない.
         */
        void setUserObject (void* user_object);


        /**
         * @~English  Print out information of this object, for debug only.
         * @~Japanese このObject3Dの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;


        /**
         * @~English  Render this object, for inner use.
         * @~Japanese このObject3Dをレンダリングする内部使用の関数.
         */
        virtual void render (RenderState& state) const;

    protected:
        /**
         * @~English  Implement addAniamtionTrack().
         * @~Japanese アニメーション・トラックを追加するaddAnimationTrack()関数の実装関数.
         * @param[in]  animation_track  追加したいアニメーショントラック
         * @param[in]  accepted         このターゲットプロパティを受け付けたらtrueで呼び出す。
         */
        virtual void addAnimationTrack_xxx (AnimationTrack* animation_track, bool accepted);

        /**
         * @~English  Implement getReferences().
         * @~Japanese 参照しているObject3Dを取得するgetReferences()関数の実装関数.
         * @param[in]  animation_track  追加したいアニメーショントラック
         * @param[in]  references  結果を書き込む配列.
         * @return 配列に書き込むObject3Dの個数.
         */
        virtual int getReferences_xxx (Object3D** references) const;




    private:
        Object3D (const Object3D& obj);
        Object3D& operator= (const Object3D& obj);


    private:
        int   user_id;
        void* user_object;
        std::vector<AnimationTrack*> anim_tracks;
    };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Object3D& obj);

#endif
