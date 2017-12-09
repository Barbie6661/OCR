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
struct memory *init(int size) {
  struct memory *bank = malloc(sizeof(struct memory));
  bank->size = size;
  bank->matrix = malloc(sizeof(struct matrix) * size);
  for (int i = 0; i < size; i++)
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
  print_matrix(mat1, dim, dim);
  mat->mat = mat1;
  free(mat1);
  return mat;
}



  //print_matrix(temp, src->h, dst->w);

  /*for(int i = 0; i < dst->columns; i++) {
    double buff = 0;
    for(int j = 0; j < src->lines; j++) {
      buff += temp[j*dst->columns+i];
      
      if((j+1)%coefH == 0) {
  dst->mat[j/coefH*dst->columns+i] = floor(buff/(double)coefH);
  buff = 0;
      }
    }
  }
  free(temp);
  print_matrix(dst->mat, dst->lines, dst->columns);

  return dst;
}*/

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

struct matrix *CreateMat(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn)
{
  int lines = endline - beginline;
  int columns = endcolumn - begincolumn;
  struct matrix *mat = malloc(sizeof(struct matrix)
    * lines * columns);
  mat->lines = lines;
  mat->columns = columns;
  double *mat1 = malloc(sizeof(double) * columns * lines);
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = begincolumn, k = 0; i < endcolumn; i++, k++) {
    for (int j = beginline, l = 0; j < endline; j++, l++) {
      pixel = getpixel(picture, i, j);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
      if (g == 0 && r == 0)
        mat1[k + l * columns] = 1.0;
      else
        mat1[k + l * columns] = 0.0;
    }
  }
  //print_matrix(mat1, lines, columns);
  mat->mat = malloc(sizeof(double) * lines * columns);
  mat->mat = mat1;
  //mat = resize_matrix(mat, 4, 4);
  print_matrix(mat->mat, lines, columns);
  free(mat1);
  return mat;
}

//Add matrice to memory
void add_Mat(struct memory *bank, struct matrix *mat, int nbmat) {
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