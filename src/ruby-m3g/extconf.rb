#!/usr/bin/ruby
require 'mkmf'

$CPPFLAGS += "  -I/usr/include/m3g -Wno-deprecated "
$LDFLAGS  += " -lstdc++ -L/usr/lib -lm3g -lz "

have_library('m3g')
have_library('z')


create_makefile('m3g')

