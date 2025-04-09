﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creare structura Magazin
typedef struct Magazin {

	unsigned int cod;
	char* denumire;
	int nrProduse;
	float pretP;

} Magazin;

// Funcție de inițializare
Magazin initializareMagazin(unsigned int cod, const char* denumire, int nrProduse, float pretP) {

	Magazin m;
	m.cod = cod;
	m.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(m.denumire, denumire);
	m.nrProduse = nrProduse;
	m.pretP = pretP;
	return m;

}

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

// Nod listă simplă
typedef struct Nod {

	Magazin info;
	struct Nod* next;

} Nod;

// Afișare listă magazine
void afisareListaMagazin(Nod* cap) {

	while (cap != NULL) {

		afisareMagazin(cap->info);
		cap = cap->next;

	}

}

// Adăugare magazin la final
void adaugaMagazinInLista(Nod** cap, Magazin magazinNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = magazinNou;
	nou->next = NULL;

	if (*cap) {

		Nod* p = *cap;
		while (p->next != NULL) {

			p = p->next;

		}

		p->next = nou;
	}
	else {

		*cap = nou;

	}

}

// Citire listă din fișier
Nod* citireListaMagazineDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {

		while (!feof(f)) {

			Magazin m = citireMagazinFisier(f);

			if (m.denumire != NULL) {

				adaugaMagazinInLista(&cap, m);

			}
		}

		fclose(f);
	}
	else {

		printf("Fisierul nu a putut fi deschis.\n");

	}

	return cap;
}

// Dezalocare listă
void dezalocareListaMagazine(Nod** cap, int* nrMagazine) {

	while (*cap) {

		Nod* p = *cap;
		*cap = p->next;
		if (p->info.denumire) {

			free(p->info.denumire);

		}

		free(p);
		(*nrMagazine)++;

	}

}

// Stergere nod de pe pozitie
void stergereNodPozitie(Nod** cap, int pozitie) {

	if (*cap == NULL || pozitie < 0) return;

	Nod* temp = *cap;

	if (pozitie == 0) {

		*cap = (*cap)->next;
		free(temp->info.denumire);
		free(temp);
		return;

	}

	for (int i = 0; temp != NULL && i < pozitie - 1; i++) {

		temp = temp->next;

	}

	if (temp == NULL || temp->next == NULL) return;

	Nod* nodDeSters = temp->next;
	temp->next = nodDeSters->next;
	free(nodDeSters->info.denumire);
	free(nodDeSters);

}

// Functie de inserare a elementelor sortate dupa pret
void inserareSortataDupaPret(Nod** cap, Magazin m) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = m;
	nou->next = NULL;

	if (*cap == NULL || (*cap)->info.pretP > m.pretP) {

		nou->next = *cap;
		*cap = nou;
		return;

	}

	Nod* curent = *cap;
	while (curent->next != NULL && curent->next->info.pretP < m.pretP) {

		curent = curent->next;

	}

	nou->next = curent->next;
	curent->next = nou;

}