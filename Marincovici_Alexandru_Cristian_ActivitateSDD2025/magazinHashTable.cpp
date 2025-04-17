#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Magazin
typedef struct Magazin {

	unsigned int cod;
	char* denumire;
	int nrProduse;
	float pretP;

} Magazin;