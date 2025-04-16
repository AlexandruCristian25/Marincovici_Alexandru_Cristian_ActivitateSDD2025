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

// Functia de inseare in tabela
void inserareCladireInTabela(HashTable hash, Cladire cladire) {

	int pozitie = calculeazaHash(cladire.adresa, hash.dim);
	adaugaCladireInLista(&hash.tabela[pozitie], cladire);

}

// Functie de citire din fisier
HashTable citireCladiriDinFisier(const char* numeFisier, int dimensiune) {

	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {

		printf("Eroare la deschiderea fisierului.\n");
		return hash;

	}

	Cladire cladire;
	while (!feof(f)) {

		cladire = citireDinFisier(f);
		if (cladire.adresa != NULL) {

			inserareCladireInTabela(hash, cladire);

		}

	}

	fclose(f);
	return hash;

}

// Functie de afisare a tabelei
void afisareTabelaBlocuri(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] != NULL) {

			printf("\nCladirile de pe pozitia %d sunt:\n", i);
			afisareListaCladiri(ht.tabela[i]);

		}
		else {

			printf("\nPe pozitia %d nu avem cladiri\n");

		}

	}

}

// Afișare clădiri construite într-un anumit an
void afisareCladiriDinAn(HashTable ht, int an) {

	for (int i = 0; i < ht.dim; i++) {

		Nod* p = ht.tabela[i];
		while (p) {

			if (p->cladire.anConstruire == an) {

				afisareCladire(p->cladire);

			}

			p = p->next;

		}

	}

}

// Ștergere clădire după ID și an
void stergereCladireDupaIdSiAn(HashTable* ht, int id, int an) {
	for (int i = 0; i < ht->dim; i++) {

		Nod* p = ht->tabela[i];
		Nod* prev = NULL;

		while (p) {

			if (p->cladire.id == id && p->cladire.anConstruire == an) {

				if (prev == NULL) {

					ht->tabela[i] = p->next;

				}
				else {

					prev->next = p->next;

				}

				free(p->cladire.adresa);
				free(p);
				return;
			}

			prev = p;
			p = p->next;

		}

	}

}