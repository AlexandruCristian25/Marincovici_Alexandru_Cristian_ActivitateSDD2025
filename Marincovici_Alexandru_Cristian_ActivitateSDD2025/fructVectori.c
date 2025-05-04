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

// Afisare vector de Fructe
void afisareVector(Fruct* vector, int nrElemente) {

    for (int i = 0; i < nrElemente; i++) {

        afisareFruct(vector[i]);

    }

}

// Copiere primele n elemente
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

// Afisare in main
int main() {

    Fruct* nrFructe = NULL;
    int fructe = 3;

    nrFructe = (Fruct*)malloc(sizeof(Fruct) * fructe);
    nrFructe[0] = initializareFruct(23, "Mar", 10.99f);
    nrFructe[1] = initializareFruct(50, "Para", 7.99f);
    nrFructe[2] = initializareFruct(89, "Cirese", 15.99f);

    printf("Toate fructele:\n");
    afisareVector(nrFructe, fructe);

    // Primele fructe
    int nrPrimeleFructe = 2;
    Fruct* primeleFructe = copiazaPrimeleElemente(nrFructe, fructe, nrPrimeleFructe);
    printf("\nPrimele fructe:\n");
    afisareVector(primeleFructe, nrPrimeleFructe);
    dezalocareVector(&primeleFructe, &nrPrimeleFructe);

    // Fructe scumpe
    Fruct* fructeScumpe = NULL;
    int nrFructeScumpe = 0;
    copiazaFruct(nrFructe, fructe, 7.99f, &fructeScumpe, &nrFructeScumpe);
    printf("\nFructe scumpe:\n");
    afisareVector(fructeScumpe, nrFructeScumpe);
    dezalocareVector(&fructeScumpe, &nrFructeScumpe);

    // Cautare fruct dupa nume
    Fruct fruct = getPrimulFruct(nrFructe, fructe, "Cirese");
    printf("\nFruct gasit:\n");
    afisareFruct(fruct);
    if (fruct.nume != NULL) {
        free(fruct.nume);
        fruct.nume = NULL;
    }

    // Dezalocare finala
    dezalocareVector(&nrFructe, &fructe);

    return 0;

}