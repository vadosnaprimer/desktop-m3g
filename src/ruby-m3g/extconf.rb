#!/usr/bin/ruby
require 'mkmf'

SYSTEM_LIBRARIES = [
    "m3g"
]

$CPPFLAGS += "  -I.. -Wno-deprecated "
$LDFLAGS += " -lstdc++ -L.. -lm3g"

create_makefile('m3g')

