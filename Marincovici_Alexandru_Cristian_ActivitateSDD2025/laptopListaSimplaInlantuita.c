#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creare structura Laptop
typedef struct Laptop {

    unsigned int id;
    char* producator;
    int RAM;
    float pret;

} Laptop;

typedef struct Nod {

    Laptop info;
    struct Nod* next;

} Nod;

// Functie de citire a unui laptop din fisier
Laptop citireLaptopDinFisier(FILE* f) {

    char buffer[128];
    Laptop l1 = { 0, NULL, 0, 0.0f };

    if (fgets(buffer, sizeof(buffer), f)) {

        char* token;
        const char* sep = ",\n";
        token = strtok(buffer, sep);
        if (token) l1.id = atoi(token);
        token = strtok(NULL, sep);

        if (token) {

            l1.producator = (char*)malloc(strlen(token) + 1);
            strcpy(l1.producator, token);

        }

        token = strtok(NULL, sep);
        if (token) {

            l1.RAM = atoi(token);

        }
        token = strtok(NULL, sep);

        if (token) {

            l1.pret = atof(token);

        }
    }

    return l1;

}

// Functia de afisare Laptop
void afisareLaptop(Laptop laptop) {

    printf("Id: %d\n", laptop.id);
    printf("Producator: %s\n", laptop.producator);
    printf("RAM: %d GB\n", laptop.RAM);
    printf("Pret: %.2f lei\n\n", laptop.pret);

}

// Functia de afisare a listei de laptopuri
void afisareListaLaptopuri(Nod* cap) {

    while (cap) {

        afisareLaptop(cap->info);
        cap = cap->next;

    }

}

// Functia de adaugare a unui laptop in lista
void adaugaLaptopInLista(Nod** cap, Laptop laptopNou) {

    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = laptopNou;
    nou->next = NULL;

    if (*cap == NULL) {

        *cap = nou;

    }
    else {

        Nod* p = *cap;
        while (p->next) {

            p = p->next;

        }

        p->next = nou;

    }

}

// Citirea listei din fisier
Nod* citireListaLaptopuriDinFisier(const char* numeFisier) {

    Nod* cap = NULL;
    FILE* f = fopen(numeFisier, "r");

    if (f) {

        while (!feof(f)) {

            Laptop l = citireLaptopDinFisier(f);
            if (l.producator) {

                adaugaLaptopInLista(&cap, l);

            }

        }
        fclose(f);
    }
    else {

        printf("Nu s-a putut deschide fisierul %s\n", numeFisier);

    }

    return cap;

}