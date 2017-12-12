#ifndef _LAYER_H_
#define _LAYER_H_
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
struct neuro{
  double *weight, value, delta;
};

void learn();
double frand_a_b(double a, double b);
struct neuro* init_neuro(size_t nbweight);
struct neuro** init_layer(size_t nbweight, size_t nbneuro);
void front_propa(struct neuro **layer1, struct neuro **layer2, size_t len1, size_t len2);
void back_propa(struct neuro **layer1, struct neuro **layer2, size_t len1, size_t len2);
void back_propa_output(struct neuro **output_layer, double *resattendu, size_t nbneurone);
void set_weight(struct neuro **layer1, struct neuro **layer2, size_t len1, size_t len2, double t);
void set_enter(struct neuro **enter, double *input, size_t len);
void free_pointers(struct neuro **layer, size_t len);
void set_weight_in_txt(struct neuro **layer1, size_t len, char c, size_t nbweight);
int get_weight_in_txt(struct neuro **layer, size_t len, size_t nbweight, FILE* file);
double *resize(SDL_Surface *img, size_t n);
double *expected_value_tab(char c);
double error(struct neuro **output, size_t len);
char return_letter(struct neuro **output,size_t len);


#endif
