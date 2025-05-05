#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare strcutura dulciuri
typedef struct Dulciuri {

	unsigned int id;
	char* nume;
	int nrBuc;
	float pret;

}Dulciuri;

// Creare structura Nod
typedef struct Nod {

	Dulciuri dulciuri;
	struct Nod* next;

}Nod;

// Creare stuct HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Dulciuri citireFisier(FILE* f) {

	char buffer[100];
	Dulciuri d = { 0, NULL, 0, 0.0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return d;

		}
		d.id = atoi(token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return d;

		}
		d.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(d.nume, token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return d;

		}
		d.nrBuc = atoi(token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return d;

		}
		d.pret = atof(token);

	}

	return d;

}
