## Makefile dectection of characters
 
CC=gcc
 
CPPFLAGS= `pkg-config --cflags sdl` `pkg-config --cflags sdl gtk+-3.0` -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` `pkg-config --libs sdl gtk+-3.0` -lSDL_image -lm -export-dynamic -rdynamic
 
OBJ=main.o segmentation.o greyscale.o pixel_operations.o main.o
DEP= ${SRC:.o=.d}
 
all: main
 
main: ${OBJ}
 
clean:
		${RM} ${OBJ} ${DEP} *~
		${RM} main
 
-include ${DEP}
 
# END
