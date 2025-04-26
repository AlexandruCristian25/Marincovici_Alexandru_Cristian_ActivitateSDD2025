#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Reteta
typedef struct Reteta {

	unsigned int nr;
	int nrMedicamente;
	char* numeMedic;
	float valoare;

}Reteta;