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

// Citire din fisier
Student citireDinFisier(FILE* f) {

	char buffer[100];
	Student s = { 0, NULL, 0, 0.0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return s;
		s.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.nume = (char*)malloc(strlen(token) + 1);
		strcpy(s.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.varsta = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.medie = atof(token);

	}

	return s;

}

// Functia de afisare a studentului
void afisarePacienti(Student student) {

	printf("Id: %u\n", student.id);
	printf("Nume: %s\n", student.nume);
	printf("Varsta: %d\n", student.varsta);
	printf("Medie: %.2f\n", student.medie);

}

// Initializare Heap
Heap initializareHeap(int lungime) {

	Heap heap;
	heap.lungime = lungime;
	heap.nrStudenti = 0;
	heap.vector = (Student*)malloc(sizeof(Student) * lungime);

	return heap;

}

