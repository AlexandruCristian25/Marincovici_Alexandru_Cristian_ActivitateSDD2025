#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura JocVideo
typedef struct JocVideo {

	unsigned int id;
	char* nume;
	int nrCopii;
	float pret;

}JocVideo;

// Creare structura nod
typedef struct Nod {

	JocVideo jocVideo;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
JocVideo citireFisier(FILE* f) {

	char buffer[100];
	JocVideo j = { 0, NULL, 0, 0.0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(j.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.nrCopii = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return j;

		}
		j.pret = atof(token);

	}

	return j;

}

// Afisare Joc Video
void afisareJocVideo(JocVideo jocVideo) {

	printf("Id: %u\n", jocVideo.id);
	printf("Nume: %s\n", jocVideo.nume);
	printf("Nr exemplare: %d\n", jocVideo.nrCopii);
	printf("Pret: %.2f\n", jocVideo.pret);

}