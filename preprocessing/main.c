# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# include "pixel_operations.h"
# include "greyscale.h"
# include "segmentation.h"
# include "../createMat.h"

// Waiting for key
void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

// Initilizing SDL
void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

// Loading an image from a file
SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}


// Main function
int main(int argc, char *argv[])
{
  if (argc < 2)
    return 1;
  init_sdl();
  SDL_Surface* picture = load_image(argv[1]);
  //display_image(picture);

  Greyscale(picture);
  //display_image(picture);

  Binarisation(picture);
  //display_image(picture);
  int n = Count_letters(picture);
  struct memory *memory = DetectAll(picture, n);
  display_image(picture);

  print_all_matrix(memory);

  Clear_memory(memory);

  return 0;
}
