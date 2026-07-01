# Catalogo Musicale Dinamico - Progetto di Programmazione e Strutture Dati (PSD)

Questo repository contiene il progetto software sviluppato in **C** per l'esame di Programmazione e Strutture Dati. L'obiettivo è la gestione dinamica di un catalogo di album musicali attraverso l'implementazione rigorosa di un Tipo Astratto di Dato (ADT) basato su una **Lista Concatenata**, garantendo i principi di *Information Hiding* e astrazione logica.

## Obiettivi del Progetto
- **Information Hiding:** Separazione netta tra l'interfaccia pubblica esposta all'utente e i dettagli implementativi delle strutture dati.
- **Gestione Dinamica della Memoria:** Utilizzo di strutture collegate tramite puntatori per gestire quantità di dati non note a priori provenienti da file o input utente.
- **Testing Automatizzato:** Implementazione di una test suite basata su file di input e "oracoli" per la verifica formale del comportamento del software (PASS/FAIL).

## Architettura del Software e ADT

Il sistema è strutturato secondo un approccio modulare a livelli di astrazione:

1. **`idalbum` (Elemento d'appoggio):** Definito in `ADT_Album.h`, incapsula i dati del singolo album (Titolo, Artista, Genere, Anno).
2. **`lista` (Struttura Principale):** Definita in `Album.h` come puntatore a una struttura opaca (`struct album`). L'utente interagisce con la lista esclusivamente tramite i prototipi accademici forniti, senza poter accedere direttamente ai puntatori `next` o ai campi interni dei nodi.

### Specifiche Sintattiche e Semantiche Principali

| Operatore | Specifica Sintattica | Pre-condizione | Post-condizione / Effetto |
| :--- | :--- | :--- | :--- |
| `nuovaLista` | `() -> lista` | *Nessuna* | Restituisce una lista vuota (`NULL`) |
| `aggiungiAlbum` | `(lista, char*, char*, char*, int) -> lista` | Stringhe `!= NULL`, `1800 <= anno <= 2024` | Inserisce il nuovo nodo in testa alla lista |
| `rimuoviAlbum` | `(lista, int) -> lista` | Lista non vuota, `posizione > 0` | Elimina il nodo alla posizione specificata |
| `ordinannoCatalogo`| `(lista) -> lista` | Lista correttamente allocata | Restituisce la lista ordinata per anno decrescente |

---

## Interfacce Utente Implementate

Il file `main.c` si divide in due modalità operative selezionabili all'avvio:

1. **Interfaccia di Testing (Da File):** Progettata per il debug strutturato. Legge i comandi direttamente da file esterni, esegue le operazioni in blocco (aggiunta, rimozione, ricerca) e scrive i risultati in un file di output.
2. **Interfaccia Interattiva (CLI):** Un menu testuale completo a disposizione dell'utente per manipolare il catalogo in tempo reale (aggiunta, rimozione, modifica campi, inversione lista, ordinamento e stampa).

---

## Robustezza e Test Suite Automatica

Il progetto include un sistema di testing formale guidato da un file di configurazione (`test_suite.txt`). 

### Flusso del Test Automatizzato:
1. Il programma legge l'identificativo del test (es. `TC1`) e l'operazione associata.
2. Genera dinamicamente i percorsi dei file necessari: `TC1_input.txt` e `TC1_oracolo.txt`.
3. Elabora l'input, genera l'output su `TC1_output.txt` e lo confronta elemento per elemento con l'oracolo tramite la funzione `comparaAlbum`.
4. Scrive l'esito nel file `risultati.txt` marcando il test come **PASS** se l'output coincide con l'oracolo, o **FAIL** in caso di discrepanze.

*Nota:* In caso di dati non conformi all'interno dei file di input, il sistema è progettato per essere robusto, richiedendo la correzione manuale all'utente da linea di comando senza mandare in crash l'applicazione.

---

## Compilazione ed Esecuzione

### Prerequisiti
- Compilatore GCC
- Make utility (opzionale)
