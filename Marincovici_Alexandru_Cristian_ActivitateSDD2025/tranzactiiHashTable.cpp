#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creare Structura Tranzactie
typedef struct Tranzactie {

    unsigned int numarTranzactie;
    char* denumireComerciant;
    char* numeClient;
    float valoareCuDiscount;
    float discountProcentual;
    char* tipPlata;

} Tranzactie;

typedef struct Nod {

    Tranzactie* info;
    struct Nod* next;

} Nod;

typedef struct HT {

    Nod** vector;
    int dimensiune;

} HT;

Tranzactie* initializareTranzactie(unsigned int numarTranzactie, char* denumireComerciant, char* numeClient, float valoareCuDiscount, float discountProcentual, char* tipPlata) {

    Tranzactie* tranzactie = (Tranzactie*)malloc(sizeof(Tranzactie));
    tranzactie->numarTranzactie = numarTranzactie;
    tranzactie->denumireComerciant = (char*)malloc(strlen(denumireComerciant) + 1);
    strcpy(tranzactie->denumireComerciant, denumireComerciant);
    tranzactie->numeClient = (char*)malloc(strlen(numeClient) + 1);
    strcpy(tranzactie->numeClient, numeClient);
    tranzactie->valoareCuDiscount = valoareCuDiscount;
    tranzactie->discountProcentual = discountProcentual;
    tranzactie->tipPlata = (char*)malloc(strlen(tipPlata) + 1);
    strcpy(tranzactie->tipPlata, tipPlata);

    return tranzactie;

}

Nod* initializareNod(Tranzactie* info) {

    Nod* nod = (Nod*)malloc(sizeof(Nod));

    nod->info = info;
    nod->next = NULL;

    return nod;

}