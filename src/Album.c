//file Album.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Album.h" //Inclusione del file header per la definizione della lista e i prototipi di funzioni

//Definizione della struttura album
struct album{
    char *titolo;//Stringa per il titolo
	char *artista;//Stringa per il nome dell'artista
	char *genere; //Stringa per il genere musicale
	int anno;//Intero per l'anno di uscita dell'album
    struct album *next;//Puntatore al prossimo album della lista
};

//Definizione della funzione nuovaLista per creare una nuova lista vuota
lista nuovaLista(void){
    return NULL; //Restituisce NULL, indicando una lista vuota
}
//Funzione per verificare se la lista è vuota
int listaVuota(lista l){
    return l == NULL; //Restituisce 1 se la lista è vuota (NULL), altrimenti restituisce 0
}
//Funzione per aggiungere un nuovo album in testa alla lista (catalogo)
lista aggiungiAlbum(lista l, char *tit, char *art, char *gen, int anno){
    struct album *nuovo; //Dichiarazione di un puntatore a un nuovo nodo
	//Inizializzazione delle 3 lunghezze delle stringhe date in input alla funzione
	int len1=strlen(tit);
	int len2=strlen(art);
	int len3=strlen(gen);
    nuovo = malloc(sizeof(struct album)); //Allocazione della memoria per il nuovo nodo
    //Verifica se l'allocazione della memoria è riuscita
	if (nuovo != NULL) { 
		//Allocazione del titolo della grandezza di len1 e controllo per verificare la riuscita
		if(!(nuovo->titolo=malloc(len1*sizeof(char)+1))){
			fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
			exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
		}
        strcpy(nuovo->titolo, tit);//Copia della stringa nella struttura
		//Allocazione dell'artista della grandezza di len2 e controllo per verificare la riuscita
		if(!(nuovo->artista=malloc(len2*sizeof(char)+1))){
			fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
			exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
		}
		strcpy(nuovo->artista, art);//Copia della stringa nella struttura
		//Allocazione del genere della grandezza di len3 e controllo per verificare la riuscita
		if(!(nuovo->genere=malloc(len3*sizeof(char)+1))){
			fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
			exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
		}
		strcpy(nuovo->genere, gen);//Copia della stringa nella struttura
		nuovo->anno=anno;//Copia dell'anno nella struttura
        nuovo->next = l; //Collega il nuovo nodo al nodo successivo, che è la lista l
        l = nuovo; //Aggiorna il puntatore alla testa della lista in modo che punti al nuovo nodo
    }
    return l;//Restituisce il puntatore alla lista aggiornata
}
//Funzione per la rimozione di un album dalla lista (catalogo) data la posizione
lista rimuoviAlbum(lista l, int pos){
	idalbum *x;//Dichiaro un puntatore alla struttura idalbum
	int i=0;//Variabile contatore
	lista ltmp = nuovaLista(); //Lista di appoggio
	lista lout = nuovaLista(); //Lista che forniremo in output
	lista lapp;//Lista di appoggio per liberare la memoria
	/*Ciclo che scandisce la lista di input fino alla posizione pos e
	memorizza i primi pos-1 elementi in una lista di appoggio ltmp*/
	while(i < pos && !listaVuota(l)){//Finchè la lista l non è vuota e i minore di pos
		x = prendiPrimo(l);//Memorizza l'album in testa alla lista in x
		ltmp = aggiungiAlbum(ltmp, x->titolo, x->artista, x->genere, x->anno);//Aggiunge l'album alla lista temporanea
		lapp=l;//Assegno il puntatore della testa della lista a lapp 
		l = codaLista(l);//Passo all'album successivo della lista di input
		free(lapp);//Libero la memoria della vecchia testa della lista
		i++;//Incremento il contatore
	}
	//Controllo della precondizione: la lista di input ha almeno pos elementi
	if(i==pos){
		//Saltiamo l'album da togliere
		lapp=l;//Assegno il puntatore della testa della lista a lapp
		l = codaLista(l);//Passo all'album successivo della lista di input
		free(lapp);//Libero la memoria dell'album da rimuovere
		//Inseriamo in ltmp i restanti elementi della lista
		while(!listaVuota(l)){//Finchè la lista non è vuota
			x = prendiPrimo(l);//Memorizza l'album in testa alla lista in x
			ltmp = aggiungiAlbum(ltmp, x->titolo, x->artista, x->genere, x->anno);//Aggiunge l'album alla lista temporanea
			lapp=l;//Assegno il puntatore della testa della lista a lapp 
			l = codaLista(l);//Passo all'album successivo della lista di input
			free(lapp);//Libero la memoria della vecchia testa della lista
		}
		free(l);//Libero la memoria della lista di input
		lout=invertiLista(ltmp);//Restituisce l'inverso della lista temporanea e l'assegna a lout
	}else{
		printf("La posizione %d non esiste\n", pos);//Avviso di uso errato della funzione
	}
	while(!listaVuota(ltmp)){//Finchè la lista temporanea non è vuota
		lapp=ltmp;//Assegno il puntatore della testa della lista temporanea a lapp
		ltmp = codaLista(ltmp);//Passo all'album successivo della lista temporanea
		free(lapp);//Libero la memoria della vecchia testa della lista
	}
	free(ltmp);//Libero la memoria della lista temporanea
	//Restituisce la lista di output con l'elemento rimosso o
	//lista vuota se la lista di input non ha pos elementi
	return(lout);
}
//Funzione che modifica un parametro di un album nella lista
int modificaAlbum(lista l){
	int r;//Variabile che contiene la risposta dell'utente
	char titolo[MAX_LEN+1];//Variabile che immagazzina la stringa
	printf("Inserisci il titolo dell'album che vuoi modificare (max %d caratteri): ", MAX_LEN);
	gets(titolo);//Prende in input la stringa
	titolo[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
	titolo[strcspn(titolo, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
	fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
	while(!listaVuota(l)){//Finchè la lista non è vuota
		if(!(strcmp(l->titolo, titolo))){//Compara il titolo della struttura con quello cercato
			break;//Se lo trova esce dal ciclo
		}
		l = codaLista(l);//Passa all'album successivo
	}
	if(!listaVuota(l)){//Controlla che la lista non sia vuota
		do{
			printf("Cosa vuoi modificare?\n");//Chiede all'utente il campo da modificare
			printf("    - 1: Titolo\n");
			printf("    - 2: Artista\n");
			printf("    - 3: Genere\n");
			printf("    - 4: Anno\n");
			printf("    - 0: Chiudi\n");
			scanf("%d", &r);//Immagazzina la risposta
			getc(stdin);//Toglie eventuali caratteri sovrabbondanti
		}while(r<0 || r>4);//Verifica se l'utente ha inserito un valore da 1 a 4
		char string[MAX_LEN+1];//Dichiarazione array di caratteri per l'input
		fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
		fflush(stdout);//Toglie eventuali caratteri sovrabbondanti
		switch(r){//Controlla il valore di r
			case 0:{//Caso della chiusura
				return 2;//Restituisce il controllo alla funzione chiamante, restituendo 2 (chiusura)
			}
			case 1:{//Caso del titolo
				printf("Inserisci il nuovo titolo (max %d caratteri): ", MAX_LEN);
				gets(string);//Prende in input la stringa
				string[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
				string[strcspn(string, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
				fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
				if(!(l->titolo=malloc(strlen(string)*sizeof(char)+1))){//Alloca il titolo della lista
					fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
					exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
				}
				strcpy(l->titolo, string);//Copia della stringa nella struttura
				break;
			}
			case 2:{//Caso dell'artista
				printf("Inserisci il nuovo artista (max %d caratteri): ", MAX_LEN);
				gets(string);//Prende in input la stringa
				string[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
				string[strcspn(string, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
				fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
				if(!(l->artista=malloc(strlen(string)*sizeof(char)+1))){//Alloca l'artista della lista
					fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
					exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
				}
				strcpy(l->artista, string);//Copia della stringa nella struttura
				break;
			}
			case 3:{//Caso del genere
				printf("Inserisci il nuovo genere (max %d caratteri): ", MAX_LEN);
				gets(string);//Prende in input la stringa
				string[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
				string[strcspn(string, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
				fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
				if(!(l->genere=malloc(strlen(string)*sizeof(char)+1))){//Alloca il genere della lista
					fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
					exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
				}
				strcpy(l->genere, string);//Copia della stringa nella struttura
				break;
			}
			case 4:{//Caso dell'anno
				int anno;//Dichiarazione variabile che conterrà l'input dell'utente
				do{
					printf("Inserisci il nuovo anno (minimo 1800 - massimo %d): ", ANNO_CORRENTE);
					scanf("%d", &anno);//Prende in input l'intero salvandolo nella struttura
				}while(anno<1800 || anno>ANNO_CORRENTE);//Verifica che il valore inserito sia un effettivo valore valido (tra 1800 e ANNO_CORRENTE)
				l->anno=anno;//Assegno alla struttura il valore preso in input
				break;
			}
		}
		return 1;//Restituisce il controllo alla funzione chiamante, restituendo 1 (successo)
	}else{
		//Album non presente nel catalogo
		return 0;//Restituisce il controllo alla funzione chiamante, restituendo 0 (fallito)
	}
}
//Funzione che restituisce la coda della lista (catalogo)
lista codaLista(lista l){
    lista temp; //Dichiarazione di un puntatore temporaneo lista
    if (l != NULL){ //Verifica se la lista non è vuota
        temp = l->next; //Se l'elemento corrente non è l'ultimo, assegna il puntatore al prossimo elemento alla variabile temporanea
	}else{
        temp = NULL; //Se la lista è vuota, la coda sarà anche vuota
	}
    return temp; //Restituisce la coda della lista (una nuova lista)
}
//Funzione che restituisce il primo album della lista
idalbum* prendiPrimo(lista l){
    idalbum *alb;//Dichiarazione di una struttura temporanea per memorizzare il primo elemento della lista
	if(!(alb=calloc(1, sizeof(idalbum)))){ //Alloca la struttura e verifica la riuscita dell'allocazione
		fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
		exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
	}
	//Inizializzazione delle 3 lunghezze delle stringhe dei campi di idalbum
	int len1=strlen(l->titolo);
	int len2=strlen(l->artista);
	int len3=strlen(l->genere);
    if (l != NULL){ //Verifica se la lista non è vuota
		//Allocazione del titolo della grandezza di len1 e controllo per verificare la riuscita
		if(!(alb->titolo=malloc(len1*sizeof(char)+1))){
			fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
			exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
		}
        strcpy(alb->titolo, l->titolo);//Copia della stringa nella struttura
		//Allocazione dell'artista della grandezza di len2 e controllo per verificare la riuscita
		if(!(alb->artista=malloc(len2*sizeof(char)+1))){
			fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
			exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
		}
		strcpy(alb->artista, l->artista);//Copia della stringa nella struttura
		//Allocazione del genere della grandezza di len3 e controllo per verificare la riuscita
		if(!(alb->genere=malloc(len3*sizeof(char)+1))){
			fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
			exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
		}
		strcpy(alb->genere, l->genere);//Copia della stringa nella struttura
		alb->anno=l->anno;//Copia dell'anno nella struttura
    }else{
        alb = NULL; //Se la lista è vuota, l'album è vuoto
	}
    return alb; //Restituisce il primo album della lista
}
//Funzione che restituisce quanti elementi contiene la lista (catalogo)
int grandezzaLista(lista l){
	int n=0;//Inizializzazione del contatore
	while (!listaVuota(l)){//Finché non raggiunge la fine della lista
		n++;//Il primo elemento contribuisce al conteggio
		l = codaLista(l);//Continua la visita degli elementi successivi
	}
	return n;//Restituisce il contatore
}
//Funzione che inverte la lista, quindi il primo elemento diventa l'ultimo, il secondo diventa penultimo (e viceversa) e così via...
lista invertiLista(lista l){
	lista inv;//Dichiarazione di un puntatore a una nuova lista invertita
	idalbum *x;//Dichiarazione di una variabile temporanea per memorizzare il valore degli elementi
	inv = nuovaLista();//Inizializzazione della nuova lista vuota
	//Ciclo finché la lista originale non è vuota
	while (!listaVuota(l)) {
		x = prendiPrimo(l);//Ottiene il valore del primo album della lista originale
		inv = aggiungiAlbum(inv, x->titolo, x->artista, x->genere, x->anno);//Aggiunge il valore alla testa della lista invertita
		l = codaLista(l);//Passa al prossimo elemento della lista originale
	}
	return inv;//Restituisce la lista invertita
}
//Funzione che cerca un determinato album nel catalogo e restituisce la posizione
int posizioneAlbum(lista l, idalbum *x){
	int pos=0; //Contatore di posizione
	int trovato=0;//Variabile booleana utilizzata come "flag" per verificare se l'album è presente o no
	idalbum *alb;//Dichiarazione di una variabile temporanea per memorizzare il valore degli album
	while(!listaVuota(l) && !trovato){//Finchè la lista non è vuota e trovato vale 0
		alb=prendiPrimo(l);//Prendiamo l'album in testa alla lista
		if(comparaAlbum(alb, x)==0){//Compariamo l'album con quello passato in input alla funzione utilizzando la funzione comparaAlbum() definita in ADT_Album.h
			trovato=1;//Settiamo la "flag" a 1
		}else{//Altrimenti
			pos++;//Incrementa il contatore di posizione
			l = codaLista(l);//Continuiamo la visita degli elementi della lista
		}
	}
	//1 delle due condizioni per uscire dal ciclo è stata soddisfatta
	if(!trovato)//Controlliamo il valore della flag
		pos = -1; //Se non trovato restituiamo come posizione -1
	return pos;//Restituiamo la posizione dell'elemento
}
//Funzione che cerca un album nella lista per un parametro e restituisce un catalogo con gli album trovati
lista cercaAlbum(lista l){
	int r;//Variabile che contiene la risposta dell'utente
	lista ltrovati = nuovaLista();//Dichiarazione e inizializzazione della lista di output con gli album trovati
	do{
		printf("Cosa vuoi cercare?\n");//Chiede all'utente il campo da cercare
		printf("    - 1: Titolo\n");
		printf("    - 2: Artista\n");
		printf("    - 3: Genere\n");
		printf("    - 4: Anno\n");
		printf("    - 0: Chiudi\n");
		scanf("%d", &r);//Immagazzina la risposta
		fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
	}while(r<0 || r>4);//Verifica se l'utente ha inserito un valore da 0 a 4
	switch(r){//Controlla il valore di r
		case 0:{//Caso della chiusura
			return ltrovati;//Restituisce la lista vuota
		}
		case 1:{//Caso del titolo
			char str[MAX_LEN+1];//Variabile che immagazzina la stringa
			printf("Inserisci il titolo che vuoi cercare (max %d caratteri): ", MAX_LEN);
			gets(str);//Prende in input la stringa
			str[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
			str[strcspn(str, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
			fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
			idalbum *album;//Dichiara la struttura di appoggio per salvare gli album trovati
			while(!listaVuota(l)){//Finchè la lista non è vuota
				if(!(strcmp(l->titolo, str))){//Compara il titolo della struttura con quello cercato
					album=prendiPrimo(l);//Prende l'album in testa alla lista
					//output_id(album);//Stampa l'album corrispondente
					ltrovati = aggiungiAlbum(ltrovati, album->titolo, album->artista, album->genere, album->anno);//Aggiunge l'album alla lista di output
				}
				l = codaLista(l);//Passa all'album successivo
			}
			return ltrovati;//Restituisce la lista con gli album trovati (NULL se non ne ha trovati)
			break;
		}
		case 2:{//Caso dell'artista
			char str[MAX_LEN+1];//Variabile che immagazzina la stringa
			printf("Inserisci l'artista che vuoi cercare (max %d caratteri): ", MAX_LEN);
			gets(str);//Prende in input la stringa
			str[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
			str[strcspn(str, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
			fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
			idalbum *album;//Dichiara la struttura di appoggio per salvare gli album trovati
			while(!listaVuota(l)){//Finchè la lista non è vuota
				if(!(strcmp(l->artista, str))){//Compara l'artista della struttura con quello cercato
					album=prendiPrimo(l);//Prende l'album in testa alla lista
					//output_id(album);//Stampa l'album corrispondente
					ltrovati = aggiungiAlbum(ltrovati, album->titolo, album->artista, album->genere, album->anno);//Aggiunge l'album alla lista di output
				}
				l = codaLista(l);//Passa all'album successivo
			}
			return ltrovati;//Restituisce la lista con gli album trovati (NULL se non ne ha trovati)
			break;
		}
		case 3:{//Caso del genere
			char str[MAX_LEN+1];//Variabile che immagazzina la stringa
			printf("Inserisci il genere che vuoi cercare (max %d caratteri: ", MAX_LEN);
			gets(str);//Prende in input la stringa
			str[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
			str[strcspn(str, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
			fflush(stdin);//Toglie eventuali caratteri sovrabbondanti
			idalbum *album;//Dichiara la struttura di appoggio per salvare gli album trovati
			while(!listaVuota(l)){//Finchè la lista non è vuota
				if(!(strcmp(l->genere, str))){//Compara il genere della struttura con quello cercato
					album=prendiPrimo(l);//Prende l'album in testa alla lista
					//output_id(album);//Stampa l'album corrispondente
					ltrovati = aggiungiAlbum(ltrovati, album->titolo, album->artista, album->genere, album->anno);//Aggiunge l'album alla lista di output
				}
				l = codaLista(l);//Passa all'album successivo
			}
			return ltrovati;//Restituisce la lista con gli album trovati (NULL se non ne ha trovati)
			break;
		}
		case 4:{//Caso dell'anno
			do{
				printf("Inserisci l'anno che vuoi cercare (minimo 1800 - massimo %d): ", ANNO_CORRENTE);
				scanf("%d", &r);//Prende in input l'anno (riutilizzo la variabile r)
			}while(r<1800 || r>ANNO_CORRENTE);//Verifica che il valore inserito sia un effettivo valore valido (tra 1800 e ANNO_CORRENTE)
			idalbum *album;//Dichiara la struttura di appoggio per salvare gli album trovati
			while(!listaVuota(l)){//Finchè la lista non è vuota
				if(l->anno==r){//Compara l'anno della struttura con quello cercato
					album=prendiPrimo(l);//Prende l'album in testa alla lista
					//output_id(album);//Stampa l'album corrispondente
					ltrovati = aggiungiAlbum(ltrovati, album->titolo, album->artista, album->genere, album->anno);//Aggiunge l'album alla lista di output
				}
				l = codaLista(l);//Passa all'album successivo
			}
			return ltrovati;//Restituisce la lista con gli album trovati (NULL se non ne ha trovati)
			break;
		}
		default:{
			return ltrovati;//Restituisce la lista vuota (Opzionale: per evitare errori)
		}
	}
}
//Funzione che cerca un album nella lista per un parametro dato da file e restituisce un catalogo con gli album trovati
lista fcercaAlbum(FILE *f, lista l){
	if(f==NULL){//Controlla che il file sia correttamente aperto
		perror("Errore nell'apertura del file\n");
		return NULL;//Restituisce il controllo alla funzione chiamante
	}
	int r, anno;//Variabile che contiene la risposta dell'utente
	char riga[300], stringa[MAX_LEN+1];//Stringa dove salva la riga del file
	lista ltrovati = nuovaLista();//Dichiarazione e inizializzazione della lista di output con gli album trovati
	fgets(riga, 300, f);//Prende in input la stringa del file e la salva in (riga) 
	sscanf(riga, "%d %s", &r, stringa);//sscanf() prende l'input da una stringa (numero che identifica il parametro, stringa da cercare)
	stringa[MAX_LEN]='\0';//Si assicura che la stringa sia della dimensione adatta
	while(r<1 || r>4){//Verifica che il valore inserito sia un effettivo valore valido (tra 1 e 4)
		printf("Parametro dell'album non valido\n");
		printf("Cosa vuoi cercare?\n");//Chiede all'utente il campo da cercare
		printf("    - 1: Titolo\n");
		printf("    - 2: Artista\n");
		printf("    - 3: Genere\n");
		printf("    - 4: Anno\n");
		scanf("%d", &r);
		fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
	}
	if(r==4){//Se il parametro passato è l'anno (4) 
		anno=atoi(stringa);//Converte la stringa in intero
		while(anno<1800 || anno>ANNO_CORRENTE){//Verifica che il valore inserito sia un effettivo valore valido (tra 1800 e la costante ANNO_CORRENTE)
			printf("Anno dell'album non valido\n");
			printf("Immetti l'anno dell'album (minimo 1800 - massimo %d): ", ANNO_CORRENTE);
			scanf("%d", &anno);//Salva l'intero per l'anno
			fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
		}
	}
	idalbum *album;//Dichiara la struttura di appoggio per salvare gli album trovati
	switch(r){//Controlla il valore di r
		case 1:{//Caso del titolo
			while(!listaVuota(l)){//Finchè la lista non è vuota
				if(!(strcmp(l->titolo, stringa))){//Compara il titolo della struttura con quello cercato
					album=prendiPrimo(l);//Prende l'album in testa alla lista
					ltrovati = aggiungiAlbum(ltrovati, album->titolo, album->artista, album->genere, album->anno);//Aggiunge l'album alla lista di output
				}
				l = codaLista(l);//Passa all'album successivo
			}
			return ltrovati;//Restituisce la lista con gli album trovati (NULL se non ne ha trovati)
			break;
		}
		case 2:{//Caso dell'artista
			while(!listaVuota(l)){//Finchè la lista non è vuota
				if(!(strcmp(l->artista, stringa))){//Compara l'artista della struttura con quello cercato
					album=prendiPrimo(l);//Prende l'album in testa alla lista
					//output_id(album);//Stampa l'album corrispondente
					ltrovati = aggiungiAlbum(ltrovati, album->titolo, album->artista, album->genere, album->anno);//Aggiunge l'album alla lista di output
				}
				l = codaLista(l);//Passa all'album successivo
			}
			return ltrovati;//Restituisce la lista con gli album trovati (NULL se non ne ha trovati)
			break;
		}
		case 3:{//Caso del genere
			while(!listaVuota(l)){//Finchè la lista non è vuota
				if(!(strcmp(l->genere, stringa))){//Compara il genere della struttura con quello cercato
					album=prendiPrimo(l);//Prende l'album in testa alla lista
					//output_id(album);//Stampa l'album corrispondente
					ltrovati = aggiungiAlbum(ltrovati, album->titolo, album->artista, album->genere, album->anno);//Aggiunge l'album alla lista di output
				}
				l = codaLista(l);//Passa all'album successivo
			}
			return ltrovati;//Restituisce la lista con gli album trovati (NULL se non ne ha trovati)
			break;
		}
		case 4:{//Caso dell'anno
			while(!listaVuota(l)){//Finchè la lista non è vuota
				if(l->anno==anno){//Compara l'anno della struttura con quello cercato
					album=prendiPrimo(l);//Prende l'album in testa alla lista
					//output_id(album);//Stampa l'album corrispondente
					ltrovati = aggiungiAlbum(ltrovati, album->titolo, album->artista, album->genere, album->anno);//Aggiunge l'album alla lista di output
				}
				l = codaLista(l);//Passa all'album successivo
			}
			return ltrovati;//Restituisce la lista con gli album trovati (NULL se non ne ha trovati)
			break;
		}
		default:{
			return ltrovati;//Restituisce la lista vuota (Opzionale: per evitare errori)
		}
	}
}
//Funzione che cerca un album nella lista per il titolo e restituisce un 1 se l'ha trovato, 0 altrimenti
int cercaTitolo(lista l, char *tit){
	int f=0;//Variabile booleana "flag" che inizializza a 0
	while(!listaVuota(l)){//Finchè la lista non è vuota
		if(!(strcmp(l->titolo, tit))){//Compara il titolo della struttura con quello cercato
			f=1;//Titolo trovato, "flag" settata a 1
			break;
		}
		l = codaLista(l);//Passa all'album successivo
	}
	return f;//Restituisce la flag, 1 se ha trovato il titolo, 0 altrimenti
}
//Funzione che stampa tutti gli album del catalogo
void stampaCatalogo(lista l){
	int i = 0; //Inizializzazione di un contatore per la posizione degli elementi
	idalbum *val; //Dichiarazione di una variabile temporanea per memorizzare il valore degli elementi
	//Ciclo finché la lista non è vuota
	while (!listaVuota(l)){
		val = prendiPrimo(l);//Ottiene il valore del primo elemento della lista
		printf("%d Album:\n", i+1);// Stampa la posizione dell'album
		output_id(val);//Stampa il valore dell'album utilizzando la funzione output_id() definita in ADT_Album.h
		l = codaLista(l);//Passa al prossimo album del catalogo
		i++; //Incrementa il contatore della posizione
	}
	return;//Restituisce il controllo alla funzione chiamante
}
//Funzione che stampa tutti gli album del catalogo in un file passato alla funzione
void fstampaCatalogo(FILE *f, lista l){
	if(f==NULL){//Controlla che il file sia correttamente aperto
		perror("Errore nell'apertura del file\n");
		return;//Restituisce il controllo alla funzione chiamante
	}
	idalbum *val; //Dichiarazione di una variabile temporanea per memorizzare il valore degli elementi
	//Ciclo finché la lista non è vuota
	while (!listaVuota(l)){
		val = prendiPrimo(l);//Ottiene il valore del primo elemento della lista
		fprintf(f, "%s %s %s %d\n", val->titolo, val->artista, val->genere, val->anno);//Stampa il valore dell'album, utilizzando la funzione fprintf(), nel file di output
		l = codaLista(l);//Passa al prossimo album del catalogo
	}
	return;//Restituisce il controllo alla funzione chiamante
}
//Funzione che scambia i campi di due liste
void scambia(lista l1, lista l2){
	//Salvo i valori della prima lista
	char *titolo=l1->titolo, *artista=l1->artista, *genere=l1->genere;
	int anno=l1->anno;
	
	//Copia della seconda lista nella prima
	if(!(l1->titolo=malloc(strlen(l2->titolo)*sizeof(char)+1))){//Alloca il titolo della prima lista
		fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
		exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
	}
	strcpy(l1->titolo, l2->titolo);//Copia del titolo della seconda lista nella prima
	if(!(l1->artista=malloc(strlen(l2->artista)*sizeof(char)+1))){//Alloca l'artista della prima lista
		fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
		exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
	}
	strcpy(l1->artista, l2->artista);//Copia dell'artista della seconda lista nella prima
	if(!(l1->genere=malloc(strlen(l2->genere)*sizeof(char)+1))){//Alloca il genere della prima lista
		fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
		exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
	}
	strcpy(l1->genere, l2->genere);//Copia del genere della seconda lista nella prima
	l1->anno=l2->anno;//Copia dell'anno della seconda lista nella prima
	
	//Copio gli elementi salvati precedentemente nella seconda lista
	if(!(l2->titolo=malloc(strlen(titolo)*sizeof(char)+1))){//Alloca il titolo della seconda lista
		fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
		exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
	}
	strcpy(l2->titolo, titolo);//Copia del titolo della prima lista nella seconda
	if(!(l2->artista=malloc(strlen(artista)*sizeof(char)+1))){//Alloca l'artista della seconda lista
		fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
		exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
	}
	strcpy(l2->artista, artista);//Copia dell'artista della prima lista nella seconda
	if(!(l2->genere=malloc(strlen(genere)*sizeof(char)+1))){//Alloca il genere della seconda lista
		fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
		exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
	}
	strcpy(l2->genere, genere);//Copia del genere della prima lista nella seconda
	l2->anno=anno;//Copia dell'anno della prima lista nella seconda
	return;//Restituisce il controllo alla funzione chiamante
}
//Funzione che riordina in modo decrescente il catalogo (lista) in base all'anno
lista ordinannoCatalogo(lista l){
	if(!(listaVuota(l)) && !(listaVuota(l->next))) {//Verifica che la lista e il suo successivo non siano vuoti
		int f;//Dichiarazione variabile booleana "flag", per la verifica dello scambio
		do{
			lista ltmp = l;//Inizializzazione lista temporanea che punta ad l
			f = 0;//Inizializzazione variabile flag a 0
			while(!(listaVuota(ltmp->next))){//Finchè la prossima lista non è vuota
				lista lapp = ltmp;//Dichiarazione lista di appoggio che punta a all'album attuale
				ltmp = codaLista(ltmp);//Passo al prossimo album della lista
				if ((lapp->anno) < (ltmp->anno)){//Controlla se l'anno della prima lista è minore di quello della seconda
					scambia(lapp, ltmp);//Scambia i campi delle due liste
					f = 1;//Imposta la variabile flag a 1 poichè è avvenuto uno scambio
				}
			}
		}while(f != 0);//Se non sono avvenuti scambi il flag vale 0 ed esce dal ciclo
	}
	//stampaCatalogo(l);
	return l;//Restituisce la lista ordinata
}
