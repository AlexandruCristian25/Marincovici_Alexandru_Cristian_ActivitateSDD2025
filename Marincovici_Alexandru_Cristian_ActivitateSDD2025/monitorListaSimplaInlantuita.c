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

// Functia de initializare
Monitor initializareMonitor(unsigned int cod, char* producator,
	float diagonala, int nrPorturi) {

	Monitor m;
	m.cod = cod;
	m.producator = (char*)malloc(sizeof(char) * strlen(producator) + 1);
	strcpy(m.producator, producator);
	m.diagonala = diagonala;
	m.nrPorturi = nrPorturi;

	return m;

}