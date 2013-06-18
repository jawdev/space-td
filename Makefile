COMPILER=g++
MACHINE=$(shell uname -s)
ifeq ($(MACHINE),Darwin)
	LIBRARIES=-lm SDLmain.m -framework SDL -framework OpenGL -framework Cocoa
	CFLAGS=-I. -I/Library/Frameworks/SDL.framework/Headers -Wall -m64 -O2 -pthread
else
	LIBRARIES=-lm -lSDL -lGL
	CFLAGS=-I. -Wall -m64 -O2 -pthread
endif
OBJDIR=.obj
SOURCES=main.cc
DEPENDENCIES=config.h
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
