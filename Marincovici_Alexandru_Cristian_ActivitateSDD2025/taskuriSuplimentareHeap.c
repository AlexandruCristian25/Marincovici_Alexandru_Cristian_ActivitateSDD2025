#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Pacient
typedef struct Pacient {

	unsigned int id;
	char* nume;
	int varsta;
	int inaltime;
	int gradUrgenta;

}Pacient;

// Creare structura Heap
typedef struct Heap {

	int lungime;
	Pacient* vector;
	int nrPacienti;

}Heap;

// Citire din fișier
Pacient citireDinFisier(FILE* f) {

	char buffer[100];
	Pacient p = { 0, NULL, 0, 0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return p;
		p.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return p;
		p.nume = (char*)malloc(strlen(token) + 1);
		strcpy(p.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return p;
		p.varsta = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return p;
		p.inaltime = atoi(token);

		token = strtok(NULL, ",;\n");
		if (!token) return p;
		p.gradUrgenta = atoi(token);

	}

	return p;

}

// Functia de afisare a pacientului
void afisarePacienti(Pacient pacient) {

	printf("Id: %u\n", pacient.id);
	printf("Nume: %s\n", pacient.nume);
	printf("Varsta: %d\n", pacient.varsta);
	printf("Inaltime: %d\n", pacient.inaltime);
	printf("Grad Urgenta: %d\n", pacient.gradUrgenta);

}

// Initializare Heap
Heap initializareHeap(int lungime) {

	Heap heap;
	heap.lungime = lungime;
	heap.nrPacienti = 0;
	heap.vector = (Pacient*)malloc(sizeof(Pacient) * lungime);

	return heap;

}

// Functia de filtrare a Heap-ului
void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;

	if (pozFiuSt < heap.nrPacienti && heap.vector[pozMax].id < heap.vector[pozFiuSt].id) {

		pozMax = pozFiuSt;

	}

	if (pozFiuDr < heap.nrPacienti && heap.vector[pozMax].id < heap.vector[pozFiuDr].id) {

		pozMax = pozFiuDr;

	}

	if (pozMax != pozitieNod) {

		Pacient aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;

		if (pozMax <= (heap.nrPacienti - 2) / 2) {

			filtreazaHeap(heap, pozMax);

		}

	}

}

// Citire Heap din fisier
Heap citireHeapPacientDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializareHeap(7);

	while (!feof(f)) {

		heap.vector[heap.nrPacienti++] = citireDinFisier(f);

	}

	fclose(f);

	for (int i = (heap.nrPacienti - 2) / 2; i >= 0; i--) {

		filtreazaHeap(heap, i);

	}

	return heap;

}

// Functie de afisare a Heap-ului
void afisareHeap(Heap heap) {

	for (int i = 0; i < heap.nrPacienti; i++) {

		afisarePacienti(heap.vector[i]);

	}

}

// Functia de afisare a elementelor ascunse din heap
void afiseazaHeapAscuns(Heap heap) {

	for (int i = heap.nrPacienti; i < heap.lungime; i++) {

		afisarePacienti(heap.vector[i]);

	}

}

// Extragere a unui element din Heap
Pacient extragePacient(Heap* heap) {

	if (heap->nrPacienti > 0) {

		Pacient aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrPacienti - 1];
		heap->vector[heap->nrPacienti - 1] = aux;
		heap->nrPacienti--;
		for (int i = (heap->nrPacienti - 2) / 2; i >= 0; i--) {

			filtreazaHeap(*heap, i);

		}

		return aux; // shallow copy

	}

}

// Extragere urgente (cu prioritate pe gradUrgenta)
Pacient extrageUrgente(Heap* heap) {
	Pacient p = { 0, NULL, 0, 0, 0 };

	if (heap->nrPacienti > 0) {
		Pacient aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrPacienti - 1];
		heap->vector[heap->nrPacienti - 1] = aux;
		heap->nrPacienti--;

		for (int i = (heap->nrPacienti - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}

		return aux;
	}

	return p;
}

// Dezalocare Heap
void dezalocareHeap(Heap* heap) {

	for (int i = 0; i < heap->lungime; i++) {

		free(heap->vector[i].nume);

	}

	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrPacienti = 0;

}

// Afisarea in main
int main() {

	Heap heap = citireHeapPacientDinFisier("urgente.txt");
	afisareHeap(heap);

	printf("\n=============  Urgente extrase  ===========\n");
	afisarePacienti(extrageUrgente(&heap));
	afisarePacienti(extrageUrgente(&heap));
	afisarePacienti(extrageUrgente(&heap));
	afisarePacienti(extrageUrgente(&heap));
	afisarePacienti(extrageUrgente(&heap));
	afisarePacienti(extrageUrgente(&heap));
	afisarePacienti(extrageUrgente(&heap));

	printf("\n=============  Heap-ul ascuns  ===========\n");
	afiseazaHeapAscuns(heap);

	printf("\n=========== Urgente extrase (prioritate mare = grad mare) ==========\n");
	while (heap.nrPacienti > 0) {

		afisarePacienti(extrageUrgente(&heap));

	}

	printf("\n=============  Heap-ul dupa dezalocare  ===========\n");
	dezalocareHeap(&heap);

	return 0;

}