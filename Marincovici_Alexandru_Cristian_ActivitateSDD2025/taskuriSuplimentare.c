#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//Nume Marincovici Alexandru, prima litera din nume este M iar cea din prenume este A vom construi clasa Magazin
typedef struct Magazin {

	unsigned int cod;
	char* denumire;
	int nrProduse;
	float pretP;

}Magazin;

//Initializare magazin
Magazin initializareMagazin(unsigned int cod, const char* denumire, int nrProduse, float pretP) {

	Magazin m;
	m.cod = 1;
	m.denumire = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
	strcpy(m.denumire, denumire);
	m.nrProduse = nrProduse;
	m.pretP = pretP;
	return m;

}

//Afisarea magazinului
void afisareMagazin(Magazin m) {

	if (m.denumire != NULL) {

		printf("%d. Magazinul %s are %d de produse, iar pretul produsului este de %5.2f lei. \n",
			m.cod, m.denumire, m.nrProduse, m.pretP);

	}
	else {

		printf("%d. Magazinul are %d de produse, iar pretul produsului este de %5.2f lei. \n",
			m.cod, m.nrProduse, m.pretP);

	}

}

// Funcție pentru modificarea prețului 
void modificaPret(Magazin* m, float noulPret) {

	if (noulPret > 0) {

		m->pretP = noulPret;

	}

}

// Funcție pentru calculul prețului mediu al produselor
float calculMediePreturi(Magazin m) {

	if (m.nrProduse == 0) {

		return 0;

	}

	return m.pretP / m.nrProduse;
}

//Funcita de afisare a vectorului
void afisareVector(Magazin* vector, int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisareMagazin(vector[i]);

	}

}

//Functie de copiere a doua atribute dintr-un vector alocat dinamic intr-un vector nou 
Magazin* copiazaPrimeleElemente(Magazin* vector, int nrElemente,
	int nrElementeCopiate) {

	Magazin* vectorNou = NULL;
	vectorNou = (Magazin*)malloc(sizeof(Magazin) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {

		vectorNou[i] = vector[i];
		vectorNou[i].denumire = (char*)malloc(sizeof(char) * strlen(vector[i].denumire) + 1);
		strcpy(vectorNou[i].denumire, vector[i].denumire);

	}

	return vectorNou;

}

//Functie de copiere a unui atribut conditionat dintr-un vector alocat dinamic intr-un vector nou
void copiazaProduseScumpe(Magazin* vector, char nrElemente, float pretMinim, Magazin** vectorNou, int* dimensiune) {

	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {

		if (vector[i].pretP >= pretMinim) {

			(*dimensiune)++;

		}

	}

	if ((*vectorNou) != NULL) {

		free(*vectorNou);

	}

	*vectorNou = (Magazin*)malloc(sizeof(Magazin) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {

		if (vector[i].pretP >= pretMinim) {

			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].denumire = (char*)malloc(sizeof(char) * strlen(vector[i].denumire) + 1);
			strcpy((*vectorNou)[k].denumire, vector[i].denumire);
			k++;

		}

	}

}

//Functia de dezalocare
void dezalocare(Magazin* m) {

	if (m->denumire != NULL) {

		free(m->denumire);
		m->denumire = NULL;

	}

}

//Afisarea in main
int main() {

	Magazin m;
	m = initializareMagazin(1, "Magazin1", 50, 14.36);
	afisareMagazin(m);
	modificaPret(&m, 12);
	afisareMagazin(m);
	printf("\nMedia preturilor: %.2f\n", calculMediePreturi(m));
	dezalocare(&m);
	afisareMagazin(m);

	//Vector alocat dinamic cu 5 obiecte
	Magazin* magazine = NULL;
	int nrMagazine = 5;
	magazine = (Magazin*)malloc(sizeof(Magazin) * nrMagazine);
	magazine[0] = initializareMagazin(1, "Auchan", 25, 9.99);
	magazine[1] = initializareMagazin(2, "Carrefour", 36, 7.50);
	magazine[2] = initializareMagazin(3, "MegaImage", 50, 3.25);
	magazine[3] = initializareMagazin(4, "Kaufland", 75, 1.20);
	magazine[4] = initializareMagazin(5, "LIDL", 58, 4.36);

	afisareVector(magazine, nrMagazine);


	return 0;

}