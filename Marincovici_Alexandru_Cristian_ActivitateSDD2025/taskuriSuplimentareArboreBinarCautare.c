#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Magazin
typedef struct Magazin {

	unsigned int cod;
	char* denumire;
	int nrProduse;
	float pretP;

}Magazin;

// Creare Structura Nod
typedef struct Nod {

	Magazin info;
	struct Nod* stanga;
	struct Nod* dreapta;

}Nod;

// Initalizare Magazin
Magazin initializareMagazin(unsigned int cod, const char* denumire,
	int nrProduse, float pretP) {

	Magazin m;
	m.cod = cod;
	m.denumire = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
	strcpy(m.denumire, denumire);
	m.nrProduse = nrProduse;
	m.pretP = pretP;

	return m;

}

// Creare nod
Nod* creareNod(Magazin m, Nod* stanga, Nod* dreapta) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializareMagazin(m.cod, m.denumire,
		m.nrProduse, m.pretP);
	nou->stanga = stanga;
	nou->dreapta = dreapta;

	return nou;

}

// Inserare Arbore
Nod* inserareArbore(Nod* radacina, Magazin m) {

	if (radacina) {

		if (m.cod < radacina->info.cod) {

			radacina->stanga = inserareArbore(radacina->stanga, m);
			return radacina;

		}
		else if (m.cod > radacina->info.cod) {

			radacina->dreapta = inserareArbore(radacina->dreapta, m);
			return radacina;

		}
		else {

			return radacina;

		}

	}

	return creareNod(m, NULL, NULL);

}

// Recursivitate
int maxim(int a, int b) {

	return a > b ? a : b;

}

int nrNiveluri(Nod* radacina) {

	if (radacina) {

		return 1 + maxim(nrNiveluri(radacina->stanga), nrNiveluri(radacina->dreapta));

	}
	else {

		return 0;

	}

}

// Functia de afisare preordine(Rad St Dr)
void afisarePreordine(Nod* radacina) {

	if (radacina) {

		printf("\n%u %s %d %.2f\n", radacina->info.cod,
			radacina->info.denumire, radacina->info.nrProduse,
			radacina->info.pretP);
		afisarePreordine(radacina->stanga);
		afisarePreordine(radacina->dreapta);

	}

}