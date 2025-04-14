#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//Creare structura Joc
typedef struct Joc {

	unsigned int id;
	char* nume;
	int nrCopii;
	char* producator;

}Joc;

// Functia de initializare
Joc initializareJoc(unsigned int id, const char* nume,
	int nrCopii, const char producator) {

	Joc j;
	j.id = id;
	j.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(j.nume, nume);
	j.nrCopii = nrCopii;
	j.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(j.producator, producator);

	return j;

}

typedef struct Nod {

	Joc joc;
	struct Nod* next;
	struct Nod* prev;

}Nod;