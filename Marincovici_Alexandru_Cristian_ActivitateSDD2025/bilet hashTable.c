#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Bilet
typedef struct Bilet {
	unsigned int id;
	char* nume;
	int nrLoc;
	float pret;
} Bilet;

// Creare structura Nod
typedef struct Nod {
	Bilet bilet;
	struct Nod* next;
} Nod;