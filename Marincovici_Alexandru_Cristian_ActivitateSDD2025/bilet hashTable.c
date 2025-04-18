#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Bilet
typedef struct Bilet {
	unsigned int id;
	char* nume;
	int nrLoc;
	float pret;
} Bilet;

// Creare structura Nod
typedef struct Nod {
	Bilet bilet;
	struct Nod* next;
} Nod;

// Creare structura HashTable
typedef struct HashTable {
	int dim;
	Nod** tabela;
} HashTable;

// Citire din fisier
Bilet citireBiletFisier(FILE* f) {
	char buffer[100];
	Bilet b = { 0, NULL, 0, 0.0f };

	if (fgets(buffer, sizeof(buffer), f)) {
		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return b;
		b.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return b;
		b.nume = (char*)malloc(strlen(token) + 1);
		strcpy(b.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return b;
		b.nrLoc = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return b;
		b.pret = (float)atof(token);
	}
	return b;
}