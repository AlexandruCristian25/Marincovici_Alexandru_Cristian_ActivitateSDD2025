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

