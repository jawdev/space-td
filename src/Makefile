COMPILER=g++
MACHINE=$(shell uname -s)
CFLAGS=-I. -Wall -m64 -O2 -pthread -std=c++11
ifeq ($(MACHINE),Darwin)
	LIBRARIES=-lm -framework OpenGL -framework GLUT -framework Cocoa
else
	ifeq ($(MACHINE),Windows_NT)
		LIBRARIES=-lm -lopengl32 -lglut32 -lglu32
	else
		LIBRARIES=-lm -lGLEW -lGL -lGLU -lglut
	endif
endif
OBJDIR=.obj
SOURCES=display.cc shader.cc shape.cc main.cc
DEPENDENCIES=display.h oglpg_vmath.h shader.h shape.h config.h
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
