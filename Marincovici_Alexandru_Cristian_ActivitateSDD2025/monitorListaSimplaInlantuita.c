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

// Afisare lista monitoare
void afisareListaMonitoare(Nod* cap) {

	while (cap != NULL) {

		afisareMonitor(cap->info);
		cap = cap->next;

	}

}

// Adaugare monitor la sfarsit
void adaugaMonitorInLista(Nod** cap, Monitor monitorNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = monitorNou;
	nou->next = NULL;

	if (*cap) {

		Nod* p = *cap;
		while (p->next != NULL) {

			p = p->next;

		}

		p->next = nou;

	}
	else {

		*cap = nou;

	}

}

// Citire lista din fisier
Nod* citireListaDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {

		while (!feof(f)) {

			Monitor m = citireFisier(f);

			if (m.producator != NULL) {

				adaugaMonitorInLista(&cap, m);

			}

		}

		fclose(f);

	}
	else {

		printf("\nFisierul nu a putut fi deschis\n");

	}

	return cap;

}

// Dezalocare lista
void dezalocareLista(Nod** cap, int* nrMonitoare) {

	while (*cap) {

		Nod* p = *cap;
		*cap = p->next;
		if (p->info.producator) {

			free(p->info.producator);

		}

		free(p);
		(*nrMonitoare)++;

	}

}

// Afisare in main
int main() {

	Nod* cap = citireListaDinFisier("monitor.txt");
	afisareListaMonitoare(cap);

	int nrMonitoare = 0;
	dezalocareLista(&cap, &nrMonitoare);

	return 0;

}