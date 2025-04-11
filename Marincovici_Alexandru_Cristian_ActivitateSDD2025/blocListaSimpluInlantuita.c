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

// Functie de citire a unui Bloc din fisier
Bloc citireBlocDinFisier(FILE* f) {

	char buffer[100];
	Bloc b;

	if (fgets(buffer, sizeof(buffer), f)) {

		char* token;
		const char* sep = ",\n";
		token = strtok(buffer, sep);
		if (token) {

			b.nrBloc = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			b.numeBloc = (char*)malloc(strlen(token) + 1);
			strcpy(b.numeBloc, token);

		}
		token = strtok(NULL, sep);

		if (token) {

			b.nrApartamente = atoi(token);

		}
		token = strtok(NULL, sep);

		if (token) {

			b.nrLocuitori = atoi(token);

		}

	}

	return b;

}

// Functia de afisare Bloc
void afisareBloc(Bloc bloc) {

	printf("Nr bloc: %d\n", bloc.nrBloc);
	printf("Nume bloc: %s\n", bloc.numeBloc);
	printf("Nr apartamente: %d\n", bloc.nrApartamente);
	printf("Nr locuitori: %d\n", bloc.nrLocuitori);

}


