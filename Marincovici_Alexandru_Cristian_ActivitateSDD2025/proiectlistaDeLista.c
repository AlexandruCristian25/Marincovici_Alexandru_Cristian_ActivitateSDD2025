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