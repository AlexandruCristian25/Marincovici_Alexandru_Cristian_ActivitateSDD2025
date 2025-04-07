#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef struct Spital {

	unsigned int codS;
	char* nume;
	int nrSectii;

}Spital;

//Initializare spital
Spital initializareSpital(unsigned int codS,
	const char* nume, int nrSectii) {

	Spital s;
	s.codS = codS;
	s.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(s.nume, nume);
	s.nrSectii = nrSectii;

	return s;

}
