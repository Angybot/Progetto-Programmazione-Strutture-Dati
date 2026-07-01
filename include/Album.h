//file Album.h
#include "ADT_Album.h"//Inclusione del file header per le funzioni dell'ADT_Album
#define MAX_LEN 50//Costante che definisce la lunghezza massima delle stringhe
#define ANNO_CORRENTE 2024//Costante che definisce l'anno corrente
//Definizione del tipo lista (aka struct album*, puntatore alla struttura album) che rappresenta il catalogo
typedef struct album *lista;

//Funzione che restituisce una nuova lista vuota
lista nuovaLista(void);

//Funzione per verificare se la lista è vuota
int listaVuota(lista l);

//Funzione che alloca un nuovo album e lo aggiunge in testa alla lista (catalogo)
lista aggiungiAlbum(lista l, char *tit, char *art, char *gen, int anno);

//Funzione che, data la posizione, rimuove un album dalla lista (catalogo) e libera la memoria
lista rimuoviAlbum(lista l, int pos);

//Funzione che modifica un parametro di un album nella lista
int modificaAlbum(lista l);

//Funzione che restituisce la coda della lista (tutti gli elementi tranne il 1°, la testa)
lista codaLista(lista l);

//Funzione che restituisce il primo album della lista
idalbum* prendiPrimo(lista l);

//Funzione che restituisce quanti elementi contiene la lista (catalogo)
int grandezzaLista(lista l);

//Funzione che inverte la lista, lista di input: <a1, a2, ..., an-1, an> diventa <an, an-1, ..., a2, a1>: lista di output
lista invertiLista(lista l);

//Funzione che cerca un determinato album, preso in input dalla funzione, nel catalogo e restituisce la posizione
int posizioneAlbum(lista l, idalbum *x);

//Funzione che cerca un album nella lista per il titolo e restituisce un 1 se l'ha trovato, 0 altrimenti
int cercaTitolo(lista l, char *tit);

//Funzione che cerca un album nella lista per un parametro e restituisce un catalogo con gli album trovati
lista cercaAlbum(lista l);

//Funzione che cerca un album nella lista per un parametro dato da file e restituisce un catalogo con gli album trovati
lista fcercaAlbum(FILE *f, lista l);

//Funzione che stampa tutti gli album del catalogo
void stampaCatalogo(lista l);

//Funzione che stampa tutti gli album del catalogo in un file passato alla funzione
void fstampaCatalogo(FILE *f, lista l);

//Funzione che scambia i campi di due liste
//void scambia(lista l1, lista l2);

//Funzione che riordina il catalogo (lista) in base all'anno
lista ordinannoCatalogo(lista l);

