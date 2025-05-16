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

// Afisare in main
int main() {

	Student s;

	Student s1 = initializareStudent(12, "Popescu Ion", 20, 8.50);
	printf("Id: %d", s1.id);
	printf("Nume: %s", s1.nume);
	printf("Varsta: %d", s1.varsta);
	printf("Medie: %.2f", s1.medie);
	printf("\n\n");

	Student s2 = initializareStudent(12, "Sibila Maria", 25, 9.20);
	printf("Id: %d", s2.id);
	printf("Nume: %s", s2.nume);
	printf("Varsta: %d", s2.varsta);
	printf("Medie: %.2f", s2.medie);
	printf("\n\n");

	Student s3 = initializareStudent(12, "Mateescu Andrei", 23, 7.50);
	printf("Id: %d", s3.id);
	printf("Nume: %s", s3.nume);
	printf("Varsta: %d", s3.varsta);
	printf("Medie: %.2f", s3.medie);
	printf("\n\n");

	int nrStudenti = 3;
	Student* vectorStud = (Student*)malloc(sizeof(Student) * nrStudenti);
	vectorStud[0] = s1;
	vectorStud[1] = s2;
	vectorStud[2] = s3;

	for (int i = 0; i < nrStudenti; i++) {

		afisareStudent(vectorStud[i]);

	}

	// Stiva

	int nr;
	char* buffer[100];
	Nod* stiva = NULL;
	Nod* coadaPrim = NULL;
	Nod* coadaUltim = NULL;

	FILE* f = fopen("student.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++) {

		fscanf(f, "%d", &s.id);
		fscanf(f, "%s", buffer);
		s.nume = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
		strcpy(s.nume, buffer);
		fscanf(f, "%d", &s.varsta);
		fscanf(f, "%.2f", &s.medie);

		push(&stiva, s);
		put(&coadaPrim, &coadaUltim, s);

		free(s.nume);

	}
	fclose(f);

	afisare(stiva);
	Student s5;

	pop(&stiva, &s5);
	afisare(stiva);

	afisare(coadaPrim);

	return 0;

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