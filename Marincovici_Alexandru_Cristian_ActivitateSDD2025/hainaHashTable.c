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

// Initializare HashTable
HashTable initializareHashTable(int dimeniune) {

	HashTable ht;
	ht.dim = dimeniune;
	ht.tabela = (Nod**)malloc(dimeniune * sizeof(Nod*));
	for (int i = 0; i < dimeniune; i++) {

		ht.tabela[i] = NULL;

	}

	return ht;

}

// Calcularea hash-ului
int calucaleazaHash(const char* nume, int dimensiune) {

	unsigned int hash = 0;
	for (int i = 0; i < strlen(nume); i++) {

		hash = hash * 31 + (unsigned char)nume[i];

	}

	return hash % dimensiune;

}

// Functia de inserare a unui element in tabela
void inserareInTabela(HashTable hash, Haina haina) {

	int pozitie = calucaleazaHash(haina.nume, hash.dim);
	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->haina = haina;
		hash.tabela[pozitie]->next = NULL;

	}
	else {

		adaugaFIsierInLista(hash.tabela[pozitie], haina);

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

		Haina haina = citireFisier(f);
		if (haina.nume != NULL) {

			inserareInTabela(hash, haina);

		}

	}

	fclose(f);
	return hash;

}

// Functia de afisare a tabelei
void afisareTabela(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] != NULL) {

			printf("Hainele de pe pozitia %d sunt: \n", i);
			afisareLista(ht.tabela[i]);

		}
		else {

			printf("\nPe pozitia %d nu avem haine: \n", i);

		}

	}

}

// Functia de dezalocare a listei
void dezalocareLista(Nod** cap) {

	Nod* p = *cap;
	while (p) {

		Nod* p = *cap;
		while (p) {

			Nod* temp = p;
			p = p->next;
			if (temp->haina.nume != NULL) {

				free(temp->haina.nume);

			}

			if (temp->haina.culoare != NULL) {

				free(temp->haina.culoare);

			}

			free(temp);

		}

		*cap = NULL;

	}

}

// Functia de dezalocare a tabelei
void dealocareTabela(HashTable* ht) {

	for (int i = 0; i < ht->dim; i++) {

		dezalocareLista(&(ht->tabela[i]));

	}

	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;

}

// Afisare in main
int main() {

	HashTable ht = citireDinFisier("haina.txt", 8);
	afisareTabela(ht);

	printf("\n ============  Lista haine  =========== \n");
	afisareTabela(ht);

	dezalocareLista(&ht);

	printf("\n ============  Lista haine dupa dezalocare  =========== \n");
	afisareTabela(ht);

	return 0;

}
