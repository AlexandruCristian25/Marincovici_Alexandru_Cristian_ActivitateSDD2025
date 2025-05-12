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