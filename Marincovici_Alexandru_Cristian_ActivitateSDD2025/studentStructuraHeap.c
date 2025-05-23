#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Student
typedef struct Student {

	int id;
	char* nume;
	int varsta;
	float medie;

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
		s.nume = (char*)malloc(strlen(token) + 1);
		strcpy(s.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.varsta = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) return s;
		s.medie = atof(token);

	}

	return s;

}

// Functia de afisare a studentului
void afisarePacienti(Student student) {

	printf("Id: %u\n", student.id);
	printf("Nume: %s\n", student.nume);
	printf("Varsta: %d\n", student.varsta);
	printf("Medie: %.2f\n", student.medie);

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
