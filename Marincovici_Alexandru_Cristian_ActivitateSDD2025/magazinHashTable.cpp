#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Magazin
typedef struct Magazin {

	unsigned int cod;
	char* denumire;
	int nrProduse;
	float pretP;

} Magazin;

// Creare structura nod
typedef struct Nod {

	Magazin magazin;
	struct Nod* next;

} Nod;

// Creare structura tabela de dispersie
typedef struct HashTable {

	int dim;
	Nod** tabela;

} HashTable;