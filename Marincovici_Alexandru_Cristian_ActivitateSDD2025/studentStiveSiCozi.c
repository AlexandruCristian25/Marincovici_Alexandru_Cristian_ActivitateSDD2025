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

// Initializare Student
Student initializareStudent(int id, const char* nume,
	int varsta, float medie) {

	Student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.varsta = varsta;
	s.medie = medie;

	return s;

}

// Functia de afisare
void afisareStudent(Student student) {

	printf("Id: %d", student.id);
	printf("Nume: %s", student.nume);
	printf("Varsta: %d", student.varsta);
	printf("Medie: %.2f", student.medie);

}