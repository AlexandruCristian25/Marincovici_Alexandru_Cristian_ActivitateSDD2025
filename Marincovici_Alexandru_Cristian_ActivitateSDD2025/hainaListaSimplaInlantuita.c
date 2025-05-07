#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare struct Haina
typedef struct Haina {

	unsigned int cod;
	char* producator;
	int nrExemplare;
	float pret;

}Haina;

// Creare structura Nod
typedef struct Nod {

	Haina info;
	struct Nod* next;

}Nod;