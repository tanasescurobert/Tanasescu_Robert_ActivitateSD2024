#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct Locuinta {
	int id;
	char* strada;
	int nr;
};

void inserareLocuintaInVector(struct Locuinta** vector, int* dim, struct Locuinta locuinta) {

	struct Locuinta* copie;
	copie = malloc(sizeof(struct Locuinta) * (++(*dim)));

	for (int i = 0; i < (*dim) - 1; i++) {
		copie[i] = (*vector)[i];
	}

	copie[(*dim) - 1] = locuinta;
	if ((*vector) != NULL) {
		free((*vector));
	}
	(*vector) = copie;
}

void citireDinFisier(const char* fisier, struct Locuinta** vector, int* dim) {

	if (fisier != NULL && strlen(fisier) > 0)
	{
		FILE* f = fopen(fisier, "r");

		if (f != NULL) {
			(*dim) = 0;
			char buffer[100];
			char delimiter[] = ",\n";
			while (fgets(buffer, 100, f) != NULL) {

				char* token;
				struct Locuinta locuinta;

				token = strtok(buffer, delimiter);
				locuinta.id = atoi(token);

				token = strtok(NULL, delimiter);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);

				token = strtok(NULL, delimiter);
				locuinta.nr = atoi(token);

				inserareLocuintaInVector(vector, dim, locuinta);
			}
		}
		fclose(f);
	}

}

void afisareLocuinta(struct Locuinta locuinta) {
	printf("ID: %d\t Strada: %s\t Nr: %d\t", locuinta.id, locuinta.strada, locuinta.nr);
}

void afisareVectorLocuinte(struct Locuinta* vector, int dim) {
	for (int i = 0; i < dim; i++) {
		afisareLocuinta(vector[i]);
	}
}

void stergeLocuinta(struct Locuinta** vector, int* dim, int id) {

	char flag = 0;
	for (int i = 0; i < (*dim); i++) {
		if ((*vector)[i].id == id) {
			flag = 1;
			break;
		}
	}

	if (flag == 1) {
		struct Locuinta* copie = malloc(sizeof(struct Locuinta) * ((*dim) - 1));
		int indexNou = 0;

		for (int i = 0; i < (*dim); i++) {
			if ((*vector)[i].id != id)
			{
				copie[indexNou++] = (*vector)[i];
			}

		}
		(*dim)--;
		if ((*vector) != NULL) {
			free((*vector));
		}
		(*vector) = copie;

	}
}


void citireMatriceFisier(const char* fisier, struct Locuinta** matrice, int nr_linii, int* nr_coloane) {

	if (fisier != NULL && strlen(fisier) > 0)
	{
		FILE* f = fopen(fisier, "r");

		if (f != NULL) {	
			char buffer[100];
			char delimiter[] = ",\n";

			while (fgets(buffer, 100, f) != NULL) {

				char* token;
				struct Locuinta locuinta;

				token = strtok(buffer, delimiter);
				locuinta.id = atoi(token);

				token = strtok(NULL, delimiter);
				locuinta.strada = (char*)malloc(strlen(token) + 1);
				strcpy(locuinta.strada, token);

				token = strtok(NULL, delimiter);
				locuinta.nr = atoi(token);

				int pozitie;
				pozitie = locuinta.nr % 2;
				inserareLocuintaInVector(&(matrice[pozitie]), &(nr_coloane[pozitie]), locuinta);
			}
		}
		fclose(f);
	}

}

void afisareMatrice(struct Locuinta** matrice, int nr_linii, int* nr_coloane)
{
	for (int i = 0; i < nr_linii; i++) {
		for (int j = 0; j < nr_coloane[i]; j++) {
			afisareLocuinta(matrice[i][j]);
		}
		printf("\n");
	}
}

void afisareIdDePeOParte(int paritate, struct Locuinta** matrice, int nr_linii, int* nr_coloane) {
	
	paritate = paritate % 2;
	
	for (int j = 0; j < nr_coloane[paritate]; j++) {
		printf("%d ", matrice[paritate][j].id);
	}
	
}

struct Locuinta cautareDupaID(int idCautat, struct Locuinta** matrice, int nr_linii, int* nr_coloane) {
	for (int i = 0; i < nr_linii; i++)
	{
		for (int j = 0; j < nr_coloane[i]; j++) {
			if (matrice[i][j].id == idCautat) {
				return matrice[i][j];
			}
		}	
	}

	struct Locuinta copie;
	copie.id = 0;
	copie.nr = -1;
	copie.strada = NULL;

	return copie; 
}

void dezalocareMatrice(struct Locuinta*** matrice, int* nr_linii, int** nr_coloane) {
	for (int i = 0; i < (*nr_linii); i++)
	{
		for (int j = 0; j < (*nr_coloane)[i]; j++)
		{
			free((*matrice)[i][j]);
			(*matrice)[i][j].strada = NULL;
		}
		free((*matrice)[i]);
	}
	free(*matrice);
	*matrice = NULL; 

	(*nr_linii) = 0;
	free(*nr_coloane);
	*nr_coloane = NULL;

}

void schimbareNrLocuinta(struct Locuinta** matrice, int nrLinii, int* nrColoane, int nrLocuinta) {
	int pozitie = nrLocuinta % 2;
	int idLocuinta = -1;
	int indexInVector = -1;

	for (int i = 0; i < nrColoane[pozitie]; i++)
	{
		if (matrice[pozitie][i].nr == nrLocuinta) { 
			matrice[pozitie][i].nr++;
			idLocuinta = matrice[pozitie][i].id;
			indexInVector = i;
		}
	}

	if (idLocuinta != -1) {
		int index = (nrLocuinta + 1) % 2;
		inserareLocuintaInVector(&(matrice[index]), &(nrColoane[index]), matrice[pozitie][indexInVector]);
		stergeLocuinta(&(matrice[pozitie]), &(nrColoane[pozitie]), idLocuinta);
		
	}
}

void main() {
    
	int nr_linii;
	int* nr_coloane;
	struct Locuinta** matrice;

	nr_linii = 2;
	nr_coloane = malloc(sizeof(int) * nr_linii);
	matrice = malloc(sizeof(struct Locuinta*) * nr_linii);

	for (int i = 0; i < nr_linii; i++) {
		matrice[i] = NULL;
		nr_coloane[i] = 0;
	}

	citireMatriceFisier("locuinte.txt", matrice, nr_linii, nr_coloane);
	afisareMatrice(matrice, nr_linii, nr_coloane);
	printf("\n");
	afisareIdDePeOParte(3, matrice, nr_linii, nr_coloane);

	struct Locuinta locuinta1 = cautareDupaID(43, matrice, matrice, nr_linii, nr_coloane);
	printf("\n");
	afisareLocuinta(locuinta1);

	printf("\n");
	schimbareNrLocuinta(matrice, nr_linii, nr_coloane, 15);
	printf("\n\nDupa mutare\n");
	afisareMatrice(matrice, nr_linii, nr_coloane);


	dezalocareMatrice(&matrice, &nr_linii, &nr_coloane);

}