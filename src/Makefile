# File: Makefile
# Author: dgrubb
# Date: 24/04/2018

# Aliases
CC  = gcc
CPP = g++
RM  = rm -rf

# Compilation flags
CPPFLAGS = -O3 \
		   -g \
		   -Wall \
		   -Wextra \
		   -Werror \
		   -pedantic \
		   -fPIC \
		   -std=c++11 \
		   -Wno-vla \
		   -Wno-return-type \
		   -Wno-unused-parameter \
		   -Wno-missing-field-initializers

# Source files
SRCS = oak.cpp \
	acorn/A3000.cpp \
	display.cpp \
	lock.cpp \
	settings.cpp \
	state.cpp \
	timers.cpp \
	debug.cpp

OBJS=$(subst .cpp,.o,$(SRCS))

LDFLAGS=-lconfig++ \
		-lrt \
		-lpthread \
		-lSDL2 \
		-lSDL2_image

####################
# Cleanup directives
####################

all: oak

oak: $(OBJS)
	$(CPP) -o oak $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

clean: clean-objects

dist-clean: clean-objects
	$(RM) oak

clean-objects:
	for i in $(OBJS); \
		do (if test -e "$$i"; then ($(RM) $$i ); fi ); done
