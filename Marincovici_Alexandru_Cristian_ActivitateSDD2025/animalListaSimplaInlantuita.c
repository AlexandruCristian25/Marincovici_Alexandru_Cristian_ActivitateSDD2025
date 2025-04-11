#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Animal
typedef struct Animal {

	unsigned int id;
	char* nume;
	int nrBuc;
	float pret;

}Animal;

typedef struct Nod {

	Animal info;
	struct Nod* next;

}Nod;