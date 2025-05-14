#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Masina
typedef struct Masina {

	unsigned int id;
	char* producator;
	int nrUsi;
	float pret;

}Masina;

// Creare structura Nod
typedef struct Nod {

	Masina info;
	struct Nod* next;

}Nod;

// Functia de citire din fisier
Masina cititreDinFisier(FILE* f) {

	char buffer[100];
	Masina m = { 0, NULL, 0, 0.0 };
	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.producator = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(m.producator, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.nrUsi = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.pret = atof(token);

	}

	return m;

}

// Functia de afisare
void afisareMasina(Masina masina) {

	printf("Id: %u\n", masina.id);
	printf("Producator: %s\n", masina.producator);
	printf("Nr usi: %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);

}

// Functia de afisare a listei
void afisareLista(Nod* cap) {

	while (cap) {

		afisareMasina(cap->info);
		cap = cap->next;

	}

}

// Functia de adaugare a unui element in lista
void adaugareInLista(Nod** cap, Masina masinaNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;

	if (*cap == NULL) {

		*cap = nou;

	}
	else {

		Nod* p = *cap;
		while (p->next) {

			p = p->next;

		}

		p->next = nou;

	}

}

// Citire lista din fisier
Nod* citireListaDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");

	if (f) {

		while (!feof(f)) {

			Masina m = cititreDinFisier(f);
			if (m.producator) {

				adaugareInLista(&cap, m);

			}

		}
		fclose(f);

	}

	return cap;

}

// Functia de dezalocare a listei
void dezalocareLista(Nod** cap) {

	while (*cap) {

		Nod* p = *cap;
		*cap = p->next;
		if (p->info.producator) {

			free(p->info.producator);

		}

		free(p);

	}

}

