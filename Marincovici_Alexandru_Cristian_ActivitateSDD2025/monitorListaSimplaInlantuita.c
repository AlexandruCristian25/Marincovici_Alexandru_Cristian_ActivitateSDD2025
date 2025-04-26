#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

// Creare structura Monitor
typedef struct Monitor {

	unsigned int cod;
	char* producator;
	float diagonala;
	int nrPorturi;

}Monitor;