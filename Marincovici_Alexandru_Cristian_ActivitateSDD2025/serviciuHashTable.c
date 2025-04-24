#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Serviciu
typedef struct Serviciu {

	unsigned int id;
	char* tipServiciu;
	char* numeClient;
	float suma;
	unsigned int timp;

}Serviciu;

// Creare structura nod
typedef struct Nod {

	Serviciu serviciu;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;