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