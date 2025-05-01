#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Proiect proiect;
typedef struct nodLS nodLS;
typedef struct nodLP nodLP;

// Creare structura Proiect
typedef struct Proiect {

	unsigned int id;
	char* nume;
	unsigned char caracteristici;
	int* dimensiune;

}Proiect;