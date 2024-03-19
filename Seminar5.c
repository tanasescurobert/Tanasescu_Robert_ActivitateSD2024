#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h> 

typedef struct CafeneauaMea Cafenea;
typedef struct Nod Nod;

struct CafeneauaMea 
{
    char* nume;
    int nrLocuri;
    float suprafata;
};
struct Nod 
{
    Cafenea info;
    Nod* next;
};

Cafenea initializare(const char* nume, int nrLocuri, float suprafata) {
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = malloc(sizeof(char) * (strlen(nume) + 1));    
    strcpy(cafenea.nume, nume);   

    return cafenea;
}

Nod* inserareInceput(Cafenea c, Nod* cap)
{
    Nod* nou = malloc(sizeof(Nod));
    nou->next = cap;
    nou->info = initializare(c.nume, c.nrLocuri, c.suprafata); 

    return nou; 
}

void afisareCafenea(Cafenea c) {
    printf("\nDenumire: %s, Nr. locuri: %d, Suprafata: %.2f", c.nume, c.nrLocuri, c.suprafata);
}

void afisare(Nod* lista) {
    while (lista != NULL)
    {
        afisareCafenea(lista->info);
        lista = lista->next;
    }
}

//numele cafenelei cu densitatea cea mai mica (nrlocuri/suprafata)
char* numeCafeneaDensitateMin(Nod* lista) {
    if (lista != NULL)
    {
        if (lista->info.suprafata != 0)
        {
            float min = lista->info.nrLocuri / lista->info.suprafata;
            Nod* adresaMin = lista;
            lista = lista->next;
            while (lista != NULL)
            {
                if (lista->info.nrLocuri / lista->info.suprafata < min)
                {
                    min = lista->info.nrLocuri / lista->info.suprafata;
                    adresaMin = lista;
                }
                lista = lista->next;
            }
            char* numeMin;
            numeMin = malloc(sizeof(char) * (strlen(adresaMin->info.nume) + 1));
            strcpy(numeMin, adresaMin->info.nume); 
            return numeMin;
        }
    }
    return NULL;
}

void stergeLista(Nod** nod) {
    while (*nod != NULL)
    {
        Nod* aux;
        aux = *nod;
        *nod = (*nod)->next;
        free(aux->info.nume);
        free(aux);
    }
    *nod = NULL;
}

void inserareFinal(Nod** lista, Cafenea c) {
    if ((*lista) == NULL) {
        (*lista) = inserareInceput(c, *lista);
    }
    else {
        Nod* curent = (*lista);
        while (curent->next != NULL) {
            curent = curent->next;
        }
        Nod* n = malloc(sizeof(Nod));
        n->info = initializare(c.nume, c.nrLocuri, c.suprafata);  
        n->next = NULL; 
        curent->next = n;  
    }
}

void main() 
{
    Nod* cap = NULL;
    
    Cafenea c1 = initializare("Tucano", 12, 20);
    Cafenea c2 = initializare("Teds", 17, 17.3);
    Cafenea c3 = initializare("Urban", 65, 33);
    Cafenea c4 = initializare("Starbucks", 34, 67);

    cap = inserareInceput(c1, cap); 
    cap = inserareInceput(c2, cap); 
    cap = inserareInceput(c3, cap); 
    afisare(cap);

    char* numeMin = numeCafeneaDensitateMin(cap);
    printf("\n\nCafeneaua cu densitatea cea mai mica este %s\n", numeMin);
    
    inserareFinal(&cap, c4);
    afisare(cap);

    stergeLista(&cap);
    afisare(cap);

    free(c1.nume);
    c1.nume = NULL; 
    free(c2.nume);
    c2.nume = NULL;
    free(c3.nume);
    c3.nume = NULL;

    free(numeMin);



}