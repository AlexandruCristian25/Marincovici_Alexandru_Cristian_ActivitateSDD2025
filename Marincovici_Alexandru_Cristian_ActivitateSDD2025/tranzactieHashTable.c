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