#Regola per il target principale main.exe
main.exe: ADT_Album.o Album.o main.o
	gcc ADT_Album.o Album.o main.o -o main.exe
#Regola per il file oggetto ADT_Album.o
ADT_Album.o: ADT_Album.h ADT_Album.c
	gcc -c ADT_Album.c
#Regola per il file oggetto Album.o
Album.o: Album.h Album.c
	gcc -c Album.c
#Regola per il file oggetto main.o
main.o: Album.h main.c
	gcc -c main.c
#Regola per la pulizia dei file oggetto e dell'eseguibile
clean: 
	rm *.o main.exe