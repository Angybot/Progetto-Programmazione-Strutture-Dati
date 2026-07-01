//file ADT_Album.c
#include <stdio.h>
#include <string.h>
#include "ADT_Album.h"

//Funzione che stampa un album
void output_id(idalbum *album){
	//Stampa i campi della struttura idalbum
	printf("Titolo: %s\n",album->titolo);
	printf("Artista: %s\n",album->artista);
	printf("Genere: %s\n",album->genere);
	printf("Anno: %d\n",album->anno);
	return;//Restituisce il controllo alla funzione chiamante
}
//Funzione che verifica se due album sono uguali
int comparaAlbum(idalbum *x, idalbum *y){
	if(x->anno==y->anno){//Controlla se l'anno dei due album è uguale altrimenti restituisce 1
		if(!(strcmp(x->genere, y->genere))){//Controlla se il genere dei due album è uguale altrimenti restituisce 1
			if(!(strcmp(x->artista, y->artista))){//Controlla se l'artista dei due album è uguale altrimenti restituisce 1
				if(!(strcmp(x->titolo, y->titolo))){//Controlla se il titolo dei due album è uguale altrimenti restituisce 1
					return 0;//Gli album sono identici e restituisce 0
				}
			}
		}
	}
	return 1;//Almeno 1 dei valori degli album è diverso e restituisce 1
}