#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Student
typedef struct Student {

	unsigned int id;
	char* nume;
	int varsta;
	float medie;

}Student;

// Creare structura Nod
typedef struct Nod {

	Student info;
	struct Nod* stanga;
	struct Nod* dreapta;
	int grad;

}Nod;

// Initializare Student
Student initializareStudent(unsigned int id, const char* nume,
	int varsta, float medie) {

	Student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.varsta = varsta;
	s.medie = medie;

	return s;

}