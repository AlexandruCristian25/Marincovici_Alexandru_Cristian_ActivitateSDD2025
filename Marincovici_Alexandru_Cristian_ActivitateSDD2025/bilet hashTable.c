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

// Afisare bilet
void afisareBilet(Bilet bilet) {
	printf("Id: %d\n", bilet.id);
	printf("Nume: %s\n", bilet.nume);
	printf("Nr loc: %d\n", bilet.nrLoc);
	printf("Pret: %.2f\n", bilet.pret);
}

// Functie de afisare a listei
void afisareListaBilete(Nod* cap) {
	while (cap) {
		afisareBilet(cap->bilet);
		cap = cap->next;
	}
}

// Functie de adaugare in lista
void adaugaBiletInLista(Nod* cap, Bilet biletNou) {
	Nod* p = cap;
	while (p->next) {
		p = p->next;
	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->bilet = biletNou;
	nou->next = NULL;
	p->next = nou;
}