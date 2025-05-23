﻿#define _CRT_SECURE_NO_WARNINGS
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

// Ștergere clădire după ID
void stergereCladireDupaId(HashTable* ht, int id) {

	for (int i = 0; i < ht->dim; i++) {

		Nod* p = ht->tabela[i];
		Nod* anterior = NULL;

		while (p) {

			if (p->cladire.id == id) {

				if (anterior == NULL) {

					ht->tabela[i] = p->next;

				}
				else {

					anterior->next = p->next;

				}

				free(p->cladire.adresa);
				free(p);
				return;

			}

			anterior = p;
			p = p->next;

		}

	}

}

// Salvare în vector a clădirilor dintr-un an
Cladire* cladirileDinAn(HashTable ht, int an, int* nrGasite) {

	*nrGasite = 0;
	for (int i = 0; i < ht.dim; i++) {

		Nod* p = ht.tabela[i];
		while (p) {

			if (p->cladire.anConstruire == an) {

				(*nrGasite)++;

			}

			p = p->next;

		}

	}

	if (*nrGasite == 0) {

		return NULL;

	}

	Cladire* vector = (Cladire*)malloc((*nrGasite) * sizeof(Cladire));
	int index = 0;

	for (int i = 0; i < ht.dim; i++) {

		Nod* p = ht.tabela[i];
		while (p) {

			if (p->cladire.anConstruire == an) {

				vector[index++] = p->cladire;

			}

			p = p->next;

		}

	}

	return vector;

}

// Modificare an construire pentru un ID dat
void modificaAnConstruire(HashTable* ht, int id, int vechiAn, int nouAn) {

	for (int i = 0; i < ht->dim; i++) {

		Nod* p = ht->tabela[i];
		Nod* prev = NULL;

		while (p) {

			if (p->cladire.id == id && p->cladire.anConstruire == vechiAn) {


				if (prev == NULL) {

					ht->tabela[i] = p->next;

				}
				else {

					prev->next = p->next;

				}

				p->cladire.anConstruire = nouAn;
				int pozNoua = calculeazaHash(p->cladire.adresa, ht->dim);
				p->next = ht->tabela[pozNoua];
				ht->tabela[pozNoua] = p;

				return;

			}

			prev = p;
			p = p->next;

		}

	}

}

// Functie de dezalocare a listei
void dezalocareLista(Nod** cap) {

	Nod* p = *cap;
	while (p) {

		Nod* temp = p;
		p = p->next;
		if (temp->cladire.adresa != NULL) {

			free(temp->cladire.adresa);
			temp->cladire.adresa = NULL;

		}

		free(temp);

	}

	*cap = NULL;

}

// Functia de dezalocare a tabelei de dispersie
void dezalocareTabela(HashTable* ht) {

	for (int i = 0; i < ht->dim; i++) {

		dezalocareLista(&(ht->tabela[i]));

	}

	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;

}

//Afisare in main
int main() {

	HashTable ht = citireCladiriDinFisier("bloc.txt", 7);
	printf("\n--- Tabela Initiala ---\n");
	afisareTabelaBlocuri(ht);

	printf("\n--- Cladirile din anul 2005 ---\n");
	afisareCladiriDinAn(ht, 2005);

	printf("\n--- Stergere cladire cu id=2 si an=2005 ---\n");
	stergereCladireDupaIdSiAn(&ht, 2, 2005);
	afisareTabelaBlocuri(ht);

	printf("\n--- Stergere cladire cu id=3 (indiferent de an) ---\n");
	stergereCladireDupaId(&ht, 3);
	afisareTabelaBlocuri(ht);

	printf("\n--- Vector cladirile din 2010 (cu deep copy) ---\n");
	int nr = 0;
	Cladire* vector = cladirileDinAn(ht, 2010, &nr);
	for (int i = 0; i < nr; i++) {
		afisareCladire(vector[i]);
		free(vector[i].adresa);  // eliberăm deep copy-ul
	}
	free(vector);

	printf("\n--- Modificare an construire pentru cladirea cu id=4 ---\n");
	modificaAnConstruire(&ht, 4, 2010, 2022);
	afisareTabelaBlocuri(ht);

	dezalocareTabela(&ht);
	return 0;

}