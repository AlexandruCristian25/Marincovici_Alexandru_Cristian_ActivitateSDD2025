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

typedef struct nod {

	Joc info;
	struct nod* next;

}nod;