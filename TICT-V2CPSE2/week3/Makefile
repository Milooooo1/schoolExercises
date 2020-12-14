#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := ball.cpp wall.cpp drawable.cpp cube.cpp screen_object.cpp image.cpp

# header files in this project
HEADERS := ball.hpp wall.hpp drawable.hpp cube.hpp screen_object.hpp exceptions.hpp image.hpp

# other places to look for files for this project
SEARCH  :=

# set REATIVE to the next higher directory
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
