#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Student
typedef struct Student {

	unsigned int cod;
	char* nume;
	int varsta;
	float medie;

}Student;

// Creare structura nod
typedef struct Nod {

	Student student;
	struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

	int dim;
	Nod** tabela;

}HashTable;

// Citire din fisier
Student citireStudentFisier(FILE* f) {

	char buffer[100];
	Student s = { 0, NULL, 0, 0.0 };

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token = strtok(buffer, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.cod = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.nume = (char*)malloc(sizeof(char) * strlen(token) + 1);
		strcpy(s.nume, token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.varsta = atoi(token);

		token = strtok(NULL, ",;\n");
		if (token == NULL) {

			return s;

		}
		s.medie = atof(token);

	}

	return s;

}

// Afisare Student
void afisareStudent(Student student) {

	printf("Cod: %d\n", student.cod);
	printf("Nume: %s\n", student.nume);
	printf("Varsta: %d\n", student.varsta);
	printf("Medie: %.2f\n", student.medie);

}

// Functie de afisare a listei
void afisareListaStudenti(Nod* cap) {

	while (cap) {

		afisareStudent(cap->student);
		cap = cap->next;

	}

}

// Functie de adaugare in lista
void adaugaStudentInLista(Nod* cap, Student studentNou) {

	Nod* p = cap;
	while (p->next) {

		p = p->next;

	}

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->student = studentNou;
	nou->next = NULL;
	p->next = nou;

}

// Initializare HashTable
HashTable initializareHashTable(int dimensiune) {

	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {

		ht.tabela[i] = NULL;

	}

	return ht;

}

// Calcularea hash-ului
int calculeazaHash(const char* nume, int dimensiune) {

	int suma = 0;
	for (int i = 0; i < strlen(nume); i++) {

		suma += nume[i];

	}

	return suma % dimensiune;

}

// Functie de inserare a unui element in tabela
void inserareStudentInTabela(HashTable hash, Student student) {

	int pozitie = calculeazaHash(student.nume, hash.dim);
	if (hash.tabela[pozitie] == NULL) {

		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->student = student;
		hash.tabela[pozitie]->next = NULL;

	}
	else {

		adaugaStudentInLista(hash.tabela[pozitie], student);

	}

}

// Citirea elementelor din fisier
HashTable citireStudentDinFisier(const char* numeFisier, int dimensiune) {

	HashTable hash = initializareHashTable(dimensiune);
	FILE* f = fopen(numeFisier, "r");
	if (!f) {

		printf("Eroare la deschiderea fisierului!\n");
		return hash;

	}
	while (!feof(f)) {

		Student student = citireStudentFisier(f);
		if (student.nume != NULL) {

			inserareStudentInTabela(hash, student);

		}

	}

	fclose(f);
	return hash;

}

// Functie de afisare a tabelei
void afisareTabelaDeStudenti(HashTable ht) {

	for (int i = 0; i < ht.dim; i++) {

		if (ht.tabela[i] != NULL) {

			printf("\nStudentii de pe pozitia %d sunt: \n", i);
			afisareListaStudenti(ht.tabela[i]);

		}
		else {

			printf("\nPe pozitia %d nu avem studenti: \n", i);

		}

	}

}

// Functie de stergere a unui student cu o media cea mai mare din tabela
void stergereStudetnMedieMare(HashTable ht) {

	float max = 0;

	if (ht.tabela) {

		for (int i = 0; i < ht.dim; i++) {
			Nod* aux = ht.tabela[i];
			while (aux) {

				if (max < ht.tabela[i]->student.medie) {

					max = ht.tabela[i]->student.medie;

				}
				aux = aux->next;

			}

		}

		for (int i = 0; i < ht.dim; i++) {

			Nod* aux = ht.tabela[i];
			Nod* prev = NULL;
			while (aux) {

				if (ht.tabela[i]->student.medie == max) {

					Nod* temp = aux;
					if (prev == NULL) {

						ht.tabela[i] = aux->next;
						aux = ht.tabela[i];

					}
					else {

						prev = aux->next;
						aux = aux->next;

					}

					free(temp->student.nume);
					free(temp);

				}
				else {

					prev = aux;
					aux = aux->next;

				}

			}

		}

	}

}
