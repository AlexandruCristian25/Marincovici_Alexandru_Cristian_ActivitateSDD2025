#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

//Creare lista dubla pentru un folder cu un anumit numar de fisiere
typedef struct Fisier {

	unsigned int id;
	char* numeF;
	int memorie;
	int* nrCopii;

}Fisier;

// Creare contructor cu parametri
Fisier creareFisier(unsigned int id, const char* numeF, int memorie, int* nrCopii) {

	Fisier fs;
	fs.id = id;
	fs.numeF = (char*)malloc(sizeof(char) * strlen(numeF) + 1);
	strcpy_s(fs.numeF, sizeof(char) * strlen(numeF) + 1, numeF);
	fs.memorie = memorie;
	fs.nrCopii = (int*)malloc(sizeof(int));
	for (int i = 0; i < memorie; i++) {

		fs.nrCopii[i] = nrCopii[i];

	}

	return fs;

}

typedef struct nod {

	struct nod* prev;
	Fisier info;
	struct nod* next;

}nod;

typedef struct LD {

	nod* prim;
	nod* ultim;

}LD;


