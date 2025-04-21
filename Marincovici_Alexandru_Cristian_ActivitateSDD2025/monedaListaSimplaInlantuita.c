#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Moneda
typedef struct Moneda {

	char* taraEmitenta;
	int valoareN;
	float greutate;
	int anEmitere;

}Moneda;

typedef struct Nod {

	Moneda info;
	struct Nod* next;

}Nod;