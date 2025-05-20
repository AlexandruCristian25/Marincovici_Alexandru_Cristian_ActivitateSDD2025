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

// Inițializare Joc
Joc initializareJoc(int cod, const char* nume, float pret) {

    Joc j;
    j.cod = cod;
    j.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(j.nume, nume);
    j.pret = pret;

    return j;

}

// Creare nod în arbore
Nod* creareNod(Joc j, Nod* stanga, Nod* dreapta) {

    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = initializareJoc(j.cod, j.nume, j.pret);
    nou->stanga = stanga;
    nou->dreapta = dreapta;

    return nou;

}

// Inserare nod în arbore dupa cod
Nod* inserareArbore(Nod* radacina, Joc j) {

    if (radacina) {

        if (j.cod < radacina->info.cod) {

            radacina->stanga = inserareArbore(radacina->stanga, j);
            return radacina;

        }

        else if (j.cod > radacina->info.cod) {

            radacina->dreapta = inserareArbore(radacina->dreapta, j);
            return radacina;

        }
        else {

            return radacina;

        }

    }

    return creareNod(j, NULL, NULL);

}