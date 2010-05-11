#!/usr/bin/ruby
# -*- coding: utf-8 -*-
require 'm3g'
require 'pp'
require 'opengl'
require 'glew'

class MyApp

  def resize width, height
    g3d = M3G::Graphics3D::instance
    g3d.viewport = 0,0,width,height
    cam = @wld.active_camera
    cam.perspective = 45, height/(width*1.0), 0.1, 100
  end
  
  def display
    g3d = M3G::Graphics3D::instance
    g3d.render @wld
    GLUT.SwapBuffers
  end

  def initialize
puts "hello world"
    GLUT.Init
    GLUT.InitDisplayMode    GLUT::GLUT_DOUBLE | GLUT::GLUT_RGB | GLUT::GLUT_DEPTH
    GLUT.CreateWindow       "Kity on your lap."
    GLEW.Init

    positions = M3G::VertexArray.new 4, 3, 2
    positions[0, 4] = [1,-1,0, 1,1,0, -1,-1,0, -1,1,0]
    p positions[2]

    vertices = M3G::VertexBuffer.new 
    vertices.positions = positions, 1, [0,0,0]
    
    tris = M3G::TriangleStripArray.new 0, [4]
    app  = M3G::Appearance.new
    
    mesh = M3G::Mesh.new vertices, tris, app
    
    cam = M3G::Camera.new
    cam.translate 0,0,5
    
    @wld = M3G::World.new
    @wld.active_camera = cam
    @wld.add_child cam
    @wld.add_child mesh

    key_seq = M3G::KeyframeSequence.new 2,3, M3G::KeyframeSequence::LINEAR
    key_seq.keyframe[0] = 100, [1,10,100]
    pp key_seq.keyframe[0]

    GLUT.ReshapeFunc method(:resize).to_proc
    GLUT.DisplayFunc method(:display).to_proc
    GLUT.MainLoop
  end

end

myapp = MyApp.new

puts "正常終了"

