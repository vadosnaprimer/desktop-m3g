
#ifndef __M3G_ANIMATION_CONTROLLER_HPP__
#define __M3G_ANIMATION_CONTROLLER_HPP__

#include "m3g/Object3D.hpp"
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
         * @return 複製されたAnimationControllerオブジェクト.
         */
        AnimationController* duplicate () const;

        /**
         * @~English  Retrieve the ending time of the current active interval of this animation controller, in the world time units.
         * @~Japanese このアニメーションコントローラーのアクティブ期間の終了時刻を返す。単位はワールド時間.
         * @return アクティブ区間の終了時刻.
         */
        int   getActiveIntervalEnd () const;

        /**
         * @~English  Retrieve the starting time of the current active interval of this animation controller, in the world time units.
         * @~Japanese  このアニメーションコントローラーのアクティブ期間の開始時刻を返す。単位はワールド時間.
         * @return アクティブ区間の開始時刻.
         */
        int   getActiveIntervalStart () const;

        /**
         * @~English  Retrievews the sequence time that corresponds to the given world time.
         * @~Japanese 与えられたワールド時刻に一致するシーケンス時刻の取得.
         * @param[in] world_time  ワールド時刻.
         * @return 与えられたワールド時刻に対応するシーケンス時刻
         */
        float getPosition (int world_time) const;

        /**
         * @~English  Returns the current reference world time.
         * @~Japanese カレントのリファレンスワールド時間の取得.
         * @return リファレンスとしているワールド時間.
         */
        int   getRefWorldTime () const;

        /**
         * @~English  Retrieves the currently set playback speed of this animation controller.
         * @~Japanese このアニメーションコントローラーに設定された再生速度の取得.
         * @return 再生速度.
         */
        float getSpeed () const;

        /**
         * @~English  Retrieves the currently set blending weight for this animation controller.
         * @~Japanese このアニメーションコントローラーに設定されたブレンドウェイトを返す.
         * @return ウェイト値.
         */
        float getWeight () const;

        /**
         * @~English  Sets the world time interval during which this animation controller is active.
         * @~Japanese このアニメーションコントローラーがアクティブなワールド時間の期間を設定する。
         * @param[in] start アクティブ区間の開始時刻.
         * @param[in] end   アクティブ区間の終了時刻.
         */
        void  setActiveInterval (int start, int end);

        /**
         * @~English  Sets a new playback position, relative to world time.
         * @~Japanese あるワールド時刻に対応する再生位置（シーケンス時刻）を新しく指定する.
         * @param[in] sequence_time シーケンス時刻.
         * @param[in] world_time    ワールド時刻.
         */
        void  setPosition (float sequence_time, int world_time);

        /**
         * @~English  Sets a new playback speed for this animation.
         * @~Japanese このアニメーションの再生速度を設定する.
         * @param[in] speed      再生速度。1が標準. 
         * @param[in] world_time 現在のワールド時刻を指定する.
         * 引数のworld_timeはアニメーションをなめらかに変化させるために
         * 内部で必要とするパラメーターで、通常気にする必要はない。
         */
        void  setSpeed (float speed, int world_time);

        /**
         * @~English  Sets the blending weight for this animation controller.
         * @~Japanese このアニメーションコントローラーにウェイト値を設定する.
         * param[in] weight  ウェイト値.
         */
        void  setWeight (float weight);

        /**
         * @internal
         * @~English  query specified world_time is in active interval, This is not under M3G spesification.
         * @~Japanese 指定されたworld_timeがアクティブ区間内だったらtrueを返すM3G非標準の関数.
         * @param[in] world_time ワールド時刻.
         * @return このコントローラーがアクティブならtrue, 非アクティブならfalseが返る.
         */
        bool isActive (int world_time) const;


        /**
         * @~English  Print out information of this class, for debug only.
         * @~Japanese このAnimationControllerオブジェクトの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        virtual AnimationController* duplicate_xxx (Object3D* obj) const;

    private:
        AnimationController (const AnimationController& anim_ctr);
        AnimationController& operator= (const AnimationController& anim_ctr);

    private:
        ActiveInterval active_interval;
        float          blending_weight;
        float          speed;
        float          reference_world_time;
        float          reference_sequence_time;
    };


} // namespace m3g

std::ostream& operator<< (std::ostream& out, const m3g::AnimationController& ctrl);


#endif
