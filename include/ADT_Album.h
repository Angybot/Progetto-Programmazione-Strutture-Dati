//file ADT_Album.h

// Definizione della struttura idalbum
typedef struct{
    char *titolo;//Stringa per il titolo
	char *artista;//Stringa per il nome dell'artista
	char *genere;//Stringa per il genere musicale
	int anno;//Intero per l'anno di uscita dell'album
} idalbum;

//Funzione che stampa un album
void output_id(idalbum *album);

//Funzione che verifica se due album sono uguali
int comparaAlbum(idalbum *x, idalbum *y);
