COMPILER=g++
CFLAGS=-I. -Wall -m64 -O2 -pthread
LIBRARIES=-lm
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

.phony: clean

clean:
	rm -f $(BINARY) $(OBJDIR)/*.o *~ core
