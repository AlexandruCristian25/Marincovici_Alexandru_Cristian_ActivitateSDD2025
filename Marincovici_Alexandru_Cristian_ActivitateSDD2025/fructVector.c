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