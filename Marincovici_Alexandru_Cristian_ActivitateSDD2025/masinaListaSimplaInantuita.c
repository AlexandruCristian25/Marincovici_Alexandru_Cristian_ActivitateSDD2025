#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Masina
typedef struct Masina {

	unsigned int id;
	char* producator;
	int nrUsi;
	float pret;

}Masina;

// Creare structura Nod
typedef struct Nod {

	Masina info;
	struct Nod* next;

}Nod;