#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Creare structura Bloc
typedef struct Bloc {

	unsigned int nrBloc;
	char* numeBloc;
	int nrApartamente;
	int nrLocuitori;

}Bloc;

typedef struct Nod {

	Bloc info;
	struct Nod* next;


}Nod;
