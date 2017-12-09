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


struct matrix *resizeMat(SDL_Surface *picture,int beginline,
int endline,int begincolumn, int endcolumn, int dim)
{
  struct matrix *mat = malloc(sizeof(struct matrix) * dim * dim);
  mat->lines = dim;
  mat->columns = dim;
  double *mat1 = malloc(sizeof(double) * dim * dim);
  Uint8 r, g , b;
  Uint32 pixel;
  for (int i = begincolumn, k = 0; i < endcolumn; i++, k++) {
    for (int j = beginline, l = 0; j < endline; j++, l++) {
      pixel = getpixel(picture, k*picture->w/dim, l*picture->h/dim);
      SDL_GetRGB(pixel, picture->format, &r, &g, &b);
        mat1[k + l * dim] = g%254;
    }
  }
  print_matrix(mat1, dim, dim);
  mat->mat = mat1;
  free(mat1);
  return mat;
}

static struct matrix *resize_matrix(struct matrix *src, size_t newH, size_t newW)
{

  struct matrix *dst = malloc(sizeof(struct matrix));
  dst->lines = newH;
  dst->columns = newW;
  dst->mat = malloc(sizeof(double) * dst->lines * dst->columns);
  
  int coefH = floor((double)src->lines/(double)dst->lines);
  int coefW = floor((double)src->columns/(double)dst->columns);

  //printf("COEFW : %ld \n\n", coefW);
  
  double *temp = malloc(sizeof(double)*src->lines*dst->columns);
  
  for(int i = 0; i < src->lines; i++) {
    double buff = 0;
    for(int j = 0; j < src->columns /*dst->w*/; j++) {
      buff += src->mat[i*src->columns+j];
      if((j+1)%coefW == 0) {
  //printf("%ld & %d & %.2f\n", j, i*dst->w+j/coefW, buff/(double)coefW);
  temp[i*dst->columns+j/coefW] = /*(double)floor*/(buff/(double)coefW);
  buff = 0;
      }
    }
  }

  //print_matrix(temp, src->h, dst->w);

  for(int i = 0; i < dst->columns; i++) {
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
  mat = resize_matrix(mat, 4, 4);
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