//#include <stdio.h>
//#include <malloc.h>
//#include <string.h>
//
//struct Avion {
//	int nrPers;
//	char* companie;
//	float pretBilet;
//};
//
//
//struct Avion initializare(int nrPers, const char* companie, float pretBilet) {
//
//	struct Avion avion;
//	avion.nrPers = nrPers;
//
//	avion.companie = (char*)malloc(strlen(companie) + 1);
//	strcpy_s(avion.companie, strlen(companie) + 1, companie);
//
//	avion.pretBilet = pretBilet;
//
//	return avion;
//}
//
//
//void afisareAvion(struct Avion avion) {
//	printf("Compania %s are un avion de %d locuri cu pretul de %.2f RON pe loc\n", avion.companie, avion.nrPers, avion.pretBilet);
//}
//
//
//void afisareVectorAvioane(struct Avion* avioane, int nrAvioane) {
//
//	if (avioane != NULL) {
//		for (int i = 0; i < nrAvioane; i++) {
//			afisareAvion(avioane[i]);
//		}
//	}
//}
//
//
//struct Avion* copiazaPrimeleNAvioane(struct Avion* avioane, int nrAvioane, int nrAvioaneCopiate) {
//
//	if (nrAvioaneCopiate < nrAvioane && nrAvioaneCopiate > 0)
//	{
//		struct Avion* avioaneCopiate = (struct Avion*)malloc(sizeof(struct Avion) * nrAvioaneCopiate);
//		for (int i = 0; i < nrAvioaneCopiate; i++) {
//			avioaneCopiate[i] = initializare(avioane[i].nrPers, avioane[i].companie, avioane[i].pretBilet);
//		}
//		return avioaneCopiate;
//	}
//	else return NULL;
//}
//
//
//void dezalocare(struct Avion** avioane, int* nrAvioane) {
//
//	if ((*avioane) != NULL)
//	{
//		for (int i = 0; i < *nrAvioane; i++)
//		{
//			free((*avioane)[i].companie);
//		}
//
//		free(*avioane);
//		*nrAvioane = 0;
//		*avioane = NULL;
//	}
//}
//
//
//void copiazaAvioaneIeftine(struct Avion* avioane, int nrAvioane, float pragPret, struct Avion** avioaneNoi, int* dimNoua) {
//
//	if (*avioaneNoi != NULL)
//		dezalocare(avioaneNoi, dimNoua);
//	else
//		*dimNoua = 0;
//
//	for (int i = 0; i < nrAvioane; i++) {
//		if (avioane[i].pretBilet < pragPret) {
//			(*dimNoua)++;
//		}
//	}
//
//	*avioaneNoi = (struct Avion*)malloc(sizeof(struct Avion) * (*dimNoua));
//
//	int index = 0;
//	for (int i = 0; i < nrAvioane; i++) {
//		if (avioane[i].pretBilet < pragPret)
//		{
//			(*avioaneNoi)[index++] = initializare(avioane[i].nrPers, avioane[i].companie, avioane[i].pretBilet);
//		}
//	}
//
//}
//
//
//struct Avion getAvionDupaCompanie(struct Avion* avioane, int dim, const char* companie) {
//
//	if (avioane != NULL && companie != NULL) {
//		for (int i = 0; i < dim; i++) {
//			if (avioane[i].companie != NULL)
//			{
//				if (strcmp(avioane[i].companie, companie) == 0)
//					return initializare(avioane[i].nrPers, avioane[i].companie, avioane[i].pretBilet);
//			}
//
//		}
//	}
//
//	return initializare(-1, "N/A", -1);
//
//}
//
//
//void main() {
//
//	int nrAvioane = 5;
//	struct Avion* avioane = (struct Avion*)malloc(sizeof(struct Avion) * nrAvioane);
//	for (int i = 0; i < nrAvioane; i++) {
//		avioane[i] = initializare(i + 50, "Tarom", 10 * i + 40);
//	}
//	afisareVectorAvioane(avioane, nrAvioane);
//
//
//
//	int nrAvioaneCopiate = 3;
//	struct Avion* avioaneCopiate = copiazaPrimeleNAvioane(avioane, nrAvioane, nrAvioaneCopiate);
//	printf("\nCopiere primele %d avioane:\n", nrAvioaneCopiate);
//	afisareVectorAvioane(avioaneCopiate, nrAvioaneCopiate);
//
//
//
//	struct Avion* avioaneIeftine = NULL;
//	int nrAvioaneIeftine = 0;
//	avioane[4].pretBilet = 30;
//	copiazaAvioaneIeftine(avioane, nrAvioane, 50, &avioaneIeftine, &nrAvioaneIeftine);
//	printf("\nAfisare avioane ieftine(sub %d RON):\n", 50);
//	afisareVectorAvioane(avioaneIeftine, nrAvioaneIeftine);
//
//
//
//	struct Avion avion = getAvionDupaCompanie(avioane, nrAvioane, "Tarom");
//	printf("\nAvion cautat: \n");
//	afisareAvion(avion);
//
//	dezalocare(&avioaneCopiate, &nrAvioaneCopiate);
//	dezalocare(&avioaneIeftine, &nrAvioaneIeftine);
//	free(avion.companie);
//
//	dezalocare(&avioane, &nrAvioane);
//
//
//}
