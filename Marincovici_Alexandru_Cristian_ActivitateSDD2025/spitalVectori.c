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


//Afisare spital
void afisareSpital(Spital s) {

	if (s.nume != NULL) {

		printf("%d este codul sectiei al spitalului %s iar numarul sectiilor este de %d sectii\n",
			s.codS, s.nume, s.nrSectii);

	}
	else {

		printf("%d este codul sectiei al spitaluluiiar numarul sectiilor este de %d sectii\n",
			s.codS, s.nrSectii);

	}

}

//Afisare vector
void afisareVector(Spital* vector, int nrElemente) {

	for (int i = 0; i < nrElemente; i++) {

		afisareSpital(vector[i]);

	}

}

//Vector de copiere a primelor elemente
Spital* copiazaPrimeleElemente(Spital* vector, int nrElemente,
	int nrElementeCopiate) {

	Spital* vectorNou = NULL;
	vectorNou = (Spital*)malloc(sizeof(Spital) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {

		vectorNou[i] = vector[i];
		vectorNou[i].nume = (char*)malloc(sizeof(char) * (strlen(vector[i].nume) + 1));
		strcpy(vectorNou[i].nume, vector[i].nume);

	}

	return vectorNou;

}


