#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura JocVideo
typedef struct JocVideo {

	unsigned int id;
	char* nume;
	int nrCopii;
	float pret;

}JocVideo;

// Creare structura nod
typedef struct Nod {

	JocVideo jocVideo;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;