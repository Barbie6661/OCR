# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "../preprocessing/pixel_operations.h"

// Memory structure
struct memory {
  int					size;
  struct matrix			**matrix;
};

struct matrix {
  double				*mat;
  int					lines;
  int					columns;
};

//Init 
struct memory *init(size_t size);

SDL_Surface* create_image_letter(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn);

struct matrix *resizeMat(SDL_Surface *picture, int dim);

//Add matrice to memory
void add_Mat(struct memory *bank, struct matrix *mat, size_t nbmat);

void print_matrix(double *mat, int lines, int columns);

void print_all_matrix(struct memory *bank, size_t size);

void Clear_memory(struct memory *bank);