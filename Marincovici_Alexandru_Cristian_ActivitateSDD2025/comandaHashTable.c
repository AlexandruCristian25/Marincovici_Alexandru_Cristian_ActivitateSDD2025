#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Comanda {

    unsigned int id;
    char* dataLansare;
    char* dataLivrare;
    char* client;
    float suma;

}Comanda;

typedef struct nodLS {

    Comanda info;
    struct nodLS* next;

}nodLS;

typedef struct HT {

    int dimensiune;
    nodLS** vector;

}HT;

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

void afisareListaSimpla(nodLS* cap) {

    nodLS* aux = cap;
    while (aux) {

        printf("Comanda %u lansata la %s, livrata pe %s, client %s, suma %.2f\n",
            aux->info.id, aux->info.dataLansare, aux->info.dataLivrare, aux->info.client, aux->info.suma);
        aux = aux->next;

    }

}

nodLS* inserareInceput(nodLS* cap, Comanda c) {

    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->info = creareComanda(c.id, c.dataLansare, c.dataLivrare, c.client, c.suma);
    nou->next = NULL;

    if (cap == NULL) {

        cap = nou;

    }
    else {

        nou->next = cap;
        cap = nou;

    }

    return cap;
}

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

int nrComenzi(HT tabela, const char* dataLivrare) {

    int nr = 0;

    if (tabela.vector) {

        for (int i = 0; i < tabela.dimensiune; i++) {

            if (tabela.vector[i]) {

                nodLS* aux = tabela.vector[i];
                while (aux) {

                    if (strcmp(dataLivrare, aux->info.dataLivrare) == 0) {

                        nr++;

                    }

                    aux = aux->next;

                }

            }

        }

        return nr;

    }

}

nodLS* salveazaListaNoua(HT tabela, const char* dataLivrare) {

    nodLS* listaNoua = NULL;
    if (tabela.vector) {

        for (int i = 0; i < tabela.dimensiune; i++) {

            if (tabela.vector[i]) {

                nodLS* aux = tabela.vector[i];
                while (aux) {

                    if (strcmp(dataLivrare, aux->info.dataLivrare) == 0) {

                        listaNoua = inserareInceput(listaNoua, aux->info);

                    }

                    aux = aux->next;

                }

            }

        }

        return listaNoua;

    }

}

void stergereComenzi(HT tabela, const char* dataLivrare) {

    int nr = 0;
    if (tabela.vector) {

        for (int i = 0; i < tabela.dimensiune; i++) {

            if (tabela.vector[i]) {

                nodLS* aux = tabela.vector[i];
                nodLS* prev = NULL;
                while (aux) {

                    if (strcmp(dataLivrare, aux->info.dataLivrare) == 0) {

                        nodLS* temp = aux;
                        if (prev == NULL) {

                            tabela.vector[i] = aux->next;
                            aux = tabela.vector[i];

                        }
                        else {

                            prev->next = aux->next;
                            aux = prev->next;

                        }

                        free(temp->info.dataLansare);
                        free(temp->info.dataLivrare);
                        free(temp->info.client);
                        free(temp);

                    }
                    else {

                        prev = aux;
                        aux = aux->next;

                    }

                }

            }

        }

    }

}

void dezalocareLS(nodLS* lista) {

    nodLS* aux = lista;
    while (aux) {

        free(aux->info.dataLansare);
        free(aux->info.dataLivrare);
        free(aux->info.client);

        nodLS* temp = aux->next;
        free(aux);
        aux = temp;

    }

}


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

int main() {

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
        if (token) c.id = atoi(token);

        token = strtok(NULL, delimitator);
        if (token) {

            c.dataLansare = (char*)malloc(strlen(token) + 1);
            strcpy(c.dataLansare, token);

        }

        token = strtok(NULL, delimitator);
        if (token) {

            c.dataLivrare = (char*)malloc(strlen(token) + 1);
            strcpy(c.dataLivrare, token);

        }

        token = strtok(NULL, delimitator);
        if (token) {

            c.client = (char*)malloc(strlen(token) + 1);
            strcpy(c.client, token);

        }

        token = strtok(NULL, delimitator);
        if (token) c.suma = atof(token);

        inserareHT(tabela, c);

        free(c.dataLansare);
        free(c.dataLivrare);
        free(c.client);
    }

    fclose(f);
    afisareHT(tabela);
    int nr = nrComenzi(tabela, "15.02.2025");
    printf("\n%d\n", nr);

    nodLS* listaNoua = salveazaListaNoua(tabela, "15.02.2025");
    printf("\nLista noua: \n");
    afisareListaSimpla(listaNoua);

    stergereComenzi(tabela, "15.02.2025");
    afisareHT(tabela);
    afisareListaSimpla(listaNoua);

    dezalocareHT(tabela);

    return 0;

}