#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Student
typedef struct Student {

	unsigned int id;
	char* nume;
	int varsta;
	float medie;

}Student;

// Creare structura Nod
typedef struct Nod {

	Student info;
	struct Nod* stanga;
	struct Nod* dreapta;
	int grad;

}Nod;

// Initializare Student
Student initializareStudent(unsigned int id, const char* nume,
	int varsta, float medie) {

	Student s;
	s.id = id;
	s.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.varsta = varsta;
	s.medie = medie;

	return s;

}

// Creare nod
Nod* creareNod(Student s, Nod* stanga, Nod* dreapta) {

	Nod* nou = (char*)malloc(sizeof(Nod));
	nou->info = initializareStudent(s.id, s.nume, s.varsta, s.medie);
	nou->stanga = stanga;
	nou->dreapta = dreapta;

}

// Cheie de inserare = id
Nod* inserareArbore(Nod* radacina, Student s) {

	if (radacina) {

		if (s.id < radacina->info.id) {

			radacina->stanga = inserareArbore(radacina->stanga, s);
			return radacina;

		}
		else if (s.id > radacina->info.id) {

			radacina->dreapta = inserareArbore(radacina->dreapta, s);
			return radacina;

		}
		else {

			return radacina;

		}

	}

	return creareNod(s, NULL, NULL);

}