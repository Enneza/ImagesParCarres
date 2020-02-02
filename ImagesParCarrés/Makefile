SHELL = /bin/sh
CC = gcc
MACHINE= $(shell uname -s)


ifeq ($(MACHINE), Darwin)
GL_LDFLAGS = -framework OpenGL -framework GLUT -framework Cocoa
else
GL_LDFLAGS = -lGL -lglut -lGLU
endif

CFLAGS = -Wall -g
LDFLAGS = -lm $(GL_LDFLAGS)

PROGNAME = palette
HEADERS = bmp.h
SOURCES = main.c ppm.c modif.c fonctions_references.c
OBJ = $(SOURCES:.c=.o)

all: $(PROGNAME)

$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

clean:
	@$(RM) $(PROGNAME) $(OBJ) *~ gmon.out core.*