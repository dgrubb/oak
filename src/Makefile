# File: Makefile
# Author: dgrubb
# Date: 05/03/2019

# Aliases
CC  = gcc
CPP = g++
RM  = rm -rf

CFLAGS = -O3 \
		   -g \
		   -Wall \
		   -std=c11 \
		   -pedantic

# Include directories
INC = -I./ \
	  -I./acorn \
	  -I./acorn/arm2

# Source files
SRCS = oak.c \
	display.c \
	settings.c \
	state.c \
	util.c \
	acorn/A3000.c \
	acorn/ioc.c \
	acorn/memc.c \
	acorn/vidc.c \
	acorn/arm2/arm2.c \
	acorn/arm2/arm_op.c \
	debug.c

OBJS=$(subst .c,.o,$(SRCS))

LDFLAGS=-lconfig \
		-lrt \
		-lpthread \
		-lSDL2 \
		-lSDL2_image

####################
# Cleanup directives
####################

all: oak

oak: $(OBJS)
	$(CC) $(INC) -o oak $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

check:
	cppcheck -v --std=c11 --language=c --enable=all ./

clean: clean-objects

dist-clean: clean-objects
	$(RM) oak

clean-objects:
	for i in $(OBJS); \
		do (if test -e "$$i"; then ($(RM) $$i ); fi ); done
