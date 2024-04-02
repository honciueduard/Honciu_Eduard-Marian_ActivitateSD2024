#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CafeneauaMea Cafenea;

struct CafeneauaMea {
    char* nume;
    int nrLocuri;
    float suprafata;
};

typedef struct Nod {
    Cafenea cafenea;
    struct Nod* anterior;
    struct Nod* urmator;
} Nod;

typedef struct ListaDubla {
    struct Nod* cap;
    struct Nod* coada;
} ListaDubla;

void inserareInceput(ListaDubla* lista, Cafenea cafenea) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->anterior = NULL;
    nou->cafenea = cafenea;
    nou->urmator = lista->cap;
    if (lista->cap != NULL) {
        lista->cap->anterior = nou;
        lista->cap = nou;
    }
    else {
        lista->coada = nou;
    }
    lista->cap = nou;
}

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);

    return cafenea;
}

void afisareCafenea(Cafenea c) {
    printf("\nDenumire: %s Nr scaune: %i Suprafata %.2f\n", c.nume, c.nrLocuri, c.suprafata);
}

void afisareLista(ListaDubla lista) {
    Nod* nod = lista.cap;

    while (nod != NULL) {
        afisareCafenea(nod->cafenea);
        nod = nod->urmator;
    }
}

ListaDubla stergeCafeneaDupaNume(ListaDubla lista, const char* nume) {
    if (nume == NULL) {
        return lista;
    }
    Nod* nod = lista.cap;

    while (nod && strcmp(nod->cafenea.nume, nume) != 0) {
        nod = nod->urmator;
    }
    if (nod != NULL) {
        if (nod->urmator == NULL && nod->anterior == NULL) {
            lista.cap = NULL;
            lista.coada = NULL;
        }
        else if (nod->anterior == NULL) {
            lista.cap = nod->urmator;
            lista.cap->anterior = NULL;
        }
        else if (nod->urmator == NULL) {
            lista.coada = nod->anterior;
            lista.coada->urmator = NULL;
        }
        else {
            nod->anterior->urmator = nod->urmator;
            nod->urmator->anterior = nod->anterior;
        }
        free(nod->cafenea.nume);
        free(nod);
        return lista;
    }
    else {
        return lista;
    }
}

ListaDubla stergeLista(ListaDubla lista) {
    while (lista.cap != NULL) {
        free(lista.cap->cafenea.nume);
        Nod* temp = lista.cap;
        lista.cap = lista.cap->urmator;
        free(temp);
    }
    lista.cap = NULL;
    lista.coada = NULL;
    return lista;
}

int NrTotalLocuri(ListaDubla lista) {
    if (lista.cap == NULL) return 0;
    int nrLocuri = 0;
    Nod* nod = lista.coada;
    while (nod != NULL) {
        nrLocuri += nod->cafenea.nrLocuri;
        nod = nod->anterior;
    }
    return nrLocuri;
}

void main() {
    ListaDubla lista;
    lista.cap = NULL;
    lista.coada = NULL;

    Cafenea cafenea1 = initializareCafenea("Tucano", 12, 20);
    Cafenea cafenea2 = initializareCafenea("Teds", 17, 17.3);
    Cafenea cafenea3 = initializareCafenea("Urban", 19, 33);
    Cafenea cafenea4 = initializareCafenea("Starbucks", 25, 43);

    inserareInceput(&lista, cafenea1);
    inserareInceput(&lista, cafenea2);
    inserareInceput(&lista, cafenea3);
    inserareInceput(&lista, cafenea4);

    afisareLista(lista);

    /*printf("\n-----------------------\n");

    lista = stergeCafeneaDupaNume(lista, "Teds");
    afisareLista(lista);

    printf("\n-----------------------\n");

    lista = stergeCafeneaDupaNume(lista, "Tucano");
    afisareLista(lista);

    printf("\n-----------------------\n");

    lista = stergeCafeneaDupaNume(lista, "Starbucks");
    afisareLista(lista);

    printf("\n-----------------------\n");

    lista = stergeCafeneaDupaNume(lista, "Sb");
    afisareLista(lista);

    printf("\n-----------------------\n");

    lista = stergeCafeneaDupaNume(lista, "Urban");
    afisareLista(lista);

    printf("\n-----------------------\n");

    lista = stergeLista(lista);
    afisareLista(lista);*/

    printf("\n-----------------------\n");

    int nrLocuri = NrTotalLocuri(lista);
    printf("\nNr locuri: %d", nrLocuri);

}