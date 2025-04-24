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