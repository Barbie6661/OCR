// grayscale.h

# include <SDL/SDL.h>
# include <stdio.h>
# include <stdlib.h>


# include "pixel_operations.h"

// Put the picture in nuance of grey
void Greyscale (SDL_Surface *picture);

//Find seuil value
Uint8 Seuil(SDL_Surface *picture);

// Put the picture only in dark and white
void Binarisation(SDL_Surface *picture, Uint8 seuil);
