#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Fisier
typedef struct Fisier {

	char* denumire;
	char* caleF;
	char* extensieF;
	unsigned int dimensiune;

}Fisier;

// Creare structura Nod
typedef struct Nod {

	Fisier fisier;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Fisier citireFisier(FILE* f) {

	char buffer[100];
	Fisier fs = { NULL, NULL, NULL, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return fs;

		}
		fs.denumire = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(fs.denumire, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fs;

		}
		fs.caleF = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(fs.caleF, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fs;

		}
		fs.extensieF = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(fs.extensieF, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fs;

		}
		fs.dimensiune = atoi(token);

	}

	return fs;

}

// Afisare Fisier
void afisareFisier(Fisier fisier) {

	printf("Denumire: %s\n", fisier.denumire);
	printf("Cale fisier: %s\n", fisier.caleF);
	printf("Extensie fisier: %s\n", fisier.extensieF);
	printf("Dimensiune: %d\n", fisier.dimensiune);

}