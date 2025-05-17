#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Film
typedef struct Film {

	unsigned int id;
	char* numeF;
	int nrActori;
	float pretBilet;

}Film;

// Creare structura Nod
typedef struct Nod {

	Film film;
	struct Nod* next;
	struct Nod* prev;

}Nod;

// Functia de initializare
Film initialiareFilm(unsigned int id, const char numeF,
	int nrActori, float pretBilet) {

	Film fi;
	fi.id = id;
	fi.numeF = (char*)malloc(sizeof(char) * strlen(numeF) + 1);
	strcpy(fi.numeF, numeF);
	fi.nrActori = nrActori;
	fi.pretBilet = pretBilet;

	return fi;

}