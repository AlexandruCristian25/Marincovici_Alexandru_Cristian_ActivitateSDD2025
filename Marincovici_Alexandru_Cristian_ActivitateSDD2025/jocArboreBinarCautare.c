#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Joc
typedef struct Joc {

    int cod;
    char* nume;
    float pret;

} Joc;

// Creare structura Nod
typedef struct Nod {

    Joc info;
    struct Nod* stanga;
    struct Nod* dreapta;

} Nod;