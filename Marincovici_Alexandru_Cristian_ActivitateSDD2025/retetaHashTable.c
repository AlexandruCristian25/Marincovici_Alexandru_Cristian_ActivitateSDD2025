#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Reteta
typedef struct Reteta {

	unsigned int nr;
	int nrMedicamente;
	char* numeMedic;
	float valoare;

}Reteta;

// Creare structura Nod
typedef struct Nod {

	Reteta reteta;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

//Citire din fisier
Reteta citireFisier(FILE* f) {

	char buffer[100];
	Reteta r = { 0, 0, NULL, 0.0f };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return r;

		}
		r.nr = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return r;

		}
		r.nrMedicamente = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return r;

		}
		r.numeMedic = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(r.numeMedic, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return r;

		}
		r.valoare = (float)atof(token);

	}

	return r;

}

// Afisare Reteta
void afisareReteta(Reteta reteta) {

	printf("Nr: %d\n", reteta.nr);
	printf("Nr medicamente: %d\n", reteta.nrMedicamente);
	printf("Nume medic: %s\n", reteta.numeMedic);
	printf("Valoare: %.2f\n", reteta.valoare);

}