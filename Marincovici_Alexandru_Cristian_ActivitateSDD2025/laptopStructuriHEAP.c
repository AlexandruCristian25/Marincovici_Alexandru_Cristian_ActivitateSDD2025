#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Laptop
typedef struct Laptop {

	int id;
	char* producator;
	int nrBuc;
	float pret;

}Student;

// Creare structura Heap
typedef struct Heap {

	int lungime;
	Student* vector;
	int nrStudenti;

}Heap;

// Citire din fisier
Student citireDinFisier(FILE* f) {

	char buffer[100];
	Student s = { 0, NULL, 0, 0.0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) return s;
		s.id = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.producator = (char*)malloc(strlen(token) + 1);
		strcpy(s.producator, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.nrBuc = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.pret = atof(token);

	}

	return s;

}

// Functia de afisare a studentului
void afisarePacienti(Student student) {

	printf("Id: %u\n", student.id);
	printf("Producator: %s\n", student.producator);
	printf("Nr bucati: %d\n", student.nrBuc);
	printf("Pret: %.2f\n", student.pret);

}

// Initializare Heap
Heap initializareHeap(int lungime) {

	Heap heap;
	heap.lungime = lungime;
	heap.nrStudenti = 0;
	heap.vector = (Student*)malloc(sizeof(Student) * lungime);

	return heap;

}

// Functia de filtrare a Heap-ului
void filtreazaHeap(Heap heap, int pozitieNod) {

	int pozFiuSt = 2 * pozitieNod + 1;
	int pozFiuDr = 2 * pozitieNod + 2;
	int pozMax = pozitieNod;

	if (pozFiuSt < heap.nrStudenti && heap.vector[pozMax].id < heap.vector[pozFiuSt].id) {

		pozMax = pozFiuSt;

	}

	if (pozFiuDr < heap.nrStudenti && heap.vector[pozMax].id < heap.vector[pozFiuDr].id) {

		pozMax = pozFiuDr;

	}

	if (pozMax != pozitieNod) {

		Student aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;

		if (pozMax <= (heap.nrStudenti - 2) / 2) {

			filtreazaHeap(heap, pozMax);

		}

	}

}

// Citire Heap din fisier
Heap citireHeapPacientDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	Heap heap = initializareHeap(7);

	while (!feof(f)) {

		heap.vector[heap.nrStudenti++] = citireDinFisier(f);

	}

	fclose(f);

	for (int i = (heap.nrStudenti - 2) / 2; i >= 0; i--) {

		filtreazaHeap(heap, i);

	}

	return heap;

}

// Functie de afisare a Heap-ului
void afisareHeap(Heap heap) {

	for (int i = 0; i < heap.nrStudenti; i++) {

		afisarePacienti(heap.vector[i]);

	}

}

// Functia de afisare a elementelor ascunse din heap
void afiseazaHeapAscuns(Heap heap) {

	for (int i = heap.nrStudenti; i < heap.lungime; i++) {

		afisarePacienti(heap.vector[i]);

	}

}

// Extragere a unui element din Heap
Student extragePacient(Heap* heap) {

	if (heap->nrStudenti > 0) {

		Student aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrStudenti - 1];
		heap->vector[heap->nrStudenti - 1] = aux;
		heap->nrStudenti--;
		for (int i = (heap->nrStudenti - 2) / 2; i >= 0; i--) {

			filtreazaHeap(*heap, i);

		}

		return aux; // shallow copy

	}

}

// Extragere urgente (cu prioritate pe gradUrgenta)
Student extrageUrgente(Heap* heap) {
	Student s = { 0, NULL, 0, 0.0 };

	if (heap->nrStudenti > 0) {
		Student aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrStudenti - 1];
		heap->vector[heap->nrStudenti - 1] = aux;
		heap->nrStudenti--;

		for (int i = (heap->nrStudenti - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}

		return aux;
	}

	return s;

}

// Dezalocare Heap
void dezalocareHeap(Heap* heap) {

	for (int i = 0; i < heap->lungime; i++) {

		free(heap->vector[i].producator);

	}

	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrStudenti = 0;

}

