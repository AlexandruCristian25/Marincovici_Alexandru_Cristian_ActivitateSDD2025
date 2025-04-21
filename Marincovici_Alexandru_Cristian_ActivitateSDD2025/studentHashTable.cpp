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

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Student citireStudentFisier(FILE* f) {

	char buffer[100];
	Student s = { 0, NULL, 0, 0.0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(s.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.varsta = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.medie = atof(token);

	}

	return s;

}

// Afisare Student
void afisareStudent(Student student) {

	printf("Cod: %d\n", student.cod);
	printf("Nume: %s\n", student.nume);
	printf("Varsta: %d\n", student.varsta);
	printf("Medie: %.2f\n", student.medie);

}

// Functie de afisare a listei
void afisareListaStudenti(Nod* cap) {

	while (cap) {

		afisareStudent(cap->student);
		cap = cap->next;

	}

}