//draw.c

//This file contains function for drawing red lines around character

# include "draw.h"

// Draw red line to delimited characters

// On the width
void DrawWidth (SDL_Surface *picture, int begincolumn, int endcolumn, int line) {
  Uint32 pixel;
  for (int i = begincolumn; i <= endcolumn; i++) {
    // Create a red pixel and put it on the picture at the right place
    pixel = SDL_MapRGB(picture->format, 255, 0, 0);
    putpixel(picture, i, line, pixel);
  }
}

// On the height
void DrawHeight (SDL_Surface *picture, int beginline, int endline, int column) {
  Uint32 pixel;
  for (int j = beginline; j <= endline; j++) {
    pixel = SDL_MapRGB(picture->format, 255, 0, 0);
    putpixel(picture, column, j, pixel);
  }
}

// Draw all around the character
void Draw (SDL_Surface *picture, int beginline, int endline,
int begincolumn, int endcolumn) {
  DrawHeight(picture, beginline, endline, begincolumn);
  DrawHeight(picture, beginline, endline, endcolumn);
  DrawWidth(picture, begincolumn, endcolumn, beginline);
  DrawWidth(picture, begincolumn, endcolumn, endline);
}