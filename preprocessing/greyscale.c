// greyscale.c

# include <SDL/SDL.h>
# include <stdio.h>
# include <stdlib.h>

# include "greyscale.h"

// Put the picture in nuance of grey
void Greyscale (SDL_Surface *picture)
{
  Uint8 r, g, b;
  Uint32 pixel;
  for (int i = 0; i < picture->w; i++)
  {
    for (int j = 0; j < picture->h; j++)
    {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      Uint8 luminance = r * 0.3 + g * 0.59 + b * 0.11;
      Uint32 new_pixel = SDL_MapRGB(picture->format, luminance, luminance, luminance);
      putpixel(picture, i, j, new_pixel);
    }
  }
}

// Put the picture only in dark and white
void Binarisation(SDL_Surface *picture)
{
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = 0; i < picture->w; i++)
  {
    for (int j = 0; j < picture->h; j++)
    {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g < 127)
      	 g = 0;
      else
      	 g = 255;
      pixel = SDL_MapRGB(picture->format, g, g, g);
      putpixel(picture, i, j, pixel);
    }
  }
}
