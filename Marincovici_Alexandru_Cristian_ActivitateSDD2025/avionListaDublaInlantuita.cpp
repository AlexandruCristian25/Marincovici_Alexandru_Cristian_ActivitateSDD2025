#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Avion
typedef struct Avion {

	unsigned int id;
	char* nume;
	int nrPasageri;
	float pret;

}Avion;

// Functie de initializare
Avion initializareAvion(unsigned int id, const char* nume,
	int nrPasageri, float pret) {

	Avion a;
	a.id = id;
	a.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(a.nume, nume);
	a.nrPasageri = nrPasageri;
	a.pret = pret;

	return a;

}

typedef struct Nod {

	Avion avion;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Citire din fisier
Avion citireAvionFisier(FILE* f) {

	char buffer[100];
	Avion a = { 0, NULL, 0, 0.0f };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return a;
		a.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return a;
		a.nume = (char*)malloc(strlen(token) + 1);
		strcpy(a.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return a;
		a.nrPasageri = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return a;
		a.pret = (float)atof(token);

	}

	return a;

}

// Functia de afisare a avionului
void afisareAvion(Avion avion) {

	printf("Id: %d\n", avion.id);
	printf("Nume: %s\n", avion.nume);
	printf("Nr pasageri: %d\n", avion.nrPasageri);
	printf("Pret: %.2f\n", avion.pret);

}

// Creare structura lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

}ListaDubla;

// Functia de afisare a listei de la inceput
void afisareListaMagazineInceput(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareAvion(p->avion);
		p = p->next;

	}

}

