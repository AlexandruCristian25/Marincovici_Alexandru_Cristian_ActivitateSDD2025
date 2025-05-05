#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare strcutura dulciuri
typedef struct Dulciuri {

	unsigned int id;
	char* nume;
	int nrBuc;
	float pret;

}Dulciuri;

// Creare structura Nod
typedef struct Nod {

	Dulciuri dulciuri;
	struct Nod* next;

}Nod;

// Creare stuct HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Dulciuri citireFisier(FILE* f) {

	char buffer[100];
	Dulciuri d = { 0, NULL, 0, 0.0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return d;

		}
		d.id = atoi(token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return d;

		}
		d.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(d.nume, token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return d;

		}
		d.nrBuc = atoi(token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return d;

		}
		d.pret = atof(token);

	}

	return d;

}

// Afisare Dulciuri
void afisareDulciuri(Dulciuri dulciuri) {

	printf("Id: %u\n", dulciuri.id);
	printf("Nume: %s\n", dulciuri.nume);
	printf("Nr bucati: %d\n", dulciuri.nrBuc);
	printf("Pret: %.2f\n", dulciuri.pret);

}

// Functie de afisare a listei
void afisareLista(Nod* cap) {

	while (cap) {

		afisareDulciuri(cap->dulciuri);
		cap = cap->next;

	}

}

// Functie de adaugare in lista
void adaugareFisierInLista(Nod* cap, Dulciuri dulciuriNoi) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->dulciuri = dulciuriNoi;
	nou->next = NULL;
	p->next = nou;

}

// Initializare HashTable
HashTable initialzareHashTable(int dimensiune) {

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
void inserareInTabela(HashTable hash, Dulciuri dulciuri) {

	int pozitie = calculeazaHash(dulciuri.nume, hash.dim);
	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->dulciuri = dulciuri;
		hash.tabela[pozitie]->next = NULL;

	}
	else {

		adaugareFisierInLista(hash.tabela[pozitie], dulciuri);

	}

}

// Citirea elementelor din fisier
HashTable citireDinFisier(const char* numeFisier, int dimensiune) {

	HashTable hash = initialzareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {

		printf("Eroare la deschiderea fisierului!");
		return hash;

	}
	else {

		while (!feof(f)) {

			Dulciuri dulciuri = citireFisier(f);
			if (dulciuri.nume != NULL) {

				inserareInTabela(hash, dulciuri);

			}

		}

	}

	fclose(f);
	return hash;

}

// Functia de afisare a tabelei
void afisareTabela(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] != NULL) {

			printf("Dulciurile de pe pozitia %d sunt: \n", i);
			afisareLista(ht.tabela[i]);

		}
		else {

			printf("\nPe pozitia %d nu avem dulciuri: \n", i);

		}


	}

}

// Functia de dezalocare a listei
void dezalocareLista(Nod** cap) {

	Nod* p = *cap;
	while (p) {

		Nod* temp = p;
		p = p->next;
		if (temp->dulciuri.nume = NULL) {

			free(temp->dulciuri.nume);

		}

		free(temp);

	}

	*cap = NULL;

}

// Functia de dezlocare a tabelei
void dezalocareTabela(HashTable* ht) {

	for (int i = 0; i < ht->dim; i++) {

		dezalocareLista(&(ht->tabela[i]));

	}

	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;

}

// Afisare in main
int main() {

	HashTable ht = citireDinFisier("dulciuri.txt", 6);
	afisareTabela(ht);

	printf("\n ============  Lista dulciuri  ============== \n");
	afisareTabela(ht);

	dezalocareTabela(&ht);

	printf("\n ============  Lista dulciuri dupa dezalocare  ============== \n");
	afisareTabela(ht);

	return 0;

}
