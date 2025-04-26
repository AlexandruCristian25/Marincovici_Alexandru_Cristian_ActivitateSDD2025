#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Monitor
typedef struct Monitor {

	unsigned int cod;
	char* producator;
	float diagonala;
	int nrPorturi;

}Monitor;

// Functia de initializare
Monitor initializareMonitor(unsigned int cod, char* producator,
	float diagonala, int nrPorturi) {

	Monitor m;
	m.cod = cod;
	m.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(m.producator, producator);
	m.diagonala = diagonala;
	m.nrPorturi = nrPorturi;

	return m;

}

// Citire din fisier
Monitor citireFisier(FILE* f) {

	char buffer[100];
	Monitor m = { 0, NULL, 0.0f, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.producator = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(m.producator, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.diagonala = (float)atof(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return m;

		}
		m.nrPorturi = atoi(token);

	}

	return m;

}

// Nod lista simpla
typedef struct Nod {

	Monitor info;
	struct Nod* next;

}Nod;