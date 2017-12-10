#include "layer.h"
#include <err.h>
#include <dirent.h>
#include "../preprocessing/pixel_operations.h"

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
  if(c)
  {
    file = fopen("weights.ocr", "w");
  }
  else
  {
    file = fopen("weights.ocr", "a");
  }
  if(!file)
  {
    errx(1, "Can't load weights");
  }
  for (size_t i = 0; i < len; i++)
    {
      for (size_t j = 0; j < nbweight; j++)
      {
        fprintf(file, "%lf\n", *(layer1[i] -> weight + j));
        //fprintf(stderr, "%lf\n", *(layer1[i]->weight + j));
      }
    }
  fclose(file);
}

int get_weight_in_txt(struct neuro **layer, size_t len, size_t nbweight, FILE* file)
{
  if(!file)
  {
    return 0;
  }
  for (size_t i = 0; i < len; i++)
  {
    for (size_t j = 0; j < nbweight; j++)
    {
      fscanf(file, "%lf", &*(layer[i]->weight + j));
    }
  }
  return 1;

}

double *resize(SDL_Surface *img, size_t n)
{
  double *tab = malloc(sizeof(double) * n * n);
  Uint8 r, g, b;
  for (size_t x = 0; x < n; x++)
  {
    for (size_t y = 0; y < n; y++)
    {
      SDL_GetRGB(getpixel(img, x*img->w/n, y*img->h/n), img->format, &r, &g, &b);
      *(tab + x * n + y) = r%254;
      //printf("%ld\n", x + y*32);
    }
  }
  return tab;
}
double *expected_value_tab(char c)
{
  double *res = calloc(26, sizeof(double));
  if(c >= 'a' && c <= 'z')
  {
    res[c-'a'] = 1;
  }
  else if(c >= 'A' && c <= 'Z')
  {
    res[c-'A'] = 1;
  }
  return res;
}

double error(struct neuro **output, size_t len)
{
  double error = 0;
  for (size_t i = 0; i < len; i++) {
    error += fabs(output[i] -> delta);
  }
  return error;
}
void learn()
{
  struct neuro **inputs = init_layer(150, 900);
  struct neuro **hidden = init_layer(26,150);
  struct neuro **output = init_layer(0,26);
  char *ch = malloc(sizeof(char)* 200);
  double *res;
  double *tab;
  double err = 10000;
  FILE* file = NULL;
  file = fopen("weight.ocr", "r");
  get_weight_in_txt(inputs, 900, 150,file);
  get_weight_in_txt(hidden, 150,26,file);
  //printf("inputs :%lf, hidden : %lf\n", inputs[0] -> weight[0], hidden[0] -> weight[0] );
  //lsprintf("inputs :%lf, hidden : %lf\n", inputs[0] -> weight[1], hidden[0] -> weight[1] );
  for (size_t i = 0; err > 70; i++)
  {
    err = 0;
    DIR * j = opendir("./neuro/learning");
    struct dirent * dr;
    dr = readdir(j);
    dr = readdir(j);
    while ((dr = readdir(j)) != NULL)
    {
      strcpy(ch, "./neuro/learning/");
      strcat(ch, dr->d_name);

      SDL_Surface *img = IMG_Load(ch);
      res = expected_value_tab(dr -> d_name[0]);
      tab = resize(img, 30);
      set_enter(inputs, tab, 900);
      front_propa(inputs, hidden,900,150);
      front_propa(hidden, output,150,26);
      back_propa_output(output, res, 26);
      back_propa(hidden, output,150,26);
      back_propa(inputs,hidden,900,150);
      set_weight(inputs, hidden,900,150, 0.002);
      set_weight(hidden, output,150,26, 0.002);
      SDL_FreeSurface(img);
      free(res);
      free(tab);
      err += error(output, 26);
    }
    err /= 12;

    printf("%lf\n", err );
  }
  hidden[0] -> weight[0] = 0.10;
  set_weight_in_txt(inputs, 900,1,150);
  set_weight_in_txt(hidden, 150,0,26);
  //printf("inputs :%lf, hidden : %lf\n", inputs[0] -> weight[0], hidden[0] -> weight[0] );
  //printf("inputs :%lf, hidden : %lf\n", inputs[0] -> weight[1], hidden[0] -> weight[1] );
  //printf("inputs :%lf, hidden : %lf\n", inputs[0] -> weight[0], hidden[0] -> weight[0] );
  //printf("inputs :%lf, hidden : %lf\n", inputs[0] -> weight[1], hidden[0] -> weight[1] );
  fclose(file);
  free_pointers(inputs,900);
  free_pointers(hidden,150);
  free_pointers(output,26);
}

void only_front()
{

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
