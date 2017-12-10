## Makefile dectection of characters
 
CC=gcc -fsanitize=address
 
CPPFLAGS= `pkg-config --cflags sdl` -MMD 
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3 -g
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image -lm
 
OBJ= ../Matrix/createMat.o contrast.o segmentation.o greyscale.o pixel_operations.o main.o
DEP= ${OBJ:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
		${RM} ${OBJ} ${DEP} *~
		${RM} main
 
-include ${DEP}
 
# END
