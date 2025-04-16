#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Cladire
typedef struct Cladire {

	unsigned int id;
	char* adresa;
	int anConstruire;
	int nrApartamente;

}Cladire;

// Creare structura nod pentru Lista Smpla Inlantuita
typedef struct Nod {

	Cladire cladire;
	struct Nod* next;

}Nod;

// Creare structura tabela de dispersie
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Cladire citireDinFisier(FILE* f) {

	char buffer[100];
	Cladire c = { 0,NULL,0, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.adresa = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(c.adresa, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.anConstruire = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.nrApartamente = atoi(token);

	}

	return c;

}

// Functia de afisare
void afisareCladire(Cladire cladire) {

	printf("Id: %d\n", cladire.id);
	printf("Adresa: %s\n", cladire.adresa);
	printf("An construire: %d\n", cladire.anConstruire);
	printf("Nr apartamente: %d\n", cladire.nrApartamente);

}

// Functie de afisare a unui element de pe o anumita pozitie din lista
void afisareListaCladiri(Nod* cap) {

	while (cap) {

		afisareCladire(cap->cladire);
		cap = cap->next;

	}

}

// Functie de adaugare a unui element in lista existenta
void adaugaCladireInLista(Nod** cap, Cladire cladireNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->cladire = cladireNoua;
	nou->next = NULL;

	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* p = *cap;
		while (p->next) {
			p = p->next;
		}
		p->next = nou;
	}
}

// Initializare HashTable
HashTable initializareHashTable(int dimensiune) {

	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));

	for (int i = 0; i < dimensiune; i++) {

		ht.tabela[i] = NULL;

	}

	return ht;

}

// Functia de calculare a Hash-ului
int calculeazaHash(const char* adresa, int dimensiune) {

	int suma = 0;
	for (int i = 0; i < strlen(adresa); i++) {

		suma += adresa[i];

	}

	return suma % dimensiune;

}