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
SOURCES := src/drivers/UART/UART-due.cpp src/drivers/NRF24L01+/NRF.c \
		src/drivers/IO/due-PIO.c src/communication/communication-device.c \
		src/SPI/SPI-due.cpp src/SendIRMessageControl.cpp src/ReceiveIRMessageControl.cpp \
    src/RunGameControl.cpp src/TriggerButtonControl.cpp src/PlayerData.cpp \
		src/communication/communication-host.cpp src/display.cpp src/SpeakerControl.cpp

# header files in this project
HEADERS := $(shell find ./src/ -name "*.h") $(shell find ./src/ -name "*.hpp")

# other places to look for files for this project
SEARCH  := $(shell find ./src/ -type d)

# set RELATIVE to the next higher directory 
# and defer to the appropriate Makefile.* there

HEAP              ?= BMPTK
BMPTK := bmptk
PROJECT = src/device-main

# Agressive optimisations because...
PROJECT_CPP_FLAGS += -O3

RESULTS += src/device-main.lss

RELATIVE := .


RTOS := $(RELATIVE)/rtos

include $(RTOS)/makefile.inc

include $(RELATIVE)/Makefile.due
