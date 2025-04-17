#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Magazin
typedef struct Magazin {

	unsigned int cod;
	char* denumire;
	int nrProduse;
	float pretP;

} Magazin;

// Creare structura nod
typedef struct Nod {

	Magazin magazin;
	struct Nod* next;

} Nod;

// Creare structura tabela de dispersie
typedef struct HashTable {

	int dim;
	Nod** tabela;

} HashTable;

// Citire din fișier
Magazin citireMagazinFisier(FILE* f) {

	char buffer[100];
	Magazin m = { 0, NULL, 0, 0.0f };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return m;
		m.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.denumire = (char*)malloc(strlen(token) + 1);
		strcpy(m.denumire, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.nrProduse = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.pretP = (float)atof(token);

	}

	return m;

}

// Functia de afisare a magazinului
void afisareMagazin(Magazin magazin) {

	printf("Cod: %d\n", magazin.cod);
	printf("Denumire: %s\n", magazin.denumire);
	printf("Nr produse: %d\n", magazin.nrProduse);
	printf("Pret: %.2f\n", magazin.pretP);

}

// Functia de afisare a listei
void afisareListaMagazine(Nod* cap) {

	while (cap) {

		afisareMagazin(cap->magazin);
		cap = cap->next;

	}

}