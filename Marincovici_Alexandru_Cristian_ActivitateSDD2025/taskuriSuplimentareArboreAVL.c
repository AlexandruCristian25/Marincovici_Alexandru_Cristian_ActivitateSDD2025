﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare Structura Magazin
typedef struct Magazin {

	int cod;
	char* numeM;
	int nrProduse;
	float pretP;

}Magazin;

// Creare structura Nod
typedef struct Nod {

	Magazin info;
	struct Nod* stanga;
	struct Nod* dreapta;

}Nod;

// Creare structura vector
typedef struct Vector {

	Magazin* vector;
	int dimensiune;
	int capacitate;

}Vector;

// Creare structura lista simpla inlantuita
typedef struct NodLS {

	Magazin info;
	struct NodLS* next;

}NodLS;

// Creare structura lista dubla inlantuita
typedef struct NodLD {

	Magazin info;
	struct NodLD* prev;
	struct NodLD* next;

}NodLD;

// Initializare Magazin
Magazin initializareMagazin(int cod, const char* numeM,
	int nrProduse, float pretP) {

	Magazin m;
	m.cod = cod;
	m.numeM = (char*)malloc(sizeof(char) * strlen(numeM) + 1);
	strcpy(m.numeM, numeM);
	m.nrProduse = nrProduse;
	m.pretP = pretP;

	return m;

}

// Initializare vector
void initializareVector(Vector* v, int capacitateInitiala) {

	v->vector = (Magazin*)malloc(sizeof(Magazin) * capacitateInitiala);
	v->dimensiune = 0;
	v->capacitate = capacitateInitiala;

}

// Creare nod nou
Nod* creareNod(Magazin m, Nod* stanga, Nod* dreapta) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializareMagazin(m.cod, m.numeM, m.nrProduse, m.pretP);
	nou->stanga = stanga;
	nou->dreapta = dreapta;

	return nou;

}

// Inserare arbore
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

// Inserare final lista simpla
void inserareFinalLS(NodLS** cap, Magazin m) {

	NodLS* nou = (NodLS*)malloc(sizeof(NodLS));
	nou->info = initializareMagazin(m.cod, m.numeM, m.nrProduse, m.pretP);
	nou->next = NULL;

	if (*cap == NULL) {

		*cap = nou;

	}
	else {

		NodLS* temp = *cap;
		while (temp->next) {

			temp = temp->next;

		}

		temp->next = nou;

	}

}

// Inserare final lista dubla
void inserareFinalLD(NodLD** cap, NodLD** coada, Magazin m) {

	NodLD* nou = (NodLD*)malloc(sizeof(NodLD));
	nou->info = initializareMagazin(m.cod, m.numeM, m.nrProduse, m.pretP);
	nou->next = NULL;
	nou->prev = NULL;

	if (*cap == NULL) {

		*cap = *coada = nou;

	}
	else {

		nou->prev = *coada;
		(*coada)->next = nou;
		*coada = nou;

	}

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

// Rad St Dr
void afisarePreordine(Nod* radacina) {

	if (radacina) {

		printf("\n%d %s %d %.2f\n", radacina->info.cod,
			radacina->info.numeM, radacina->info.nrProduse,
			radacina->info.pretP);
		afisarePreordine(radacina->stanga);
		afisarePreordine(radacina->dreapta);

	}

}

// St Rad Dr
void afisareInordine(Nod* radacina) {

	if (radacina) {

		afisareInordine(radacina->stanga);
		printf("\n%d %s %d %.2f\n", radacina->info.cod,
			radacina->info.numeM, radacina->info.nrProduse,
			radacina->info.pretP);
		afisareInordine(radacina->dreapta);

	}

}

// St Dr Rad
void afisarePostordine(Nod* radacina) {

	if (radacina) {

		afisarePostordine(radacina->stanga);
		afisarePostordine(radacina->dreapta);
		printf("\n%d %s %d %.2f\n", radacina->info.cod,
			radacina->info.numeM, radacina->info.nrProduse,
			radacina->info.pretP);

	}

}

// Functia de cautare nod dupa Id
Nod* cautaNod(Nod* radacina, int codCautat) {

	if (radacina == NULL) {

		return NULL;

	}
	if (codCautat == radacina->info.cod) {

		return radacina;

	}
	else if (codCautat < radacina->info.cod) {

		return cautaNod(radacina->stanga, codCautat);

	}
	else {

		return cautaNod(radacina->dreapta, codCautat);

	}

}

// Adaugare in vector
void adaugaInVector(Vector* v, Magazin m) {

	if (v->dimensiune >= v->capacitate) {

		v->capacitate *= 2;
		v->vector = (Magazin*)realloc(v->vector, sizeof(Magazin) * v->capacitate);

	}

	v->vector[v->dimensiune++] = initializareMagazin(m.cod, m.numeM, m.nrProduse, m.pretP);

}

// Afisare lista simpla inlantuita
void afisareLista(NodLS* cap) {

	while (cap) {

		printf("%d %s %d %.2f\n", cap->info.cod, cap->info.numeM, cap->info.nrProduse, cap->info.pretP);
		cap = cap->next;

	}

}

// Afisare lista dubla inlantuita
void afisareListaLD(NodLD* cap) {

	NodLD* temp = cap;
	while (temp) {

		printf("%d %s %d %.2f\n", temp->info.cod, temp->info.numeM,
			temp->info.nrProduse, temp->info.pretP);
		temp = temp->next;

	}

}

void salvarePreordine(Nod* radacina, Vector* v) {

	if (radacina) {

		adaugaInVector(v, radacina->info);
		salvarePreordine(radacina->stanga, v);
		salvarePreordine(radacina->dreapta, v);

	}

}

void salvareInordine(Nod* radacina, Vector* v) {

	if (radacina) {

		salvareInordine(radacina->stanga, v);
		adaugaInVector(v, radacina->info);
		salvareInordine(radacina->dreapta, v);

	}

}

/// Afisare Preordine Inorde Postordine Vector
void salvarePreordine(Nod* radacina, Vector* v) {

	if (radacina) {

		adaugaInVector(v, radacina->info);
		salvarePreordine(radacina->stanga, v);
		salvarePreordine(radacina->dreapta, v);

	}

}

void salvareInordine(Nod* radacina, Vector* v) {

	if (radacina) {

		salvareInordine(radacina->stanga, v);
		adaugaInVector(v, radacina->info);
		salvareInordine(radacina->dreapta, v);

	}

}


void salvarePostordine(Nod* radacina, Vector* v) {

	if (radacina) {

		salvarePostordine(radacina->stanga, v);
		salvarePostordine(radacina->dreapta, v);
		adaugaInVector(v, radacina->info);

	}

}

//Afisare Preordine Inorde Postordine Lista Simpla
void salvarePreordineLS(Nod* radacina, NodLS** cap) {

	if (radacina) {

		inserareFinalLS(cap, radacina->info);
		salvarePreordineLS(radacina->stanga, cap);
		salvarePreordineLS(radacina->dreapta, cap);

	}

}

void salvareInordineLS(Nod* radacina, NodLS** cap) {

	if (radacina) {

		salvareInordineLS(radacina->stanga, cap);
		inserareFinalLS(cap, radacina->info);
		salvareInordineLS(radacina->dreapta, cap);

	}

}

void salvarePostordineLS(Nod* radacina, NodLS** cap) {

	if (radacina) {

		salvarePostordineLS(radacina->stanga, cap);
		salvarePostordineLS(radacina->dreapta, cap);
		inserareFinalLS(cap, radacina->info);

	}

}

//Afisare Preordine Inorde Postordine Lista Dubla inlantuita
void salvarePreordineLD(Nod* radacina, NodLD** cap, NodLD** coada) {

	if (radacina) {

		inserareFinalLD(cap, coada, radacina->info);
		salvarePreordineLD(radacina->stanga, cap, coada);
		salvarePreordineLD(radacina->dreapta, cap, coada);
	}

}

void salvareInordineLD(Nod* radacina, NodLD** cap, NodLD** coada) {

	if (radacina) {

		salvareInordineLD(radacina->stanga, cap, coada);
		inserareFinalLD(cap, coada, radacina->info);
		salvareInordineLD(radacina->dreapta, cap, coada);
	}

}

void salvarePostordineLD(Nod* radacina, NodLD** cap, NodLD** coada) {

	if (radacina) {

		salvarePostordineLD(radacina->stanga, cap, coada);
		salvarePostordineLD(radacina->dreapta, cap, coada);
		inserareFinalLD(cap, coada, radacina->info);

	}

}

// Dezalocare arbore
void dezalocareArbore(Nod* radacina) {

	if (radacina) {

		Nod* tempStanga = radacina->stanga;
		Nod* tempDreapta = radacina->dreapta;
		dezalocareArbore(radacina->stanga);
		dezalocareArbore(radacina->dreapta);
		free(radacina->info.numeM);
		free(radacina);

	}

}

// Dezalocare vector
void dezalocareVector(Vector* v) {

	for (int i = 0; i < v->dimensiune; i++) {

		free(v->vector[i].numeM);

	}

	free(v->vector);
	v->dimensiune = 0;
	v->capacitate = 0;

}

// Dezalocare lista simpla inlantuita
void dezalocareLista(NodLS** cap) {

	while (*cap) {

		NodLS* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.numeM);
		free(temp);

	}

}

// Dezalocare lista dubla inlantuita
void dezalocareListaLD(NodLD** cap) {

	while (*cap) {

		NodLD* temp = *cap;
		*cap = (*cap)->next;
		free(temp->info.numeM);
		free(temp);

	}

}

// Afisare in main
int main() {

	Magazin m;
	Nod* radacina = NULL;

	char buffer[100];
	char separator[] = ",";
	char* token;

	FILE* f = fopen("magazin.txt", "r");
	while (fgets(buffer, 100, f)) {

		token = strtok(buffer, separator);
		m.cod = atoi(token);

		token = strtok(NULL, separator);
		m.numeM = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(m.numeM, token);

		token = strtok(NULL, separator);
		m.nrProduse = atoi(token);

		token = strtok(NULL, separator);
		m.pretP = atof(token);

		radacina = inserareArbore(radacina, m);
		free(m.numeM);

	}
	fclose(f);

	afisarePreordine(radacina);

	int codDeCautat = 10;

	Nod* nodGasit = cautaNod(radacina, codDeCautat);
	if (nodGasit) {

		printf("\nNod gasit: %d %s %d %.2f\n",
			nodGasit->info.cod,
			nodGasit->info.numeM,
			nodGasit->info.nrProduse,
			nodGasit->info.pretP);

	}
	else {

		printf("\nNod cu codul %d nu a fost găsit.\n", codDeCautat);

	}

	Vector vectorPre;
	initializareVector(&vectorPre, 10);
	salvarePreordine(radacina, &vectorPre);

	printf("\nAfisare rezultate: \n");
	for (int i = 0; i < vectorPre.dimensiune; i++) {
		printf("%d %s %d %.2f\n",
			vectorPre.vector[i].cod,
			vectorPre.vector[i].numeM,
			vectorPre.vector[i].nrProduse,
			vectorPre.vector[i].pretP);
	}

	printf("\nAfisare lista simpla inlantuita: \n");
	NodLS* lista = NULL;
	salvareInordineLS(radacina, &lista);
	afisareLista(lista);
	dezalocareLista(&lista);

	printf("\nAfisare lista dubla inlantuita: \n");
	NodLD* capLD = NULL;
	NodLD* coadaLD = NULL;

	salvareInordineLD(radacina, &capLD, &coadaLD);
	afisareListaLD(capLD);
	dezalocareListaLD(&capLD);

	dezalocareArbore(radacina);

	return 0;

}
