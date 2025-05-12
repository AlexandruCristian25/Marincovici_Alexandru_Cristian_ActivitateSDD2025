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