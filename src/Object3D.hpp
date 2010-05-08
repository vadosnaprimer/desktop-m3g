#ifndef __OBJECT3D_HPP__
#define __OBJECT3D_HPP__

#include <GL/glew.h>
#include <iosfwd>
#include <vector>
#include "m3gdef.hpp"
#include "m3ginternal.hpp"
#include "Object.hpp"

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
    virtual void addAnimationTrack (AnimationTrack* animation_track);

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
     * @~English  Retrieves an object that has the given uer ID and is reachable from this object.
     * @~Japanese このオブジェクトと到達できるオブジェクトから指定のユーザーIDのオブジェクトを見つける.
     */
    virtual Object3D* find (int user_id) const;


    /** 
     * @~English  Gets an AnimationTrack by index.
     * @~Japanese 指定のインデックスのアニメーショントラックを見つける.
     */
    AnimationTrack* getAnimationTrack (int index) const;

    /**
     * @~English  Gets the number of AnimationTracks currently associated with this Object3D.
     * @~Japanese このObject3Dに関連づけられているアニメーショントラックの数の取得.
     */
    int getAnimationTrackCount () const;

    /**
     * @~English  Returns the number of direct Object3D references in this object, and fills in the objects to the given array.
     * @~Japanese このオブジェクトから参照しているObject3Dの数を返し、配列をそのポインターで埋める.
     */
    virtual int getReferences (Object3D** references) const;

    /**
     * @~English  Gets the user ID of this object.
     * @~Japanese このオブジェクトのユーザーIDを返す.
     */
    int getUserID () const;

    /**
     * @~English  Rerieves the user object that is currently associated with this Object3D.
     * @~Japanese このオブジェクトに現在関連づけられているユーザーオブジェクトを返す.
     *            注意：本当はkey,valueのペアでなければならない。あとで修正する。
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
     *            注意：本当はkey,valueのペアでなければならない。あとで修正する。
     */
    void setUserObject (int id, char* value);

    /**
     * @~English  Retrievs object type, for inner use.
     * @~Japanese オブジェクトタイプを取得するM3G非標準の関数.
     */
    int  getObjectType () const;

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
     * @~English  Sets object type.
     * @~Japanese オブジェクトタイプの設定.
     */
    void setObjectType (int type);

  

  private:
    int   obj_type;     ///< M3G非標準のオブジェクトタイプ
    int   user_id;
    std::vector<AnimationTrack*> anim_tracks;
  };

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Object3D& obj);

#endif
