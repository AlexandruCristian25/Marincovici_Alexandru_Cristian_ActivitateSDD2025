#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Tara
typedef struct Tara {

	unsigned int cod;
	char* nume;
	int nrLocuitori;
	int PIB

}Tara;

// Creare structura Nod
typedef struct Nod {

	Tara info;
	struct Nod* next;

}Nod;