## Makefile dectection of characters
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD -g
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image
 
OBJ= ../createMat.o segmentation.o greyscale.o pixel_operations.o main.o
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
		${RM} ${OBJ} ${DEP} *~
		${RM} main
 
-include ${DEP}
 
# END
