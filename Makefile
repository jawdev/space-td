COMPILER=g++
MACHINE=$(shell uname -s)
CFLAGS=-I. -Wall -m64 -O2 -pthread
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
SOURCES=shader.cc main.cc
DEPENDENCIES=shader.h config.h
BINARY=spacetd

#################################################

OBJ = $(patsubst %,$(OBJDIR)/%.o,$(SOURCES))

$(OBJDIR)/%.o: % $(DEPENDENCIES)
	$(COMPILER) -c -o $@ $< $(CFLAGS)

$(BINARY): $(OBJ)
	$(COMPILER) -o $@ $^ $(CFLAGS) $(LIBRARIES)

.PHONY: clean

clean:
	rm -f $(BINARY) $(OBJDIR)/*.o *~ core
