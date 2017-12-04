#include "createMat.h"

void init(struct memory *memory) {
  memory->mat = NULL;
  memory->next = NULL;
}

struct matrice *CreateMat(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn)
{
  struct matrice *matrice = malloc(sizeof(struct matrice) * endline + 1 - beginline);
  matrice->lines = endline + 1 - beginline;
  matrice->columns = endcolumn + 1 - begincolumn;
  int mat[matrice->columns * matrice->lines];
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = beginline; i <= endline; i++) {
    for (int j = begincolumn; j <= endcolumn; j++) {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 255)
        mat[j + i * matrice->columns] = 1;
      else
        mat[j + i * matrice->columns] = 0;
    }
  }
  matrice->mat = mat;
  return matrice;
}

//Add matrice to memory
void add_Mat(struct memory *memory, struct matrice *mat) {
  while (memory)
    memory = memory->next;
  memory->mat = mat;
}

void print_matrix(struct matrice *mat) {
  for (int i = 0; i < mat->lines; i++) {
    for (int j = 0; j < mat->columns; j++)
      printf("%d;" , mat->mat[j + i * mat->columns]);
    printf("\n");
  }
  printf("\n");
}

void print_all_matrix(struct memory *memory) {
  for (; memory; memory = memory->next)
    print_matrix(memory->mat);
}

static void Clear_Mats(struct memory *memory) {
  struct memory *tmp = memory;
  for (;memory->next ; memory = tmp) {
    tmp = memory->next;
    free(memory);
  }
  free(tmp);
}

void Clear_memory(struct memory *memory) {
  Clear_Mats(memory);
  free(memory);
}