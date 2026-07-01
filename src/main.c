#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Album.h"
#define MAX 300//Definisce la grandezza massima delle righe
int main(int argc, char *argv[]){
    int r;//Variabile che useremo per immagazzinare le risposte dell'utente
	do{
		printf("Vuoi prendere l'input da file? (1 per SI/0 per NO)\n");
		scanf("%d", &r);//Immagazzina la risposta in r
	}while(r<0 || r>1);//Controlla che sia un valore valido
	if(r){//Caso input da file
		if (argc != 2){//Se gli argomenti passati 
			printf("Utilizzo: %s <file_test_suite>\n", argv[0]);
			printf("    - file_test_suite: ID Test Case, Operazione da fare(1 per Aggiunta, 2 per Rimozione, 3 per Ricerca)\n");
			return 1;//Chiude la funzione main restituendo 1 (file mancante)
		}
		char *nome_ts = argv[1];//Salva la stringa data in input
		FILE *file_ts = fopen(nome_ts, "r");//Apre il file della stringa in lettura
		if (file_ts == NULL){//Controlla che il file sia correttamente aperto
			printf("Impossibile aprire il file %s\n", nome_ts);
			return 1;//Chiude la funzione main restituendo 1 (file mancante)
		}
		char riga[MAX];//Array di caratteri per immagazzinare le righe come stringhe
		char tc_id[4];//Stringa contenente l'identificativo del test case
		while(fgets(riga, MAX, file_ts)){//Immagazzina le righe del file finchè non è vuoto
			lista l = nuovaLista();//Dichiarazione della lista che useremo come catalogo
			int c=sscanf(riga, "%3s %d", tc_id, &r);//sscanf() prende l'input da una stringa (id test case e operazione da fare)
			tc_id[3]='\0';
			if(r<0 || r>3){//Controlla l'input passato
				printf("Input da file non valido");
				return 2;//Chiude la funzione main restituendo 2 (input non valido)
			}
			//Dichiarazioni variabili utili
			char input_nomef[MAX], output_nomef[MAX], oracolo_nomef[MAX];//Dichiarazione variabili per i file
			char titolo[MAX_LEN+1], artista[MAX_LEN+1], genere[MAX_LEN+1];//Dichiara gli array di caratteri dove immagazzinare i dati
			int anno, f_titolo;//Dichiara l'intero per l'anno e una "flag" che verifica che il titolo non esista già
			//Costruisce i nomi dei file
			strcpy(input_nomef, tc_id);//Copia l'id del test case
			strcat(input_nomef, "_input.txt");//Concatena la stringa per l'input
			FILE *finput = fopen(input_nomef, "r");//Apre il file di input in lettura
			if(finput==NULL){//Controlla che il file esiste e sia aperto correttamente
				printf("Impossibile aprire il file %s\n", input_nomef);
				return 1;//Chiude la funzione main restituendo 1 (file mancante)
			}
			strcpy(output_nomef, tc_id);//Copia l'id del test case
			strcat(output_nomef, "_output.txt");//Concatena la stringa per l'output
			FILE *foutput = fopen(output_nomef, "w");//Apre il file di output in scrittura
			//Non effettua il controllo poichè se il file non esiste lo crea
			strcpy(oracolo_nomef, tc_id);//Copia l'id del test case
			strcat(oracolo_nomef, "_oracolo.txt");//Concatena la stringa per l'oracolo
			FILE *foracolo = fopen(oracolo_nomef, "r");//Apre il file oracolo in lettura
			if(foracolo==NULL){//Controlla che il file esiste e sia aperto correttamente
				printf("Impossibile aprire il file %s\n", oracolo_nomef);
				return 1;//Chiude la funzione main restituendo 1 (file mancante)
			}
			FILE *risultati = fopen("risultati.txt", "a");//Apre il file dei risultati in "appending" (ossia tutte le cose che verranno scritte andranno ad aggiungersi a quelle già presenti sul file)
			//lista listatrovati;//Dichiara la lista che potrebbe venir utilizzata nella ricerca
			//Controlla l'operazione da eseguire
			switch(r){
				case 0:{//Caso chiusura
					return 0;//Chiude la funzione main e quindi il programma restituendo 0
				}
				case 1:{//Caso aggiunta
					//lista aggiungiAlbum(lista l, char *tit, char *art, char *gen, int anno);
					while(fgets(riga, MAX, finput)!=NULL){//Prende in input la stringa del file controllando sia diversa da NULL e la salva in (riga) 
						sscanf(riga, "%s %s %s %d", titolo, artista, genere, &anno);//sscanf() prende l'input da una stringa (titolo, artista, genere, anno)
						do{
							f_titolo=0;//Setta la flag a 0
							if(cercaTitolo(l, titolo)==1){//Verifica che il titolo non esista già
								f_titolo=1;//Setta la flag a 1
								printf("Questo titolo è già presente nel catalogo\n");//Avvisa l'utente
								printf("Immetti il titolo dell'album (max %d caratteri): ", MAX_LEN);//MAX_LEN costante definita in "Album.h"
								gets(titolo);//Salva la stringa per il titolo
								titolo[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
								titolo[strcspn(titolo, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
								fflush(stdin);
							}
						}while(f_titolo==1);//Se la flag è 1 il titolo esiste già e forza il reinserimento
						while(anno<1800 || anno>ANNO_CORRENTE){//Verifica che il valore inserito sia un effettivo valore valido (tra 1800 e la costante ANNO_CORRENTE)
							printf("Anno dell'album non valido\n");
							printf("Immetti l'anno dell'album (minimo 1800 - massimo %d): ", ANNO_CORRENTE);
							scanf("%d", &anno);//Salva l'intero per l'anno
							fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
						}
						l=aggiungiAlbum(l, titolo, artista, genere, anno);//Passa tutti i parametri alla funzione che aggiunge l'album
					}
					l=ordinannoCatalogo(l);//Ordiniamo la lista per anno
					lista l_oracolo= nuovaLista();//Dichiarazione della lista contenente gli album dell'oracolo
					while(fgets(riga, MAX, foracolo)!=NULL){//Prende in input la stringa del file controllando sia diversa da NULL e la salva in (riga) 
						sscanf(riga, "%s %s %s %d", titolo, artista, genere, &anno);//sscanf() prende l'input da una stringa (titolo, artista, genere, anno)
						l_oracolo=aggiungiAlbum(l, titolo, artista, genere, anno);//Passa tutti i parametri alla funzione che aggiunge l'album alla lista oracolo
					}
					l_oracolo=invertiLista(l_oracolo);//Invertiamo la lista per averla nell'ordine in cui è stata letta
					l_oracolo=ordinannoCatalogo(l_oracolo);//Ordiniamo la lista per anno
					int diverso=0;//"flag" che verifica che tutti gli album siano uguali
					idalbum *alb_out, *alb_oracolo;//Dichiarazione di variabili temporanee per memorizzare i valori degli album
					fstampaCatalogo(foutput, l);//Passa la lista alla funzione fstampaCatalogo() che ne stampa gli album nel file di output
					//Controlla le liste per verificare siano uguali
					while(!listaVuota(l) && !listaVuota(l_oracolo)){//Finchè le liste non sono vuote
						alb_out=prendiPrimo(l);//Prendiamo l'album in testa alla lista l
						alb_oracolo=prendiPrimo(l_oracolo);//Prendiamo l'album in testa alla lista l_oracolo
						
						if(comparaAlbum(alb_out, alb_oracolo)==1){//Compariamo gli album utilizzando la funzione comparaAlbum() definita in ADT_Album.h
							diverso=1;//Settiamo la "flag" a 1
						}
						l = codaLista(l);//Continuiamo la visita degli elementi della lista l
						l_oracolo = codaLista(l_oracolo);//Continuiamo la visita degli elementi della lista l_oracolo
					}
					//Non effettua il controllo poichè se il file non esiste lo crea
					if(diverso==1){
						fprintf(risultati, "%s FAIL\n", tc_id);
					}else{   
						fprintf(risultati, "%s PASS\n", tc_id);	
					}
					while(!listaVuota(l)){//Finchè il puntatore all'album corrente non è vuoto
						lista l2=l;//Assegna ad una nuova lista il puntatore alla lista precedente
						l=codaLista(l);//Scorri al nuovo album nella lista precedente
						free(l2);//Libera il puntatore al vecchio album
					}
					free(l);//Libera il puntatore alla lista
					break;//Esce dallo switch
				}
				case 2:{//Caso rimozione
					//lista rimuoviAlbum(lista l, int pos);
					int posizione;//Dichiara la variabile per la posizione
					fscanf(finput, "%d\n", &posizione);//Prende in input la posizione
					while(posizione<0){//Verifica che sia inserito un numero positivo
						printf("Posizione di rimozione non valida\n");//Avvisa l'utente
						printf("Immetti la posizione dell'album da rimuovere: ");
						scanf("%d", &posizione);//Prende in input la posizione
						fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
					}
					while(fgets(riga, MAX, finput)!=NULL){//Prende in input la stringa del file controllando sia diversa da NULL e la salva in (riga) 
						sscanf(riga, "%s %s %s %d", titolo, artista, genere, &anno);//sscanf() prende l'input da una stringa (titolo, artista, genere, anno)
						do{
							f_titolo=0;//Setta la flag a 0
							if(cercaTitolo(l, titolo)==1){//Verifica che il titolo non esista già
								f_titolo=1;//Setta la flag a 1
								printf("Questo titolo è già presente nel catalogo\n");//Avvisa l'utente
								printf("Immetti il titolo dell'album (max %d caratteri): ", MAX_LEN);//MAX_LEN costante definita in "Album.h"
								gets(titolo);//Salva la stringa per il titolo
								titolo[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
								titolo[strcspn(titolo, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
								fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
							}
						}while(f_titolo==1);//Se la flag è 1 il titolo esiste già e forza il reinserimento
						while(anno<1800 || anno>ANNO_CORRENTE){//Verifica che il valore inserito sia un effettivo valore valido (tra 1800 e la costante ANNO_CORRENTE)
							printf("Anno dell'album non valido\n");
							printf("Immetti l'anno dell'album (minimo 1800 - massimo %d): ", ANNO_CORRENTE);
							scanf("%d", &anno);//Salva l'intero per l'anno
							fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
						}
						l=aggiungiAlbum(l, titolo, artista, genere, anno);//Passa tutti i parametri alla funzione che aggiunge l'album
					}
					l=rimuoviAlbum(l, posizione);//Passa i parametri alla funzione che rimuove l'album
					if(listaVuota(l))//Controlla che la lista non sia vuota
						printf("Posizione non valida poichè non ci sono %d elementi nel catalogo\n", posizione);//Stampa avviso
					l=ordinannoCatalogo(l);//Ordiniamo la lista per anno
					lista l_oracolo= nuovaLista();//Dichiarazione della lista contenente gli album dell'oracolo
					while(fgets(riga, MAX, foracolo)!=NULL){//Prende in input la stringa del file controllando sia diversa da NULL e la salva in (riga) 
						sscanf(riga, "%s %s %s %d", titolo, artista, genere, &anno);//sscanf() prende l'input da una stringa (titolo, artista, genere, anno)
						l_oracolo=aggiungiAlbum(l, titolo, artista, genere, anno);//Passa tutti i parametri alla funzione che aggiunge l'album alla lista oracolo
					}
					l_oracolo=invertiLista(l_oracolo);//Invertiamo la lista per averla nell'ordine in cui è stata letta
					l_oracolo=ordinannoCatalogo(l_oracolo);//Ordiniamo la lista per anno
					int diverso=0;//"flag" che verifica che tutti gli album siano uguali
					idalbum *alb_out, *alb_oracolo;//Dichiarazione di variabili temporanee per memorizzare i valori degli album
					fstampaCatalogo(foutput, l);//Passa la lista alla funzione fstampaCatalogo() che ne stampa gli album nel file di output
					//Controlla le liste per verificare siano uguali
					while(!listaVuota(l) && !listaVuota(l_oracolo)){//Finchè le liste non sono vuote
						alb_out=prendiPrimo(l);//Prendiamo l'album in testa alla lista l
						alb_oracolo=prendiPrimo(l_oracolo);//Prendiamo l'album in testa alla lista l_oracolo
						
						if(comparaAlbum(alb_out, alb_oracolo)==1){//Compariamo gli album utilizzando la funzione comparaAlbum() definita in ADT_Album.h
							diverso=1;//Settiamo la "flag" a 1
						}
						l = codaLista(l);//Continuiamo la visita degli elementi della lista l
						l_oracolo = codaLista(l_oracolo);//Continuiamo la visita degli elementi della lista l_oracolo
					}
					//Non effettua il controllo poichè se il file non esiste lo crea
					if(diverso==1){
						fprintf(risultati, "%s FAIL\n", tc_id);
					}else{   
						fprintf(risultati, "%s PASS\n", tc_id);	
					}
					while(!listaVuota(l)){//Finchè il puntatore all'album corrente non è vuoto
						lista l2=l;//Assegna ad una nuova lista il puntatore alla lista precedente
						l=codaLista(l);//Scorri al nuovo album nella lista precedente
						free(l2);//Libera il puntatore al vecchio album
					}
					free(l);//Libera il puntatore alla lista
					break;//Esce dallo switch
				}
				case 3:{//Caso cerca
					//lista fcercaAlbum(FILE *f, lista l);
					while(fgets(riga, MAX, finput)!=NULL){//Prende in input la stringa del file controllando sia diversa da NULL e la salva in (riga) 
						sscanf(riga, "%s %s %s %d", titolo, artista, genere, &anno);//sscanf() prende l'input da una stringa (titolo, artista, genere, anno)
						do{
							f_titolo=0;//Setta la flag a 0
							if(cercaTitolo(l, titolo)==1){//Verifica che il titolo non esista già
								f_titolo=1;//Setta la flag a 1
								printf("Questo titolo è già presente nel catalogo\n");//Avvisa l'utente
								printf("Immetti il titolo dell'album (max %d caratteri): ", MAX_LEN);//MAX_LEN costante definita in "Album.h"
								gets(titolo);//Salva la stringa per il titolo
								titolo[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
								titolo[strcspn(titolo, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
								fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
							}
						}while(f_titolo==1);//Se la flag è 1 il titolo esiste già e forza il reinserimento
						while(anno<1800 || anno>ANNO_CORRENTE){//Verifica che il valore inserito sia un effettivo valore valido (tra 1800 e la costante ANNO_CORRENTE)
							printf("Anno dell'album non valido\n");
							printf("Immetti l'anno dell'album (minimo 1800 - massimo %d): ", ANNO_CORRENTE);
							scanf("%d", &anno);//Salva l'intero per l'anno
							fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
						}
						l=aggiungiAlbum(l, titolo, artista, genere, anno);//Passa tutti i parametri alla funzione che aggiunge l'album
					}
					getc(stdin);//Pulisce caratteri sovrabbondanti rimasti nel buffer
					char nome_cercafile[MAX];//Dichiarazione variabile per il file
					printf("Inserisci il file da dove vuoi prendere i parametri da cercare\n");//Io ho usato il file cerca.txt
					gets(nome_cercafile);//Salva la stringa per il titolo
					nome_cercafile[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
					nome_cercafile[strcspn(nome_cercafile, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
					fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
					FILE *fcerca = fopen(nome_cercafile, "r");//Apre il file di input in lettura
					if(fcerca==NULL){//Controlla che il file esiste e sia aperto correttamente
						printf("Impossibile aprire il file %s\n", nome_cercafile);
						return 1;//Chiude la funzione main restituendo 1 (file mancante)
					}
					l=fcercaAlbum(fcerca, l);//Immagazzina gli album trovati in una lista (output della funzione cercaAlbum())
					if(listaVuota(l)){//Controlla il valore della lista per verificare se è vuota
						printf("Nessun album trovato!\n");//Avvisa l'utente di nessun riscontro
					}
					fclose(fcerca);//Chiude il file di ricerca
					l=ordinannoCatalogo(l);//Ordiniamo la lista per anno
					lista l_oracolo= nuovaLista();//Dichiarazione della lista contenente gli album dell'oracolo
					while(fgets(riga, MAX, foracolo)!=NULL){//Prende in input la stringa del file controllando sia diversa da NULL e la salva in (riga) 
						sscanf(riga, "%s %s %s %d", titolo, artista, genere, &anno);//sscanf() prende l'input da una stringa (titolo, artista, genere, anno)
						l_oracolo=aggiungiAlbum(l, titolo, artista, genere, anno);//Passa tutti i parametri alla funzione che aggiunge l'album alla lista oracolo
					}
					l_oracolo=invertiLista(l_oracolo);//Invertiamo la lista per averla nell'ordine in cui è stata letta
					l_oracolo=ordinannoCatalogo(l_oracolo);//Ordiniamo la lista per anno
					int diverso=0;//"flag" che verifica che tutti gli album siano uguali
					idalbum *alb_out, *alb_oracolo;//Dichiarazione di variabili temporanee per memorizzare i valori degli album
					fstampaCatalogo(foutput, l);//Passa la lista alla funzione fstampaCatalogo() che ne stampa gli album nel file di output
					//Controlla le liste per verificare siano uguali
					while(!listaVuota(l) && !listaVuota(l_oracolo)){//Finchè le liste non sono vuote
						alb_out=prendiPrimo(l);//Prendiamo l'album in testa alla lista l
						alb_oracolo=prendiPrimo(l_oracolo);//Prendiamo l'album in testa alla lista l_oracolo
						if(comparaAlbum(alb_out, alb_oracolo)==1){//Compariamo gli album utilizzando la funzione comparaAlbum() definita in ADT_Album.h
							diverso=1;//Settiamo la "flag" a 1
						}
						l = codaLista(l);//Continuiamo la visita degli elementi della lista l
						l_oracolo = codaLista(l_oracolo);//Continuiamo la visita degli elementi della lista l_oracolo
					}
					//Non effettua il controllo poichè se il file non esiste lo crea
					if(diverso==1){
						fprintf(risultati, "%s FAIL\n", tc_id);
					}else{   
						fprintf(risultati, "%s PASS\n", tc_id);	
					}
					while(!listaVuota(l)){//Finchè il puntatore all'album corrente non è vuoto
						lista l2=l;//Assegna ad una nuova lista il puntatore alla lista precedente
						l=codaLista(l);//Scorri al nuovo album nella lista precedente
						free(l2);//Libera il puntatore al vecchio album
					}
					free(l);//Libera il puntatore alla lista
					break;//Esce dallo switch
				}
			}//switch(r)
			//Chiusura vari file
			fclose(finput);//Chiude il file di input
			fclose(foracolo);//Chiude il file dell'oracolo
			fclose(foutput);//Chiude il file di output
			fclose(risultati);//Chiude il file risultati
		}//while(fgets())
		fclose(file_ts);//Chiude il file della test suite
		printf("FINITO!\n");//Avvisa l'utente di aver terminato le operazioni
		return 0;
	}
	//Caso input utente
	lista l = nuovaLista();//Dichiarazione della lista che useremo come catalogo
	r=1;//Settiamo a 1 per essere sicuri di entrare nel ciclo
	while(r!=0){//Finchè r non vale 0 (valore di chiusura del programma)
		do{
			printf("\nCosa vuoi fare?\n");//Menù dove l'utente sceglie cosa vuole fare
			printf("    - 1: Aggiungere un album\n");
			printf("    - 2: Eliminare un album tramite posizione\n");
			printf("    - 3: Modificare un album\n");
			printf("    - 4: Trova la posizione di un album\n");
			printf("    - 5: Cerca un album\n");
			printf("    - 6: Ordina il catalogo in modo decrescente per anno di uscita\n");
			printf("    - 7: Per sapere quanti album ci sono nel catalogo\n");
			printf("    - 8: Stampa il catalogo\n");
			printf("    - 0: Chiudi il programma\n");
			scanf("%d", &r);//Immagazzina la risposta in r
			getc(stdin);//Pulisce il buffer da caratteri sovrabbondanti
		}while(r<0 || r>8);//Verifica che il valore inserito sia un effettivo valore valido
		switch(r){//Controlla i casi
			case 0:{//Caso chiusura
				while(!listaVuota(l)){//Finchè il puntatore all'album corrente non è vuoto
					lista l2=l;//Assegna ad una nuova lista il puntatore alla lista precedente
					l=codaLista(l);//Scorri al nuovo album nella lista precedente
					free(l2);//Libera il puntatore al vecchio album
				}
				free(l);//Libera il puntatore alla lista
				return 0;//Chiude la funzione main e quindi il programma restituendo 0
			}
			case 1:{//Caso aggiunta
				//lista aggiungiAlbum(lista l, char *tit, char *art, char *gen, int anno);
				char titolo[MAX_LEN+1], artista[MAX_LEN+1], genere[MAX_LEN+1];//Dichiara gli array di caratteri dove immagazzinare i dati
				int anno, f_titolo;//Dichiara l'intero per l'anno e una "flag" che verifica che il titolo non esista già
				do{
					f_titolo=0;//Setta la flag a 0
					printf("Immetti il titolo dell'album (max %d caratteri): ", MAX_LEN);//MAX_LEN costante definita in "Album.h"
					gets(titolo);//Salva la stringa per il titolo
					titolo[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
					titolo[strcspn(titolo, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
					if(cercaTitolo(l, titolo)==1){//Verifica che il titolo non esista già
						f_titolo=1;//Setta la flag a 1
						printf("Questo titolo è già presente nel catalogo\n");//Avvisa l'utente
					}
					fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
					fflush(stdout);//Toglie eventuali caratteri sovrabbondanti
				}while(f_titolo==1);//Se la flag è 1 il titolo esiste già e forza il reinserimento
				printf("\nImmetti il nome dell'artista(max %d caratteri): ", MAX_LEN);
				gets(artista);//Salva la stringa per l'artista
				artista[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
				artista[strcspn(artista, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
				fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
				fflush(stdout);//Toglie eventuali caratteri sovrabbondanti
				printf("\nImmetti il genere dell'album(max %d caratteri): ", MAX_LEN);
				gets(genere);//Salva la stringa per il genere
				genere[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
				genere[strcspn(genere, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
				fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
				fflush(stdout);//Toglie eventuali caratteri sovrabbondanti
				do{
					printf("\nImmetti l'anno dell'album (minimo 1800 - massimo %d): ", ANNO_CORRENTE);
					scanf("%d", &anno);//Salva l'intero per l'anno
					fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
				}while(anno<1800 || anno>ANNO_CORRENTE);//Verifica che il valore inserito sia un effettivo valore valido (tra 1800 e la costante ANNO_CORRENTE)
				l=aggiungiAlbum(l, titolo, artista, genere, anno);//Passa tutti i parametri alla funzione che aggiunge l'album
				break;//Esce dallo switch
			}
			case 2:{//Caso rimozione
				//lista rimuoviAlbum(lista l, int pos);
				int posizione;//Dichiara la variabile per la posizione
				do{
					printf("Immetti la posizione dell'album da rimuovere: ");
					scanf("%d", &posizione);//Prende in input la posizione
				}while(posizione<0);//Verifica che sia inserito un numero positivo
				fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
				l=rimuoviAlbum(l, posizione);//Passa i parametri alla funzione che rimuove l'album
				if(listaVuota(l))//Controlla che la lista non sia vuota
					printf("Posizione non valida poichè non ci sono %d elementi nel catalogo\n", posizione);//Stampa avviso
				break;//Esce dallo switch
			}
			case 3:{//Caso modifica
				//int modificaAlbum(lista l);
				int output=modificaAlbum(l);//Passo la lista alla funzione modificaAlbum() e salvo il valore di ritorno in una variabile intera (output)
				//Controlla il valore di output della funzione e stampa i relativi avvisi
				if(output==1){
					printf("Valore modificato con successo\n");//Caso restituzione 0
				}else{
					if(output==0){
						printf("Album non presente nel catalogo\n");//Caso restituzione 1
					}else{
						printf("Funzione modifica chiusa con successo\n");//Caso restituzione 2
					}
				}
				break;//Esce dallo switch
			}
			case 4:{//Caso trova posizione
				//int posizioneAlbum(lista l, idalbum *x);
				char ti[MAX_LEN+1], ar[MAX_LEN+1], ge[MAX_LEN+1];//Dichiara gli array di caratteri dove immagazzinare i dati
				idalbum *z=calloc(1, sizeof(idalbum));//Dichiara e alloca una struttura idalbum
				if(z==NULL){//Controlla se l'allocazione è riuscita
					fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
					exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
				}
				int an, pos;//Dichiara l'intero per l'anno e per la posizione
				
				printf("Immetti il titolo dell'album (max %d caratteri): ", MAX_LEN);
				gets(ti);//Salva la stringa per il titolo
				ti[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
				ti[strcspn(ti, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
				fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
				fflush(stdout);//Toglie eventuali caratteri sovrabbondanti
				int len1=strlen(ti);//Variabile che contiene la lunghezza della stringa del titolo utilizzando strlen()
				z->titolo=malloc(len1*sizeof(char)+1);//Alloca la stringa titolo della struttura della grandezza della stringa presa in input
				if(z->titolo==NULL){//Controlla se l'allocazione è riuscita
					fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
					exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
				}
				strcpy(z->titolo, ti);//Copia la stringa nella struttura usando strcpy()
				
				printf("\nImmetti il nome dell'artista dell'album (max %d caratteri): ", MAX_LEN);
				gets(ar);//Salva la stringa per l'artista
				ar[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
				ar[strcspn(ar, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
				fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
				fflush(stdout);//Toglie eventuali caratteri sovrabbondanti
				int len2=strlen(ar);//Variabile che contiene la lunghezza della stringa dell'artista utilizzando strlen()
				z->artista=malloc(len2*sizeof(char)+1);//Alloca la stringa artista della struttura della grandezza della stringa presa in input
				if(z->artista==NULL){//Controlla se l'allocazione è riuscita
					fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
					exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
				}
				strcpy(z->artista, ar);//Copia la stringa nella struttura usando strcpy()
				
				printf("\nImmetti il genere dell'album (max %d caratteri): ", MAX_LEN);
				gets(ge);//Salva la stringa per il genere
				ge[MAX_LEN]='\0';//Evita che la stringa vada oltre la grandezza dell'array
				ge[strcspn(ge, "\n")]='\0';//funzione strcspn() che restituisce l'indice dove ha trovato il carattere "\n" e in quella posizione salva il carattere di fine stringa '\0'
				fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
				fflush(stdout);//Toglie eventuali caratteri sovrabbondanti
				int len3=strlen(ge);//Variabile che contiene la lunghezza della stringa dell'artista utilizzando strlen()
				z->genere=malloc(len3*sizeof(char)+1);//Alloca la stringa artista della struttura della grandezza della stringa presa in input
				if(z->genere==NULL){//Controlla se l'allocazione è riuscita
					fprintf(stderr, "Allocazione della memoria fallita\n");//Avviso di errore
					exit(EXIT_FAILURE);//Uscita dal programma per fallita allocazione
				}
				strcpy(z->genere, ge);//Copia la stringa nella struttura usando strcpy()
				
				do{
					printf("\nImmetti l'anno dell'album (minimo 1800 - massimo %d): ", ANNO_CORRENTE);
					scanf("%d", &an);//Salva l'intero per l'anno
					fflush(stdin);//Pulisce il buffer da caratteri sovrabbondanti
					fflush(stdout);//Toglie eventuali caratteri sovrabbondanti
				}while(an<1800 || an>ANNO_CORRENTE);//Verifica che il valore inserito sia un effettivo valore valido (tra 1800 e la costante ANNO_CORRENTE)
				z->anno=an;//Immagazzino l'anno preso in input nella struttura
				
				pos=posizioneAlbum(l, z);//Chiamo la funzione posizioneAlbum e gli passo i parametri richiesti
				if(pos!=-1){//Controllo l'output della funzione e stampo l'avviso per il caso verificato
					printf("L'album c'è ed è in posizione %d\n", pos);
				}else{
					printf("L'album non è presente in lista\n");
				}
				break;//Esce dallo switch
			}
			case 5:{//Caso cerca
				//lista cercaAlbum(lista l);
				lista listatrovati=cercaAlbum(l);//Immagazzina gli album trovati in una lista (output della funzione cercaAlbum())
				if(listaVuota(listatrovati)){//Controlla il valore della lista per verificare se è vuota
					printf("Nessun album trovato!\n");//Avvisa l'utente di nessun riscontro
				}else{
					stampaCatalogo(listatrovati);//Passa la lista alla funzione stampaCatalogo() che ne stampa gli album
				}
				break;//Esce dallo switch
			}
			case 6:{//Caso ordina
				//lista ordinannoCatalogo(lista l);
				lista listordinata=ordinannoCatalogo(l);//Immagazzina l'output della funzione ordinannoCatalogo()
				printf("Catalogo ordinato per anno decrescente:\n");//Avviso per l'utente
				stampaCatalogo(listordinata);//Passa la lista alla funzione stampaCatalogo() che ne stampa gli album
				break;//Esce dallo switch
			}
			case 7:{//Caso grandezza
				//int grandezzaLista(lista l);
				int len = grandezzaLista(l);//Passo la lista alla funzione grandezzaLista() e salvo l'output in len
				//Non ho bisogno di verificare l'output della funzione che in caso di lista vuota è 0
				printf("Il catalogo contiene %d album\n", len);//Stampo la grandezza della lista
				break;//Esce dallo switch
			}
			case 8:{//Caso stampa
				//void stampaCatalogo(lista l);
				stampaCatalogo(l);//Passo la lista alla funzione stampaCatalogo()
				break;//Esce dallo switch
			}
		}
	}
    return 0;
}
