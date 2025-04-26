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

// Functia de afisare a listei
void afisareLista(Nod* cap) {

	while (cap) {

		afisareReteta(cap->reteta);
		cap = cap->next;

	}

}

// Functia de adaugare in lista
void adaugaRetetaInLista(Nod* cap, Reteta retetaNoua) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->reteta = retetaNoua;
	nou->next = NULL;
	p->next = nou;

}

// Initializare HashTable
HashTable initilaizareHashTable(int dimensiune) {

	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {

		ht.tabela[i] = NULL;

	}

	return ht;

}

// Calcularea hash-ului
int calculeazaHash(const char* numeMedic, int dimensiune) {

	int suma = 0;
	for (int i = 0; i < strlen(numeMedic); i++) {

		suma += numeMedic[i];

	}

	return suma % dimensiune;

}

// Functia de inserare a unui element in tabela
void inserareRetetaInTabela(HashTable hash, Reteta reteta) {

	int pozitie = calculeazaHash(reteta.numeMedic, hash.dim);
	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->reteta = reteta;
		hash.tabela[pozitie]->next = NULL;

	}
	else {

		adaugaRetetaInLista(hash.tabela[pozitie], reteta);

	}

}

// Citirea elementelor din fisier
HashTable citireRetetaDinFisier(const char* numeFisier, int dimensiune) {

	HashTable hash = initilaizareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {

		printf("\nEroare la deschiderea fisierului!\n");
		return hash;

	}

	while (!feof(f)) {

		Reteta reteta = citireFisier(f);
		if (reteta.numeMedic != NULL) {

			inserareRetetaInTabela(hash, reteta);

		}

	}

	fclose(f);
	return hash;

}

// Functie de afisare a tabelei
void afisareTabelaDeRetete(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] != NULL) {

			printf("\nRetetele de pe pozitia %d sunt:\n");
			afisareLista(ht.tabela[i]);

		}
		else {

			printf("\nPe pozitia %d nu avem retete:\n", i);

		}

	}

}