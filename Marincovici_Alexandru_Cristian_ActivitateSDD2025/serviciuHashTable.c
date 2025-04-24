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

// Citire din fisier
Serviciu citireFisier(FILE* f) {

	char buffer[100];
	Serviciu s = { 0, NULL, NULL, 0.0f, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.id = atoi(token);

		token = strtok(NULL, ",;/n");
		if (token == NULL) {

			return s;

		}
		s.tipServiciu = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(s.tipServiciu, token);

		token = strtok(NULL, ",;/n");
		if (token == NULL) {

			return s;

		}
		s.numeClient = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(s.numeClient, token);

		token = strtok(NULL, ",;/n");
		if (token == NULL) {

			return s;

		}
		s.suma = (float)atof(token);

		token = strtok(NULL, ",;/n");
		if (token == NULL) {

			return s;

		}
		s.timp = atoi(token);

	}

	return s;

}