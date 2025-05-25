#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Laptop
typedef struct Laptop {

	int id;
	char* producator;
	int nrBuc;
	float pret;

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
		s.producator = (char*)malloc(strlen(token) + 1);
		strcpy(s.producator, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.nrBuc = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.pret = atof(token);

	}

	return s;

}

// Functia de afisare a studentului
void afisarePacienti(Student student) {

	printf("Id: %u\n", student.id);
	printf("Producator: %s\n", student.producator);
	printf("Nr bucati: %d\n", student.nrBuc);
	printf("Pret: %.2f\n", student.pret);

}