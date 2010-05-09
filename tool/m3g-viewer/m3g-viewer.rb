#!/usr/bin/ruby
require 'Qt4'
require 'M3GWidget'

app = Qt::Application.new ARGV

mw = M3GWidget.new
mw.show

app.exec
