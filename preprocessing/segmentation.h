// segmentation.h

# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>


// Draw red line to delimited characters

// On the width
void DrawWidth(SDL_Surface *picture, int begincolumn, int endcolumn, int line);
// On the height

void DrawHeight(SDL_Surface *picture, int beginline, int endline, int column);

void Draw (SDL_Surface *picture, int beginline, int endline, int begincolumn, int endcolumn);

// return the first line where a black pixel was found
int FirstLine (SDL_Surface *picture, int begin);

// return the end line where a black pixel was found linked to the first line
int EndLine (SDL_Surface *picture, int begin);

// return the first column where a black pixel was found
int FirstChar (SDL_Surface *picture, int beginline, int endline, int begincolumn);

// return the last column where a black pixel was found
int EndChar (SDL_Surface *picture, int beginline, int endline, int begincolumn);

int Count_letters(SDL_Surface *picture);
// Detect all characters of the picture
struct memory *DetectAll(SDL_Surface *picture, int nbletters);
