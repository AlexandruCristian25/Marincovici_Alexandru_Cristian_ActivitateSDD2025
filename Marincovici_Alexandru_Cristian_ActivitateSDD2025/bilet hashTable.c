#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Bilet
typedef struct Bilet {
	unsigned int id;
	char* nume;
	int nrLoc;
	float pret;
} Bilet;

// Creare structura Nod
typedef struct Nod {
	Bilet bilet;
	struct Nod* next;
} Nod;

// Creare structura HashTable
typedef struct HashTable {
	int dim;
	Nod** tabela;
} HashTable;

// Citire din fisier
Bilet citireBiletFisier(FILE* f) {
	char buffer[100];
	Bilet b = { 0, NULL, 0, 0.0f };

	if (fgets(buffer, sizeof(buffer), f)) {
		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return b;
		b.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return b;
		b.nume = (char*)malloc(strlen(token) + 1);
		strcpy(b.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return b;
		b.nrLoc = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return b;
		b.pret = (float)atof(token);
	}
	return b;
}

// Afisare bilet
void afisareBilet(Bilet bilet) {
	printf("Id: %d\n", bilet.id);
	printf("Nume: %s\n", bilet.nume);
	printf("Nr loc: %d\n", bilet.nrLoc);
	printf("Pret: %.2f\n", bilet.pret);
}

// Functie de afisare a listei
void afisareListaBilete(Nod* cap) {
	while (cap) {
		afisareBilet(cap->bilet);
		cap = cap->next;
	}
}

// Functie de adaugare in lista
void adaugaBiletInLista(Nod* cap, Bilet biletNou) {
	Nod* p = cap;
	while (p->next) {
		p = p->next;
	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->bilet = biletNou;
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
	int suma = 0;
	for (int i = 0; i < strlen(nume); i++) {
		suma += nume[i];
	}
	return suma % dimensiune;
}

// Functie de inserare a unui element in tabela
void inserareBiletInTabela(HashTable hash, Bilet bilet) {
	int pozitie = calculeazaHash(bilet.nume, hash.dim);
	if (hash.tabela[pozitie] == NULL) {
		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->bilet = bilet;
		hash.tabela[pozitie]->next = NULL;
	}
	else {
		adaugaBiletInLista(hash.tabela[pozitie], bilet);
	}
}

// Citirea elementelor din fisier
HashTable citireBiletDinFisier(const char* numeFisier, int dimensiune) {
	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {
		printf("Eroare la deschiderea fisierului!\n");
		return hash;
	}
	while (!feof(f)) {
		Bilet bilet = citireBiletFisier(f);
		if (bilet.nume != NULL) {
			inserareBiletInTabela(hash, bilet);
		}
	}
	fclose(f);
	return hash;
}

// Functie de afisare a tabelei
void afisareTabelaDeBilete(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			printf("\nBiletele de pe pozitia %d sunt: \n", i);
			afisareListaBilete(ht.tabela[i]);
		}
		else {
			printf("\nPe pozitia %d nu avem bilete\n", i);
		}
	}
}

// Functie de dezalocare a listei
void dezalocareListaBilete(Nod** cap) {
	Nod* p = *cap;
	while (p) {
		Nod* temp = p;
		p = p->next;
		if (temp->bilet.nume != NULL) {
			free(temp->bilet.nume);
		}
		free(temp);
	}
	*cap = NULL;
}

// Functie de dezalocare a tabelei
void dezalocareTabelaDeBilete(HashTable* ht) {
	for (int i = 0; i < ht->dim; i++) {
		dezalocareListaBilete(&(ht->tabela[i]));
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dim = 0;
}

// Calcularea mediei din lista
float calculeazaMedieLista(Nod* cap) {
	float suma = 0;
	int nrElemente = 0;
	while (cap) {
		suma += cap->bilet.pret;
		nrElemente++;
		cap = cap->next;
	}
	return (nrElemente > 0 ? (suma / nrElemente) : 0);
}

// Calcularea preturilor per clustere
float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	float* preturi = NULL;
	*nrClustere = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			(*nrClustere)++;
		}
	}
	preturi = (float*)malloc(sizeof(float) * (*nrClustere));
	int contor = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			preturi[contor] = calculeazaMedieLista(ht.tabela[i]);
			contor++;
		}
	}
	return preturi;
}

// Extragerea unui element din lista
Bilet getBiletDinLista(Nod* cap, const char* nume) {
	Bilet b;
	b.id = -1;
	while (cap && strcmp(cap->bilet.nume, nume) != 0) {
		cap = cap->next;
	}
	if (cap) {
		b = cap->bilet;
		b.nume = (char*)malloc(strlen(cap->bilet.nume) + 1);
		strcpy(b.nume, cap->bilet.nume);
	}
	return b;
}

// Extragere element dupa nume
Bilet getBiletDupaNume(HashTable ht, const char* numeCautat) {
	Bilet b;
	b.id = -1;
	int pozitie = calculeazaHash(numeCautat, ht.dim);
	if (pozitie >= 0 && pozitie < ht.dim) {
		return getBiletDinLista(ht.tabela[pozitie], numeCautat);
	}
	return b;
}

// Afisarea in main
int main() {
	HashTable ht = citireBiletDinFisier("bilet.txt", 8);
	afisareTabelaDeBilete(ht);

	int nrClustere = 0;
	float* pret = calculeazaPreturiMediiPerClustere(ht, &nrClustere);

	printf("\nPreturile medii per clustere sunt:\n");
	for (int i = 0; i < nrClustere; i++) {
		printf("%.2f ", pret[i]);
	}
	printf("\n");
	free(pret);

	Bilet bilet = getBiletDupaNume(ht, "Bilet2 Bilet2");

	if (bilet.id != -1) {
		printf("Bilet cautat:\n");
		afisareBilet(bilet);
		if (bilet.nume != NULL) {
			free(bilet.nume);
		}
	}
	else {
		printf("Biletul nu a fost gasit. Biletul respectiv nu are nici un loc disponibil.\n");
	}

	dezalocareTabelaDeBilete(&ht);
	return 0;
}