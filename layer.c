#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Differents structures declarations */


struct link{

	struct link *next;
	double value;
};

struct neuro{

	struct neuro *next;
	struct link  *link;
	double weight;

};

struct layer{
	struct layer *previous;
	struct neuro *neuro;
	struct layer *next;
};

struct enter{
	struct enter *next;
	int value;
};

struct exit{
	struct exit *next;
	float value;
	char name;
};


/*Temporary prototypes*/
struct layer *init_layer();
struct neuro *init_neuro();
struct link *init_link();
struct enter *init_enter();
struct exit *init_exit();

struct exit *init_neuronal_network(int nblayers, int nbenters, int nbexits);
struct enter *init_enter_list(int nenters);
struct layer *init_layer_list(int nbenters);
struct exit *init_exit_list(int nbenters);
struct neuro *init_neuro_list(int nbexits);




int main(){
	return 0;
}

/*Initialisation of all the element to NULL*/
struct layer *init_layer(){
	struct layer *res = malloc(sizeof(struct layer));
	res -> next = NULL;
	return res; 
}

struct neuro *init_neuro(){
	struct neuro *res = malloc(sizeof(struct neuro));
	res -> next =  NULL;
	return res;
}

struct link *init_link(){
	struct link *res = malloc(sizeof(struct link));
	res -> next = NULL;
	return res;
}

struct enter *init_enter(){
	struct enter *res = malloc(sizeof(struct enter));
	res -> next = NULL; 
	return res;
}

struct exit *init_exit(){
	struct exit *res = malloc(sizeof(struct exit));
	res -> next = NULL;
	return res;
}

/*Initialisation of Neuronal network*/
struct exit *init_neuronal_network(int nblayers, int nbenters, int nbexits){
	struct enter *enter = init_enter_list(nbenters);
	struct layer *layer = init_layer_list(nblayers);
	struct exit *exit = init_exit_list(nbexits);
	//FIXMEE
}
	
/*Initialisation of all the list to NULL */
struct enter *init_enter_list(int nbenters){

	struct enter *enter = init_enter();
        struct enter *tmp = enter;
	for(size_t i = 0; i < nbenters; i++)
	{
	       	tmp -> next = init_enter();
		tmp  = tmp -> next;
	}
	return enter;
}

struct layer *init_layer_list(int nblayers){
	struct layer *layer = init_layer();
	struct layer *tmp = layer;
	for(size_t i = 0; i < nblayers; i++)
	{
		tmp -> next = init_layer();
		tmp = tmp -> next;
	}
	return layer;
}

struct exit *init_exit_list(int nbexits){
	struct exit *exit = init_exit();
	struct exit *tmp = exit;
	for(size_t i = 0; i < nbexits; i++)
	{
		tmp -> next = init_exit();
		tmp = tmp -> next;
	}
	return exit;
}

struct neuro *init_neuro_list(int nbexits){
        struct neuro *neuro = init_neuro();
	struct neuro *tmp = neuro;
	for(size_t i = 0; i < nbexits; i++)
	{
		tmp -> next = init_neuro();
		tmp = tmp -> next;
	}							         
	return neuro;
}

