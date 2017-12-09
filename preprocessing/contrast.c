# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "pixel_operations.h"


SDL_Surface* contrast(SDL_Surface* image)
{
  Uint8 maxi = 0;
  Uint8 mini = 255;
  
    for (unsigned x = 0; x < (unsigned)(image->w); x++)
    for (unsigned y = 0; y < (unsigned)(image->h); y++)
    {
      Uint32 pixel = getpixel(image, x, y);
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      if ((r+g+b)/3 > maxi)
        maxi = (r+g+b)/3;
      if ((r+g+b)/3 < mini)
        mini = (r+g+b)/3;
    }
  Uint8 max = 255;

  for (unsigned x = 0; x < (unsigned)(image->w); x++)
    for (unsigned y = 0; y < (unsigned)(image->h); y++)
    {
      Uint32 pixel = getpixel(image, x, y);
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(pixel, image->format, &r, &g, &b);
      Uint8 c = ((r+g+b)/3 - mini)*max/maxi;

      Uint8 t = c / 25;
      if (c % 25 > 12)
         t += 1;
      c = 25 * t;

      pixel = SDL_MapRGB(image->format, c, c, c);
      putpixel(image, x, y, pixel);
    }
  return image;
}
