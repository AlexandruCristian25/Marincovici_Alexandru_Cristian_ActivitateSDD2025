#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Animal
typedef struct Animal {

	unsigned int id;
	char* nume;
	int nrBuc;
	float pret;

}Animal;

typedef struct Nod {

	Animal info;
	struct Nod* next;

}Nod;

// Functie de citire a unui animal din fisier
Animal citireAnimalDinFisier(FILE* f) {

	char buffer[100];
	Animal a;

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token;
		const char* sep = ",\n";
		token = strtok(buffer, sep);
		if (token) {

			a.id = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			a.nume = (char*)malloc(strlen(token) + 1);
			strcpy(a.nume, token);

		}
		token = strtok(NULL, sep);

		if (token) {

			a.nrBuc = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			a.pret = atof(token);

		}


	}

	return a;

}

// Functia de afisare
void afisareAnimal(Animal animal) {

	printf("Id: %d\n", animal.id);
	printf("Nume: %s\n", animal.nume);
	printf("Nr buc: %d\n", animal.nrBuc);
	printf("Pret: %.2f\n", animal.pret);

}

// Functia de afisare a listei de animale
void afisareListaAnimale(Nod* cap) {

	while (cap) {

		afisareAnimal(cap->info);
		cap = cap->next;

	}

}

// Functia de adaugare a unui animal in lista
void adaugareAnimalInLista(Nod** cap, Animal animalNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = animalNou;
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
Nod* citireListaAnimaleDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");

	if (f) {

		while (!feof(f)) {

			Animal a = citireAnimalDinFisier(f);
			if (a.nume) {

				adaugareAnimalInLista(&cap, a);

			}

		}

		fclose(f);

	}

	return cap;

}

// Dezalocare lista
void dezalocareListaAnimale(Nod** cap) {

	while (*cap) {

		Nod* p = *cap;
		*cap = p->next;
		if (p->info.nume) {

			free(p->info.nume);

		}

		free(p);

	}

}

// Calculeaza pret mediu
float calculeazaPretMediu(Nod* cap) {

	float suma = 0.0f;
	int contor = 0;

	while (cap) {

		suma += cap->info.pret;
		contor++;
		cap = cap->next;

	}

	return suma / contor;

}

// Afisare in main
int main() {

	Nod* cap = citireListaAnimaleDinFisier("animal.txt");

	printf("====== Lista animale =======\n");
	afisareListaAnimale(cap);

	float pretMediu = calculeazaPretMediu(cap);
	printf("Pretul mediu este de %.2f lei\n", pretMediu);
	dezalocareListaAnimale(&cap);

	printf("====== Lista animale dupa dezalocare =======\n");
	afisareListaAnimale(cap);

	return 0;

}