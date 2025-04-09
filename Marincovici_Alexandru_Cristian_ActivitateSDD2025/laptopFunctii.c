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