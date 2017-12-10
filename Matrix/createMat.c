#include "createMat.h"
#include <math.h>

// Memory structure

/*struct memory {
  int        size;
  struct matrix     **matrix;
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
  bank->size = size;
  bank->matrix = malloc(sizeof(struct matrix) * size);
  for (size_t i = 0; i < size; i++)
    bank->matrix[i] = NULL;
  return bank;
}

struct matrix *resizeMat(SDL_Surface *picture, int dim)
{
  struct matrix *mat = malloc(sizeof(struct matrix) * dim * dim);
  mat->lines = dim;
  mat->columns = dim;
  double *mat1 = malloc(sizeof(double) * dim * dim);
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      pixel = getpixel(picture, i*picture->w/dim, j*picture->h/dim);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
        mat1[i + j * dim] = !(g%254);
    }
  }
  //print_matrix(mat1, dim, dim);
  mat->mat = mat1;
  print_matrix(mat->mat, dim, dim);
  free(mat1);
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
  //print_matrix(mat->mat, mat->lines, mat->columns);
  bank->matrix[nbmat] = mat;
  //print_matrix(bank->matrix[nbmat]->mat,
   //bank->matrix[nbmat]->lines, bank->matrix[nbmat]->columns);
}

void print_matrix(double *mat,int lines,int columns) {
  printf("bM\n");
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++)
      printf("%1g" , mat[j + i * columns]);
    printf("\n");
  }
  printf("\n");
  printf("EM\n");
}

void print_all_matrix(struct memory *bank, size_t size) {
  printf("Begin\n");
  double tab[3] = {3,3,3};
  for (size_t i = 0; i < size; i++)
    bank->matrix[i]->mat = tab;
    /*print_matrix(bank->matrix[i]->mat, bank->matrix[i]->lines,
     bank->matrix[i]->columns);*/

  printf("End\n");
}

/*static void Clear_Mats(struct memory *bank) {
  struct memory *tmp = bank;
  for (;bank->next ; bank = tmp) {
    tmp = bank->next;
    free(bank);
  }
  free(tmp);
}*/

void Clear_memory(struct memory *bank) {
  //Clear_Mats(bank);
  free(bank->matrix);
  free(bank);
}