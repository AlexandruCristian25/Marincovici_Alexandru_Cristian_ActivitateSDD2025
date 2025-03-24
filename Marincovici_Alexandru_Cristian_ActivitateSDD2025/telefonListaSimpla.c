#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>;
#include <stdlib.h>;
#include <malloc.h>;
#include <string.h>;

typedef struct Telefon {

	unsigned int id;
	char* producator;
	float pret;

}Telefon;

typedef struct nod {

	Telefon info;
	struct nod* next;

}nod;

//Creare contructor cu parametri
Telefon initializareTelefon(int id, const char* producator, float pret) {

	Telefon t;
	t.id = id;
	t.producator = (char*)malloc(sizeof(producator) * strlen(producator) + 1);
	strcpy_s(t.producator, sizeof(producator) * strlen(producator) + 1, producator);
	t.pret = pret;

	return t;

}

//Inserare nod inceput
nod* inserareInceput(nod* cap, Telefon t) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = initializareTelefon(t.id, t.producator, t.pret);
	nou->next = NULL;
	if (cap == NULL) {

		cap = nou;
		nou->next = cap;

	}
	else {

		nod* aux = cap;
		while (aux->next != cap) {

			aux = aux->next;

		}

		aux->next = nou;
		aux->next = cap;

	}

	return cap;

}