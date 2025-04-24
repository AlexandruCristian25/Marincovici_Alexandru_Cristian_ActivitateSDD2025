#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Fisier
typedef struct Fisier {

	char* denumire;
	char* caleF;
	char* extensieF;
	unsigned int dimensiune;

}Fisier;

// Creare structura Nod
typedef struct Nod {

	Fisier fisier;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Fisier citireFisier(FILE* f) {

	char buffer[100];
	Fisier fs = { NULL, NULL, NULL, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return fs;

		}
		fs.denumire = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(fs.denumire, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fs;

		}
		fs.caleF = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(fs.caleF, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fs;

		}
		fs.extensieF = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(fs.extensieF, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fs;

		}
		fs.dimensiune = atoi(token);

	}

	return fs;

}

// Afisare Fisier
void afisareFisier(Fisier fisier) {

	printf("Denumire: %s\n", fisier.denumire);
	printf("Cale fisier: %s\n", fisier.caleF);
	printf("Extensie fisier: %s\n", fisier.extensieF);
	printf("Dimensiune: %d\n", fisier.dimensiune);

}

// Functie de afisare a listei
void afisareListaFisiere(Nod* cap) {

	while (cap) {

		afisareFisier(cap->fisier);
		cap = cap->next;

	}

}

// Functie de adaugare in lista
void adaugaFisierInLista(Nod* cap, Fisier fisierNou) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->fisier = fisierNou;
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

// Calcularea hash-ului
int calculeazaHash(const char* nume, int dimensiune) {

	unsigned int hash = 0;
	for (int i = 0; i < strlen(nume); i++) {

		hash = hash * 31 + (unsigned char)nume[i];

	}

	return hash % dimensiune;

}

// Functie de inserare a unui element in tabela
void inserareFisierInTabela(HashTable hash, Fisier fisier) {

	int pozitie = calculeazaHash(fisier.denumire, hash.dim);
	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->fisier = fisier;
		hash.tabela[pozitie]->next = NULL;

	}
	else {

		adaugaFisierInLista(hash.tabela[pozitie], fisier);

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

		Fisier fisier = citireFisier(f);
		if (fisier.denumire != NULL) {

			inserareFisierInTabela(hash, fisier);

		}

	}

	fclose(f);
	return hash;

}

// Functie de afisare a tebelei
void afisareTabelaDeFisiere(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] != NULL) {

			printf("Fisierele de pe pozitia %d sunt: \n", i);
			afisareListaFisiere(ht.tabela[i]);

		}
		else {

			printf("\nPe pozitia %d nu avem studenti: \n", i);

		}

	}

}