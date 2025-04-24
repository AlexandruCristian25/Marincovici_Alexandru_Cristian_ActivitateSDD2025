#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Proiect
typedef struct Proiect {

	unsigned int id;
	char* titluP;
	char* beneficiar;
	unsigned char nrExecutanti;
	float bugetA;

}Proiect;

// Functia de initializare
Proiect initializareProiect(unsigned int id, char* titluP, char* beneficiar,
	unsigned char nrExecutanti, float bugetA) {

	Proiect p;
	p.id = id;
	p.titluP = (char*)malloc(sizeof(char) * strlen(titluP) + 1);
	strcpy(p.titluP, titluP);
	p.beneficiar = (char*)malloc(sizeof(char) * strlen(beneficiar) + 1);
	strcpy(p.beneficiar, beneficiar);
	p.nrExecutanti = nrExecutanti;
	p.bugetA = bugetA;

	return p;

}