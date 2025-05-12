#define _CRT_SECURE_NO_WARNIGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Creare structura Ghiozdan
typedef struct Ghiozdan {

	unsigned int id;
	char* producator;
	int capacitate;
	float pret;

}Ghiozdan;