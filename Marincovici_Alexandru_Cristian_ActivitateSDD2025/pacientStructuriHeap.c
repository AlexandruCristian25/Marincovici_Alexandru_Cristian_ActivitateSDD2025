#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Pacient
typedef struct Pacient {

	unsigned int id;
	char* nume;
	int varsta;
	int inaltime;
	int gradUrgenta;

}Pacient;

// Creare structura Heap
typedef struct Heap {

	int lungime;
	Pacient* vector;
	int nrPacienti;

}Heap;