#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare stuctura Telefon
typedef struct Telefon {

	unsigned int cod;
	char* producator;
	int nrExemplare;
	float pret;

}Telefon;

// Functia de initializare
Telefon initializareTelefon(unsigned int cod, const char* producator,
	int nrExemplare, float pret) {

	Telefon t;
	t.cod = cod;
	t.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(t.producator, producator);
	t.nrExemplare = nrExemplare;
	t.pret = pret;

	return t;

}

// Creare structura nod
typedef struct Nod {

	Telefon telefon;
	struct Nod* next;
	struct Nod* prev;


}Nod;