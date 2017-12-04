# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "preprocessing/pixel_operations.h"

// Memory structure
struct memory {
  struct matrice		*mat;
  struct memory 		*next;
};

struct matrice {
  int					*mat;
  int 					lines;
  int 					columns;
};

//Init 
void init(struct memory *memory);

struct matrice *CreateMat(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn);

//Add matrice to memory
void add_Mat(struct memory *memory, struct matrice *mat);

void print_matrix(struct matrice *mat);

void print_all_matrix(struct memory *memory);

void Clear_memory(struct memory *memory);