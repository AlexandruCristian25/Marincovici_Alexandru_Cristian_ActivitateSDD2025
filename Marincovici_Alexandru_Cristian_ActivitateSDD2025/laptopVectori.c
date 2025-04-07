#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Laptop {

	unsigned int id;
	char* producator;
	int RAM;
	float pret;

}Laptop;

//Initializare laptop
Laptop initializareLaptop(unsigned int id, const char* producator,
	int RAM, float pret) {

	Laptop l;
	l.id = id;
	l.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(l.producator, producator);
	l.RAM = RAM;
	l.pret = pret;

	return l;

}