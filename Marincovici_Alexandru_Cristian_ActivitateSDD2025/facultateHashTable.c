#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Facultate
typedef struct Facultate {

	unsigned int cod;
	char* nume;
	int nrLocuri;
	int nrCredite;

}Facultate;

// Creare strcutura Nod
typedef struct Nod {

	Facultate facultate;
	struct Nod* next;

}Nod;