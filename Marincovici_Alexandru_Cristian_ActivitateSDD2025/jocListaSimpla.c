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

//Afisare si dezalocare
void afisare(nod* cap) {

	nod* aux = cap;
	while (aux) {

		printf("%u, %s, %u, %2.3f \n", aux->info.id, aux->info.nume,
			aux->info.nrBuc, aux->info.pret);
		aux = aux->next;

	}

}

void dezalocare(nod* cap) {

	nod* aux = cap;
	free(aux->info.nume);
	nod* temp = aux->next;
	free(aux);
	aux = temp;

}

//Afisarea in main
void main() {

	Joc j;
	nod* cap = NULL;
	char buffer[50];
	int nr;

	FILE* f = fopen("jocuri.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++) {

		fscanf(f, "%d", &j.id);
		fscanf(f, "%d", &j.id);
		j.nume = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
		strcpy(j.nume, buffer);
		fscanf(f, "%d", &j.id);
		fscanf(f, "%d", &j.id);

		cap = inserareSfarsit(cap, j);
		free(j.nume);

	}

	fclose(f);
	afisare(cap);
	dezalocare(cap);

}