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
	return 0;

}