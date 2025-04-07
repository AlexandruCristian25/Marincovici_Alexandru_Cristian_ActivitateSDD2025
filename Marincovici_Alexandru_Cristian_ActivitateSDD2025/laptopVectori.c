#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Laptop {

	unsigned int id;
	char* producator;
	int RAM;
	float pret;

}Laptop;

//Initializare laptop
Laptop initializareLaptop(unsigned int id, const char* producator,
	int RAM, float pret) {

	Laptop l;
	l.id = id;
	l.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(l.producator, producator);
	l.RAM = RAM;
	l.pret = pret;

	return l;

}

//Afisare laptop
void afisareLaptop(Laptop l) {

	if (l.producator != NULL) {

		printf("\n%d Laptopul %s are %d RAM iar pretul este de %5.2f lei",
			l.id, l.producator, l.RAM, l.pret);

	}
	else {

		printf("\n%d Laptopul are %d RAM iar pretul este de %5.2f lei",
			l.id, l.RAM, l.pret);

	}

}

//Afisare vector
void afisareVector(Laptop* vector, int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisareLaptop(vector[i]);

	}

}

//Vector de copiere a primelor elemente
Laptop* copiazaPrimeleElemente(Laptop* vector, int nrElemente,
	int nrElementeCopiate) {

	Laptop* vectorNou = NULL;
	vectorNou = (Laptop*)malloc(sizeof(Laptop) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {

		vectorNou[i] = vector[i];
		vectorNou[i].producator = (char*)malloc(sizeof(char) * (strlen(vector[i].producator) + 1));
		strcpy(vectorNou[i].producator, vector[i].producator);

	}

	return vectorNou;

}

//Vector de copiere a anumitor elemente
void copiazaLaptop(Laptop* vector, char nrElemente, float pretMinim,
	Laptop** vectorNou, int* dimensiune) {

	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {

		if (vector[i].pret >= pretMinim) {

			(*dimensiune)++;

		}

	}

	if ((*vectorNou) != NULL) {

		free(*vectorNou);

	}

	*vectorNou = (Laptop*)malloc(sizeof(Laptop) * (*dimensiune));

	int k = 0;
	for (int i = 0; i < nrElemente; i++) {

		if (vector[i].pret >= pretMinim) {

			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].producator = (char*)malloc(sizeof(char) * strlen(vector[i].producator) + 1);
			strcpy((*vectorNou)[k].producator, vector[i].producator);
			k++;

		}

	}

}

//Vector de copiere a unui element conditionat
Laptop getPrimulLaptop(Laptop* vector, int nrElemente, const char* producator) {

	Laptop l;
	l.producator = NULL;
	for (int i = 0; i < nrElemente; i++) {

		if (strcmp(vector[i].producator, producator) == 0) {

			l = vector[i];
			l.producator = (char*)malloc(sizeof(char) * strlen(vector[i].producator) + 1);
			strcpy(l.producator, vector[i].producator);

			return l;

		}

	}

	return l;

}

//Dezalocarea vectorului
void dezalocareVector(Laptop** vector, int* nrElemente) {

	for (int i = 0; i < (*nrElemente); i++) {

		if ((*vector)[i].producator != NULL) {

			free((*vector)[i].producator);

		}

	}

	free(*vector);
	*vector = NULL;
	*nrElemente = 0;

}