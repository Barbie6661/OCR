#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "greyscale.h"
#include "pixel_operations.h"
#include "segmentation.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>

typedef struct
{
        GtkBuilder *builder;
        gpointer user_data;
} SGlobalData;
      
static SGlobalData data;   
static GtkImage *image;

      // Initilizing SDL
void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}
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

      G_MODULE_EXPORT void on_quit_clicked()
      {
		  gtk_main_quit();
	  }
	   G_MODULE_EXPORT void on_MainWindow_clicked()
      {
		  gtk_main_quit();
	  }
	  G_MODULE_EXPORT void on_Charger_selection_changed()
	  {
		  GtkFileChooser *file=GTK_FILE_CHOOSER(gtk_builder_get_object (data.builder, "Charger"));
		  const gchar *filename=gtk_file_chooser_get_filename(file);
		  image=GTK_IMAGE(gtk_builder_get_object(data.builder, "Image"));
		  gtk_image_set_from_file(image, filename);
	  }	    
	  G_MODULE_EXPORT void on_treatment_image_TESTocr_clicked()
	  {
		init_sdl();
	    SDL_Surface* picture = load_image("TESTocr.png");
	    display_image(picture);
	    
	    Greyscale(picture);
        display_image(picture);

        Binearisation(picture);
        display_image(picture);

        DetectAll(picture);
        display_image(picture);
        
	  }
	  G_MODULE_EXPORT void on_treatment_image_LAST_clicked()
	  {
		init_sdl();
	    SDL_Surface* picture = load_image("LAST.png");
	    display_image(picture);
	    
	    Greyscale(picture);
        display_image(picture);

        Binearisation(picture);
        display_image(picture);

        DetectAll(picture);
        display_image(picture);
	  }

      int
      main(int argc, char *argv [])
      {
		
        GtkWidget *fenetre_principale = NULL;
        SGlobalData data;
        GError *error = NULL;
        gchar *filename = NULL;
       
        /* Initialisation de la bibliothèque Gtk. */
        gtk_init(&argc, &argv);

        /* Ouverture du fichier Glade de la fenêtre principale */
        data.builder = gtk_builder_new();
 
        /* Création du chemin complet pour accéder au fichier test.glade. */
        /* g_build_filename(); construit le chemin complet en fonction du système */
        /* d'exploitation. ( / pour Linux et \ pour Windows) */
        filename =  g_build_filename ("OCR.glade", NULL);

        /* Chargement du fichier OCR.glade. */
        gtk_builder_add_from_file (data.builder, filename, &error);
        g_free (filename);
        if (error)
        {
          gint code = error->code;
          g_printerr("%s\n", error->message);
          g_error_free (error);
          return code;
        }
        /* Affectation des signaux de l'interface aux différents CallBacks. */
        gtk_builder_connect_signals (data.builder, &data);

        /* Récupération du pointeur de la fenêtre principale */
        fenetre_principale = GTK_WIDGET(gtk_builder_get_object (data.builder, "MainWindow"));

        /* Affichage de la fenêtre principale. */
        gtk_widget_show_all (fenetre_principale);

        gtk_main();

        return 0;
      }

