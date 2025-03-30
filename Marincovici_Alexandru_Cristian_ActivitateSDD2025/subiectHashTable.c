#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creare tabela de dispersie pentru 5 comenzi
typedef struct Comanda {
    unsigned int id;
    char* dataLansare;
    char* dataLivrare;
    char* client;
    float suma;
} Comanda;

typedef struct nodLS {
    Comanda info;
    struct nodLS* next;
} nodLS;

typedef struct HT {
    int dimensiune;
    nodLS** vector;
} HT;

