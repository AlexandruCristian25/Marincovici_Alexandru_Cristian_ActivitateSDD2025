#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//Am creat o lista simpla cu un numar e calatori si destinatii

typedef struct Calatorie {

	unsigned int nrCalatorie;
	char* destinatie;
	int nrPersoane;
	float pret;

}Calatorie;

//Creare constructor cu parametri

Calatorie creareCalatorie(unsigned int nrCalatorie, char* destinatie, int nrPersoane, float pret) {

	Calatorie c;
	c.nrCalatorie = nrCalatorie;
	c.destinatie = (char*)malloc(sizeof(char) * strlen(destinatie) + 1);
	strcpy(c.destinatie, destinatie);
	c.nrPersoane = nrPersoane;
	c.pret = pret;

	return c;

}

typedef struct nod {

	Calatorie info;
	struct nod* next;

}nod;

//creare nod

nod* inserareInceput(nod* cap, Calatorie c) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = c;
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

//Am inserat nodul final

nod* inserareFinal(nod* cap, Calatorie c) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = creareCalatorie(c.nrCalatorie, c.destinatie, c.nrPersoane, c.pret);
	nou->next = NULL;

	if (cap == NULL) {

		cap = nou;

	}
	else {

		nod* aux = cap;
		while (aux->next) {

			aux = aux->next;

		}

		aux = aux->next;

	}

	return cap;

}

//Vectorul de afisare

void afisare(nod* cap) {

	nod* aux = cap;
	while (aux) {

		printf("%u, %s, %u, %1.2f \n", aux->info.nrCalatorie, aux->info.destinatie,
			aux->info.nrPersoane, aux->info.pret);
		aux = aux->next;

	}

}

//Am dezalocat memoria

void dezalocare(nod* cap) {

	nod* aux = cap;
	while (aux) {

		free(aux->info.destinatie);
		nod* temp = aux->next;
		free(aux);
		aux = temp;

	}

}

//Afisam in main

void main() {

	Calatorie c;
	nod* cap = NULL;
	char buffer[50];
	int nr;
	FILE* f = fopen("calatorii.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++) {

		fscanf(f, "%u", &c.nrCalatorie);
		fscanf(f, "%s", buffer);
		c.destinatie = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
		strcpy(c.destinatie, buffer);
		fscanf(f, "%u", &c.nrPersoane);
		fscanf(f, "%f", &c.pret);

		cap = inserareFinal(cap, c);
		free(c.destinatie);

	}

	fclose(f);
	afisare(cap);
	dezalocare(cap);

}