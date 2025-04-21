#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Student
typedef struct Student {

	unsigned int cod;
	char* nume;
	int varsta;
	float medie;

}Student;

// Creare structura nod
typedef struct Nod {

	Student student;
	struct Nod* next;

}Nod;