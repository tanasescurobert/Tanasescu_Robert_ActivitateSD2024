#include <stdio.h>
#include <stdlib.h>

struct Locuinta {
	int nrCamere;
	float pret;
	char scara;
	char* zona;
};


void vectorCopiere(struct Locuinta* vector, struct Locuinta** vectorNou, int lungime, int *lungimeNou, int nrMinCamere)
{
	*vectorNou = malloc(sizeof(struct Locuinta) * lungime);
	*lungimeNou = 0;

	for (int i = 0; i < lungime; i++)
	{
		if (vector[i].nrCamere >= nrMinCamere) 
		{
			(*vectorNou)[*lungimeNou] = vector[i]; 
			(*lungimeNou)++; 
		}
	}

}


void vectorMutare(struct Locuinta* vector, struct Locuinta** vectorNou, int *lungime, int* lungimeNou, float maxPret)
{
	*vectorNou = malloc(sizeof(struct Locuinta) * (*lungime));
	*lungimeNou = 0;
	int dim = 0;

	for (int i = 0; i < *lungime; i++) {
		if (vector[i].pret <= maxPret)
		{
			(*vectorNou)[*lungimeNou] = vector[i];
			(*lungimeNou)++;
		}
		else {
			vector[dim] = vector[i];
			dim++;
		}
	}

	*lungime = dim;
}


void concatVectori(struct Locuinta* v1, struct Locuinta* v2, struct Locuinta** vConcat, int dim1, int dim2, int* dimNoua) {
	
	*vConcat = malloc(sizeof(struct Locuinta) * (dim1 + dim2));
	*dimNoua = dim1 + dim2;

	for (int i = 0; i < dim1; i++)
	{
		(*vConcat)[i] = v1[i];
	}
	for (int i = 0; i < dim2; i++)
	{
		(*vConcat)[dim1 + i] = v2[i];   
	}

}


void afisare(struct Locuinta *vector, int nrLocuinte) {

	if (vector != NULL)
	{
		for (int i = 0; i < nrLocuinte; i++) {
			printf("Nr camere: %d, Pret: %.2f, Scara: %c, Zona: %s\n",
				vector[i].nrCamere, vector[i].pret, vector[i].scara, vector[i].zona);
		}
	}
}


void main() {

#pragma region 

	//struct Locuinta locuinte[] = {
	//{1, 49999.99, 'A', "Militari"},
	//{2, 58000, 'B', "Drumul Taberei"},
	//{3, 63000, 'C', "Crangasi"},
	//{3, 81000.99, 'C', "Titan"},
	//{4, 105000, 'D', "Crangasi"},
	//};

	//int nrLocuinte = sizeof(locuinte) / sizeof(locuinte[0]);
	//int lungimeNou;

	//int nrMinCamere;
	//printf("Introduceti numarul minim de camere: ");
	//scanf_s("%d", &nrMinCamere);

	//struct Locuinta** vNou = NULL;
	//vectorCopiere(locuinte, &vNou, nrLocuinte, &lungimeNou, nrMinCamere); 

	//printf("Vector nou: \n");
	//afisare(vNou, lungimeNou);
	//free(vNou); 

	//printf("\nVector original: \n");
	//afisare(locuinte, nrLocuinte);

#pragma endregion Copiere in vector nou

#pragma region 

	/*struct Locuinta locuinte[] = {
	{1, 49999.99, 'A', "Militari"},
	{2, 58000, 'B', "Drumul Taberei"},
	{3, 63000, 'C', "Crangasi"},
	{3, 81000.99, 'C', "Titan"},
	{4, 105000, 'D', "Crangasi"},
	};

	int nrLocuinte = sizeof(locuinte) / sizeof(locuinte[0]);
	int lungimeNou;

	float maxPret;
	printf("Introduceti pretul maxim locuinta: ");
	scanf_s("%f", &maxPret);

	struct Locuinta** vNou2 = NULL; 
	vectorMutare(locuinte, &vNou2, &nrLocuinte, &lungimeNou, maxPret);

	printf("Vector nou: \n");
	afisare(vNou2, lungimeNou);
	free(vNou2); 

	printf("\nVector original: \n");
	afisare(locuinte, nrLocuinte);*/


#pragma endregion Mutare in vector nou

#pragma region 

	struct Locuinta v1[] = {		
		{2, 58000, 'B', "Drumul Taberei"},
		{4, 105000, 'C', "Crangasi"},
		{3, 63000, 'C', "Crangasi"},
	};
	struct Locuinta v2[] = {
		{3, 81000.99, 'C', "Titan"},
		{1, 49999.99, 'A', "Titan"},
	};

	int dim1 = sizeof(v1) / sizeof(v1[0]);
	int dim2 = sizeof(v2) / sizeof(v2[0]);
	int dimNoua;

	struct Locuinta** vConcat = NULL; 
	concatVectori(v1, v2, &vConcat, dim1, dim2, &dimNoua);

	printf("Vector concatenat: \n");
	afisare(vConcat, dimNoua); 

	free(vConcat);

#pragma endregion Concatenare vectori

}