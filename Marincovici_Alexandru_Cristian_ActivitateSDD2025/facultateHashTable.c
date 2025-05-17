#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Facultate
typedef struct Facultate {

	unsigned int cod;
	char* nume;
	int nrLocuri;
	int nrCredite;

}Facultate;

// Creare strcutura Nod
typedef struct Nod {

	Facultate facultate;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Facultate citireFisier(FILE* f) {

	char buffer[100];
	Facultate fa = { 0, NULL, 0, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",'\n");
		if (token == NULL) {

			return fa;

		}
		fa.cod = atoi(token);

		token = strtok(NULL, ",'\n");
		if (token == NULL) {

			return fa;

		}
		fa.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(fa.nume, token);

		token = strtok(NULL, ",'\n");
		if (token == NULL) {

			return fa;

		}
		fa.nrLocuri = atoi(token);

		token = strtok(NULL, ",'\n");
		if (token == NULL) {

			return fa;

		}
		fa.nrCredite = atoi(token);

	}

	return fa;

}

// Functie de afisare a fisierului
void afisareFisier(Facultate facultate) {

	printf("Cod: %u\n", facultate.cod);
	printf("Nume: %s\n", facultate.nume);
	printf("Nr locuri: %u\n", facultate.nrLocuri);
	printf("Nr credite: %u\n", facultate.nrCredite);

}

// Functie de afisare a listei
void afisareLista(Nod* cap) {

	while (cap) {

		afisareFisier(cap->facultate);
		cap = cap->next;

	}

}

// Functie de adaugare in lista
void adaugaInLista(Nod* cap, Facultate facultateNoua) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->facultate = facultateNoua;
	nou->next = NULL;
	p->next = nou;

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

// Calcularea hash
int caulculeazaHash(const char* nume, int dimensiune) {

	unsigned int hash = 0;
	for (int i = 0; i < strlen(nume); i++) {

		hash = hash * 31 + (unsigned char)nume[i];

	}

	return hash % dimensiune;

}

// Functie de inserare a unui element in tabela
void inserareInTabela(HashTable hash, Facultate facultate) {

	int pozitie = caulculeazaHash(facultate.nume, hash.dim);
	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->facultate = facultate;
		hash.tabela[pozitie]->next = NULL;

	}
	else {

		adaugaInLista(hash.tabela[pozitie], facultate);

	}

}

// Citirea elementelor din fisier
HashTable citireDinFisier(const char* numeFisier, int dimensiune) {

	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {

		printf("Eroare la deschiderea fisierului\n");
		return hash;

	}
	while (!feof(f)) {

		Facultate facultate = citireFisier(f);
		if (facultate.nume != NULL) {

			inserareInTabela(hash, facultate);

		}

	}

	fclose(f);
	return hash;

}

// Functie de afisare a tabelei
void afisareTabela(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i != NULL]) {

			printf("Facultatile de pe pozitia %d sunt: \n", i);
			afisareLista(ht.tabela[i]);

		}
		else {

			printf("Pe pozitia %d nu avem facultati: \n", i);

		}

	}

}

// Functia de dezalocare a listei
void dezalocareLista(Nod** cap) {

	Nod* p = *cap;
	while (p) {

		Nod* temp = p;
		p = p->next;
		if (temp->facultate.nume != NULL) {

			free(temp->facultate.nume);

		}

		free(temp);

	}

	*cap = NULL;

}