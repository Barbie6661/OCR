# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "pixel_operations.h"

// Memory structure
struct memory {
  int					size;
  struct matrix			**tab;
};

struct matrix {
  double				*mat;
  int					lines;
  int					columns;
};

//Init the memory
struct memory *init(size_t size);

// Create an image of the character from the picture
SDL_Surface* create_image_letter(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn);

// Put a picture on a matrix with a size chosen
struct matrix *resizeMat(SDL_Surface *picture, int dim);

//Add matrice to memory
void add_Mat(struct memory *bank, struct matrix *mat, size_t nbmat);

void print_matrix(double *mat, int lines, int columns);

void print_all_matrix(struct memory *bank, size_t size);

void Clear_memory(struct memory *bank, size_t nbletters);
