
#ifndef __M3G_BONE_WEIGHT_HPP__
#define __M3G_BONE_WEIGHT_HPP__

#include "m3g/Matrix.hpp"

namespace m3g {

  
    class Node;

    /**
     * @internal
     * @~English  Store bone index and weight, for inner use.
     * @~Japanese ボーンインデックスとウェイトを保持する内部使用の構造体.
     */
    struct BoneWeight {
        BoneWeight (int i, int w) : index(i), weight(w) {};
        int index;
        int weight;
    };

    /**
     * @internal
     * @~English  Store bind pose (at rest).
     * @~Japanese バインドポーズ(の逆行列)を保存する内部使用の構造体.
     */
    struct BindPose {
        BindPose (Node* n, const Matrix& m) : bone(n), inverse(m) {};
        Node*  bone;
        Matrix inverse;
    };

}// namespace m3g

#endif

