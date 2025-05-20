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

// Inserare nod in arbore dupa cod
Nod* inserareArbore(Nod* radacina, Restaurant r) {

    if (radacina) {

        if (r.nrAngajati < radacina->info.nrAngajati) {

            radacina->stanga = inserareArbore(radacina->stanga, r);
            return radacina;

        }

        else if (r.nrAngajati > radacina->info.nrAngajati) {

            radacina->dreapta = inserareArbore(radacina->dreapta, r);
            return radacina;

        }
        else {

            return radacina;

        }

    }

    return creareNod(r, NULL, NULL);

}

// Afisare Preordine Inordine Postordine
void afisarePreordine(Nod* radacina) {

    if (radacina) {

        printf("\n%d %s% %d\n", radacina->info.nrAngajati,
            radacina->info.adresa, radacina->info.nrLivrari);
        afisarePreordine(radacina->stanga);
        afisarePreordine(radacina->dreapta);

    }

}

void afisareInordine(Nod* radacina) {

    if (radacina) {

        afisareInordine(radacina->stanga);
        printf("\n%d %s% %d\n", radacina->info.nrAngajati,
            radacina->info.adresa, radacina->info.nrLivrari);
        afisareInordine(radacina->dreapta);

    }

}

void afisarePostordine(Nod* radacina) {

    if (radacina) {

        afisarePostordine(radacina->stanga);
        afisarePostordine(radacina->dreapta);
        printf("\n%d %s% %d\n", radacina->info.nrAngajati,
            radacina->info.adresa, radacina->info.nrLivrari);

    }

}

// Recursivitate
int maxim(int a, int b) {

    return (a > b) ? a : b;

}

int nrNiveluri(Nod* radacina) {

    if (radacina) {

        return 1 + maxim(nrNiveluri(radacina->stanga), nrNiveluri(radacina->dreapta));

    }

    return 0;

}

// Dezalocare arbore binar
void dezalocareArbore(Nod* radacina) {

    if (radacina) {

        dezalocareArbore(radacina->stanga);
        dezalocareArbore(radacina->dreapta);
        free(radacina->info.adresa);
        free(radacina);

    }

}