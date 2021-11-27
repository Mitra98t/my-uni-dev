/*
Implementare una libreria per lavorare con liste bidimensionali utilizzate per tenere traccia di versioni di file. Ogni file è definito dal suo path assoluto, più una lista di versioni. Per ogni versione abbiamo un ID numerico e una timestamp con la data della versione. 
Scrivere una struttura di dati FileList che utilizza liste concatenate per mantenere le versioni, e per mantenere la lista stessa di file. 
Implementare le seguenti funzioni:
int addFile(FileList* fl ,const char* filename) - aggiunge un file nuovo alla lista (in testa) e restituisce 0 in caso di successo, 1 in caso di errore. La lista di versioni del nuovo file è vuota. Se il file esiste già non aggiunge niente e restituisce 1. 
int addVersion(FileList* fl, const char* filename, int versionID, time_t timestamp) - aggiunge una nuova versione alla lista di versione del file con il nome filename. Se il file non esiste nella lista, lo aggiunge. La funzione restituisce 0 in caso di successo, 1 in caso di errore.
int removeFile(FileList* fl ,const char* filename) - rimuove un file con tutte le sue versioni dalla lista. Se il file non esiste restituisce 1, altrimenti 0.
int removeVersion (FileList* fl, const char* filename, int versionID)  - rimuove una versione da un file nella lista. Se il file non esiste, restituisce 1, se la versione non esiste, restituisce 2, altrimenti 0.
VersionList getHist(FileList fl, const char* filename) - restituisce la lista di versioni del file passato come parametro. Il tipo di return VersionList è lo stesso della struttura di dati utilizzata per mantenere la lista di versioni.
void freeFileList(FileList* fl) - libera la memoria per la lista FileList. Dopo la chiamata il puntatore fl deve essere NULL.
FileList loadFileList(const char* file) - legge una lista da un file testuale. Ogni file e le sue versioni sono rappresentate su una riga nel formato “nome file: versione, timestamp; versione, timestamp; … versione, timestamp” Restituisce  la lista di file, NULL in caso di errore.
int saveFileList(FileList f, const char* file) - salva una lista di file in un file testuale, nel formatto descritto sopra. La funzione restituisce 0 in caso di successo, 1 in caso di errore.

Non editare la funzione main e i file di input e output che trovate su REPL.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "FileList.h"


int main(void) {
	char fname[100],command[200];
	scanf("%s",fname);

  	FileList f= loadFileList(fname);
	VersionList h=NULL;
	if(f){
		int option;
		scanf("%d",&option);
		switch(option){
			case 1: 
				saveFileList(f,"realout1.txt");
				sprintf(command,"diff %s %s","out1.txt","realout1.txt");
  			system(command);
				break;
		
			case 2:
				addFile(&f,"/home/user/f9.txt");
				saveFileList(f,"realout2.txt");
				sprintf(command,"diff %s %s","out2.txt","realout2.txt");
  			system(command);
				break;

			case 3:
				addVersion(&f,"/home/user/f9.txt",1,1637507877);
				saveFileList(f,"realout3.txt");
				sprintf(command,"diff %s %s","out3.txt","realout3.txt");
  			system(command);
				break;

			case 4:
				addVersion(&f,"/home/user/f2.txt",2,1637507890);
				saveFileList(f,"realout4.txt");
				sprintf(command,"diff %s %s","out4.txt","realout4.txt");
  			system(command);
				break;

			case 5:
				removeFile(&f,"/home/user/f2.txt");
				saveFileList(f,"realout5.txt");
				sprintf(command,"diff %s %s","out5.txt","realout5.txt");
  			system(command);
				break;

			case 6:
				removeVersion(&f,"/home/user/t3.txt",2);
				saveFileList(f,"realout6.txt");
				sprintf(command,"diff %s %s","out6.txt","realout6.txt");
  			system(command);
				break;

			case 7:
				h=getHist(f,"/home/user/t3.txt");
				assert(h!=NULL);
				freeFileList(&f);
				assert(f==NULL);
		}
		printf("Done.\n");
	}
	else{
		printf("Errore.\n");
	}
}


// int main(int argc, char **argv)
// {
// 	FileList fl = NULL;

// 	addFile(&fl, "tocco");

// 	addVersion(&fl, "tocco", 1, 1637507877);
// 	addVersion(&fl, "tocco", 2, 1637507877);
// 	removeVersion(&fl, "tocco", 2);
// 	addVersion(&fl, "tocco", 3, 1637507877);
// 	addFile(&fl, "cacchina");
// 	addFile(&fl, "pipo");
// 	removeFile(&fl, "tocco");

// 	stampaTMP(fl);
	
// 	printf("REMOVED_____________________________________\n\n");

// 	freeFileList(&fl);
// 	stampaTMP(fl);

// 	return 0;
// }
