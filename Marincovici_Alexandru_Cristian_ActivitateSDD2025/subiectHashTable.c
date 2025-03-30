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

//Crearea functiei de afisare dar si afisarea tabelei de dispersie
int functieInserare(HT tabela, const char* dataLansare) {
    return dataLansare[0] % tabela.dimensiune;
}

int inserareHT(HT tabela, Comanda c) {
    int pozitie = functieInserare(tabela, c.dataLansare);
    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->info = creareComanda(c.id, c.dataLansare, c.dataLivrare, c.client, c.suma);
    nou->next = NULL;

    if (tabela.vector[pozitie] == NULL) {
        tabela.vector[pozitie] = nou;
    }
    else {
        nodLS* aux = tabela.vector[pozitie];
        while (aux->next) {
            aux = aux->next;
        }
        aux->next = nou;
    }
    return pozitie;
}

//Afisare tabelei de dispersie
void afisareHT(HT tabela) {
    for (int i = 0; i < tabela.dimensiune; i++) {
        if (tabela.vector[i]) {
            printf("Pozitie %d:\n", i);
            nodLS* aux = tabela.vector[i];
            while (aux) {
                printf("Comanda %u lansata la %s, livrata pe %s, client %s, suma %.2f\n",
                    aux->info.id, aux->info.dataLansare, aux->info.dataLivrare, aux->info.client, aux->info.suma);
                aux = aux->next;
            }
        }
    }
}

//Dezalocarea tabelei de dispersie
void dezalocareHT(HT tabela) {
    for (int i = 0; i < tabela.dimensiune; i++) {
        nodLS* aux = tabela.vector[i];
        while (aux) {
            free(aux->info.dataLansare);
            free(aux->info.dataLivrare);
            free(aux->info.client);
            nodLS* temp = aux;
            aux = aux->next;
            free(temp);
        }
    }
    free(tabela.vector);
}

//Afisare in main
void main() {
    HT tabela;
    tabela.dimensiune = 100;
    tabela.vector = (nodLS**)calloc(tabela.dimensiune, sizeof(nodLS*));

    char buffer[100];
    char delimitator[] = ",";
    char* token;

    FILE* f = fopen("comenzi.txt", "r");
    if (!f) {
        printf("Eroare la deschiderea fisierului!\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), f)) {
        Comanda c;
        token = strtok(buffer, delimitator);
        `