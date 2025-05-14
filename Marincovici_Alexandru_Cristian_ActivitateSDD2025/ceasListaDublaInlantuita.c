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