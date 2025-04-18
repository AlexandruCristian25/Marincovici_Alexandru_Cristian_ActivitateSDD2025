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

// Functia de afisare a listei
void afisareLista(Nod* cap) {

	while (cap) {

		afisareMagazin(cap->smartwatch);
		cap = cap->next;

	}

}

// Functia de adaigare a unui element in lista
void adaugaInLista(Nod* cap, Smartwatch smartwatchNou) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->smartwatch = smartwatchNou; // shallow copy
	nou->next = NULL;
	p->next = nou;

}

// Initializare tabela de dispersie
HashTable initializareHashTable(int dimensiune) {

	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {

		ht.tabela[i] = NULL;

	}

	return ht;

}

// Functia de calculare a hash-ului
int calculeazaHash(const char* nume, int dimensiune) {

	int suma = 0;
	for (int i = 0; i < strlen(nume); i++) {

		suma += nume[i];

	}

	return suma % dimensiune;

}

// Functia de inserare a unui element in tabela
void inserareMagazinInTabela(HashTable hash, Smartwatch smartwatch) {

	int pozitie = calculeazaHash(smartwatch.producator, hash.dim);

	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->smartwatch = smartwatch;
		hash.tabela[pozitie]->next = NULL;


	}
	else {

		adaugaInLista(hash.tabela[pozitie], smartwatch);

	}

}

// Functia de citire a elementelor tabelei din fisier
HashTable citireDinFisier(const char* numeFisier, int dimensiune) {

	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {

		printf("Eroatre la deschiderea fisierului\n");
		return hash;

	}
	while (!feof(f)) {

		Smartwatch smartwatch = citireSmartwatchFisier(f);
		if (smartwatch.producator != NULL) {

			inserareMagazinInTabela(hash, smartwatch);

		}

	}
	fclose(f);
	return hash;

}

// Functia de afisare a tabelei
void afisareTabela(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] != NULL) {

			printf("\nSmartwatch-urile de pe pozitia %d sunt:\n", i);
			afisareLista(ht.tabela[i]);

		}
		else {

			printf("\nPe pozitia %d nu avem magazine\n", i);

		}

	}

}

// Functia de dezalocare a listei
void dezalocareLista(Nod** cap) {

	Nod* p = *cap;
	while (p) {

		Nod* temp = p;
		p = p->next;
		if (temp->smartwatch.producator != NULL) {

			free(temp->smartwatch.producator);

		}
		free(temp);

	}
	*cap = NULL;

}

// Functia de dezalocare a tabelei
void dezalocareTabela(HashTable* ht) {

	for (int i = 0; i < ht->dim; i++) {

		dezalocareLista(&(ht->tabela[i]));

	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;

}

// Functia de calculare a mediei listei
float calculeazaMedieLista(Nod* cap) {

	float suma = 0;
	int nrElemente = 0;
	while (cap) {

		suma += cap->smartwatch.pret;
		nrElemente++;
		cap = cap->next;

	}

	return (nrElemente > 0 ? (suma / nrElemente) : 0);

}

// Functia de extragere a unui element din lista
Smartwatch getSmartwatchDinLista(Nod* cap, const char* nume) {

	Smartwatch s;
	s.id = -1;
	while (cap && strcmp(cap->smartwatch.producator, nume) != 0) {

		cap = cap->next;

	}
	if (cap) {

		s = cap->smartwatch;
		s.producator = (char*)malloc(strlen(cap->smartwatch.producator) + 1);
		strcpy(s.producator, cap->smartwatch.producator);

	}

	return s;

}

// Extragerea unui element dupa producator
Smartwatch getSmartwatchDupaDenumire(HashTable ht, const char* producatorCautat) {


	Smartwatch s;
	s.id = -1;
	int pozitie = calculeazaHash(producatorCautat, ht.dim);
	if (pozitie >= 0 && pozitie < ht.dim) {

		return getSmartwatchDinLista(ht.tabela[pozitie], producatorCautat);

	}

	return s;

}