#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Haina
typedef struct Haina {

	char* nume;
	char* culoare;
	float pret;

}Haina;

// Creare structura Nod
typedef struct Nod {

	Haina haina;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;