#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Ceas
typedef struct Ceas {

	unsigned int id;
	char* nume;
	int greutate;
	float pret;

}Ceas;

// Creare structura Nod
typedef struct Nod {

	Ceas info;
	struct Nod* next;

}Nod;