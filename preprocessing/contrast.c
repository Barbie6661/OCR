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
      Uint8 nv = ((r+g+b)/3 - mini)*max/maxi;

      Uint8 d = nv/25;
      if (nv%25 > 12)
        d += 1;
      nv = 25 * d;

      pixel = SDL_MapRGB(image->format, nv, nv, nv);
      putpixel(image, x, y, pixel);
    }
  return image;
}
