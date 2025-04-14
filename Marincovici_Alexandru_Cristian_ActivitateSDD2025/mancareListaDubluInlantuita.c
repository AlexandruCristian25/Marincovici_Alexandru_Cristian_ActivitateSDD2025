#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Mancare
typedef struct Mancare {

	unsigned int cod;
	char* nume;
	int nrIngrediente;

}Mancare;

// Functia de initializare
Mancare initializareMancare(unsigned int cod, const char* nume, int nrIngrediente) {

	Mancare m;
	m.cod = cod;
	m.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(m.nume, nume);
	m.nrIngrediente = nrIngrediente;

	return m;

}

typedef struct Nod {

	Mancare mancare;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Citire din fisier
Mancare citireMancareInFisier(FILE* f) {

	char buffer[100];
	Mancare m = { 0,NULL,0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(m.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.nrIngrediente = atoi(token);

	}

	return m;

}

// Functia de afisare
void afisareMancare(Mancare mancare) {

	printf("Cod: %d\n", mancare.cod);
	printf("Cod: %s\n", mancare.nume);
	printf("Nume: %s\n", mancare.nrIngrediente);

}

// Creare structura lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

}ListaDubla;
