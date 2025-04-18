#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Smartwatch
typedef struct Smartwatch {

	unsigned int id;
	char* producator;
	int baterie;
	float pret;

}Smartwatch;