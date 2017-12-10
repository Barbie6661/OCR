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
#endif
