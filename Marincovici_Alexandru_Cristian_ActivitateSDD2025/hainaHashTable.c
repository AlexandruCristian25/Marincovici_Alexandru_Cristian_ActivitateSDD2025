#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Haina
typedef struct Haina {

	char* nume;
	char* culoare;
	float pret;

}Haina;

// Creare structura Nod
typedef struct Nod {

	Haina haina;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Haina citireFisier(FILE* f) {

	char buffer[100];
	Haina h = { NULL, NULL, 0.0 };
	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = (buffer, ",;\n");
		if (token == NULL) {

			return h;

		}
		h.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(h.nume, token);

		token = (NULL, ",;\n");
		if (token == NULL) {

			return h;

		}
		h.culoare = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(h.culoare, token);

		token = (buffer, ",;\n");
		if (token == NULL) {

			return h;

		}
		h.pret = atof(token);

	}

	return h;

}

// Afisare fisier
void afisareFisier(Haina haina) {

	printf("Nume: %s\n", haina.nume);
	printf("Culoare: %s\n", haina.culoare);
	printf("Pret: %.2f\n", haina.pret);

}

// Functia de afisare a listei
void afisareLista(Nod* cap) {

	while (cap) {

		afisareFisier(cap->haina);
		cap = cap->next;

	}

}

// Functia de adaugare in lista
void adaugaFIsierInLista(Nod* cap, Haina hainaNoua) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->haina = hainaNoua;
	nou->next = NULL;
	p->next = nou;

}