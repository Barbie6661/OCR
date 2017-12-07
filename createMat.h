# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "preprocessing/pixel_operations.h"

// Memory structure
struct memory {
  int					size;
  struct matrix			**matrix;
};

struct matrix {
  int					*mat;
  int					lines;
  int					columns;
};

//Init 
struct memory *init(int size);

struct matrix *CreateMat(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn);

//Add matrice to memory
void add_Mat(struct memory *bank, struct matrix *mat, int nbmat);

void print_matrix(int *mat, int lines, int columns);

void print_all_matrix(struct memory *bank, int size);

void Clear_memory(struct memory *bank);