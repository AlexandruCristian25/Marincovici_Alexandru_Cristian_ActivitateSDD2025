#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Virus
typedef struct Virus {

	unsigned int cod;
	char* nume;
	char* tip;
	int nrTulpini;

}Virus;

// Functia de initializare
Virus initializareVirus(unsigned int cod, const char* nume,
	const char* tip, int nrTulpini) {

	Virus v;
	v.cod = cod;
	v.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(v.nume, nume);
	v.tip = (char*)malloc(sizeof(char) * strlen(tip) + 1);
	strcpy(v.tip, tip);
	v.nrTulpini = nrTulpini;

	return v;

}

// Creare structura Nod
typedef struct Nod {

	Virus virus;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Citire din fisier
Virus citireFisier(FILE* f) {

	char buffer[100];
	Virus v = { 0, NULL, NULL, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return v;

		}
		v.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return v;

		}
		v.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(v.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return v;

		}
		v.tip = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(v.tip, token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return v;

		}
		v.nrTulpini = atoi(token);

	}

	return v;

}

// Functia de afisare a Virusului
void afisareVirus(Virus virus) {

	printf("Cod: %u\n", virus.cod);
	printf("Nume: %s\n", virus.nume);
	printf("Tip: %s\n", virus.tip);
	printf("Nr tulpini: %d\n", virus.nrTulpini);

}