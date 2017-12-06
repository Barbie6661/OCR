#include "createMat.h"

// Memory structure

/*struct memory {
  size_t        size;
  struct matrix     **matrix;
};

struct matrix {
  size_t          *mat;
  size_t          lines;
  size_t          columns;
};
*/

//Init the memory
struct memory *init(int size) {
  struct memory *bank = malloc(sizeof(struct memory));
  bank->size = size;
  bank->matrix = malloc(sizeof(struct matrix) * size);
  for (int i = 0; i < size; i++)
    bank->matrix[i] = NULL;
  return bank;
}

struct matrix *CreateMat(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn)
{
  int lines = endline + 1 - beginline;
  int columns = endcolumn + 1 - begincolumn;
  struct matrix *mat = malloc(sizeof(struct matrix)
    * lines * columns);
  mat->lines = lines;
  mat->columns = columns;
  int mat1[columns * lines];
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = beginline; i <= endline; i++) {
    for (int j = begincolumn; j <= endcolumn; j++) {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 255)
        mat1[j + i * columns] = 1;
      else
        mat1[j + i * columns] = 0;
    }
  }
  mat->mat = mat1;
  return mat;
}

//Add matrice to memory
void add_Mat(struct memory *bank, struct matrix *mat, int nbmat) {
  bank->matrix[nbmat] = mat;
}

void print_matrix(struct matrix *mat) {
  for (int i = 0; i < mat->lines; i++) {
    for (int j = 0; j < mat->columns; j++)
      printf("%d;" , mat->mat[j + i * mat->columns]);
    printf("\n");
  }
  printf("\n");
}

void print_all_matrix(struct memory *bank, int size) {
  for (int i = 0; i < size; i++)
    print_matrix(bank->matrix[i]);
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