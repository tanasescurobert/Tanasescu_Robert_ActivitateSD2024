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

Nod* rotireDreapta(Nod* rad) {
	if (rad) {
		Nod* aux = rad->st;
		rad->st = aux->dr;
		aux->dr = rad;

		return aux;
	}
	else {
		return rad;
	}
}

Nod* rotireStanga(Nod* rad) {
	if (rad) { 
		Nod* aux = rad->dr; 
		rad->dr = aux->st;  
		aux->st = rad; 

		return aux; 
	}
	else {
		return rad; 
	}
}

int calculInaltime(Nod* rad) {
	if (rad != NULL)
	{
		int inaltimeST = calculInaltime(rad->st);
		int inaltimeDR = calculInaltime(rad->dr);

		if (inaltimeST > inaltimeDR) {
			return inaltimeST;
		}
		else return inaltimeDR;
	}

	else return 0;
}

int calculGradEchilibru(Nod* rad) {
	int inaltimeSubarboreST = calculInaltime(rad->st);
	int inaltimeSubarboreDR = calculInaltime(rad->dr);

	return inaltimeSubarboreST - inaltimeSubarboreDR;  
}

void inserareInArbore(Nod** radacina, Cinema c) { 
	if (*radacina) {
		if ((*radacina)->info.id > c.id) {
			inserareInArbore(&((*radacina)->st), c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}

		int grad = calculGradEchilibru(*radacina);
		if (grad == 2) { //dezechilbru in stanga
			int gradCopil = calculGradEchilibru((*radacina)->st);
			
			if (gradCopil == -1) {
				(*radacina)->st = rotireStanga((*radacina)->st);
			}
			*radacina = rotireDreapta(*radacina);
		}
		else if (grad == -2) { //dezechilbru in dreapta
			int gradCopil = calculGradEchilibru((*radacina)->dr); 
			 
			if (gradCopil == -1) { 
				(*radacina)->dr = rotireDreapta((*radacina)->dr);  
			}
			*radacina = rotireStanga(*radacina);  
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

void stergereArbore(Nod* rad) { 

	if (*rad) {
		stergereArbore((&(*rad))->st);
		stergereArbore((&(*rad))->dr);  

		if (rad->info.listaFilme) {
			for (int i = 0; i < (*rad)->info.listaFilme; i++) {
				free((*rad)->info.listaFilme[i]);
			}
			free(rad->info.listaFilme);
		}

		free(rad);
		(*rad) = NULL; 
	}

}

Cinema calculCinemaCuNrMax(Nod* rad) {
	if (rad) {
		Cinema cinemaST = calculCinemaCuNrMax(rad->st);
		Cinema cinemaDR = calculCinemaCuNrMax(rad->dr);
		Cinema cinemaMAX;
		
		if (rad->info.nrFilme > cinemaST.nrFilme && rad->info.nrFilme > cinemaDR.nrFilme) {
			cinemaMAX = rad;
		}
		else if ( cinemaST.nrFilme > cinemaDR.nrFilme) {
			cinemaMAX = cinemaST;
		}
		else {
			cinemaMAX = cinemaDR;
		}

		return cinemaMAX;
	}
	else {
		Cinema c;
		c.id = -1;
		c.listaFilme = NULL;
		c.nrFilme = 0;
		return c;
	}
}

void main() {
	Nod* arbore = NULL;
	arbore = citireDinFisier("Seminar12.txt");

	printf("\n-----PREORDINE-----\n");
	afisareArborePreordine(arbore);
	
	printf("\n\nNumar filme: %d", nrFilmeRedate(arbore)); 

	printf("\nCinema cu nr max de filme:\n"); 
	Cinema cinema = calculCinemaCuNrMax(arbore); 
	afisareCinema(cinema); 

	stergereArbore(&arbore);
	afisareArborePreordine(arbore);
}