#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Quiz Quiz;
typedef struct Heap Heap;

struct Quiz {
	char* materie;
	int grileGresite;
};

struct Heap {
	Quiz* vector;
	int dim;
	int dimTotal;
};

Heap initializareHeap(int nr) {
	Heap heap;
	heap.vector = malloc(nr * sizeof(Quiz)); 
	heap.dimTotal = nr;  
	heap.dim = 0;  
	return heap; 
}

Quiz initializareQuiz(char* materie, int grileGresite) {
	Quiz q;

	q.materie = malloc(strlen(materie) + 1);
	strcpy(q.materie, materie);
	q.grileGresite = grileGresite;

	return q;
}

Heap adaugareQuizOnHeap(Quiz quiz, Heap heap) {
	if (heap.dim < heap.dimTotal)
	{
		heap.vector[heap.dim] = quiz;
		heap.dim++;
	}

	return heap;
}

void afisareQuiz(Quiz q) {
	printf("Materia: %s\t", q.materie);
	printf("Grile gresite: %d\n", q.grileGresite);

}

void afisareHeap(Heap heap) { 

	for (int i = 0; i < heap.dim; i++) {
		afisareQuiz(heap.vector[i]);
	}
}

void filtreazaHeap(Heap heap, int pozRadacina) {
	
	int nodSt = pozRadacina * 2 + 1; 
	int nodDr = pozRadacina * 2 + 2; 
	int idxMin = pozRadacina;

	if (nodSt < heap.dim && heap.vector[nodSt].grileGresite < heap.vector[idxMin].grileGresite)
	{
		idxMin = nodSt; 
	}

	if (nodDr < heap.dim && heap.vector[nodDr].grileGresite < heap.vector[idxMin].grileGresite)
	{
		idxMin = nodDr; 
	}

	if (idxMin == pozRadacina) {
		Quiz aux;
		aux = heap.vector[pozRadacina];
		heap.vector[pozRadacina] = heap.vector[idxMin];
		heap.vector[idxMin] = aux;
		if (idxMin * 2 + 1 < heap.dim - 1) {
			filtreazaHeap(heap, idxMin); 
		}		
	}

}

Quiz extragereMin(Heap* heap) {
	if (heap->dim > 0) {
		Quiz aux;
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->dim - 1];
		heap->vector[heap->dim - 1] = aux;

		heap->dim--;

		for (int i = heap->dim / 2 + 1; i > 0; i--) {
			filtreazaHeap((*heap), i);
		}

		return aux;
	}
	else {
		return initializareQuiz("N/A", -1);
	}
}

void dezalocareTotala(Heap* heap) {
	for (int i = 0; i < heap->dimTotal, i++) {
		free(heap->vector[i].materie)

	}
	
}

void main() {
	Heap heap;
	heap = initializareHeap(6);  
	heap.vector[0] = initializareQuiz("Structuri de date", 3);
	heap.vector[1] = initializareQuiz("Java", 7);
	heap.vector[2] = initializareQuiz("Baze de date", 5);
	heap.vector[3] = initializareQuiz("Structuri de date", 2);
	heap.vector[4] = initializareQuiz("ATP", 9);
	heap.vector[5] = initializareQuiz("MRAI", 4);

	heap.dim = 6;
	afisareHeap(heap);

	for (int i = heap.dim / 2 + 1; i > 0; i--) {
		filtreazaHeap(heap, i);
	}
	printf("\n");
	afisareHeap(heap);

	printf("\n");
	afisareQuiz(extragereMin(&heap));  
	afisareQuiz(extragereMin(&heap)); 
	afisareQuiz(extragereMin(&heap));
	afisareQuiz(extragereMin(&heap)); 




}