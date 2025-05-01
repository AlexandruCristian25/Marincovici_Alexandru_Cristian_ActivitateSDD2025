#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Proiect proiect;
typedef struct nodLS nodLS;
typedef struct nodLP nodLP;

// Creare structura Proiect
typedef struct Proiect {

	unsigned int id;
	char* nume;
	unsigned char caracteristici;
	int* dimensiune;

}Proiect;

// Initializare proiect
Proiect initilaizareProiect(unsigned int id, const char* nume,
	unsigned char caracteristici, int* dimensiune) {

	Proiect p;
	p.id = id;
	p.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(p.nume, nume);
	p.caracteristici = caracteristici;
	for (int i = 0; i < caracteristici; i++) {

		p.dimensiune[i] = dimensiune[i];

	}

	return p;

}

// Afisare Proiect
void afisareProiect(Proiect proiect) {

	printf("Id: %u\n", proiect.id);
	printf("Nume: %s\n", proiect.nume);
	printf("Caracteristici: %u\n", proiect.caracteristici);
	printf("Dimensiune: %d\n", proiect.dimensiune);

}

// Citire din fisier
Proiect citireDinFisier(FILE* f) {

	char buffer[100];
	Proiect p = { 0, NULL, NULL, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.id = atoi(token);

		token = (NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(p.nume, token);

		token = (NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.caracteristici = atoi(token);

		token = (NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.dimensiune = atoi(token);

	}

	return p;

}

// Creare structura Lista simpla - nodLS
typedef struct nodLS {

	Proiect info;
	nodLS* next;

};

// Creare structura Lista principala - nodLP
typedef struct nodeLP {

	nodLS* info;
	nodLP* next;

};