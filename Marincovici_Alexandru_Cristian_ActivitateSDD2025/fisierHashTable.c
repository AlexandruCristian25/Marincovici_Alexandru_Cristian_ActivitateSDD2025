#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Fisier
typedef struct Fisier {

	char* denumire;
	char* caleF;
	char* extensieF;
	unsigned int dimensiune;

}Fisier;

// Creare structura Nod
typedef struct Nod {

	Fisier fisier;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;