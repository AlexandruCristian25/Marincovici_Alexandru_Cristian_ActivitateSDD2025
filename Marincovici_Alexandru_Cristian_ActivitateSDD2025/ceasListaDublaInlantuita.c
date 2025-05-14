#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Carte
typedef struct Carte {

	unsigned int cod;
	char* nume;
	int nrExemplare;
	float pret;

}Carte;

// Functia de initializare
void initilizareCarte(unsigned int cod, const char* nume,
	int nrExemplare, float pret) {

	Carte c;
	c.cod = cod;
	c.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(c.nume, nume);
	c.nrExemplare = nrExemplare;
	c.pret = pret;

}