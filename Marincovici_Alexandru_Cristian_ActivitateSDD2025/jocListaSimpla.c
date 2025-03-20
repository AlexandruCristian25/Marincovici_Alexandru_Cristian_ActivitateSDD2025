#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>;
#include <stdlib.h>;
#include <malloc.h>;
#include <string.h>;

typedef struct Joc {

	unsigned int id;
	char* nume;
	int nrBuc;
	float pret;

}Joc;

//Creare contructor cu parametri
Joc creareJoc(unsigned int id, char* nume, int nrBuc, float pret) {

	Joc j;
	j.id = id;
	j.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(j.nume, nume);
	j.nrBuc = nrBuc;
	j.pret = pret;

	return j;
}

typedef struct nod {

	Joc info;
	struct nod* next;

}nod;

//Inserare nod inceput si sfarsit
nod* inserareInceput(nod* cap, Joc j) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->next = NULL;

	if (cap == NULL) {

		cap = nou;

	}
	else {

		nou->next = cap;
		cap = nou;

	}

	return cap;

}

nod* inserareSfarsit(nod* cap, Joc j) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareJoc(j.id, j.nume, j.nrBuc, j.pret);
	nou->next = NULL;

	if (cap == NULL) {

		cap = nou;

	}
	else {

		nod* aux = cap;
		while (aux->next) {

			aux = aux->next;

		}

		aux->next = nou;

	}

	return cap;

}

