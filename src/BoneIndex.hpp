
#ifndef __BONE_INDEX_HPP__
#define __BONE_INDEX_HPP__

#include "Matrix.hpp"

namespace m3g {

  
  class Node;

    /**
     * @~English  Store bone index and weight, for inner use.
     * @~Japanese ボーンインデックスとウェイトを保持する内部使用の構造体.
     */
    struct BoneIndex {
      BoneIndex (int i, int w) : index(i), weight(w) {};
      int index;
      int weight;
    };

    /**
     * @~English  Store bind pose (at rest).
     * @~Japanese バインドポーズを保存する内部使用の構造体.
     */
    struct BindPose {
      BindPose (Node* n, const Matrix& m) : bone(n), inverse(m) {};
      Node*  bone;
      Matrix inverse;
    };

}// namespace m3g

#endif

