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

// Initializare Restaurant
Restaurant initializareRestaurant(int nrAngajati,
    const char* adresa, int nrLivrari) {

    Restaurant r;
    r.nrAngajati = nrAngajati;
    r.adresa = (char*)malloc(sizeof(char) * (strlen(adresa) + 1));
    strcpy(r.adresa, adresa);
    r.nrLivrari = nrLivrari;

    return r;

}

// Creare nod in arbore
Nod* creareNod(Restaurant r, Nod* stanga, Nod* dreapta) {

    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = initializareRestaurant(r.nrAngajati,
        r.adresa, r.nrLivrari);
    nou->stanga = stanga;
    nou->dreapta = dreapta;

    return nou;

}