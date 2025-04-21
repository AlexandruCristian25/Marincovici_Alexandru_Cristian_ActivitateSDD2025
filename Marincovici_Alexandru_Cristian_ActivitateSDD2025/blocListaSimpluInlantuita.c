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

// Functia de afisare a listei de blocuri
void afisareListaBlocuri(Nod* cap) {

	while (cap) {

		afisareBloc(cap->info);
		cap = cap->next;

	}

}

// Functia de adaugare a unui bloc in lista
void adaugaBlocInLista(Nod** cap, Bloc blocNou) {

	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = blocNou;
	nou->next = NULL;

	if (*cap == NULL) {

		*cap = nou;

	}
	else {

		Nod* p = *cap;
		while (p->next) {

			p = p->next;

		}

		p->next = nou;

	}

}

// Citirea listei din fisier
Nod* citireaListaBlocuriDinFisier(const char* numeFisier) {

	Nod* cap = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f) {

		while (!feof(f)) {

			Bloc b = citireBlocDinFisier(f);
			if (b.numeBloc) {

				adaugaBlocInLista(&cap, b);

			}

		}
		fclose(f);

	}

	return cap;

}

// Dezalocare lista
void dezalocareListaBlocuri(Nod** cap) {

	while (*cap) {

		Nod* p = *cap;
		*cap = p->next;
		if (p->info.numeBloc) {

			free(p->info.numeBloc);

		}

		free(p);

	}

}

// Afisare in main
int main() {

	Nod* cap = citireaListaBlocuriDinFisier("bloc.txt");

	printf("==== Lista blocuri ===== \n");
	afisareListaBlocuri(cap);
	dezalocareListaBlocuri(&cap);

	printf("\n==== Lista dupa dezalocare ===== \n");
	afisareListaBlocuri(cap);

	return 0;

}


