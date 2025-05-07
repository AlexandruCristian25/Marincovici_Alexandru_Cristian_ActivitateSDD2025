#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creare structura Fruct
typedef struct Fruct {

    unsigned int cod;
    char* nume;
    float pret;

} Fruct;

// Initializare Fruct
Fruct initializareFruct(unsigned int cod, const char* nume, float pret) {

    Fruct fr;
    fr.cod = cod;
    fr.nume = (char*)malloc(strlen(nume) + 1);
    strcpy(fr.nume, nume);
    fr.pret = pret;
    return fr;

}

// Afisare Fruct
void afisareFruct(Fruct fruct) {

    printf("Cod: %u, Nume: %s, Pret: %.2f\n", fruct.cod, fruct.nume, fruct.pret);

}

// Copierea primelor n elemente
Fruct* copiazaPrimeleElemente(Fruct* vector, int nrElemente, int nrElementeCopiate) {

    Fruct* vectorNou = (Fruct*)malloc(sizeof(Fruct) * nrElementeCopiate);
    for (int i = 0; i < nrElementeCopiate; i++) {

        vectorNou[i] = vector[i];
        vectorNou[i].nume = (char*)malloc(strlen(vector[i].nume) + 1);
        strcpy(vectorNou[i].nume, vector[i].nume);

    }

    return vectorNou;

}

// Copiere fructe cu pret >= pretMinim
void copiazaFruct(Fruct* vector, int nrElemente, float pretMinim, Fruct** vectorNou, int* dimensiune) {

    *dimensiune = 0;

    for (int i = 0; i < nrElemente; i++) {

        if (vector[i].pret >= pretMinim) {

            (*dimensiune)++;

        }

    }

    if (*vectorNou != NULL) {

        free(*vectorNou);

    }

    *vectorNou = (Fruct*)malloc(sizeof(Fruct) * (*dimensiune));
    int k = 0;
    for (int i = 0; i < nrElemente; i++) {

        if (vector[i].pret >= pretMinim) {

            (*vectorNou)[k] = vector[i];
            (*vectorNou)[k].nume = (char*)malloc(strlen(vector[i].nume) + 1);
            strcpy((*vectorNou)[k].nume, vector[i].nume);
            k++;

        }

    }

}

// Returneaza primul fruct cu numele dat
Fruct getPrimulFruct(Fruct* vector, int nrElemente, const char* nume) {

    Fruct fr;
    fr.nume = NULL;
    for (int i = 0; i < nrElemente; i++) {

        if (strcmp(vector[i].nume, nume) == 0) {

            fr = vector[i];
            fr.nume = (char*)malloc(strlen(vector[i].nume) + 1);
            strcpy(fr.nume, vector[i].nume);
            return fr;

        }

    }

    return fr;

}

// Dezalocare vector
void dezalocareVector(Fruct** vector, int* nrElemente) {

    for (int i = 0; i < *nrElemente; i++) {

        if ((*vector)[i].nume != NULL) {
            free((*vector)[i].nume);

        }

    }

    free(*vector);
    *vector = NULL;
    *nrElemente = 0;

}