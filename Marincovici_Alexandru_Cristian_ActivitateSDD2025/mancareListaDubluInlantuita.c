#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Mancare
typedef struct Mancare {

	unsigned int cod;
	char* nume;
	int nrIngrediente;

}Mancare;

// Functia de initializare
Mancare initializareMancare(unsigned int cod, const char* nume, int nrIngrediente) {

	Mancare m;
	m.cod = cod;
	m.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(m.nume, nume);
	m.nrIngrediente = nrIngrediente;

	return m;

}
