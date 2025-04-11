#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Animal
typedef struct Animal {

	unsigned int id;
	char* nume;
	int nrBuc;
	float pret;

}Animal;

typedef struct Nod {

	Animal info;
	struct Nod* next;

}Nod;

// Functie de citire a unui animal din fisier
Animal citireAnimalDinFisier(FILE* f) {

	char buffer[100];
	Animal a;

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token;
		const char* sep = ",\n";
		token = strtok(buffer, sep);
		if (token) {

			a.id = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			a.nume = (char*)malloc(strlen(token) + 1);
			strcpy(a.nume, token);

		}
		token = strtok(NULL, sep);

		if (token) {

			a.nrBuc = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			a.pret = atof(token);

		}


	}

	return a;

}