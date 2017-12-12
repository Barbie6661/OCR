#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "preprocessing/greyscale.h"
#include "preprocessing/pixel_operations.h"
#include "preprocessing/segmentation.h"
#include "preprocessing/createMat.h"
#include "preprocessing/contrast.h"
#include "neuro/layer.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>

typedef struct
{
        GtkBuilder *builder;
        gpointer user_data;
} SGlobalData;

#define taille_max 1000     
static SGlobalData data;  
static gchar *name_of_image=NULL;
static gchar *name_of_file="data.txt";
static gchar *contents= NULL;

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

G_MODULE_EXPORT void on_quit_clicked(){
	gtk_main_quit();
}
G_MODULE_EXPORT void on_MainWindow_clicked(){
	gtk_main_quit();
}
G_MODULE_EXPORT void on_Charger_selection_changed(){
	GObject *ex= gtk_builder_get_object (data.builder, "Charger");
	if(NULL ==ex){
		fprintf(stderr,"Charger do not exist");
	}
	GtkFileChooser *file= GTK_FILE_CHOOSER(ex);
	name_of_image=gtk_file_chooser_get_filename(file);
	GtkImage *image=GTK_IMAGE(
					gtk_builder_get_object(data.builder, "Image"));
	gtk_image_set_from_file(image, name_of_image);
}	    
G_MODULE_EXPORT void on_Display_text_clicked(){
	GtkLabel *texte = GTK_LABEL(
			gtk_builder_get_object(data.builder, "label"));
	if(NULL == texte)
	{
		fprintf(stderr,"label do not exist");
	}
	if(g_file_get_contents(name_of_file,&contents,NULL,NULL))
	{
		gtk_label_set_text(texte,contents);
	}
}
//function that writes a character array to a text file

void savedata(char data[])

{

    FILE* fichier = NULL;
    fichier = fopen("data.txt", "w");

    if (fichier != NULL)

    {

        fputs(data, fichier);

        fclose(fichier);

    }

}
G_MODULE_EXPORT void on_treatment_image_clicked(){
	GtkLabel *texte = GTK_LABEL(
					gtk_builder_get_object(data.builder, "Number"));
	learn();
	init_sdl();
	if(NULL == texte)
	{
		fprintf(stderr,"label do not exist");
	}
	if(name_of_image==NULL)
	{
		fprintf(stderr,"NULL");
	}
	char num[taille_max]="";
	/*Creation of picture*/
	SDL_Surface* picture= load_image(name_of_image);
	display_image(picture);
	/*Contrast of picture*/
	contrast(picture);
	display_image(picture);
	/*Grayscale of picture*/
	Greyscale(picture);
	display_image(picture);
	/*Binarisation of picture*/
	Binarisation(picture, Seuil(picture));
	display_image(picture);
	/*Number of picture*/
	size_t nbletters = Count_letters(picture);
	sprintf(num,"%lu",nbletters);
	gtk_label_set_text(texte, num);
	struct memory *bank = DetectAll(picture, nbletters);
	display_image(picture);
	print_all_matrix(bank, nbletters);

	struct neuro **inputs = init_layer(150, 900);
	struct neuro **hidden = init_layer(26,150);
	struct neuro **output = init_layer(0,26);

	FILE* file = NULL;
	file = fopen("neuro/weight.ocr", "r");
	get_weight_in_txt(inputs, 900, 150,file);
	get_weight_in_txt(hidden, 150,26,file);
	char str[taille_max]="";
	for (size_t i = 0; i < nbletters; i++) 
	{
		set_enter(inputs, bank -> tab[i] -> mat, 900 );
		front_propa(inputs, hidden, 900,150);
		front_propa(hidden, output,150,26);
		printf("%c ", return_letter(output, 26) );
		str[i]=return_letter(output, 26);
	}
	fclose(file);
	savedata(str);
	free_pointers(inputs,900);
	free_pointers(hidden,150);
	free_pointers(output,26);
	Clear_memory(bank, nbletters);
	SDL_FreeSurface(picture);
}
int main(int argc, char *argv []){
	GtkWidget *fenetre_principale = NULL;
	GError *error = NULL;
    gchar *filename=NULL;
    /* Initializing the Gtk library.*/
    gtk_init(&argc, &argv);
    /* Opening the Glade file from the main Window */
    data.builder = gtk_builder_new();
    /* Creating the full path to access the OCR.glade file */
    /* g_build_filename(); Construct the full path according to the */
    /*  operating system. ( / for Linux and \ for Windows) */
    filename =  g_build_filename ("OCR.glade", NULL);
    /* Chargement du fichier OCR.glade. */
    gtk_builder_add_from_file (data.builder, filename, &error);
    g_free (filename);
    if (error){
		gint code = error->code;
        g_printerr("%s\n", error->message);
        g_error_free (error);
        return code;
    }
    /* Assignement of interface signals to different Callbacks */
    gtk_builder_connect_signals (data.builder, &data);
    /* Pointer recovery from the main window */
    fenetre_principale = GTK_WIDGET(gtk_builder_get_object (data.builder, "MainWindow"));
    /* Showing the main window */
    gtk_widget_show_all (fenetre_principale);
    gtk_main();
    return 0;
}

