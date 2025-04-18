#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Smartwatch
typedef struct Smartwatch {

	unsigned int id;
	char* producator;
	int baterie;
	float pret;

}Smartwatch;

// Creare structura nod
typedef struct Nod {

	Smartwatch smartwatch;
	struct Nod* next;

}Nod;

// Creare structura tabela de dispersie
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Smartwatch citireSmartwatchFisier(FILE* f) {

	char buffer[100];
	Smartwatch s = { 0, NULL, 0, 0.0f };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.producator = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(s.producator, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.baterie = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.pret = atof(token);

	}

	return s;

}

// Functia de afisare a smartwatch-ului
void afisareSmartwatch(Smartwatch smartwatch) {

	printf("Id: %d", smartwatch.id);
	printf("Producator: %s", smartwatch.producator);
	printf("Baterie: %d", smartwatch.baterie);
	printf("Pret: %.2f", smartwatch.pret);

}