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

