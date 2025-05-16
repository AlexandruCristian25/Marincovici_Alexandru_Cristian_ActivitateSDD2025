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

} Student;

// Creare structura Nod
typedef struct Nod {

	Student info;
	struct Nod* next;

}Nod;

// Initializare Student
Student initializareStudent(int id, const char* nume,
	int varsta, float medie) {

	Student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.varsta = varsta;
	s.medie = medie;

	return s;

}

// Functia de afisare
void afisareStudent(Student student) {

	printf("Id: %d", student.id);
	printf("Nume: %s", student.nume);
	printf("Varsta: %d", student.varsta);
	printf("Medie: %.2f", student.medie);

}

// Stiva
void push(Nod** stiva, Student s) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializareStudent(s.id, s.nume, s.varsta, s.medie);
	nou->next = NULL;

	if (stiva == NULL) {

		*stiva = nou;

	}
	else {

		nou->next = *stiva;
		*stiva = nou;

	}

}

void pop(Nod** stiva, Student* s) {

	if (*stiva == NULL) {

		return -1;

	}
	else {

		*s = initializareStudent((*stiva)->info.id, (*stiva)->info.nume,
			(*stiva)->info.varsta, (*stiva)->info.medie);
		Nod* temp = (*stiva)->next;
		free((*stiva)->info.nume);
		free((*stiva));
		*stiva = temp;

		return 0;

	}

}

void afisare(Nod* stiva) {

	Nod* aux = stiva;
	while (aux) {

		afisareStudent(aux->info);
		aux = aux->next;

	}

}

// Coada
void put(Nod** prim, Nod** ultim, Student s) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = initializareStudent(s.id, s.nume,
		s.varsta, s.medie);
	nou->next = NULL;

	if (*prim == NULL && *ultim == NULL) {

		*prim = nou;
		*ultim = nou;

	}
	else {

		(*ultim)->next = nou;
		*ultim = nou;

	}

}


int get(Nod** prim, Nod** ultim, Student* s) {

	if (prim == NULL && ultim == NULL) {

		return -1;

	}
	else {

		*s = initializareStudent((*prim)->info.id, (*prim)->info.nume,
			(*prim)->info.varsta, (*prim)->info.medie);
		Nod* temp = (*prim)->next;
		free((*prim)->info.nume);
		free((*prim));
		*prim = temp;

		return 0;

	}

}