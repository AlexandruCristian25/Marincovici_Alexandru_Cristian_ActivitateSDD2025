#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Serviciu
typedef struct Serviciu {

	unsigned int id;
	char* tipServiciu;
	char* numeClient;
	float suma;
	unsigned int timp;

}Serviciu;