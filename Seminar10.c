#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;

struct Cinema {
	int id;
	int nrFilme;
	char** listaFilme;

};

struct Nod {
	Cinema info;
	Nod* st;
	Nod* dr;
};


void inserareInArbore(Nod** radacina, Cinema c) {
	if (*radacina) {
		if ((*radacina)->info.id > c.id) {
			inserareInArbore(&((*radacina)->st), c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}
	}
	else {
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL; 
		nod->st = NULL; 
		nod->info = c;

		*radacina = nod;
	}
}

Cinema citireCinema(FILE* f) {
	Cinema c;
	fscanf(f, "%d", &c.id);
	fscanf(f, "%d", &c.nrFilme);

	if (c.nrFilme != 0) {
		c.listaFilme = malloc(sizeof(char*) * c.nrFilme);
		for (int i = 0; i < c.nrFilme; i++) {
			char buffer[100];
			fscanf(f, "%s", buffer);
			c.listaFilme[i] = malloc(sizeof(char*) * (strlen(buffer) + 1));
			strcpy(c.listaFilme[i], buffer);
		}
	}
	else c.listaFilme = NULL;
	
	return c;
}

Nod* citireDinFisier(const char* fisier) {

	Nod* radacina = NULL;
	if (fisier != NULL && strlen(fisier) > 0) {
		FILE* f = fopen(fisier, "r");

		if (f != NULL) {
			int dim = 0;
			fscanf(f, "%d", &dim);

			for (int i = 0; i < dim; i++) {
				Cinema cinema;
				cinema = citireCinema(f);
				inserareInArbore(&radacina, cinema);
			}
		}
	}

	return radacina;
}

void afisareCinema(Cinema cinema) {
	printf("Cinema-ul cu id-ul %d are in derulare %d filme: ", cinema.id, cinema.nrFilme);
	for (int i = 0; i < cinema.nrFilme; i++) {
		printf("%s, ", cinema.listaFilme[i]);
	}
	printf("\n");
}

void afisareArborePreordine(Nod* rad) { 
	if (rad) {
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

void afisareArboreInordine(Nod* rad) {
	if (rad) {
		afisareArboreInordine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

int nrFilmeRedate(Nod* rad) {
	if (rad) {
		int suma = rad->info.nrFilme;
		suma += nrFilmeRedate(rad->st);
		suma += nrFilmeRedate(rad->dr);
		return suma;
	}
	else return 0;
}

void main() {
	Nod* arbore = NULL; 
	arbore = citireDinFisier("Text.txt");
	
	printf("\n-----PREORDINE-----\n");
	afisareArborePreordine(arbore);
	printf("\n-----INORDINE-----\n");
	afisareArboreInordine(arbore);
	//printf("\n-----POSTORDINE-----\n");

	printf("\n\nNUMAR FILME REDATE: %d", nrFilmeRedate(arbore));
}