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

} Student;

// Creare structura Nod
typedef struct Nod {

	Student info;
	struct Nod* next;

}Nod;