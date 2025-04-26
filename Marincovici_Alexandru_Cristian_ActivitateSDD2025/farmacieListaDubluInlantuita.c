#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Farmacie
typedef struct Farmacie {

	char* denumire;
	float suprafata;
	int nrAngajati;

}Farmacie;

// Funcția de inițializare
Farmacie initializareFarmacie(const char* denumire, float suprafata, int nrAngajati) {

	Farmacie fa;
	fa.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(fa.denumire, denumire);
	fa.suprafata = suprafata;
	fa.nrAngajati = nrAngajati;
	return fa;

}

typedef struct Nod {

	Farmacie farmacie;
	struct Nod* next;
	struct Nod* prev;

} Nod;

// Citire din fișier
Farmacie citireFisier(FILE* f) {

	char buffer[100];
	Farmacie fa = { NULL, 0.0f, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return fa;
		fa.denumire = (char*)malloc(strlen(token) + 1);
		strcpy(fa.denumire, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return fa;
		fa.suprafata = (float)atof(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return fa;
		fa.nrAngajati = atoi(token);

	}

	return fa;

}

// Functia de afisare a Farmaciei
void afisareFarmacie(Farmacie farmacie) {

	printf("Denumire: %s\n", farmacie.denumire);
	printf("Suprafata: %.2f\n", farmacie.suprafata);
	printf("Nr angajati: %d\n", farmacie.nrAngajati);

}

// Creare Structura lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

} ListaDubla;

// Functia de afisare a listei de farmacii de la inceput
void afisareListaFarmaciiInceput(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareFarmacie(p->farmacie);
		p = p->next;

	}

}

// Functia de afisare a listei de farmacii de la sfarsit
void afisareListaFarmaciiSfarsit(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afisareFarmacie(p->farmacie);
		p = p->prev;

	}

}

// Functie de adaugare a unui element la finalul listei 
void adaugaLaFinaltInLista(ListaDubla* lista, Farmacie farmacieNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->farmacie = farmacieNoua; // shalow copy
	nou->next = NULL;
	nou->prev = lista->last;

	if (lista->last != NULL) {

		lista->last->next = nou;

	}
	else {

		lista->first = nou;

	}

	lista->last = nou;
	lista->nrNoduri++;

}

// Functie de adaugare a unui element la inceputul listei
void adaugaLaInceputtInLista(ListaDubla* lista, Farmacie farmacieNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->farmacie = farmacieNoua; // shalow copy
	nou->next = lista->first;
	nou->prev = NULL;

	if (lista->first != NULL) {

		lista->first->prev = nou;

	}
	else {


		lista->last = nou;

	}

	lista->first = nou;
	lista->nrNoduri++;

}