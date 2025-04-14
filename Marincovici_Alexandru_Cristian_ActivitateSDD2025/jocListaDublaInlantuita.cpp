#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

//Creare structura Joc
typedef struct Joc {

	unsigned int id;
	char* nume;
	int nrCopii;
	char* producator;

}Joc;

// Functia de initializare
Joc initializareJoc(unsigned int id, const char* nume,
	int nrCopii, const char producator) {

	Joc j;
	j.id = id;
	j.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(j.nume, nume);
	j.nrCopii = nrCopii;
	j.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(j.producator, producator);

	return j;

}

typedef struct Nod {

	Joc joc;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Citire din fisier
Joc citireDinFisier(FILE* f) {

	char buffer[100];
	Joc j = { 0,NULL,0,NULL };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(j.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.nrCopii = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.producator = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(j.producator, token);

	}

	return j;

}

// Functia de afisare a jocului
void afisareJoc(Joc joc) {

	printf("Id: %d\n", joc.id);
	printf("Nume: %s\n", joc.nume);
	printf("Nr copii: %d\n", joc.nrCopii);
	printf("Producator: %s\n", joc.producator);

}

// Creare structura lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

}ListaDubla;

// Functia de afisare a listei de jocuri la inceput
void afisareListaJocInceput(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareJoc(p->joc);
		p = p->next;

	}

}

// Functia de afisare a listei de jocuri la sfarsit
void afisareListaJocSfarsit(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afisareJoc(p->joc);
		p = p->prev;

	}

}

// Functia de adaugare a unui element la finalul listei
void adaugaLaFinalInLista(ListaDubla* lista, Joc jocNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->joc = jocNou;
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
void adaugaLaInceputInLista(ListaDubla* lista, Joc jocNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->joc = jocNou;
	nou->next = lista->first;
	nou->prev = NULL;

	if (lista->first != NULL) {

		lista->first->prev = nou;

	}
	else {

		lista->last = nou;

	}

	lista->first = nou;
	lista->nrNoduri++;

}

// Functia de citire a elementelor din fisier
ListaDubla citireLDFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;

	while (!feof(f)) {

		adaugaLaFinalInLista(&lista, citireDinFisier(f));

	}

	fclose(f);
	return lista;

}

// Functia de dezalocare a lisatei dublu inlantuite
void dezalocareLista(ListaDubla* lista) {

	Nod* p = lista->first;
	while (p) {

		Nod* aux = p;
		p = p->next;
		if (aux->joc.nume != NULL) {

			free(aux->joc.nume);

		}

		if (aux->joc.producator != NULL) {

			free(aux->joc.producator);

		}

		free(aux);

	}

	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;

}