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
SOURCES := sfmlInterface.cpp textInterface.cpp gameCore.cpp drawable.cpp naught.cpp cross.cpp grid.cpp button.cpp

# header files in this project
HEADERS := sfmlInterface.hpp textInterface.hpp  gameCore.hpp drawable.hpp naught.hpp cross.hpp grid.hpp button.hpp def.hpp 

# other places to look for files for this project
SEARCH  := 

# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.native
