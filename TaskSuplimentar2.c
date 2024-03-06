#include <stdio.h>
#include <stdlib.h>

struct Locuinta {
	int nrCamere;
	float pret;
	char scara;
	char* zona;
};

void afisare(struct Locuinta* vector, int dim) {
	if (vector != NULL)
	{
		for (int i = 0; i < dim; i++) {
			printf("Numar camere:%d Pret:%.2f Scara:%c Zona:%s\n", vector[i].nrCamere, vector[i].pret, vector[i].scara, vector[i].zona);
		}
	}
}

void concatVectori(struct Locuinta* vector1, struct Locuinta* vector2, struct Locuinta** vConcat, int dim1, int dim2, int* dim) {
	*vConcat = malloc(sizeof(struct Locuinta) * (dim1 + dim2));
	*dim = dim1 + dim2;

	for (int i = 0; i < dim1; i++) {
		(*vConcat)[i] = vector1[i];
	}

	for (int i = 0; i < dim2; i++) {
		(*vConcat)[dim1 + i] = vector2[i];
	}

}

void copiereVector(struct Locuinta* vector, struct Locuinta** vectorNou, int dim, int* dimNoua, int nrMinCamere) {
	*vectorNou = malloc(sizeof(struct Locuinta) * dim);
	*dimNoua = 0;

	for (int i = 0; i < dim; i++) {
		if (vector[i].nrCamere >= nrMinCamere) {
			(*vectorNou)[*dimNoua] = vector[i];
			(*dimNoua)++;
		}
	}

}

void mutareVector(struct Locuinta* vector, struct Locuinta** vectorNou, int* dim, int* dimNoua, float maxPret) {
	*vectorNou = malloc(sizeof(struct Locuinta) * (*dim));
	*dimNoua = 0;
	int dim2 = 0;

	for (int i = 0; i < *dim; i++) {
		if (vector[i].pret <= maxPret)
		{
			(*vectorNou)[*dimNoua] = vector[i];
			(*dimNoua)++;
		}
		else {
			vector[dim2] = vector[i];
			dim2++;
		}
	}

	*dim = dim2;
}

void main() {

#pragma region 

	int dim = 5;
	struct Locuinta* vector = malloc(sizeof(struct Locuinta) * dim);

	vector[0] = (struct Locuinta){ 3, 65000.50, 'A', "Militari" };
	vector[1] = (struct Locuinta){ 2, 55000.75, 'B', "Titan" };
	vector[2] = (struct Locuinta){ 4, 80000.30, 'C', "Crangasi" };
	vector[3] = (struct Locuinta){ 1, 45000.20, 'D', "Berceni" };
	vector[4] = (struct Locuinta){ 3, 70000.90, 'E', "Dristor" };

	int dimNoua;
	struct Locuinta** vectorNou = NULL;

	int nrMinCamere;
	printf("Numar minim camere: ");
	scanf_s("%d", &nrMinCamere);

	copiereVector(vector, &vectorNou, dim, &dimNoua, nrMinCamere);

	printf("\nVector nou:\n");
	afisare(vectorNou, dimNoua);
	free(vectorNou);

	printf("\nVector original:\n");
	afisare(vector, dim);

#pragma endregion Copiere in vector nou 

#pragma region  

	/*int dim = 5;
	struct Locuinta* vector = malloc(sizeof(struct Locuinta) * dim);

	vector[0] = (struct Locuinta){ 3, 65000.50, 'A', "Militari" };
	vector[1] = (struct Locuinta){ 2, 55000.75, 'B', "Titan" };
	vector[2] = (struct Locuinta){ 4, 80000.30, 'C', "Crangasi" };
	vector[3] = (struct Locuinta){ 1, 45000.20, 'D', "Berceni" };
	vector[4] = (struct Locuinta){ 3, 70000.90, 'E', "Dristor" };

	int dimNoua = 0;
	struct Locuinta** vectorNou = NULL;

	float maxPret;
	printf("Pret maxim locuinta: ");
	scanf_s("%f", &maxPret);

	mutareVector(vector, &vectorNou, &dim, &dimNoua, maxPret);

	printf("\nVector nou:\n");
	afisare(vectorNou, dimNoua);
	free(vectorNou);

	printf("\nVector original:\n");
	afisare(vector, dim);*/

#pragma endregion Mutare in vector nou

#pragma region 

	/*int dim1 = 3;
	int dim2 = 2;

	struct Locuinta* vector1 = malloc(sizeof(struct Locuinta) * dim1);
	struct Locuinta* vector2 = malloc(sizeof(struct Locuinta) * dim2);

	vector1[0] = (struct Locuinta){ 3, 65000.50, 'A', "Militari" };
	vector1[1] = (struct Locuinta){ 2, 55000.75, 'B', "Titan" };
	vector1[2] = (struct Locuinta){ 4, 80000.30, 'C', "Crangasi" };

	vector2[0] = (struct Locuinta){ 1, 45000.20, 'D', "Berceni" };
	vector2[1] = (struct Locuinta){ 3, 70000.90, 'E', "Dristor" };

	int dimNoua;
	struct Locuinta** vectorConcat = NULL;

	concatVectori(vector1, vector2, &vectorConcat, dim1, dim2, &dimNoua);

	printf("Vector concatenat: \n");
	afisare(vectorConcat, dimNoua);
	free(vectorConcat);*/

#pragma endregion Concatenare vectori 

}