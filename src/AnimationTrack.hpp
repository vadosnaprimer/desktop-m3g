
#ifndef __ANIMATION_TRACK_HPP__
#define __ANIMATION_TRACK_HPP__

#include "Object3D.hpp"
#include <iosfwd>

namespace m3g {

class KeyframeSequence;
class AnimationController;

/**
 * アニメーションコントローラーとアニメーション可能なプロパティをキーフレームシーケンスに関連づける.
 */
class AnimationTrack : public Object3D
{
public:
    static const int ALPHA             = 256;
    static const int AMBIENT_COLOR     = 257;
    static const int COLOR             = 258;
    static const int CROP              = 259;
    static const int DENSITY           = 260;
    static const int DIFFUSE_COLOR     = 261;
    static const int EMISSIVE_COLOR    = 262;
    static const int FAR_DISTANCE      = 263;
    static const int FIELD_OF_VIEW     = 264;
    static const int INTENSITY         = 265;
    static const int MORPH_WEIGHTS     = 266;
    static const int NEAR_DISTANCE     = 267;
    static const int ORIENTATION       = 268;
    static const int PICKABILITY       = 269;
    static const int SCALE             = 270;
    static const int SHININESS         = 271;
    static const int SPECULAR_COLOR    = 272;
    static const int SPOT_ANGLE        = 273;
    static const int SPOT_EXPONENT     = 274;
    static const int TRANSLATION       = 275;
    static const int VISIBILITY        = 276;


public:
    /**
     * 指定されたプロパティのキーフレームシーケンスを持つアニメーショントラックを作成する.
     */
    AnimationTrack (KeyframeSequence* sequence, int property);

    /**
     * デストラクタ.
     */
    virtual ~AnimationTrack ();

    /**
     * このアニメーショントラックを制御するアニメーションコントローラーを取得する.
     */
    AnimationController* getController () const;

    /**
     * このアニメーショントラック用のキーフレームの値を持つキーフレームシーケンスを取得する.
     */
    KeyframeSequence* getKeyframeSequence () const;

    /**
     * このアニメーショントラックによるターゲットプロパティを取得する.
     */
    int getTargetProperty () const;

    /**
     * このアニメーショントラックを制御するアニメーションコントローラーを設定する.
     */
    void setController (AnimationController* controller);

    /**
     * このAnimationTrackクラスの情報を表示する。デバッグ用.
     */
  virtual std::ostream& print (std::ostream& out) const;

private:
  int property;
  KeyframeSequence* keyframe_sequence;
  AnimationController* animation_controller;
};

} // namespase m3g {

std::ostream& operator<< (std::ostream& out, const m3g::AnimationTrack& a);


#endif
