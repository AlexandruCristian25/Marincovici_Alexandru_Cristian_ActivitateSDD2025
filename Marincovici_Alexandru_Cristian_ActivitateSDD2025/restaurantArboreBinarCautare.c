#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Restaurat
typedef struct Restaurant {

    int nrAngajati;
    char* adresa;
    int nrLivrari;

} Restaurant;

// Creare structura Nod
typedef struct Nod {

    Restaurant info;
    struct Nod* stanga;
    struct Nod* dreapta;

} Nod;