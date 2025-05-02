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

// Functia de afiare a listei
void afisareLista(Nod* cap) {

	while (cap) {

		afisareJocVideo(cap->jocVideo);
		cap = cap->next;

	}

}

// Functia de adaugare in lista
void adaugaJocVideoInLista(Nod* cap, JocVideo jocNou) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->jocVideo = jocNou;
	nou->next = NULL;
	p->next = nou;

}

// Initializare HashTable
HashTable initializareHashTable(int dimensiune) {

	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {

		ht.tabela[i] = NULL;

	}

	return ht;

}

// Calculeaza hash-ul 
int calculeazaHash(const char* nume, int dimensiune) {

	int suma = 0;
	for (int i = 0; i < strlen(nume); i++) {

		suma += nume[i];

	}

	return suma % dimensiune;

}

// Functia de inserare a unui element in tabela
void inserareJocVideoInTabela(HashTable hash, JocVideo jocVideo) {

	int pozitie = calculeazaHash(jocVideo.nume, hash.dim);
	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->jocVideo = jocVideo;
		hash.tabela[pozitie]->next = NULL;

	}
	else {

		adaugaJocVideoInLista(hash.tabela[pozitie], jocVideo);

	}

}

// Citirea elementelor din fisier
HashTable citireJocVideoDinFisier(const char* numeFisier, int dimensiune) {

	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {

		printf("\nEroare la deschiderea fisierului!\n");
		return hash;

	}

	while (!feof(f)) {

		JocVideo jocVideo = citireFisier(f);
		if (jocVideo.nume != NULL) {

			inserareJocVideoInTabela(hash, jocVideo);

		}

	}

	fclose(f);
	return hash;

}
