#ifndef __OBJECT3D_HPP__
#define __OBJECT3D_HPP__

#include <GL/glew.h>
#include <iosfwd>
#include <vector>
#include "m3gdef.hpp"
#include "m3ginternal.hpp"

namespace m3g {

class AnimationTrack;

/**
 * 3Dワールドに存在する全てのオブジェクトの基底となる抽象クラス.
 */
class Object3D
{
  
public:
    /**
     * コンストラクタ.
     * 規格上はprivateにすべき
     */
    Object3D ();

    /**
     * デストラクタ.
     */
    virtual ~Object3D ();

PROTECTED:
    /**
     * このObject3Dに指定されたアニメーショントラックを追加する。
     * 既存のトラックの順番とインデックスは変更されるかもしれない.
     */
    virtual void addAnimationTrack (AnimationTrack* animation_track);

public:
    /**
     * このObject3D自身とここから到達できるObject3Dのアニメーテッドプロパティを更新する.
     */
    virtual int animate (int world_time);

    /**
     * このObjct3Dの複製を作成する.
     */
    virtual Object3D* duplicate () const;

    /**
     * このオブジェクトと到達できるオブジェクトから指定のユーザーIDのオブジェクトを見つける.
     */
    virtual Object3D* find (int userID) const;


    /** 
     * 指定のインデックスのアニメーショントラックを見つける.
     */
    AnimationTrack* getAnimationTrack (int index) const;

    /**
     * このObject3Dに関連づけられているアニメーショントラックの数の取得.
     */
    int getAnimationTrackCount () const;

    /**
     * このオブジェクトから参照しているObject3Dの数を返し、配列をそのポインターで埋める.
     */
  virtual int getReferences (Object3D** references, int size) const;

    /**
     * このオブジェクトのユーザーIDを返す.
     */
    int getUserID () const;

    /**
     * このオブジェクトに現在関連づけられているユーザーオブジェクトを返す.
     * 注意：本当はkey,valueのペアでなければならない。あとで修正する。
     */
    void* getUserObject () const;

    /**
     * このObject3Dから指定されたアニメーショントラックを削除する。
     * 既存のトラックの順番やインデックスは変更されるかもしれない。
     */
    void removeAnimationTrack (AnimationTrack* animation_track);

    /**
     * このオブジェクトのユーザーIDを設定する.
     */
    void setUserID (int userID);

    /**
     * このObject3Dに任意のアプリケーション固有のオブジェクトを関連づける。
     * ユーザーオブジェクトはコピーされない.
     * 注意：本当はkey,valueのペアでなければならない。あとで修正する。
     */
  void setUserObject (void* user_object_value);

  /**
   * このObject3Dの情報を表示する。デバッグ用.
   */
  virtual std::ostream& print (std::ostream& out) const;


protected:
  /**
   * このObject3Dをレンダリング(する内部使用の関数.
   */
  virtual void render (int pass, int index=0) const;


PROTECTED:

  void setObjectType (int type);
  int  getObjectType () const;
  virtual void findByObjectType (int obj_type, std::vector<Object3D*>& objs) const;
  

private:
  int obj_type;

private:
  int   user_id;
  void* user_object;
  std::vector<AnimationTrack*> anim_tracks;

};

} // namespace m3g {

std::ostream& operator<< (std::ostream& out, const m3g::Object3D& obj);

#endif
