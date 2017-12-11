// segmentation.h

# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>

# include "pixel_operations.h"


// Draw red line to delimited characters

// On the width
void DrawWidth(SDL_Surface *picture, int begincolumn, int endcolumn, int line);

// On the height
void DrawHeight(SDL_Surface *picture, int beginline, int endline, int column);

//This file contains function for drawing red lines around character
void Draw (SDL_Surface *picture, int beginline, int endline, int begincolumn, int endcolumn);