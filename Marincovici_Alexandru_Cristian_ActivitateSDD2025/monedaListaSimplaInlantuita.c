#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Moneda
typedef struct Moneda {

	char* taraEmitenta;
	int valoareN;
	float greutate;
	int anEmitere;

}Moneda;

typedef struct Nod {

	Moneda info;
	struct Nod* next;

}Nod;

// Citire din fisier
Moneda citireMonedaFisier(FILE* f) {

	char buffer[100];
	Moneda m = { NULL, 0, 0.0f, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return m;
		m.taraEmitenta = (char*)malloc(strlen(token) + 1);
		strcpy(m.taraEmitenta, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.valoareN = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.greutate = (float)atof(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.anEmitere = atoi(token);

	}

	return m;

}

// Afisare Moneda
void afisareMoneda(Moneda moneda) {

	printf("Tara emitenta: %s\n", moneda.taraEmitenta);
	printf("Valoare: %d\n", moneda.valoareN);
	printf("Greutate: %.2f\n", moneda.greutate);
	printf("An emitere: %d\n", moneda.anEmitere);

}

// Functia de afisare a listei de monezi
void afisareListaMonezi(Nod* cap) {

	while (cap) {

		afisareMoneda(cap->info);
		cap = cap->next;

	}

}

// Functia de adaugare a unei monezi in lista
void adaugaMonedaInLista(Nod** cap, Moneda monedaNoua) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = monedaNoua;
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
Nod* citireListaMoneziDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {

		while (!feof(f)) {

			Moneda m = citireMonedaFisier(f);
			if (m.taraEmitenta) {

				adaugaMonedaInLista(&cap, m);

			}

		}
		fclose(f);

	}

	return cap;

}

// Functia de returnare a greutatii maxime
Moneda greutateMaxima(Nod* cap) {

	float max = 0;
	Moneda m;

	if (cap) {

		Nod* aux = cap;
		while (aux) {

			if (aux->info.greutate > max) {

				max = aux->info.greutate;

			}
			aux = aux->next;

		}

		aux = cap;
		while (aux) {

			if (aux->info.greutate == max) {

				m.taraEmitenta = (char*)malloc(sizeof(char) * strlen(aux->info.taraEmitenta) + 1);
				strcpy(m.taraEmitenta, aux->info.taraEmitenta);
				m.valoareN = aux->info.valoareN;
				m.greutate = aux->info.greutate;
				m.anEmitere = aux->info.anEmitere;

				return m;

			}

			aux = aux->next;

		}

	}

}

// Dezalocare lista
void dezalocareLista(Nod** cap) {

	while (*cap) {

		Nod* p = *cap;
		*cap = p->next;
		if (p->info.taraEmitenta) {

			free(p->info.taraEmitenta);

		}

		free(p);

	}

}

// Afisare in main
int main() {

	Nod* cap = citireListaMoneziDinFisier("moneda.txt");

	printf("\n=======  Lista monezi  ===============\n");
	afisareListaMonezi(cap);

	printf("\n=======  Moneda amaxima  ===============\n");
	Moneda monedaMax = greutateMaxima(cap);
	printf("Tara emitenta: %s\n", monedaMax.taraEmitenta);
	printf("Valoare: %d\n", monedaMax.valoareN);
	printf("Greutate: %.2f\n", monedaMax.greutate);
	printf("An emitere: %d\n", monedaMax.anEmitere);

	dezalocareLista(&cap);

	printf("\n=======  Lista monezi dupa dezalocare  ===============\n");
	afisareListaMonezi(cap);

	return 0;

}