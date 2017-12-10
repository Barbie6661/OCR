// segmentation.h

# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>

// return the first line where a black pixel was found
int FirstLine (SDL_Surface *picture, int begin);

// return the end line where a black pixel was found linked to the first line
int EndLine (SDL_Surface *picture, int begin);

// return the first column where a black pixel was found
int FirstChar (SDL_Surface *picture, int beginline, int endline, int begincolumn);

// return the last column where a black pixel was found
int EndChar (SDL_Surface *picture, int beginline, int endline, int begincolumn);

// Count the number of character in the picture
size_t Count_letters(SDL_Surface *picture);

// Detect all characters of the picture and create a data bank
struct memory *DetectAll(SDL_Surface *picture, size_t nbletters);

