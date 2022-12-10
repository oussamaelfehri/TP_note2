#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include "proces1.h"

int file_vide(void)
{
    if(first == NULL && last == NULL)
         return 1;
    return 0;
}
/*------------------------*/
void ajout_activite(Processus p)
{ 
     if (p.priorite < priorite_min || p.priorite > priorite_max)
     {
          printf("La priorité du processus est incorrecte\n");
	     exit(1);
     }

     Ordonnanceur *temp = first;
     Ordonnanceur *O =  malloc(sizeof(Ordonnanceur));
     O->donnee = p;
     O->next = NULL;

     if(file_vide())
     {
          first = O;
          last = O;
     }
     else
     {  
          if(p.priorite < first->donnee.priorite)
          {
               O->next = first;
               first = O;
          }
     
          else if(p.priorite >= last->donnee.priorite)
          {
               last->next = O;
               last = O;
          }
          else
          {
               while (temp->next != NULL && temp->next->donnee.priorite <= p.priorite)
               {
                    temp = temp->next;
               }
               O->next = temp->next;
               temp->next = O;
               
          }
     }

}
/*------------------------*/

void defiler_Ordonnanceur()
{
	if(file_vide())
	{
		printf("La file est vide\n");
		exit(1);
	}
	// Comme l'ordonnanceur est trié par priorité, on supprime toujours le premier élément.
	Ordonnanceur *temp = first;
	if(first == last)
	{
		first = NULL;
		last = NULL;
	}
	else
	{
		first = first->next;
	}
	free(temp);
	}

Processus tete_Ordonnanceur(){
	if(file_vide())
	{
		printf("La file est vide\n");
		exit(1);
	}
	return first->donnee;
}
void clear_Ordonnanceur(void)
{
	// tant que la file n'est pas vide, on supprime le premier élément.
	while(!file_vide())
	{
		defiler_Ordonnanceur();
	}
}


int step()
{
    if(file_vide())
    {
		return 0;
    }
    else
    {
	printf("Nom du processus : %s\n", tete_Ordonnanceur().nom );
	printf("Durée d'exécution du processus : %f\n", tete_Ordonnanceur().duree);
	printf("Priorité du processus : %d\n", tete_Ordonnanceur().priorite);
	printf("Exécution du processus en cours...\n\n");
	sleep(tete_Ordonnanceur().duree);
	defiler_Ordonnanceur();
	return 1;
    }
}


void run()
{
if(file_vide())
{
	printf("Il n'y à aucun processus à éxecuter.\n");
	exit(1);
}
while(step());
printf("Tous les processus ont été exécutés\n");
}

//The end.