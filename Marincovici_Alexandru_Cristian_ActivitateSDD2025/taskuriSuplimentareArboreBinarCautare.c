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

// Functia de dezalocare
void dezalocareArbore(Nod* radacina) {

	Nod* tempStanga = radacina->stanga;
	Nod* tempDreapta = radacina->dreapta;
	free(radacina->info.denumire);
	free(radacina);
	dezalocareArbore(radacina->stanga);
	dezalocareArbore(radacina->dreapta);

}

// Stergere nod dupa Id
Nod* gasesteMinim(Nod* radacina) {
	while (radacina->stanga) {
		radacina = radacina->stanga;
	}
	return radacina;
}

Nod* stergereNod(Nod* radacina, unsigned int cod) {
	if (!radacina) return NULL;

	if (cod < radacina->info.cod) {
		radacina->stanga = stergereNod(radacina->stanga, cod);
	}
	else if (cod > radacina->info.cod) {
		radacina->dreapta = stergereNod(radacina->dreapta, cod);
	}
	else {
		// Nod gasit
		if (!radacina->stanga && !radacina->dreapta) {

			free(radacina->info.denumire);
			free(radacina);

			return NULL;

		}
		else if (!radacina->stanga || !radacina->dreapta) {

			Nod* copil = radacina->stanga ? radacina->stanga : radacina->dreapta;
			free(radacina->info.denumire);
			free(radacina);

			return copil;

		}
		else {

			Nod* minimDreapta = gasesteMinim(radacina->dreapta);
			free(radacina->info.denumire);
			radacina->info = initializareMagazin(minimDreapta->info.cod,
				minimDreapta->info.denumire,
				minimDreapta->info.nrProduse,
				minimDreapta->info.pretP);
			radacina->dreapta = stergereNod(radacina->dreapta, minimDreapta->info.cod);

		}
	}

	return radacina;

}

// Functia radacina primita ca parametru
Nod* subarboreInalt(Nod* radacina) {

	if (!radacina) {

		return NULL;

	}

	int inaltimeStanga = nrNiveluri(radacina->stanga);
	int inaltimeDreapta = nrNiveluri(radacina->dreapta);

	if (inaltimeStanga > inaltimeDreapta) {

		return radacina->stanga;

	}
	else if (inaltimeDreapta > inaltimeStanga) {

		return radacina->dreapta;

	}
	else {

		return NULL;

	}

}

// Functie pentru nod radacina primit
int numarNoduriSubordine(Nod* radacina) {

	if (!radacina) {

		return 0;

	}

	int total = 0;

	if (radacina->stanga) {

		total += 1 + numarNoduriSubordine(radacina->stanga);

	}

	if (radacina->dreapta) {

		total += 1 + numarNoduriSubordine(radacina->dreapta);

	}

	return total;

}
