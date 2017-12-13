## Makefile dectection of characters
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD 
CFLAGS= -Wall -Wextra -std=c99 -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm
 
OBJ= Matrix/createMat.o preprocessing/contrast.o preprocessing/segmentation.o preprocessing/greyscale.o preprocessing/draw.o preprocessing/pixel_operations.o neuro/layer.o main.o
DEP= ${OBJ:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
		${RM} ${OBJ} ${DEP} *~
		${RM} main
 
-include ${DEP}
 
# END
