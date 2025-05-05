#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Virus
typedef struct Virus {

	unsigned int cod;
	char* nume;
	char* tip;
	int nrTulpini;

}Virus;

// Functia de initializare
Virus initializareVirus(unsigned int cod, const char* nume,
	const char* tip, int nrTulpini) {

	Virus v;
	v.cod = cod;
	v.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(v.nume, nume);
	v.tip = (char*)malloc(sizeof(char) * strlen(tip) + 1);
	strcpy(v.tip, tip);
	v.nrTulpini = nrTulpini;

	return v;

}

// Creare structura Nod
typedef struct Nod {

	Virus virus;
	struct Nod* next;
	struct Nod* prev;

}Nod;