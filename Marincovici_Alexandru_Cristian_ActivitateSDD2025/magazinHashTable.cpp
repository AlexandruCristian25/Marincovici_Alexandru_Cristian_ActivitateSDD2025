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

// Functia de adaugare a unui element in lista
void adaugaMagazinInLista(Nod* cap, Magazin magazinNou) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->magazin = magazinNou; // shallow copy
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
void inserareMagazinInTabela(HashTable hash, Magazin magazin) {

	int pozitie = calculeazaHash(magazin.denumire, hash.dim);
	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->magazin = magazin;
		hash.tabela[pozitie]->next = NULL;

	}
	else {

		adaugaMagazinInLista(hash.tabela[pozitie], magazin);

	}

}

// Functia de citire a elementelor tabelei din fisier
HashTable citireMagazinDinFisier(const char* numeFisier, int dimensiune) {

	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {

		printf("Eroare la deschiderea fisierului!\n");
		return hash;

	}
	while (!feof(f)) {

		Magazin magazin = citireMagazinFisier(f);
		if (magazin.denumire != NULL) {

			inserareMagazinInTabela(hash, magazin);

		}

	}
	fclose(f);
	return hash;

}

// Functia de afisare a tabelei
void afisareTabelaDeMagazine(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] != NULL) {

			printf("\nMagazinele de pe pozitia %d sunt: \n", i);
			afisareListaMagazine(ht.tabela[i]);

		}
		else {

			printf("\nPe pozitia %d nu avem magazine\n", i);

		}

	}

}

// Functia de dezalocare a listei
void dezalocareListaMagazine(Nod** cap) {

	Nod* p = *cap;
	while (p) {

		Nod* temp = p;
		p = p->next;
		if (temp->magazin.denumire != NULL) {

			free(temp->magazin.denumire);

		}
		free(temp);
	}
	*cap = NULL;

}

// Functia de dezalocare a tabelei
void dezalocareTabelaDeMagazine(HashTable* ht) {

	for (int i = 0; i < ht->dim; i++) {

		dezalocareListaMagazine(&(ht->tabela[i]));

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

		suma += cap->magazin.pretP;
		nrElemente++;
		cap = cap->next;

	}

	return (nrElemente > 0 ? (suma / nrElemente) : 0);

}