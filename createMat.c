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
  int lines = endline - beginline;
  int columns = endcolumn - begincolumn;
  struct matrix *mat = malloc(sizeof(struct matrix)
    * lines * columns);
  mat->lines = lines;
  mat->columns = columns;
  int *mat1 = malloc(sizeof(int) * columns * lines);
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = begincolumn, k = 0; i < endcolumn; i++, k++) {
    for (int j = beginline, l = 0; j < endline; j++, l++) {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 0 && r == 0)
        mat1[k + l * columns] = 1;
      else
        mat1[k + l * columns] = 0;
    }
  }
  print_matrix(mat1, lines, columns);
  mat->mat = mat1;
  free(mat1);
  return mat;
}

//Add matrice to memory
void add_Mat(struct memory *bank, struct matrix *mat, int nbmat) {
  bank->matrix[nbmat] = mat;
}

void print_matrix(int *mat,int lines,int columns) {
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++)
      printf("%d;" , mat[j + i * columns]);
    printf("\n");
  }
  printf("\n");
}

void print_all_matrix(struct memory *bank, int size) {
  printf("Begin\n");
  for (int i = 0; i < size; i++)
    print_matrix(bank->matrix[i]->mat, bank->matrix[i]->lines,
     bank->matrix[i]->columns);
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