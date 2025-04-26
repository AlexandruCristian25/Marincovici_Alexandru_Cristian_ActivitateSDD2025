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