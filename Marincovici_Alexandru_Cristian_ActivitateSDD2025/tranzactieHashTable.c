#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare Structura Tranzactie
typedef struct Tranzactie {

    unsigned int id;
    char* denumire;
    char* numeClient;
    float dicount;

}Tranzactie;

// Creare structura Nod
typedef struct Nod {

    Tranzactie tranzactie;
    struct Nod* next;

}Nod;

// Creare structura HashTable
typedef struct HashTable {

    int dim;
    Nod** tabela;

}HashTable;

// Initializare tranzactie
Tranzactie initializareTrazanctie(unsigned int id, const char* denumire,
    const char* numeClient, float discount) {

    Tranzactie t;
    t.id = id;
    t.denumire = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
    t.numeClient = (char*)malloc(sizeof(char) * strlen(numeClient) + 1);
    t.dicount = discount;

    return t;

}

// Citire fisier
Tranzactie citireFisier(FILE* f) {
    char buffer[100];
    Tranzactie t = { 0, NULL, NULL, 0.0 };

    if (fgets(buffer, sizeof(buffer), f)) {
        char* token = strtok(buffer, ",;\n");
        if (token == NULL) return t;
        t.id = atoi(token);

        token = strtok(NULL, ",;\n");
        if (token == NULL) return t;
        t.denumire = (char*)malloc(strlen(token) + 1);
        strcpy(t.denumire, token);

        token = strtok(NULL, ",;\n");
        if (token == NULL) return t;
        t.numeClient = (char*)malloc(strlen(token) + 1);
        strcpy(t.numeClient, token);

        token = strtok(NULL, ",;\n");
        if (token == NULL) return t;
        t.dicount = atof(token);
    }

    return t;

}

// Afisare fisier
void afisareFisier(Tranzactie tranzactie) {

    printf("Id: %u\n", tranzactie.id);
    printf("Denumire: %s\n", tranzactie.denumire);
    printf("Nume client: %s\n", tranzactie.numeClient);
    printf("Discount: %.2f\n", tranzactie.dicount);

}

// Functia de afisare a listei
void afisareLista(Nod* cap) {

    while (cap) {

        afisareFisier(cap->tranzactie);
        cap = cap->next;

    }

}

// Functia de adaugare in lista
void adaugaInLista(Nod* cap, Tranzactie tranzactieNoua) {

    Nod* p = cap;
    while (p->next) {

        p = p->next;

    }

    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->tranzactie = tranzactieNoua;
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

// Calculeaza hash
int calculeazaHash(const char* nume, int dimensiune) {


    int suma = 0;
    for (int i = 0; i < strlen(nume); i++) {

        suma += nume[i];

    }

    return suma % dimensiune;

}