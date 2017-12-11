// segmentation.c
// Cut the picture and returns pointers of begin and end of character

# include <stdlib.h>
#include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "segmentation.h"
# include "draw.h"
# include "pixel_operations.h"
# include "createMat.h"



// Segmentation by line

// return the first line where a black pixel was found
int FirstLine (SDL_Surface *picture, int begin) {
  Uint8 r, g , b;
  Uint32 pixel;
  for (int j = begin; j < picture->h; j++) {
    for (int i = 0; i < picture->w; i++) {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 0) // r == g == b == 0
        return j;
    }
  }
  return -1; // -1 to indicate there is no character
}

// return the end line where a black pixel was found linked to the first line
int EndLine (SDL_Surface *picture, int begin) {
  Uint8 r, g , b;
  Uint32 pixel;
  int none = 0;
  for (int j = begin + 1; j < picture->h; j++) {
    for (int i = 0; i < picture->w; i++) {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 0) // r == g == b == 0
        none = 1;
    }
    if (none == 0)
      return j;
    none = 0;
  }
  return picture->h - 1; // The last line of the picture
}

// Segmentation by column

// return the first column where a black pixel was found
int FirstChar (SDL_Surface *picture, int beginline, int endline, int begincolumn) {
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = begincolumn; i < picture->w; i++) {
    for (int j = beginline; j <= endline; j++) {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 0) // r == g == b == 0
        return i;
    }
  }
  return -1; // No character found
}

// return the last column where a black pixel was found
int EndChar (SDL_Surface *picture, int beginline, int endline, int begincolumn) {
  Uint8 r, g , b;
  Uint32 pixel;
  int none = 0;
  for (int i = begincolumn + 1; i < picture->w; i++) {
    for (int j = beginline; j < endline; j++) {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 0) // r == g == b == 0
        none = 1;
    }
    if (none == 0)
      return i;
    none = 0;
  }
  return picture->w - 1; // The last column of the picture
}

// Count the number of character in the picture
size_t Count_letters(SDL_Surface *picture) {
  size_t cpt = 0;
  int beginline = 0, endline = 0, begincolumn = 0, endcolumn = 0;
  while (beginline < picture->h) {
    beginline = FirstLine(picture, beginline);
    if (beginline == -1)
      break;
    endline = EndLine(picture, beginline);
    while(begincolumn < picture->w) {
      begincolumn = FirstChar(picture, beginline, endline, begincolumn);
      if (begincolumn == -1) //No caracter found
      {
        begincolumn = 0;
        break;
      }
      endcolumn = EndChar(picture, beginline, endline, begincolumn);
      cpt++;
      begincolumn = endcolumn + 2;
    }
    beginline = endline + 2;
  }
  return cpt;
}

// Detect all characters of the picture and create a data bank
struct memory *DetectAll(SDL_Surface *picture, size_t nbletters) {
  size_t cpt = 0;
  struct memory *bank = init(nbletters);
  int beginline = 0, endline = 0, begincolumn = 0, endcolumn = 0;
  while (beginline < picture->h) {
    beginline = FirstLine(picture, beginline);
    if (beginline == -1)
      break;
    endline = EndLine(picture, beginline);
    while(begincolumn < picture->w) {
      begincolumn = FirstChar(picture, beginline, endline, begincolumn);
      if (begincolumn == -1) //No caracter found
      {
        begincolumn = 0;
        break;
      }
      endcolumn = EndChar(picture, beginline, endline, begincolumn);
      // Add Matrix 30 * 30 to the data bank
      add_Mat(bank, resizeMat(create_image_letter(picture,beginline,
       endline, begincolumn,endcolumn),30), cpt);
      cpt++;
      Draw(picture, beginline, endline, begincolumn, endcolumn);
      begincolumn = endcolumn + 2;
    }
    beginline = endline + 2;
  }
  return bank;
}
