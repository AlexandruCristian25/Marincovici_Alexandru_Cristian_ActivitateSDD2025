#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura JocVideo
typedef struct JocVideo {

	unsigned int id;
	char* nume;
	int nrCopii;
	float pret;

}JocVideo;