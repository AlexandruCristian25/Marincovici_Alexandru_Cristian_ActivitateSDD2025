#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare struct Haina
typedef struct Haina {

	unsigned int cod;
	char* producator;
	int nrExemplare;
	float pret;

}Haina;

// Creare structura Nod
typedef struct Nod {

	Haina info;
	struct Nod* next;

}Nod;

// Functie de citire din fisier
Haina citireDinFisier(FILE* f) {

	char buffer[100];
	Haina h = { 0, NULL, 0, 0.0 };
	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == 0) {

			return h;

		}
		h.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == 0) {

			return h;

		}
		h.producator = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(h.producator, token);

		token = strtok(NULL, ",;\n");
		if (token == 0) {

			return h;

		}
		h.nrExemplare = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == 0) {

			return h;

		}
		h.pret = atof(token);

	}

	return h;

}

// Functia de afisare
void afisareHaina(Haina haina) {

	printf("Cod: %u\n", haina.cod);
	printf("Producator: %s\n", haina.producator);
	printf("Nr exemplare: %d\n", haina.nrExemplare);
	printf("Pret: %.2f\n", haina.pret);

}