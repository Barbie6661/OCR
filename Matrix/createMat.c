#include "createMat.h"
#include <math.h>

// Memory structure

/*struct memory {
  size_t              size;
  struct matrix     **tab;
};

struct matrix {
  double          *mat;
  int          lines;
  int          columns;
};
*/

//Init the memory
struct memory *init(size_t size) {
  struct memory *bank = malloc(sizeof(struct memory));
  bank->tab = malloc(sizeof(struct matrix) * size);
  bank->size = size;
  for (size_t i = 0; i < size; i++)
    bank->tab[i] = NULL;
  return bank;
}

struct matrix *resizeMat(SDL_Surface *picture, int dim)
{
  struct matrix *mat = malloc(sizeof(struct matrix));
  mat->lines = dim;
  mat->columns = dim;
  mat->mat = malloc(sizeof(double) * dim * dim);
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      pixel = getpixel(picture, i*picture->w/dim, j*picture->h/dim);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
        mat->mat[i + j * dim] = !(g%254);
    }
  }
  SDL_FreeSurface(picture);
  return mat;
}

// Create an image of the character
SDL_Surface* create_image_letter(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn) {
  int height = endline - beginline;
  int width = endcolumn - begincolumn;
  SDL_Surface *pic = SDL_CreateRGBSurface(0,width, height,32,0,0,0,0);
  for (int i = begincolumn, k = 0; i < endcolumn; i++,k++) {
    for (int j = beginline, l = 0; j < endline; j++, l++)
      putpixel(pic, k, l, getpixel(picture, i, j));
  }
  return pic;
}

//Add matrice to memory
void add_Mat(struct memory *bank, struct matrix *mat, size_t nbmat) {
  bank->tab[nbmat] = mat;
}

void print_matrix(double *mat,int lines,int columns) {
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++)
      printf("%1g" , mat[j + i * columns]);
    printf("\n");
  }
  printf("\n");
}

void print_all_matrix(struct memory *bank, size_t size) {
  printf("Begin\n");
  for (size_t i = 0; i < size; i++) {
    print_matrix(bank->tab[i]->mat, bank->tab[i]->lines,
     bank->tab[i]->columns);
  }
  printf("End\n");
}

static void Clear_Mats(struct memory *bank, size_t nbletters) {
  for (size_t i = 0; i < nbletters; i++) {
    free(bank->tab[i]->mat);
    free(bank->tab[i]);
  }

}

void Clear_memory(struct memory *bank, size_t nbletters) {
  Clear_Mats(bank, nbletters);
  free(bank->tab);
  free(bank);
}