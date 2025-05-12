#define _CRT_SECURE_NO_WARNIGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Ghiozdan
typedef struct Ghiozdan {

	unsigned int id;
	char* producator;
	int capacitate;
	float pret;

}Ghiozdan;

// Initializare Ghiozdan
Ghiozdan initializareGhiozdan(unsigned int id, const char* producator,
	int capacitate, float pret) {

	Ghiozdan g;
	g.id = id;
	g.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(g.producator, producator);
	g.capacitate = capacitate;
	g.pret = pret;

	return g;

}

// Afisare Ghiozdan
void afisareGhiozdan(Ghiozdan ghiozdan) {

	printf("Id: %u\n", ghiozdan.id);
	printf("Producator: %s\n", ghiozdan.producator);
	printf("Capacitate: %d\n", ghiozdan.capacitate);
	printf("Pret: %.2f\n", ghiozdan.pret);

}

// Afisare vector Ghiozdane
void afisareVector(Ghiozdan* vector, int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisareGhiozdan(vector[i]);

	}

}

// Copiere primele n elemente
Ghiozdan* copiazaPrimeleElemente(Ghiozdan* vector, int nrElemente,
	int nrElementeCopiate) {

	Ghiozdan* vectorNou = (Ghiozdan*)malloc(sizeof(Ghiozdan) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {

		vectorNou[i] = vector[i];
		vectorNou[i].producator = (char*)malloc(sizeof(char) * strlen(vector[i].producator) + 1);
		strcpy(vectorNou[i].producator, vector[i].producator);

	}

	return vectorNou;

}

// Returneaza primul ghiozdan cu numele dat
Ghiozdan getPrimulGhiozdan(Ghiozdan* vector, int nrElemente,
	const char* producator) {

	Ghiozdan g;
	g.producator = NULL;
	for (int i = 0; i < nrElemente; i++) {

		if (strcmp(vector[i].producator, producator) == 0) {

			g = vector[i];
			g.producator = (char*)malloc(sizeof(char) * strlen(vector[i].producator) + 1);
			strcpy(g.producator, vector[i].producator);

			return g;

		}

	}

	return g;

}

//Dezalocare vector
void dezalocareVector(Ghiozdan** vector, int* nrElemente) {

	for (int i = 0; i < *nrElemente; i++) {

		if ((*vector)[i].producator != NULL) {

			free((*vector)[i].producator);

		}

	}

	free(*vector);
	*vector = NULL;
	*nrElemente = 0;

}
void dezalocareVector(Ghiozdan** vector, int* nrElemente) {

	for (int i = 0; i < *nrElemente; i++) {

		if ((*vector)[i].producator != NULL) {

			free((*vector)[i].producator);

		}

	}

	free(*vector);
	*vector = NULL;
	*nrElemente = 0;

}

// Afisare in main
int main() {

	Ghiozdan* nrGhiozdane = NULL;
	int ghiozdane = 3;

	nrGhiozdane = (Ghiozdan*)malloc(sizeof(Ghiozdan) * ghiozdane);
	nrGhiozdane[0] = initializareGhiozdan(1, "Producator1", 25, 299.99);
	nrGhiozdane[1] = initializareGhiozdan(2, "Producator2", 15, 199.99);
	nrGhiozdane[2] = initializareGhiozdan(3, "Producator3", 7, 99.99);

	printf("\nToate ghiozdanele: \n");
	afisareVector(nrGhiozdane, ghiozdane);

	// Primele ghiozdane
	int nrPrimeleGhiozdane = 2;
	Ghiozdan* primeleGhiozdane = copiazaPrimeleElemente(nrGhiozdane, ghiozdane, nrPrimeleGhiozdane);
	printf("\nPrimele ghiozdane: \n");
	afisareVector(primeleGhiozdane, nrPrimeleGhiozdane);
	dezalocareVector(&primeleGhiozdane, &nrPrimeleGhiozdane);

	// Cautare ghiozdan dupa producator
	Ghiozdan ghiozdan = getPrimulGhiozdan(nrGhiozdane, ghiozdane, "Producator2");
	printf("\nGhiozdan gasit: \n");
	afisareGhiozdan(ghiozdan);
	if (ghiozdan.producator != NULL) {

		free(ghiozdan.producator);
		ghiozdan.producator = NULL;

	}

	dezalocareVector(&nrGhiozdane, &ghiozdane);

	return 0;

}