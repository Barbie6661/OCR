#include "layer.h"
#include <err.h>

double frand_a_b(double a, double b)
{
  return ( rand()/(double)RAND_MAX ) * (b-a) + a;
}

struct neuro* init_neuro(size_t nbweight)
{
  struct neuro *res = malloc(sizeof(struct neuro));
  double *tab= malloc(sizeof(double) * nbweight);
  if(!res || !tab)
  {
    errx(1, "malloc failed");
  }
  for (size_t i = 0; i < nbweight; i++)
  {
    *(tab + i) = frand_a_b(-1,1);
  }
  res->weight = tab;
  //printf("%lf\n", *res->weight);
  res->value = 0;
  res->delta = 0;
  return res;
}
struct neuro** init_layer(size_t nbweight, size_t nbneuro)
 {
   struct neuro **layer = malloc(sizeof(struct neuro) * nbneuro);
   if(!layer)
   {
     errx(1, "malloc failed");
   }
   for (size_t i = 0; i < nbneuro; i++)
   {
     *(layer + i) = init_neuro(nbweight);
   }
   return layer;
 }
void front_propa(struct neuro **layer1, struct neuro **layer2, size_t len1, size_t len2)
{
    for (size_t j = 0; j < len2 ; j++) {
      double sum = 0;
    for (size_t i = 0; i < len1; i++) {
        sum += layer1[i] -> value * *(layer1[i] -> weight + j);
      }
      layer2[j] -> value = 1 / (1+exp(-sum));
    }
}
void back_propa(struct neuro **layer1, struct neuro **layer2, size_t len1, size_t len2)
{
  for (size_t i = 0; i <len1 ; i++) {
    double d = layer1[i] -> value;
    double sum = 0;
    for (size_t j = 0; j < len2; j++) {
       sum += *(layer1[i] -> weight + j) * layer2[j] -> delta;
    }
    layer1[i] -> delta = sum * d * (1-d);
  }
}

void back_propa_output(struct neuro **output_layer, double *resattendu, size_t nbneurone)
{
  for (size_t i = 0; i < nbneurone; i++)
  {
    output_layer[i] -> delta = resattendu[i] - output_layer[i] -> value;
  }
}

void set_weight(struct neuro **layer1, struct neuro **layer2, size_t len1, size_t len2, double t)
{
  for (size_t i = 0; i < len2; i++) {
    for (size_t j = 0; j < len1; j++) {
      *(layer1[j] -> weight + i) += t * layer1[j] -> value * layer2[i] -> delta;
    }
  }
}

void set_enter(struct neuro **enter, double *input, size_t len)
{
  for (size_t i = 0; i < len; i++)
  {
    enter[i] -> value = input[i];
  }
}

void free_pointers(struct neuro **layer, size_t len)
{
   for (size_t i = 0; i < len; i++) {
     free(layer[i] -> weight);
     free(layer[i]);
   }
   free(layer);
}

void set_weight_in_txt(struct neuro **layer1, size_t len, char c, size_t nbweight)
{
  FILE* file = NULL;
  if (c) {
    file = fopen("weight.ocr", "w");
  }
  else
    file = fopen("weight.ocr", "a");
  if(file != NULL)
  {
    for (size_t i = 0; i < len; i++)
    {
      for (size_t j = 0; j < nbweight; j++)
      {
        fprintf(file, "%lf\n", *(layer1[i] -> weight + j) );
      }
    }
  fclose(file);
  }
}

size_t get_weight_in_txt(struct neuro **layer1, size_t len, char c, size_t nbweight, size_t i)
{
  FILE* file = NULL;
  file = fopen("weight.ocr", "r");
  if(file !=  NULL){
    for (size_t j = 0; j < i; j++)
    {
      fscanf(file, "%lf", &*(layer1[0]->weight));
    }
    for (size_t k = 0; k < len; k++) {
      for (size_t l = 0; l < nbweight; l++)
      {
        fscanf(file, "%lf", &*(layer1[k] -> weight + l) );
        i++;
      }
    }
  }
  return i;
}

double *resize_tab(double *src, size_t x, size_t width, size_t height)
{
  double *dst = malloc(sizeof(double)* x *x);
  for (size_t i = 0; i < x; i++) {
    for (size_t j = 0; j < x; j++) {
      dst[i+j * x] = src[(i * width/x) + (j * height/x) * height];
    }
  }
  return dst;
}
double *expected_value_tab(char c)
{
  double *res = calloc(26, sizeof(size_t));
  if(c >= 'a' && c <= 'z')
  {
    res[c-'a'] = 1;
    printf("c - a = %d\n", c-'a' );
  }
  return res;
}
void learn()
{
  struct neuro **inputs = init_layer(2, 2);
  struct neuro **hidden = init_layer(1,2);
  struct neuro **output = init_layer(0,1);
  double *entree = malloc(sizeof(double) * 2);
  double res;
  for (size_t i = 0; i < 10000000; i++) {
    switch (i % 4) {
      case 0:
        res = 0;
        entree[0] = 0;
        entree[1] = 0;
        break;
      case 1:
        res = 1;
        entree[0] = 0;
        entree[1] = 1;
        break;
      case 2:
        res = 1;
        entree[0] = 1;
        entree[1] = 0;
        break;
      case 3 :
        res = 0;
        entree[0] = 1;
        entree[1] = 1;
        break;
    }
    set_enter(inputs, entree, 2);
    front_propa(inputs, hidden,2,2);
    front_propa(hidden, output,2,1);
    back_propa_output(output, &res, 1);
    back_propa(hidden, output,2,1);
    back_propa(inputs,hidden,2,2);
    set_weight(inputs, hidden,2,2, 0.2);
    set_weight(hidden, output,2,1, 0.2);
    printf("a = %lf, b = %lf \n", entree[0], entree[1] );
    printf("s = %lf\n", output[0] -> value );
  }
}

void only_front()
{

}



int main(int argc, char const *argv[]) {
  double src[] = {0,0,0,0,1,0,1,0,
                  0,0,0,0,1,0,1,0,
                  0,0,0,0,1,1,1,0,
                  0,0,0,0,1,0,1,0,
                  0,0,0,0,1,0,1,0};
  size_t x = 5;
  double *dst = resize_tab(src, x ,8, 5 );
  for (size_t i = 0; i < x+2; i++) {
    for (size_t j = 0; j < x; j++) {
      printf("%lf ,", dst[i+j] );
    }
    printf("\n");
  }
  return 0;
}
/*
0.680375
-0.211234
0.566198
0.596880
0.823295
-0.604897
0.000000
-0.329554
0.536459
0.000000
*/
