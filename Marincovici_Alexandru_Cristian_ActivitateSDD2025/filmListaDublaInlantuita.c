#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Film
typedef struct Film {

	unsigned int id;
	char* numeF;
	int nrActori;
	float pretBilet;

}Film;