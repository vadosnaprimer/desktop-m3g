#ifndef __RENDER_STATE_HPP__
#define __RENDER_STATE_HPP__

namespace m3g {

    /**
     * @~English  Struct of rendering state, for inner use.
     * @~Japanese レンダリングループ中でデータの受け渡しに使う内部使用の構造体.
     */
    struct RenderState
    {
    public:
      RenderState () : pass(0), light_index(0), layer(0), alpha(1) {};

      int   pass;
      int   light_index;
      int   layer;
      float alpha;
    };


} // namespace m3g

#endif

