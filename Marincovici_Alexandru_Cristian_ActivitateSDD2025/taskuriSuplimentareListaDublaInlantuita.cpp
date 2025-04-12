#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creare structura Magazin
typedef struct Magazin {

	unsigned int cod;
	char* denumire;
	int nrProduse;
	float pretP;

} Magazin;

// Funcție de inițializare
Magazin initializareMagazin(unsigned int cod, const char* denumire, int nrProduse, float pretP) {

	Magazin m;
	m.cod = cod;
	m.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(m.denumire, denumire);
	m.nrProduse = nrProduse;
	m.pretP = pretP;
	return m;

}

typedef struct Nod {

	Magazin magazin;
	struct Nod* next;
	struct Nod* prev;

} Nod;

// Citire din fișier
Magazin citireMagazinFisier(FILE* f) {

	char buffer[100];
	Magazin m = { 0, NULL, 0, 0.0f };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return m;
		m.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.denumire = (char*)malloc(strlen(token) + 1);
		strcpy(m.denumire, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.nrProduse = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return m;
		m.pretP = (float)atof(token);

	}

	return m;

}

// Functia de afisare a magazinului
void afisareMagazin(Magazin magazin) {

	printf("Cod: %d\n", magazin.cod);
	printf("Denumire: %s\n", magazin.denumire);
	printf("Nr produse: %d\n", magazin.nrProduse);
	printf("Pret: %.2f\n", magazin.pretP);

}

// Creare Structura lista dubla
typedef struct ListaDubla {

	Nod* first;
	Nod* last;
	int nrNoduri;

} ListaDubla;

// Functia de afisare a listei de magazine de la inceput
void afisareListaMagazineInceput(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareMagazin(p->magazin);
		p = p->next;

	}

}

// Functia de afisare a listei de magazine de la sfarsit
void afisareListaMagazineSfarsit(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afisareMagazin(p->magazin);
		p = p->prev;

	}

}

// Functie de adaugare a unui element la finalul listei 
void adaugaLaFinaltInLista(ListaDubla* lista, Magazin magazinNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->magazin = magazinNou; // shalow copy
	nou->next = NULL;
	nou->prev = lista->last;

	if (lista->last != NULL) {

		lista->last->next = nou;

	}
	else {

		lista->first = nou;

	}

	lista->last = nou;
	lista->nrNoduri++;
}

// Functie de adaugare a unui element la inceputul listei
void adaugaLaInceputtInLista(ListaDubla* lista, Magazin magazinNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->magazin = magazinNou; // shalow copy
	nou->next = lista->first;
	nou->prev = NULL;

	if (lista->first != NULL) {

		lista->first->prev = nou;

	}
	else {


		lista->last = nou;

	}

	lista->first = nou;
	lista->nrNoduri++;

}

// Functie de citire a elemtentelor din fisier
ListaDubla citireLDMagazineDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;

	while (!feof(f)) {

		adaugaLaFinaltInLista(&lista, citireMagazinFisier(f));

	}

	fclose(f);
	return lista;

}

// Functia de dezalocare a listei dublu inlantuite
void dezalocareLista(ListaDubla* lista) {

	Nod* p = lista->first;
	while (p) {

		Nod* aux = p;
		p = p->next;
		if (aux->magazin.denumire != NULL) {

			free(aux->magazin.denumire);

		}

		free(aux);

	}

	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;

}

//Functie de calculare al pretului mediu
float calculeazaPretMediu(ListaDubla lista) {

	if (lista.nrNoduri > 0) {

		float suma = 0;
		Nod* p = lista.first;
		while (p) {

			suma += p->magazin.pretP;
			p = p->next;

		}

		return suma / lista.nrNoduri;

	}

	return 0;

}

// Functie de stergere a pozitiei
void stergePozitie(ListaDubla* lista, int pozitie) {

	if (pozitie < 0 || pozitie >= lista->nrNoduri) return;

	Nod* p = lista->first;
	for (int i = 0; i < pozitie; i++) p = p->next;

	if (p->prev) p->prev->next = p->next;
	else lista->first = p->next;

	if (p->next) p->next->prev = p->prev;
	else lista->last = p->prev;

	free(p->magazin.denumire);
	free(p);
	lista->nrNoduri--;

}

// Inserare sortata crescator dupa cod
void inserareSortata(ListaDubla* lista, Magazin magazinNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->magazin = magazinNou;
	nou->next = nou->prev = NULL;

	if (!lista->first) {

		lista->first = lista->last = nou;

	}
	else {

		Nod* p = lista->first;
		while (p && p->magazin.cod < magazinNou.cod) p = p->next;
		if (!p) {

			nou->prev = lista->last;
			lista->last->next = nou;
			lista->last = nou;

		}
		else if (!p->prev) {

			nou->next = p;
			p->prev = nou;
			lista->first = nou;

		}
		else {

			nou->next = p;
			nou->prev = p->prev;
			p->prev->next = nou;
			p->prev = nou;

		}

	}

	lista->nrNoduri++;

}

// Afisare crescator si descrescator
void afisareMagazin(Magazin magazin) {
	printf("Cod: %d, Denumire: %s, NrProduse: %d, Pret: %.2f\n",
		magazin.cod, magazin.denumire, magazin.nrProduse, magazin.pretP);
}

void afisareCrescator(ListaDubla lista) {

	Nod* p = lista.first;
	while (p) {

		afisareMagazin(p->magazin);
		p = p->next;

	}

}

void afisareDescrescator(ListaDubla lista) {

	Nod* p = lista.last;
	while (p) {

		afisareMagazin(p->magazin);
		p = p->prev;

	}

}

// Salvare in lista simpla cu deep copy
typedef struct NodSimplu {

	Magazin magazin;
	struct NodSimplu* next;

} NodSimplu;

NodSimplu* salvareMagazineFiltrate(ListaDubla lista, int pragProduse) {

	NodSimplu* cap = NULL, * ultim = NULL;
	Nod* p = lista.first;

	while (p) {

		if (p->magazin.nrProduse > pragProduse) {

			NodSimplu* nou = (NodSimplu*)malloc(sizeof(NodSimplu));
			nou->magazin = initializareMagazin(p->magazin.cod, p->magazin.denumire, p->magazin.nrProduse, p->magazin.pretP);
			nou->next = NULL;

			if (!cap) cap = ultim = nou;

			else {

				ultim->next = nou;
				ultim = nou;
			}

		}

		p = p->next;

	}

	return cap;

}

void afisareListaSimpla(NodSimplu* cap) {

	while (cap) {

		afisareMagazin(cap->magazin);
		cap = cap->next;

	}

}

void dezalocareListaSimpla(NodSimplu** cap) {

	while (*cap) {

		NodSimplu* aux = *cap;
		*cap = (*cap)->next;
		free(aux->magazin.denumire);
		free(aux);

	}

}

// Interschimbare elemente pe pozitii
void interschimbaPozitii(ListaDubla* lista, int p1, int p2) {

	if (p1 < 0 || p2 < 0 || p1 >= lista->nrNoduri || p2 >= lista->nrNoduri || p1 == p2) return;

	Nod* n1 = lista->first, * n2 = lista->first;
	for (int i = 0; i < p1; i++) n1 = n1->next;
	for (int i = 0; i < p2; i++) n2 = n2->next;

	Magazin temp = n1->magazin;
	n1->magazin = n2->magazin;
	n2->magazin = temp;

}

//Afisare in main
int main() {

	ListaDubla lista = citireLDMagazineDinFisier("magazin.txt");
	afisareListaMagazineInceput(lista);
	ListaDubla lista = citireLDMagazineDinFisier("magazin.txt");

	printf("\n ======= Afisare lista de la sfarsit ============\n");
	afisareListaMagazineSfarsit(lista);

	printf("\n ======= Calculare pret mediu al magazinelor ============\n");
	printf("\nPretul mediu al magazinelor este de %.2f lei\n", calculeazaPretMediu(lista));

	printf("Lista crescator (dupa cod):\n");
	afisareCrescator(lista);

	printf("\nLista descrescator:\n");
	afisareDescrescator(lista);

	printf("\nStergere pozitie 1:\n");
	stergePozitie(&lista, 1);
	afisareCrescator(lista);

	printf("\nInterchimbare pozitiile 0 si 1:\n");
	interschimbaPozitii(&lista, 0, 1);
	afisareCrescator(lista);

	printf("\nPretul mediu: %.2f\n", calculeazaPretMediu(lista));

	printf("\nLista simpla cu magazine cu peste 10 produse:\n");
	NodSimplu* listaSimpla = salvareMagazineFiltrate(lista, 10);
	afisareListaSimpla(listaSimpla);

	printf("\n ======= Dezalocare lista ============\n");
	dezalocareLista(&lista);
	dezalocareListaSimpla(&listaSimpla);

	return 0;

}