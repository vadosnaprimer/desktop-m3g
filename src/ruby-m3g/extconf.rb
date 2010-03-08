#!/usr/bin/ruby
require 'mkmf'

SYSTEM_LIBRARIES = [
    "m3g"
]

$CPPFLAGS += " -std=c++0x -I.. "
$LDFLAGS += " -lstdc++ -L.. -lm3g"

create_makefile('m3g')

