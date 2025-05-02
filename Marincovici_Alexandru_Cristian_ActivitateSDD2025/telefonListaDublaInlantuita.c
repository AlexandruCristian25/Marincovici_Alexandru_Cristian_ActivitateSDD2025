#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare stuctura Telefon
typedef struct Telefon {

	unsigned int cod;
	char* producator;
	int nrExemplare;
	float pret;

}Telefon;

// Functia de initializare
Telefon initializareTelefon(unsigned int cod, const char* producator,
	int nrExemplare, float pret) {

	Telefon t;
	t.cod = cod;
	t.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(t.producator, producator);
	t.nrExemplare = nrExemplare;
	t.pret = pret;

	return t;

}

// Creare structura nod
typedef struct Nod {

	Telefon telefon;
	struct Nod* next;
	struct Nod* prev;


}Nod;

// Citire din fisier
Telefon citireFisier(FILE* f) {

	char buffer[100];
	Telefon t = { 0, NULL, 0, 0.0 };
	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return t;


		}
		t.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return t;


		}
		t.producator = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(t.producator, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return t;


		}
		t.nrExemplare = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return t;


		}
		t.pret = atof(token);

	}

	return t;

}

// Functia de afisare a Telefonului
void afisareTelefon(Telefon telefon) {

	printf("Cod: %u\n", telefon.cod);
	printf("Producator: %s\n", telefon.producator);
	printf("Nr exemplare: %d\n", telefon.nrExemplare);
	printf("Pret: %.2f\n", telefon.pret);

}

// Creare lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

}ListaDubla;

// Functia de afisare a listei duble la inceput
void afisareListaInceput(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareTelefon(p->telefon);
		p = p->next;

	}

}

// Functia de afisare a listei duble la sfarsit
void afisareListaSfarsit(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afisareTelefon(p->telefon);
		p = p->prev;

	}

}

// Functia de adaugare a unui element la finalul listei
void adaugaLaFinalInLista(ListaDubla* lista, Telefon telefonNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->telefon = telefonNou;
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
void adaugaLaInceputlInLista(ListaDubla* lista, Telefon telefonNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->telefon = telefonNou;
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