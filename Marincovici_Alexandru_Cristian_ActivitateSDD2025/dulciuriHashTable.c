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
