#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Film
typedef struct Film {

	unsigned int id;
	char* numeF;
	int nrActori;
	float pretBilet;

}Film;

// Creare structura Nod
typedef struct Nod {

	Film film;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Functia de initializare
Film initialiareFilm(unsigned int id, const char numeF,
	int nrActori, float pretBilet) {

	Film fi;
	fi.id = id;
	fi.numeF = (char*)malloc(sizeof(char) * strlen(numeF) + 1);
	strcpy(fi.numeF, numeF);
	fi.nrActori = nrActori;
	fi.pretBilet = pretBilet;

	return fi;

}

// Citire din fisier
Film citireFisier(FILE* f) {

	char buffer[100];
	Film fi = { 0, NULL, 0, 0.0 };
	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return fi;

		}
		fi.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fi;

		}
		fi.numeF = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(fi.numeF, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fi;

		}
		fi.nrActori = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return fi;

		}
		fi.pretBilet = atof(token);

	}

	return fi;

}

// Functia de afisare a Filmului
void afsareFilm(Film film) {

	printf("Id: %u\n", film.id);
	printf("Nume film: %s\n", film.numeF);
	printf("Nr actori: %d\n", film.nrActori);
	printf("Pret bilet: %.2f\n", film.pretBilet);

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

		afsareFilm(p->film);
		p = p->next;

	}

}

// Functia de afisare a listei de la sfarsit
void afisareListaSfarsit(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afsareFilm(p->film);
		p = p->prev;

	}

}

// Functia de adaugare a unui element la finalul listei
void adaugaLaFinalInLista(ListaDubla* lista, Film filmNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->film = filmNou;
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
void adaugaLaInceputInLista(ListaDubla* lista, Film filmNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->film = filmNou;
	nou->prev = lista->first;
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

// Functia de dezalocare
void dezalocareLista(ListaDubla* lista) {

	Nod* p = lista->first;
	while (p) {

		Nod* aux = p;
		p = p->next;
		if (aux->film.numeF != NULL) {

			free(aux->film.numeF);

		}

		free(aux);

	}

	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;

}

// Afisare in main
int main() {

	ListaDubla lista = citireLDDinFisier("filme.txt");
	afisareListaInceput(lista);

	printf("\n =============  Afisare lista de la sfarsit  ============== \n");
	afisareListaSfarsit(lista);

	dezalocareLista(&lista);

	printf("\n =============  Afisare lista dupa dezalocare  ============== \n");
	afisareListaInceput(lista);

	return 0;

}