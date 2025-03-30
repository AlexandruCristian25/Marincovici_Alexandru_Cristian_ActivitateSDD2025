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

Comanda creareComanda(unsigned int id, const char* dataLansare,
    const char* dataLivrare, const char* client, float suma) {
    Comanda c;
    c.id = id;
    c.dataLansare = (char*)malloc(strlen(dataLansare) + 1);
    strcpy(c.dataLansare, dataLansare);
    c.dataLivrare = (char*)malloc(strlen(dataLivrare) + 1);
    strcpy(c.dataLivrare, dataLivrare);
    c.client = (char*)malloc(strlen(client) + 1);
    strcpy(c.client, client);
    c.suma = suma;
    return c;
}

