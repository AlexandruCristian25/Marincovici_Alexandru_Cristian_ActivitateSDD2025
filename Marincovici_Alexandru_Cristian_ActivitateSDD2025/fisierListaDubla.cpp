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

//Inserare nod inceput si nod final

void inserareInceput(LD* lista, Fisier fs) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->prev = NULL;
	nou->info = creareFisier(fs.id, fs.numeF, fs.memorie, fs.nrCopii);
	nou->next = NULL;
	if (lista->prim == NULL) {

		lista->prim = nou;
		lista->ultim = nou;

	}
	else {

		nou->next = lista->prim;
		lista->prim->prev = nou;
		lista->prim = nou;

	}

}

LD inserareFinal(LD lista, Fisier fs) {

	nod* nou = (nod*)malloc(sizeof(nod));
	nou->prev = NULL;
	nou->info = creareFisier(fs.id, fs.numeF, fs.memorie, fs.nrCopii);
	nou->next = NULL;
	if (lista.prim == NULL) {

		lista.prim = nou;
		lista.ultim = nou;

	}
	else {

		lista.ultim->next = nou;
		nou->prev = lista.ultim;
		lista.ultim = nou;

	}
	return lista;

}

//Afisare nod inceput si final
void afisareInceput(LD lista) {

	if (lista.prim) {

		nod* aux = lista.prim;
		while (aux) {

			printf("Id: %u \n", aux->info.id);
			printf("Nume fisier: %s \n", aux->info.numeF);
			printf("Memorie: %d \n", aux->info.memorie);

			for (int i = 0; i < aux->info.memorie; i++) {

				printf("Nr copii: %d, ", aux->info.nrCopii[i]);

			}
			printf("\n\n");
			aux = aux->next;

		}

	}
	else {

		printf("Lista este goala!");

	}

}

void afisareFinal(LD lista) {

	if (lista.ultim) {

		nod* aux = lista.ultim;
		while (aux) {

			printf("Id: %u \n", aux->info.id);
			printf("Nume fisier: %s \n", aux->info.numeF);
			printf("Memorie: %d \n", aux->info.memorie);

			for (int i = 0; i < aux->info.memorie; i++) {

				printf("Nr copii: %d, ", aux->info.nrCopii[i]);

			}
			printf("\n\n");
			aux = aux->prev;

		}

	}

}


