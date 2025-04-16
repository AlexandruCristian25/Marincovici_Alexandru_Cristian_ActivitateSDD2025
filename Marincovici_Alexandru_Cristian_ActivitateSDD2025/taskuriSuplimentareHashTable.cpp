#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Cladire
typedef struct Cladire {

	unsigned int id;
	char* adresa;
	int anConstruire;
	int nrApartamente;

}Cladire;

// Creare structura nod pentru Lista Smpla Inlantuita
typedef struct Nod {

	Cladire cladire;
	struct Nod* next;

}Nod;

// Creare structura tabela de dispersie
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;