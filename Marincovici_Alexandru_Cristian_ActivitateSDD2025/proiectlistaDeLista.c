#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Proiect proiect;
typedef struct nodLS nodLS;
typedef struct nodLP nodLP;

// Creare structura Proiect
typedef struct Proiect {

	unsigned int id;
	char* nume;
	unsigned char caracteristici;
	int* dimensiune;

}Proiect;

// Initializare proiect
Proiect initilaizareProiect(unsigned int id, const char* nume,
	unsigned char caracteristici, int* dimensiune) {

	Proiect p;
	p.id = id;
	p.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(p.nume, nume);
	p.caracteristici = caracteristici;
	for (int i = 0; i < caracteristici; i++) {

		p.dimensiune[i] = dimensiune[i];

	}

	return p;

}

// Afisare Proiect
void afisareProiect(Proiect proiect) {

	printf("Id: %u\n", proiect.id);
	printf("Nume: %s\n", proiect.nume);
	printf("Caracteristici: %u\n", proiect.caracteristici);
	printf("Dimensiune: %d\n", proiect.dimensiune);

}

// Citire din fisier
Proiect citireDinFisier(FILE* f) {

	char buffer[100];
	Proiect p = { 0, NULL, NULL, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.id = atoi(token);

		token = (NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(p.nume, token);

		token = (NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.caracteristici = atoi(token);

		token = (NULL, ",;\n");
		if (token == NULL) {

			return p;

		}
		p.dimensiune = atoi(token);

	}

	return p;

}

// Creare structura Lista simpla - nodLS
typedef struct nodLS {

	Proiect info;
	nodLS* next;

};

// Creare structura Lista principala - nodLP
typedef struct nodeLP {

	nodLS* info;
	nodLP* next;

};

// Inserare in Lista Simpla
nodLS* inserareLS(nodLS* capLS, Proiect p) {

	nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
	nou->info = initilaizareProiect(p.id, p.nume,
		p.caracteristici, p.dimensiune);
	nou->next = NULL;

	if (capLS = NULL) {

		capLS = nou;

	}
	else {

		nodLS* aux = capLS;
		while (aux->next) {

			aux = aux->next;

		}

		aux->next = nou;

	}

	return capLS;

}

//Inserare in Lista Principala
nodLP* inserareLP(nodLP* capLP, nodLS* capLS) {

	nodLP* nou = (nodLP*)malloc(sizeof(nodLP));
	nou->info = capLS;
	nou->next = NULL;

	if (capLP = NULL) {

		capLP = nou;

	}
	else {

		nodLP* aux = capLP;
		while (aux->next) {

			aux = aux->next;

		}

		aux->next = nou;

	}

	return capLP;

}

// Afisare Lista Secundara
void afisareLS(nodLS* capLS) {

	nodLS* aux = capLS;
	while (aux) {

		printf("\n%u, %s, %u, %d\n", aux->info.id, aux->info.nume,
			aux->info.caracteristici, aux->info.dimensiune);
		for (int i = 0; i < aux->info.caracteristici; i++) {

			printf("%d", aux->info.dimensiune[i]);

		}

		printf("\n");
		aux = aux->next;

	}

}

// Afisare Lista Principala
void afisareLP(nodLP* capLP) {

	nodLP* aux = capLP;
	int contor = 1;
	while (aux) {

		printf("Sublista: %d\n", contor++);
		afisareLS(aux->info);
		aux = aux->next;

	}

}