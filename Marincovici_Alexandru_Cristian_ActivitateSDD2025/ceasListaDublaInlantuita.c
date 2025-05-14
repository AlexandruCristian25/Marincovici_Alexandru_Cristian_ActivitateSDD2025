#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Carte
typedef struct Carte {

	unsigned int cod;
	char* nume;
	int nrExemplare;
	float pret;

}Carte;

// Functia de initializare
void initilizareCarte(unsigned int cod, const char* nume,
	int nrExemplare, float pret) {

	Carte c;
	c.cod = cod;
	c.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrExemplare = nrExemplare;
	c.pret = pret;

}

// Creare structura Nod
typedef struct Nod {

	Carte carte;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Citire din fisier
Carte citireFisier(FILE * f) {

	char buffer[100];
	Carte c = { 0, NULL, 0, 0.0 };
	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.cod = atoi(token);

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
		c.nrExemplare = atoi(token);

		token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return c;

		}
		c.pret = atof(token);

	}

	return c;

}

// Functia de afisare
void afisareCarte(Carte carte) {

	printf("\nCod: %u\n", carte.cod);
	printf("\Nume: %s\n", carte.nume);
	printf("\Nr exemplare: %d\n", carte.nrExemplare);
	printf("\nPret: %.2f\n", carte.pret);

}

// Creare structura lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

}ListaDubla;

// Functia de afisare a listei de la inceput
void afisareListaInceput(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareCarte(p->carte);
		p = p->next;

	}

}

// Functia de afisare a listei de la sfarsit
void afisareListaSfarsit(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afisareCarte(p->carte);
		p = p->prev;

	}

}

// Functia de adaugare a unui element la finalul listei
void adaugaLaFinalInLista(ListaDubla* lista, Carte carteNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->carte = carteNoua;
	nou->next = NULL;
	nou->prev = lista->last;

	if (lista->last != NULL) {

		lista->last->next = nou;

	}
	else {

		lista->first = nou;

	}

	lista->last = nou;
	lista->nrNoduri++;

}

// Functia de adaugare a unui element la inceputul listei
void adaugaLaInceputInLista(ListaDubla* lista, Carte carteNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->carte = carteNoua;
	nou->next = lista->first;
	nou->prev = NULL;

	if (lista->first != NULL) {

		lista->first->prev = nou;

	}
	else {

		lista->first = nou;

	}

	lista->first = nou;
	lista->nrNoduri++;

}

// Functia de citire a elementelor din lista
ListaDubla citireLDDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;

	while (!feof(f)) {

		adaugaLaFinalInLista(&lista, citireFisier(f));

	}

	fclose(f);
	return lista;

}

// Functia de dezalocare
void dezalocareLista(ListaDubla* lista) {

	Nod* p = lista->first;
	while (p) {

		Nod* aux = p;
		p = p->next;
		if (aux->carte.nume != NULL) {

			free(aux->carte.nume);

		}

		free(aux);

	}

	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;

}