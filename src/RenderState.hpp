#ifndef __RENDER_STATE_HPP__
#define __RENDER_STATE_HPP__

#include <vector>

namespace m3g {

    /**
     * @~English  Struct of rendering state, for inner use.
     * @~Japanese レンダリングループ中でデータの受け渡しに使う内部使用の構造体.
     */
    struct RenderState
    {
    public:
      RenderState () : pass(0), light_index(0), layer(-999), alpha(1),
                       vertex_color_buffer_ready(false), default_vertex_color(0xffffffff) {};
      int   pass;
      int   light_index;
      int   layer;
      float alpha;
      bool  vertex_color_buffer_ready;
      int   default_vertex_color;
      std::vector<int>   valid_layers;
    };


} // namespace m3g

#endif

