#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//Creare structura Joc
typedef struct Joc {

	unsigned int id;
	char* nume;
	int nrCopii;
	char* producator;

}Joc;

// Functia de initializare
Joc initializareJoc(unsigned int id, const char* nume,
	int nrCopii, const char producator) {

	Joc j;
	j.id = id;
	j.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(j.nume, nume);
	j.nrCopii = nrCopii;
	j.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(j.producator, producator);

	return j;

}

typedef struct Nod {

	Joc joc;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Citire din fisier
Joc citireDinFisier(FILE* f) {

	char buffer[100];
	Joc j = { 0,NULL,0,NULL };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(j.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.nrCopii = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.producator = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(j.producator, token);

	}

	return j;

}

// Functia de afisare a jocului
void afisareJoc(Joc joc) {

	printf("Id: %d\n", joc.id);
	printf("Nume: %s\n", joc.nume);
	printf("Nr copii: %d\n", joc.nrCopii);
	printf("Producator: %s\n", joc.producator);

}