#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Tara
typedef struct Tara {

	unsigned int cod;
	char* nume;
	int nrLocuitori;
	int PIB

}Tara;

// Creare structura Nod
typedef struct Nod {

	Tara info;
	struct Nod* next;

}Nod;

// Functia de citire a unei Tara din fisier
Tara citireDinFisier(FILE* f) {

	char buffer[100];
	Tara t = { 0, NULL, 0, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return t;

		}
		t.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return t;

		}
		t.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(t.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return t;

		}
		t.nrLocuitori = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return t;

		}
		t.PIB = atoi(token);

	}

	return t;

}