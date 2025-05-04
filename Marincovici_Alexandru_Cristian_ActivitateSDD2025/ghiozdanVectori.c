#define _CRT_SECURE_NO_WARNIGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Ghiozdan
typedef struct Ghiozdan {

	unsigned int id;
	char* producator;
	int capacitate;
	float pret;

}Ghiozdan;

// Initializare Ghiozdan
Ghiozdan initializareGhiozdan(unsigned int id, const char* producator,
	int capacitate, float pret) {

	Ghiozdan g;
	g.id = id;
	g.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(g.producator, producator);
	g.capacitate = capacitate;
	g.pret = pret;

	return g;

}