#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Tara
typedef struct Tara {

	unsigned int cod;
	char* nume;
	int nrLocuitori;
	int PIB

}Tara;

// Creare structura Nod
typedef struct Nod {

	Tara info;
	struct Nod* next;

}Nod;

// Functia de citire a unei Tara din fisier
Tara citireDinFisier(FILE* f) {

	char buffer[100];
	Tara t = { 0, NULL, 0, 0 };

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
		t.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(t.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return t;

		}
		t.nrLocuitori = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return t;

		}
		t.PIB = atoi(token);

	}

	return t;

}

// Functia de afisare a Tarii
void afisareTara(Tara tara) {

	printf("Cod: %u\n", tara.cod);
	printf("Nume: %s\n", tara.nume);
	printf("Nr locuitori: %d\n", tara.nrLocuitori);
	printf("PIB: %d\n", tara.PIB);

}

// Functia de afisare a listei de tari
void afisareListaTari(Nod* cap) {

	while (cap) {

		afisareTara(cap->info);
		cap = cap->next;

	}

}

// Functia de adaugare a unuei Tari in lista
void adaugaTaraInLista(Nod** cap, Tara taraNoua) {

	Nod* nou = (Nod*)malloc(size(Nod));
	nou->info = taraNoua;
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
Nod* citireListaTariDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");

	if (f) {

		while (!feof(f)) {

			Tara t = citireDinFisier(f);
			if (t.nume) {

				adaugaTaraInLista(&cap, t);

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

// Afisare in main
int main() {

	Nod* cap = citireListaTariDinFisier("tara.txt");

	printf("\n ==============  Lista tari  ================== \n");
	afisareListaTari(cap);

	dezalocareLista(&cap);

	printf("\n ==============  Lista tari dupa dezalocare  ================== \n");
	afisareListaTari(cap);

}