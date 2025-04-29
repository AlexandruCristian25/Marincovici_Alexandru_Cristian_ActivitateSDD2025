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

// Citire din fișier
Pacient citireDinFisier(FILE* f) {

	char buffer[100];
	Pacient p = { 0, NULL, 0, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return p;
		p.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return p;
		p.nume = (char*)malloc(strlen(token) + 1);
		strcpy(p.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return p;
		p.varsta = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return p;
		p.inaltime = atoi(token);

		token = strtok(NULL, ",;\n");
		if (!token) return p;
		p.gradUrgenta = atoi(token);

	}

	return p;

}

// Functia de afisare a pacientului
void afisarePacienti(Pacient pacient) {

	printf("Id: %u\n", pacient.id);
	printf("Nume: %s\n", pacient.nume);
	printf("Varsta: %d\n", pacient.varsta);
	printf("Inaltime: %d\n", pacient.inaltime);
	printf("Grad Urgenta: %d\n", pacient.gradUrgenta);

}