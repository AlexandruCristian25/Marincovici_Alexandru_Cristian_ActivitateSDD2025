#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//Creare strcutura laptop
typedef struct Laptop {

	unsigned int id;
	char* producator;
	int RAM;
	float pretL;

}Laptop;

//Intializare laptop
Laptop initializareLaptop(unsigned int id, const char* producator,
	int RAM, float pretL) {

	Laptop l;
	l.id = id;
	l.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(l.producator, producator);
	l.RAM = RAM;
	l.pretL = pretL;

}

//Afisare laptop
void afisareLaptop(Laptop l) {

	if (l.producator != NULL) {

		printf("\n%d. Laptopul %s are %d RAM cu pretul de %5.2f lei\n",
			l.id, l.producator, l.RAM, l.pretL);

	}
	else {

		printf("\n%d. Laptopul are %d RAM cu pretul de %5.2f lei\n",
			l.id, l.RAM, l.pretL);

	}

}

//Functia pentru modificarea RAM-ului
void modificaRAM(Laptop* l, int ramNou) {

	if (ramNou > 0) {

		l->RAM = ramNou;

	}

}

//Functie pentru calcularea pretului mediu al laptopului
float calculeazaMediePret(Laptop l) {

	if (l.RAM > 0) {

		return 0;

	}

}

//Functia de dezalocare
void dezalocare(Laptop* l) {

	if (l->producator != NULL) {

		free(l->producator);
		l->producator = NULL;

	}

}

//Afisarea in main
int main() {

	Laptop l;
	l = initializareLaptop(1, "ASUS", 16, 3599.99);
	afisareLaptop(l);
	printf("\n\n");

	afisareLaptop(l);
	printf("\nMedia pretului este de: \n", calculeazaMediePret(l));
	dezalocare(&l);
	afisareLaptop(l);

}