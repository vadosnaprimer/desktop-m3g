
#ifndef __ANIMATION_CONTROLLER_HPP__
#define __ANIMATION_CONTROLLER_HPP__

#include "Object3D.hpp"
#include <iosfwd>

namespace m3g {

  /**
   * @~English  Controls the position, speed and weight of an animation sequence.
   * @~Japanese アニメーションシーケンスの位置、速度、ウェイトをコントロールする.
   */
  class AnimationController : public Object3D
  {
    /**
     * @~English  Structure of active interval.
     * @~Japanese アクティブ区間を保持する内部使用の構造体.
     */
    struct ActiveInterval
    {
      ActiveInterval (float start_, float end_) : start(start_), end(end_) {};
      float start;
      float end;
    };

  public:
    /**
     * @~English  Create a new AnimationController object.
     * @~Japanese アニメーションコントローラークラスのコンストラクタ.
     */
    AnimationController ();

    /**
     * @~English  Destruct a AnimationController object.
     * @~Japanese アニメーションコントローラークラスのデストラクタ.
     */
    virtual ~AnimationController ();


    /**
     * @~English  Creates a duplicate of this Object3D. 
     * @~Japanese このオブジェクトの複製の作成.
     */
    virtual AnimationController* duplicate () const;

    /**
     * @~English  Retrieve the ending time of the current active interval of this animation controller, in the world time units.
     * @~Japanese このアニメーションコントローラーのアクティブ期間の終了時刻を返す。単位はワールド時間.
     */
    int   getActiveIntervalEnd () const;

    /**
     * @~English  Retrieve the starting time of the current active interval of this animation controller, in the world time units.
     * @~Japanese  このアニメーションコントローラーのアクティブ期間の開始時刻を返す。単位はワールド時間.
     */
    int   getActiveIntervalStart () const;

    /**
     * @~English  Retrievews the sequence time that corresponds to the given world time.
     * @~Japanese 与えられたワールド時刻に一致するローカル時刻を返す.
     */
    float getPosition (int world_time) const;

    /**
     * @~English  Returns the current feference world time.
     * @~Japanese カレントのリファレンスワールド時間を返す.
     */
    int   getRefWorldTime () const;

    /**
     * @~English  Retrieves the currently set playback speed of this animation controller.
     * @~Japanese このアニメーションコントローラーに設定された再生速度を返す.
     */
    float getSpeed () const;

    /**
     * @~English  Retrieves the currently set blending weight for this animation controller.
     * @~Japanese このアニメーションコントローラーに設定されたブレンドウェイトを返す.
     */
    float getWeight () const;

    /**
     * @~English  Sets the world time interval during which this animation controller is active.
     * @~Japanese このアニメーションコントローラーがアクティブなワールド時間の期間を設定する。
     */
    void  setActiveInterval (int start, int end);

    /**
     * @~English  Sets a new playback position, relative to world time.
     * @~Japanese このアニメーションコントローラーにワールド時間で新しい再生位置を設定する.
     */
    void  setPosition (float sequenceTime, int worldTime);

    /**
     * @~English  Sets a new playback speed for this animation.
     * @~Japanese このアニメーションの再生速度を設定する.
     */
    void  setSpeed (float speed, int worldTime);

    /**
     * @~English  Sets the blending weight for this animation controller.
     * @~Japanese このアニメーションコントローラーにブレンドウェイトを設定する.
     */
    void  setWeight (float weight);

    /**
     * @~English  query specified world_time is in active interval, This is not under M3G spesification.
     * @^Japanese 指定されたworld_timeがアクティブ区間内だったらtrueを返すM3G非標準の関数.
     */
    bool isActiveInterval (int world_time) const;

    /**
     * @~English  Print out information of this class, for debug only.
     * @~Japanese このAnimationControllerクラスの情報を表示する。デバッグ用.
     */
    virtual std::ostream& print (std::ostream& out) const;


  private:
    ActiveInterval active_interval;
    float          blending_weight;
    float          speed;
    float          refference_world_time;
    float          refference_sequence_time;
  };


} // namespace m3g

std::ostream& operator<< (std::ostream& out, const m3g::AnimationController& a);


#endif
