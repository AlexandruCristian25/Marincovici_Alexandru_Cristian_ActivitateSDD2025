#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//Creare structura Joc
typedef struct Joc {

	unsigned int id;
	char* nume;
	int nrCopii;
	char* producator;

}Joc;