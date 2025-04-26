#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Farmacie
typedef struct Farmacie {

	char* denumire;
	float suprafata;
	int nrAngajati;

}Farmacie;

// Funcția de inițializare
Farmacie initializareFarmacie(const char* denumire, float suprafata, int nrAngajati) {

	Farmacie fa;
	fa.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(fa.denumire, denumire);
	fa.suprafata = suprafata;
	fa.nrAngajati = nrAngajati;
	return fa;

}

typedef struct Nod {

	Farmacie farmacie;
	struct Nod* next;
	struct Nod* prev;

} Nod;

// Citire din fișier
Farmacie citireFisier(FILE* f) {

	char buffer[100];
	Farmacie fa = { NULL, 0.0f, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return fa;
		fa.denumire = (char*)malloc(strlen(token) + 1);
		strcpy(fa.denumire, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return fa;
		fa.suprafata = (float)atof(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return fa;
		fa.nrAngajati = atoi(token);

	}

	return fa;

}

// Functia de afisare a Farmaciei
void afisareFarmacie(Farmacie farmacie) {

	printf("Denumire: %s\n", farmacie.denumire);
	printf("Suprafata: %.2f\n", farmacie.suprafata);
	printf("Nr angajati: %d\n", farmacie.nrAngajati);

}