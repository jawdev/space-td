COMPILER=g++
MACHINE=$(shell uname -s)
ifeq ($(MACHINE),Darwin)
	CFLAGS=-I. -I/usr/share/SDL/include/SDL2 -Wall -m64 -O2 -pthread
	LIBRARIES=-lm -L/usr/share/sdl/lib -lSDL2main -lSDL2 -framework OpenGL -framework Cocoa
else
	CFLAGS=-I. -Wall -m64 -O2 -pthread
	LIBRARIES=-lm -lSDL
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
