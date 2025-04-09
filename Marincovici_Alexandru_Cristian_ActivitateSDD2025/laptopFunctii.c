#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

//Creare strcutura laptop
typedef struct Laptop {

	unsigned int id;
	char* producator;
	int RAM;
	float pretL;

}Laptop;

//Intializare laptop
Laptop initializareLaptop(unsigned int id, const char* producator,
	int RAM, float pretL) {

	Laptop l;
	l.id = id;
	l.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(l.producator, producator);
	l.RAM = RAM;
	l.pretL = pretL;

}