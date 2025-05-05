#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Virus
typedef struct Virus {

	unsigned int cod;
	char* nume;
	char* tip;
	int nrTulpini;

}Virus;