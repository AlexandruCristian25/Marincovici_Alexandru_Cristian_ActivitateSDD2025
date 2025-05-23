#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Student
typedef struct Student {

	int id;
	char* nume;
	int varsta;
	float medie;

}Student;

// Creare structura Heap
typedef struct Heap {

	int lungime;
	Student* vector;
	int nrStudenti;

}Heap;