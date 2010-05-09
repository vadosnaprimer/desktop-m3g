require 'opengl'
require 'm3g'
require 'glew'
require 'pp'

class M3GWidget < Qt::GLWidget
  slots 'tackEvent()', 'tickEvent()'

  def initialize
    super
    @tick = Qt::Timer.new
    @tick.start 1000
    @fps = 0

    @tack = Qt::Timer.new
    @tack.start 33
    @tackCount = 0

    @time = 0

    connect @tick, SIGNAL('timeout()'), self, SLOT('tickEvent()')
    connect @tack, SIGNAL('timeout()'), self, SLOT('tackEvent()')
  end

  def initializeGL
    GLEW.Init
    objs = M3G::Loader::load "test.m3g"
    objs.each { |obj|
      pp obj
      if (obj.instance_of? M3G::World)
        puts "Detect World!"
        @wld = obj
      end
    }
    if (@wld.background == nil)
      @wld.background = M3G::Background.new
    end
    @wld.background.color = 0x003f7fff

  end

  def resizeGL width, height
    g3d = M3G::Graphics3D::instance
    g3d.viewport = 0,0,width,height
    @wld.active_camera.perspective = 45, width/(height*1.0), 0.1, 1000
  end

  def paintGL
    g3d = M3G::Graphics3D::instance
    g3d.render @wld

    renderText 10, 10, "fps = #{@fps}"
    puts "fps = #{@fps}"
  end

  def tackEvent
    @tackCount += 1
    @time += 33
    puts "time = {@time}"
    @wld.animate @time
    if (@time > 10000)
      @time = 0
    end
    updateGL
  end
  
  def tickEvent
    @fps = @tackCount
    @tackCount = 0
  end


end

