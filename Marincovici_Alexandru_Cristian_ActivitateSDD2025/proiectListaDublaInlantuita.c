#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Proiect
typedef struct Proiect {

	unsigned int id;
	char* titluP;
	char* beneficiar;
	unsigned char nrExecutanti;
	float bugetA;

}Proiect;

// Functia de initializare
Proiect initializareProiect(unsigned int id, char* titluP, char* beneficiar,
	unsigned char nrExecutanti, float bugetA) {

	Proiect p;
	p.id = id;
	p.titluP = (char*)malloc(sizeof(char) * strlen(titluP) + 1);
	strcpy(p.titluP, titluP);
	p.beneficiar = (char*)malloc(sizeof(char) * strlen(beneficiar) + 1);
	strcpy(p.beneficiar, beneficiar);
	p.nrExecutanti = nrExecutanti;
	p.bugetA = bugetA;

	return p;

}

typedef struct Nod {

	Proiect proiect;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Citire din fisier
Proiect citireFisier(FILE* f) {

	char buffer[100];
	Proiect p = { 0, NULL, NULL, 0, 0.0f };
	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.titluP = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(p.titluP, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.beneficiar = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(p.beneficiar, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.nrExecutanti = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.bugetA = (float)atof(token);

	}

	return p;

}

// Functia de afisare a Proiectului
void afisareProiect(Proiect proiect) {

	printf("Id: %d\n", proiect.id);
	printf("Titilu proiect: %s\n", proiect.titluP);
	printf("Beneficiar: %s\n", proiect.beneficiar);
	printf("Nr executanti: %d\n", proiect.nrExecutanti);
	printf("Buget: %.2f\n", proiect.bugetA);

}