#define _CRT_SECURE_NO_WARNINGS
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

typedef struct Nod {

	Magazin magazin;
	struct Nod* next;
	struct Nod* prev;

} Nod;

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

// Creare Structura lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

} ListaDubla;

// Functia de afisare a listei de magazine de la inceput
void afisareListaMagazineInceput(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareMagazin(p->magazin);
		p = p->next;

	}

}

// Functia de afisare a listei de magazine de la sfarsit
void afisareListaMagazineSfarsit(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afisareMagazin(p->magazin);
		p = p->prev;

	}

}