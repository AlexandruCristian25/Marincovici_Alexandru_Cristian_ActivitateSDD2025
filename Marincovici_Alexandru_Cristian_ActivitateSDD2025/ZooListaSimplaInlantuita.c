#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Zoo
typedef struct Zoo {

	unsigned int id;
	char* nume;
	int nrAnimale;
	int nrAngajati;
	float pretBilet;

}Zoo;

typedef struct Nod {

	Zoo info;
	struct Nod* next;

}Nod;