COMPILER=g++
MACHINE=$(shell uname -s)
CFLAGS=-I. -I/apps/bullet-2.81 -Wall -m64 -pthread -std=c++11 -g
LIBRARIES=-L/apps/bullet-2.81 -lm -lGLEW -lGL -lGLU -lglut
OBJDIR=.obj
SOURCES=utils.cc display.cc camera.cc light.cc shader.cc shape.cc object.cc buffer.cc state.cc manager.cc main.cc
DEPENDENCIES=utils.h geometry.h display.h oglpg_vmath.h light.h camera.h shader.h shape.h object.h buffer.h state.h manager.cc config.h
BINARY=../bin/spacetd

#################################################

OBJ = $(patsubst %,$(OBJDIR)/%.o,$(SOURCES))

$(OBJDIR)/%.o: % $(DEPENDENCIES)
	$(COMPILER) -c -o $@ $< $(CFLAGS)

$(BINARY): $(OBJ)
	$(COMPILER) -o $@ $^ $(CFLAGS) $(LIBRARIES)

.PHONY: clean

clean:
	rm -f $(BINARY) $(OBJDIR)/*.o *~ core
