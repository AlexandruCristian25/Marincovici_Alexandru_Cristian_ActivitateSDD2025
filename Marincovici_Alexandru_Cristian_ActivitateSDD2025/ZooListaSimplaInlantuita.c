#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Zoo
typedef struct Zoo {

	unsigned int id;
	char* nume;
	int nrAnimale;
	int nrAngajati;
	float pretBilet;

}Zoo;

typedef struct Nod {

	Zoo info;
	struct Nod* next;

}Nod;

// Functie de citire a unui Zoo din fisier
Zoo citireZooDinFisier(FILE* f) {

	char buffer[100];
	Zoo z1;

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token;
		const char* sep = ",\n";
		token = strtok(buffer, sep);

		if (token) {

			z1.id = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			z1.nume = (char*)malloc(strlen(token) + 1);
			strcpy(z1.nume, token);

		}
		token = strtok(NULL, sep);

		if (token) {

			z1.nrAnimale = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			z1.nrAngajati = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			z1.pretBilet = atof(token);

		}
		token = strtok(NULL, sep);

	}

	return z1;
}

// Functia de afisare Zoo
void afisareZoo(Zoo zoo) {

	printf("Id: %d\n", zoo.id);
	printf("Nume: %s\n", zoo.nume);
	printf("Nr animale: %d\n", zoo.nrAnimale);
	printf("Nr angajati: %d\n", zoo.nrAngajati);
	printf("Pret bilet: %.2f\n", zoo.pretBilet);

}

// Functia de afisare a listei
void afisareListaZoo(Nod* cap) {

	while (cap) {

		afisareZoo(cap->info);
		cap = cap->next;

	}

}

// Funcita de adaugare a unui element in lista
void adaugaZooInLista(Nod** cap, Zoo zooNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = zooNou;
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
Nod* citireListaZooDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");

	if (f) {

		while (!feof(f)) {

			Zoo z = citireZooDinFisier(f);
			if (z.nume) {

				adaugaZooInLista(&cap, z);

			}

		}

		fclose(f);

	}

	return cap;

}

// Dezalocare lista
void dezalocareListaZoo(Nod** cap) {

	while (*cap) {

		Nod* p = *cap;
		*cap = p->next;
		if (p->info.nume) {

			free(p->info.nume);

		}

		free(p);

	}

}

// Afisare in main
int main() {

	Nod* cap = citireListaZooDinFisier("zoo.txt");
	printf("=== Lista ZOO ===\n");
	afisareListaZoo(cap);
	dezalocareListaZoo(&cap);

	printf("\n=== Lista dupa dezalocare ===\n");
	afisareListaZoo(cap);

	return 0;

}

