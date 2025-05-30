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

//Afisare si dezalocare
void afisare(nod* cap) {

	nod* aux = cap;
	while (aux->next != cap) {

		printf("%u, %s \n", aux->info.id, aux->info.producator, aux->info.pret);
		aux = aux->next;

	}

	printf("%u, %s \n", aux->info.id, aux->info.producator, aux->info.pret);

}

void dezlocare(nod* cap) {

	nod* aux = cap;
	while (aux->next != cap) {

		free(aux->info.producator);
		nod* temp = aux->next;
		free(aux);
		aux = temp;

	}

	free(aux->info.producator);
	free(aux);

}

//Afisarea in main
void main() {

	int nr;
	Telefon t;
	char* buffer[50];
	nod* cap = NULL;

	FILE* f = fopen("telefon.txt", "r");
	fscanf(f, "%d", &nr);
	for (int i = 0; i < nr; i++) {

		fscanf(f, "%u", &t.id);
		fscanf(f, "%s", buffer);
		t.producator = (char*)malloc(sizeof(buffer) * strlen(buffer) + 1);
		strcpy_s(t.producator, sizeof(buffer) * strlen(buffer) + 1, buffer);
		fscanf(f, "%f", &t.pret);

		cap = inserare(cap, t);
		free(t.producator);

	}

	afisare(cap);

}