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

//Initilaizare Hash Table
HT* initializareHT(int dimensiune) {

    HT* ht = (HT*)malloc(sizeof(HT));

    ht->dimensiune = dimensiune;
    ht->vector = (Nod**)malloc(ht->dimensiune * sizeof(Nod*));

    for (int i = 0; i < ht->dimensiune; i++) {

        ht->vector[i] = NULL;

    }

    return ht;

}

int hash(HT* ht, char* numeClient) {

    int suma = 0;
    for (int i = 0; i < strlen(numeClient); i++) {

        suma += numeClient[i];

    }
    return suma % ht->dimensiune;

}

//Inserare in Hash Table
HT* inserareInHT(HT* ht, Tranzactie* tranzactie) {

    if (ht->vector != NULL) {

        int pozitie = hash(ht, tranzactie->numeClient);
        Nod* nou = initializareNod(tranzactie);

        if (ht->vector[pozitie] == NULL) {

            ht->vector[pozitie] = nou;

        }
        else {

            Nod* aux = ht->vector[pozitie];
            while (aux->next != NULL) {

                aux = aux->next;

            }
            aux->next = nou;

        }

    }

    return ht;

}

//Functia de afisare
void afisare(HT* ht) {

    if (ht != NULL) {

        for (int i = 0; i < ht->dimensiune; i++) {

            if (ht->vector[i] != NULL) {

                Nod* temp = ht->vector[i];
                while (temp != NULL) {
                    printf("Pozitie: %d \n", i);
                    printf("Numar Tranzactie: %u, Denumire Comerciant: %s, Nume Client: %s, Valoare cu Discount: %.2f, Discount Procentual: %.2f, Tip Plata: %s\n",
                        temp->info->numarTranzactie, temp->info->denumireComerciant, temp->info->numeClient, temp->info->valoareCuDiscount, temp->info->discountProcentual, temp->info->tipPlata);
                    temp = temp->next;

                }

            }

        }

    }

}

//Functia de dezalocare
void dezalocare(HT* ht) {

    if (ht->vector != NULL) {

        for (int i = 0; i < ht->dimensiune; i++) {

            Nod* temp = ht->vector[i];
            while (temp != NULL) {
                Nod* deSters = temp;
                temp = temp->next;
                free(deSters->info->denumireComerciant);
                free(deSters->info->numeClient);
                free(deSters->info->tipPlata);
                free(deSters->info);
                free(deSters);

            }

        }

        free(ht->vector);
        free(ht);

    }

}