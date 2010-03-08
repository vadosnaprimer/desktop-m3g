
#ifndef __ANIMATION_CONTROLLER_HPP__
#define __ANIMATION_CONTROLLER_HPP__

#include "Object3D.hpp"
#include "ActiveInterval.hpp"
#include <iosfwd>

namespace m3g {

/**
 * アニメーションシーケンスの位置、速度、ウェイトをコントロールする.
 */
class AnimationController : public Object3D
{
/**
 * アクティブ区間を定義する内部使用の構造体.
 */
struct ActiveInterval
{
  ActiveInterval (float start_, float end_) : start(start_), end(end_) {};
    float start;
    float end;
};

public:
    /**
     * アニメーションコントローラークラスのコンストラクタ.
     */
    AnimationController ();
    /**
     * アニメーションコントローラークラスのデストラクタ.
     */
    virtual ~AnimationController ();

    /**
     * このアニメーションコントローラーのアクティブ期間の終了時刻を返す。単位はワールド時間.
     */
    int   getActiveIntervalEnd () const;

    /**
     *  このアニメーションコントローラーのアクティブ期間の開始時刻を返す。単位はワールド時間.
     */
    int   getActiveIntervalStart () const;

    /**
     * 与えられたワールド時刻に一致するローカル時刻を返す.
     */
    float getPosition (int world_time) const;

    /**
     * カレントのリファレンスワールド時間を返す.
     */
    int   getRefWorldTime () const;

    /**
     * このアニメーションコントローラーに設定されたプレイバック速度を返す.
     */
    float getSpeed () const;

    /**
     * このアニメーションコントローラーに設定されたブレンドウェイトを返す.
     */
    float getWeight () const;

    /**
     * このアニメーションコントローラーがアクティブなワールド時間の期間を設定する。
     */
    void  setActiveInterval (int start, int end);

    /**
     * このアニメーションコントローラーにワールド時間で新しいプレイバック位置を設定する.
     */
    void  setPosition (float sequenceTime, int worldTime);

    /**
     * このアニメーションのプレイバック速度を設定する.
     */
    void  setSpeed (float speed, int worldTime);

    /**
     * このアニメーションコントローラーにブレンドウェイトを設定する.
     */
    void  setWeight (float weight);

    /**
     * このAnimationControllerクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

PRIVATE:
  /**
   * 指定されたワールド時間がアクティブ区間に入っていればtrueを返す.
   */
  bool isActiveInterval (int world_time) const;

private:
  ActiveInterval active_interval;
  float blending_weight;
  float speed;
  float refference_world_time;
  float refference_sequence_time;
};


} // namespace m3g

std::ostream& operator<< (std::ostream& out, const m3g::AnimationController& a);


#endif
