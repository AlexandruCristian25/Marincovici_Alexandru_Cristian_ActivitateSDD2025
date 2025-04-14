#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Avion
typedef struct Avion {

	unsigned int id;
	char* nume;
	int nrPasageri;
	float pret;

}Avion;

// Functie de initializare
Avion initializareAvion(unsigned int id, const char* nume,
	int nrPasageri, float pret) {

	Avion a;
	a.id = id;
	a.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(a.nume, nume);
	a.nrPasageri = nrPasageri;
	a.pret = pret;

	return a;

}

typedef struct Nod {

	Avion avion;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Citire din fisier
Avion citireAvionFisier(FILE* f) {

	char buffer[100];
	Avion a = { 0, NULL, 0, 0.0f };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return a;
		a.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return a;
		a.nume = (char*)malloc(strlen(token) + 1);
		strcpy(a.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return a;
		a.nrPasageri = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return a;
		a.pret = (float)atof(token);

	}

	return a;

}

// Functia de afisare a avionului
void afisareAvion(Avion avion) {

	printf("Id: %d\n", avion.id);
	printf("Nume: %s\n", avion.nume);
	printf("Nr pasageri: %d\n", avion.nrPasageri);
	printf("Pret: %.2f\n", avion.pret);

}

// Creare structura lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

}ListaDubla;

// Functia de afisare a listei de la inceput
void afisareListaMagazineInceput(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareAvion(p->avion);
		p = p->next;

	}

}

// Functia de afisare a listei de la sfarsit
void afisareListaMagazineSfarsit(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afisareAvion(p->avion);
		p = p->prev;

	}

}

// Functie de adaugare a unui element la finalul listei
void adaugaLaFinalInLista(ListaDubla* lista, Avion avionNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->avion = avionNou;
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

// Functie de adaugare a unui element la inceputul listei
void adaugaLaInceputlInLista(ListaDubla* lista, Avion avionNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->avion = avionNou;
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

// Functie de ctitire a elementelor din fisier
ListaDubla citireLDAvionDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;

	while (!feof(f)) {

		adaugaLaFinalInLista(&lista, citireAvionFisier(f));

	}

	fclose(f);
	return lista;

}

// Functia de dezalocare a listei dublu inlantuite
void dezalocareLista(ListaDubla* lista) {

	Nod* p = lista->first;
	while (p) {

		Nod* aux = p;
		p = p->next;
		if (aux->avion.nume != NULL) {

			free(aux->avion.nume);

		}

		free(aux);

	}

	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;

}

// Functie de calculare a pretului mediu
float calculeazaPretMediu(ListaDubla lista) {

	if (lista.nrNoduri > 0) {

		float suma = 0;
		Nod* p = lista.first;
		while (p) {

			suma += p->avion.pret;
			p = p->next;

		}

		return suma / lista.nrNoduri;

	}

	return 0;

}

// Afisare in main
int main() {

	ListaDubla lista = citireLDAvionDinFisier("avion.txt");
	afisareListaMagazineInceput(lista);

	printf("\n ======= Afisare lista de la sfarsit ============\n");
	afisareListaMagazineSfarsit(lista);

	printf("\n ======= Calculare pret mediu al biletelor ============\n");
	printf("\nPretul mediu al biletelor este de %.2f lei\n", calculeazaPretMediu(lista));

	printf("\nPretul mediu: %.2f\n", calculeazaPretMediu(lista));

	dezalocareLista(&lista);
	printf("\n =============== Afisare lista dupa dezalocare ===============\n");
	afisareListaMagazineInceput(lista);

	return 0;
}






