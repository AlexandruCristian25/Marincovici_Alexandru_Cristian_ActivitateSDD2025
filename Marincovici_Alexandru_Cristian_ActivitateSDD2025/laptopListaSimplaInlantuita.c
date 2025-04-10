#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Creare structura Laptop
typedef struct Laptop {
    unsigned int id;
    char* producator;
    int RAM;
    float pret;
} Laptop;