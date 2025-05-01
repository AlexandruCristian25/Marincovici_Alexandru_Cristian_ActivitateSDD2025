#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Rezervare rezervare;
typedef struct Nod nod;

// Creare astructura Rezervare
struct Rezervare {

	unsigned int id;
	char* hotel;
	char* client;
	int nrCamere;
	float suma;


};

rezervare createRezervare(unsigned int id, char* hotel,
	char* client, int nrCamere, float suma) {

	rezervare r;
	r.id = id;
	r.hotel = (char*)malloc(sizeof(char) * strlen(hotel) + 1);
	strcpy(r.hotel, hotel);
	r.client = (char*)malloc(sizeof(char) * strlen(client) + 1);
	strcpy(r.client, hotel);
	r.nrCamere = nrCamere;
	r.suma = suma;

	return r;

}

struct Nod {

	rezervare info;
	nod* stanga;
	nod* dreapta;

	int grad; // ptr AVL(Arbore echilibrat)

};

nod* creareNod(rezervare r, nod* stanga, nod* dreapta) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = createRezervare(r.id, r.hotel, r.client, r.nrCamere, r.suma);
	nou->stanga = stanga;
	nou->dreapta = dreapta;

	return nou;
}

//Cheie de inserare = id
nod* inserareArbore(nod* radacina, rezervare r) {

	if (radacina) {

		if (r.id < radacina->info.id) {

			radacina->stanga = inserareArbore(radacina->stanga, r);
			return radacina;

		}
		else if (r.id > radacina->info.id) {

			radacina->dreapta = inserareArbore(radacina->dreapta, r);
			return radacina;

		}
		else {

			return radacina;

		}

	}

	return creareNod(r, NULL, NULL);

}

//Radacina Stanga Dreapta
void afisarePreordine(nod* radacina) {

	if (radacina) {

		printf("Grad: %d \n %u %s %s %d %.2f \n", radacina->grad, radacina->info.id, radacina->info.hotel,
			radacina->info.client, radacina->info.nrCamere, radacina->info.suma);
		afisarePreordine(radacina->stanga);
		afisarePreordine(radacina->dreapta);

	}

}

// Recursivitate
int maxim(int a, int b) {

	return a > b ? a : b;

}

int nrNiveluri(nod* radacina) {

	if (radacina) {

		return 1 + maxim(nrNiveluri(radacina->stanga), nrNiveluri(radacina->dreapta));

	}
	else {

		return 0;

	}

}

// Functie de claculare a gradului
void calculGrad(nod* radacina) {

	if (radacina) {

		radacina->grad = (nrNiveluri(radacina->stanga) - nrNiveluri(radacina->dreapta));
		calculGrad(radacina->stanga);
		calculGrad(radacina->dreapta);

	}

}

// Rotire stanga-dreapta
nod* rotireStanga(nod* radacina) {

	nod* x = radacina->dreapta;
	nod* y = x->dreapta;

	x->stanga = radacina;
	radacina->dreapta = y;

	return x;

}

nod* rotireDreapta(nod* radacina) {

	nod* x = radacina->stanga;
	nod* y = x->stanga;

	x->dreapta = radacina;
	radacina->stanga = y;

	return x;

}

nod* rotireStangaDreapta(nod* radacina) {

	radacina->stanga = rotireStanga(radacina->stanga);

	return rotireDreapta(radacina);

}

nod* rotireDreaptaStanga(nod* radacina) {

	radacina->dreapta = rotireDreapta(radacina->dreapta);

	return rotireStanga(radacina);

}

void main() {


	//Structuri
	rezervare r;
	nod* radacina = NULL;


	//Auxiliare pentru citire
	char buffer[100];
	char separator[] = ",";
	char* token;

	FILE* f = fopen("rezervare.txt", "r");
	while (fgets(buffer, 100, f)) {

		token = strtok(buffer, separator);
		r.id = atoi(token);

		token = strtok(NULL, separator);
		r.hotel = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(r.hotel, token);

		token = strtok(NULL, separator);
		r.client = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(r.client, token);

		token = strtok(NULL, separator);
		r.nrCamere = atoi(token);

		token = strtok(NULL, separator);
		r.suma = (float)atof(token);

		radacina = inserareArbore(radacina, r);

		free(r.hotel);
		free(r.client);

	}
	fclose(f);

	int inaltime = nrNiveluri(radacina);
	printf("Inaltime: %d\n", inaltime);

	calculGrad(radacina);

	afisarePreordine(radacina);

	printf("Afisare arbore dezichilibrat:\n");
	radacina = rotireStanga(radacina);
	calculGrad(radacina);
	afisarePreordine(radacina);
	printf("Afisare arbore dupa echilibrare:\n");
	afisarePreordine(radacina);

	//return 0;

}