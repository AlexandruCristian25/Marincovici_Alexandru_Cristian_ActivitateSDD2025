#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare Structura Magazin
typedef struct Magazin {

	int cod;
	char* numeM;
	int nrProduse;
	float pretP;

}Magazin;

// Creare structura Nod
typedef struct Nod {

	Magazin info;
	struct Nod* stanga;
	struct Nod* dreapta;

}Nod;

// Creare structura vector
typedef struct Vector {

	Magazin* vector;
	int dimensiune;
	int capacitate;

}Vector;

// Creare structura lista simpla inlantuita
typedef struct NodLS {

	Magazin info;
	struct NodLS* next;

}NodLS;

// Creare structura lista dubla inlantuita
typedef struct NodLD {

	Magazin info;
	struct NodLD* prev;
	struct NodLD* next;

}NodLD;

// Initializare Magazin
Magazin initializareMagazin(int cod, const char* numeM,
	int nrProduse, float pretP) {

	Magazin m;
	m.cod = cod;
	m.numeM = (char*)malloc(sizeof(char) * strlen(numeM) + 1);
	strcpy(m.numeM, numeM);
	m.nrProduse = nrProduse;
	m.pretP = pretP;

	return m;

}

// Initializare vector
void initializareVector(Vector* v, int capacitateInitiala) {

	v->vector = (Magazin*)malloc(sizeof(Magazin) * capacitateInitiala);
	v->dimensiune = 0;
	v->capacitate = capacitateInitiala;

}