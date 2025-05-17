#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Ceas
typedef struct Ceas {

	unsigned int id;
	char* nume;
	int greutate;
	float pret;

}Ceas;

// Creare structura Nod
typedef struct Nod {

	Ceas info;
	struct Nod* next;

}Nod;

// Functia de citire din fisier
Ceas citireDinFisier(FILE* f) {

	char buffer[100];
	Ceas c = { 0, NULL, 0, 0.0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.id = atoi(token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(c.nume, token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.greutate = atoi(token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.pret = atof(token);

	}

	return c;

}

// Functia de afiare
void afisareCeas(Ceas ceas) {

	printf("Id: %u\n", ceas.id);
	printf("Nume: %s\n", ceas.nume);
	printf("Greutate: %d\n", ceas.greutate);
	printf("Pret: %.2f\n", ceas.pret);

}

// Functia de afisare a listei
void afisareLista(Nod* cap) {

	while (cap) {

		afisareCeas(cap->info);
		cap = cap->next;

	}

}

// Functia de adaugare a unui element in lista
void adaugaInLista(Nod** cap, Ceas ceasNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = ceasNou;
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

// Citirea listei din fisier
Nod* citireListaDinFisier(const char* numrFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numrFisier, "r");

	if (f) {

		while (!feof(f)) {

			Ceas c = citireDinFisier(f);
			if (c.nume) {

				adaugaInLista(&cap, c);

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
		if (p->info.nume) {

			free(p->info.nume);

		}

		free(p);

	}

}
