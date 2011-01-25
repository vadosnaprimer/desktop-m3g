
#ifndef __M3G_ANIMATION_TRACK_HPP__
#define __M3G_ANIMATION_TRACK_HPP__

#include "m3g/Object3D.hpp"
#include <iosfwd>

namespace m3g {

    class KeyframeSequence;
    class AnimationController;

    /**
     * @~English  Associates a KeyframeSequence with an AnimationController and
     *            an animatable property.
     * @~Japanese アニメーションコントローラーやアニメーション可能なプロパティを
     *            キーフレームシーケンスに関連づける.
     */
    class AnimationTrack : public Object3D
    {

    public:
        /**
         * @~English  Specifies the alpha factor of a Node, or the alpha component 
         *            of the Background color, Material diffuse color, or VertexBuffer 
         *            default color as an animation target.
         * @~Japanese ノードのα値や背景色、マテリアルの拡散カラー係数、
         *            頂点バッファーのデフォルト色をアニメーションターゲットに指定する定数.
         */
        static const int ALPHA             = 256;
        /**
         * @~English  Specifies the amibient color of a Material as an animation target.
         * @~Japanese マテリアルの環境光係数をアニメーションターゲットに指定する定数.
         */
        static const int AMBIENT_COLOR     = 257;
        /**
         * @~English  Specifies the color of a Light, Background, or Fog,
         *            or the texture blend clolor in Texture2D, 
         *            or the VertexBuffer default color as an animation target.
         * @~Japanese ライト、バックグラウンド、フォグ、テクスチャーのブレンド色、
         *            頂点バッファーのデフォルト色をアニメーションターゲットに指定する定数.
         */
        static const int COLOR             = 258;
        /**
         * @~English  Specifies the cropping parameters of a Sprite3D or Background
         *            as an animation target.
         * @~Japanese スプライト3Dや背景のクロップパラメーターをアニメーションターゲットに
         *            指定する定数.
         */
        static const int CROP              = 259;
        /**
         * @~English  Specifies the fog density in Fog as an animation target.
         * @~Japanese フォグのフォグ密度をアニメーションターゲットに指定する定数.
         */
        static const int DENSITY           = 260;
        /**
         * @~English  Specifies the diffuse color of a Material as an animation target.
         * @~Japanese マテリアルの拡散カラー係数をアニメーションターゲットに指定する定数.
         */
        static const int DIFFUSE_COLOR     = 261;
        /**
         * @~English  Spedcifies the emissive color of a Material as an animation target.
         * @~Japanese マテリアルの事故発光カラー係数をアニメーションターゲットに指定する定数.
         */
        static const int EMISSIVE_COLOR    = 262;
        /**
         * @~English  Spedcifies the far distance of a Cmaera or Fog  as an animation target.
         * @~Japanese カメラもしくはフォグのファー距離をアニメーションターゲットに指定する定数.
         */
        static const int FAR_DISTANCE      = 263;
        /**
         * @~English  Specifies the field of view of a Camera as an animation target.
         * @~Japanese カメラの視野角をアニメーションターゲットに指定する定数.
         */
        static const int FIELD_OF_VIEW     = 264;
        /**
         * @~English  Specifies the intensity of a Light as an animation target.
         * @~Japanese ライトの強度をアニメーションターゲットに指定する定数.
         */
        static const int INTENSITY         = 265;
        /**
         * @~English  Specifies the morph target weights of a MorphingMesh as an animation target.
         * @~Japanese モーフィングメッシュのモーフターゲットウェイトをアニメーションターゲットに指定する定数.
         */
        static const int MORPH_WEIGHTS     = 266;
        /**
         * @~English  Spedcifies the near distance of a Cmaera or Fog  as an animation target.
         * @~Japanese カメラもしくはフォグのニア距離をアニメーションターゲットに指定する定数.
         */
        static const int NEAR_DISTANCE     = 267;
        /**
         * @~English  Specifies the orientation(R) component of a Transformable object
         *            as an animation target.
         * @~Japanese トランスフォーム可能なオブジェクトの回転成分をアニメーションターゲットに
         *            指定する定数.
         */
        static const int ORIENTATION       = 268;
        /**
         * @~English  Specifies the picking enable flag of a Node as an animation target.
         * @~Japanese ノードのピッキング可能フラグをアニメーションターゲットに指定する定数.
         */
        static const int PICKABILITY       = 269;
        /**
         * @~English  Speifies the scale(S) componentn of a Transformable object
         *            as an animation target.
         * @~Japanese トランスフォーム可能なオブジェクトのスケール成分を
         *            アニメーションターゲットに指定する定数.
         */
        static const int SCALE             = 270;
        /**
         * @~English  Specifies the shininess of a Material as an animation target.
         * @~Japanese マテリアルのshininess成分をアニメーションターゲットに指定する定数.
         */
        static const int SHININESS         = 271;
        /**
         * @~English  Specifies the specular color of a Material as an animation target.
         * @~Japanese マテリアルの鏡面カラー係数をアニメーションターゲットに指定する定数.
         */
        static const int SPECULAR_COLOR    = 272;
        /**
         * @~English  Specifies the spot angle of a Light as an animation target.
         * @~Japanese ライトのスポット角度をアニメーションターゲットに指定する定数.
         */
        static const int SPOT_ANGLE        = 273;
        /**
         * @~English  Spedcifies the spot exponent of a Light as an animation target.
         * @~Japanese ライトのスポット指数係数をアニメーションターゲットに指定する定数.
         */
        static const int SPOT_EXPONENT     = 274;
        /**
         * @~English  Specifies the tarnlation (T) componentn of a Transformable object 
         *            as an animation target.
         * @~Japanese トランスフォーム可能なオブジェクトの平行移動成分を
         *            アニメーションターゲットに指定する定数.
         */
        static const int TRANSLATION       = 275;
        /**
         * @~English  Specifies the renderingn enable flag of a Node as an animation target.
         * @~Japanese ノードのレンダリングフラグをアニメーションターゲットに指定する定数.
         */
        static const int VISIBILITY        = 276;


    public:
        /**
         * @~English  Creates an animation track with the given keyframe sequence targeting
         *            the given property.
         * @~Japanese 指定されたプロパティのキーフレームシーケンスを持つ
         *            アニメーショントラックを作成する.
         */
        AnimationTrack (KeyframeSequence* sequence, int property);

        /**
         * @~English  Destruct a AnimationTrack object.
         * @~Japanese AnimationTrackクラスのデストラクタ.
         */
        virtual ~AnimationTrack ();


        /**
         * @~English  Creates a duplicate of this Object3D. 
         * @~Japanese このオブジェクトの複製の作成.
         */
        AnimationTrack* duplicate () const;


        /**
         * @~English  Retrieves the animation controller used for 
         *            controllling this animation track.
         * @~Japanese このアニメーショントラックを制御するアニメーションコントローラーを取得する.
         */
        AnimationController* getController () const;

        /**
         * @~English  Returns the keyframe sequence object which defines the keyframe values for this animation track.
         * @~Japanese このアニメーショントラック用のキーフレームの値を持つキーフレームシーケンスを取得する.
         */
        KeyframeSequence* getKeyframeSequence () const;

        /**
         * @~English  Returns the property targeted by this AnimationTrack.
         * @~Japanese このアニメーショントラックによるターゲットプロパティを取得する.
         */
        int getTargetProperty () const;

        /**
         * @~English  Specifieds the animation controller tobe used for 
         *            controlling this animation track.
         * @~Japanese このアニメーショントラックを制御するアニメーションコントローラーを設定する.
         */
        void setController (AnimationController* controller);


        /**
         * @~English  Print out information of this class, for debug only.
         * @~Japanese このAnimationTrackクラスの情報を表示する。デバッグ用.
         */
        virtual std::ostream& print (std::ostream& out) const;

    protected:

        /**
         * @~English  
         * @~Japanese 
         */
        AnimationTrack* duplicate_xxx (Object3D* obj) const;

        /**
         * @~English  
         * @~Japanese 
         */
        virtual int getReferences_xxx (Object3D** references) const;

    private:
        AnimationTrack (const AnimationTrack& anim_track);
        AnimationTrack& operator= (const AnimationTrack& anim_track);

    private:
        int                  property;
        KeyframeSequence*    keyframe_sequence;
        AnimationController* animation_controller;
    };

} // namespase m3g {

std::ostream& operator<< (std::ostream& out, const m3g::AnimationTrack& a);


#endif
