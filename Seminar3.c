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
	printf("ID: %d\t Strada: %s\t Nr: %d\n", locuinta.id, locuinta.strada, locuinta.nr);
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

void main() {

	struct Locuinta* locuinte = NULL; 
	int dim = 3;
	citireDinFisier("locuinte.txt", &locuinte, &dim);
	printf("Vector initial:\n\n"); 
	afisareVectorLocuinte(locuinte, dim);  

	stergeLocuinta(&locuinte, &dim, 17);
	printf("Vector modificat:\n\n");
	afisareVectorLocuinte(locuinte, dim); 

}