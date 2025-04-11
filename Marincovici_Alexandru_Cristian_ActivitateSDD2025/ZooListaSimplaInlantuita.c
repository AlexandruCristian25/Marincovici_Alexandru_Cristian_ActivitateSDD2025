#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Zoo
typedef struct Zoo {

	unsigned int id;
	char* nume;
	int nrAnimale;
	int nrAngajati;
	float pretBilet;

}Zoo;

typedef struct Nod {

	Zoo info;
	struct Nod* next;

}Nod;

// Functie de citire a unui Zoo din fisier
Zoo citireZooDinFisier(FILE* f) {

	char buffer[100];
	Zoo z1;

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token;
		const char* sep = ",\n";
		token = strtok(buffer, sep);

		if (token) {

			z1.id = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			z1.nume = (char*)malloc(strlen(token) + 1);
			strcpy(z1.nume, token);

		}
		token = strtok(NULL, sep);

		if (token) {

			z1.nrAnimale = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			z1.nrAngajati = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			z1.pretBilet = atof(token);

		}
		token = strtok(NULL, sep);

	}

	return z1;
}
