#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h> 

typedef struct CafeneauaMea Cafenea;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

struct CafeneauaMea
{
    char* nume;
    int nrLocuri;
    float suprafata;
};

struct Nod {
    Cafenea cafenea;
    Nod* anterior;
    Nod* urmator;
};

struct ListaDubla {
    Nod* cap;
    Nod* coada;
};

void inserareInceput(ListaDubla* listaDubla, Cafenea cafenea) {
    Nod* nod = malloc(sizeof(Nod));
    nod->anterior = NULL;
    nod->cafenea = cafenea;
    nod->urmator = listaDubla->cap;
    if (listaDubla->cap != NULL)
        listaDubla->cap->anterior = nod;
    else
        listaDubla->coada = nod;
    
    listaDubla->cap = nod;
}


Cafenea initializare(const char* nume, int nrLocuri, float suprafata) {
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);

    return cafenea;
}

void afisareCafenea(Cafenea c) {
    printf("\nDenumire: %s, Nr. locuri: %d, Suprafata: %.2f", c.nume, c.nrLocuri, c.suprafata);
}

void afisare(ListaDubla lista) {
    Nod* nod = lista.cap; 
    while (nod != NULL) 
    {
        afisareCafenea(nod->cafenea); 
        nod = nod->urmator;  
    }
}

ListaDubla stergeCafeneaDupaNume(ListaDubla lista, const char* nume) {
    if (nume == NULL)
        return lista;

    Nod* nod = lista.cap;
    while (nod && strcmp(nod->cafenea.nume, nume) != 0) {
        nod = nod->urmator;
    }

    if (nod != NULL)
    {
        if (nod->urmator == NULL && nod->anterior == NULL)
        {
            lista.cap = NULL; 
            lista.coada = NULL;
        }
        else 
        {
            if (nod->anterior == NULL)
            {
                lista.cap = nod->urmator;
                lista.cap->anterior = NULL;
            }
            else
            {
                if (nod->urmator == NULL)
                {
                    lista.coada = nod->anterior;
                    lista.coada->urmator = NULL;
                }
                else {
                    nod->anterior->urmator = nod->urmator;
                    nod->urmator->anterior = nod->anterior;
                }
            }
        }
        free(nod->cafenea.nume);
        free(nod);
    }

    return lista;
}

ListaDubla stergeToateCafenelele(ListaDubla lista) {
    while (lista.cap != NULL)
    {
        free(lista.cap->cafenea.nume);
        Nod* temp = lista.cap;
        lista.cap = lista.cap->urmator;
        free(temp);
    }
    lista.cap = NULL; 
    lista.coada = NULL; 
    return lista;
}

int nrTotalLocuri(ListaDubla lista) {
    if (lista.cap == NULL)
    {
        return 0;
    }

    int nrLocuri = 0;
    Nod* nod = lista.coada;

    while (nod != NULL)
    {
        nrLocuri += nod->cafenea.nrLocuri;
        nod = nod->anterior;
    }
    return nrLocuri;
}

void main()
{
    Cafenea c1 = initializare("Tucano", 12, 20);
    Cafenea c2 = initializare("Teds", 17, 17.3);
    Cafenea c3 = initializare("Urban", 65, 33);
    Cafenea c4 = initializare("Starbucks", 34, 67);
    
    ListaDubla listaDubla;
    listaDubla.cap = NULL; 
    listaDubla.coada = NULL;

    inserareInceput(&listaDubla, c1);
    inserareInceput(&listaDubla, c2); 
    inserareInceput(&listaDubla, c3); 
    inserareInceput(&listaDubla, c4);

    // lista initiala cu cafenele
    afisare(listaDubla);
    printf("\n");

    listaDubla = stergeToateCafenelele(listaDubla); 
    afisare(listaDubla);
    printf("\n");

    //listaDubla = stergeCafeneaDupaNume(listaDubla, "Teds");
    //afisare(listaDubla);
    //printf("\n");

    //listaDubla = stergeCafeneaDupaNume(listaDubla, "Starbucks");
    //afisare(listaDubla);
    //printf("\n"); 

    //listaDubla = stergeCafeneaDupaNume(listaDubla, "saddas"); // nu exista, nu se sterge nimic
    //afisare(listaDubla);
    //printf("\n"); 

    //listaDubla = stergeCafeneaDupaNume(listaDubla, "Tucano");
    //afisare(listaDubla);
    //printf("\n"); 

    //listaDubla = stergeCafeneaDupaNume(listaDubla, "Urban");
    //afisare(listaDubla);
}