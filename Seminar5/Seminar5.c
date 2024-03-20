#include<stdio.h>
#include<stdlib.h>

typedef struct Cafenea {
    char* nume;
    int nrLocuri;
    float suprafata;
} Cafenea;

typedef struct Nod {
    Cafenea info;
    struct Nod* next;
} Nod;

Cafenea initializareCafenea(const char* nume, int nrLocuri, float suprafata) {
    Cafenea cafenea;
    cafenea.nrLocuri = nrLocuri;
    cafenea.suprafata = suprafata;
    cafenea.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(cafenea.nume, nume);
    return cafenea;
}

Nod* inserareInceput(Cafenea c, Nod* cap) {
    Nod* nou = malloc(sizeof(Nod));
    nou->next = cap;
    nou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
    return nou;
}

void afisareCafenea(Cafenea c) {
    printf("\nDenumire: %s Nr scaune: %i Suprafata: %.2f\n", c.nume, c.nrLocuri, c.suprafata);
}

void afisareCafenele(Nod* lista) {
    while (lista != NULL) {
        afisareCafenea(lista->info);
        lista = lista->next;
    }
}

//numele cafenelei cu densitatea cea mai mica
char* numeCafeneaDensitateMinima(Nod* lista) {
    if (lista != NULL) {
        if (lista->info.suprafata != 0) {
            float minim = lista->info.nrLocuri / lista->info.suprafata;
            Nod* adresa = lista;
            lista = lista->next;
            while (lista != NULL) {
                if (lista->info.nrLocuri / lista->info.suprafata < minim) {
                    minim = lista->info.nrLocuri / lista->info.suprafata;
                    adresa = lista;
                }
                lista = lista->next;
            }
            char* nume = malloc(sizeof(char) * (strlen(adresa->info.nume) + 1));
            strcpy(nume, adresa->info.nume);
            return nume;
        }
    }
    return NULL;
}

void stergeLista(Nod** cap) {
    while (*cap != NULL) {
        Nod* aux;
        aux = (*cap);
        *cap = (*cap)->next;
        free(aux->info.nume);
        free(aux);
    }
    *cap = NULL;
}

void inserareFinal(Nod** lista, Cafenea c) {
    if ((*lista) == NULL) {
        (*lista) = inserareInceput(c, (*lista));
    }
    else {
        Nod* curent = *lista;
        while (curent->next != NULL) {
            curent = curent->next;
        }
        Nod* nou = (Nod*)malloc(sizeof(Nod));
        nou->info = initializareCafenea(c.nume, c.nrLocuri, c.suprafata);
        nou->next = NULL;
        curent->next = nou;
    }
}

void main() {
    Nod* cap = NULL;

    Cafenea cafenea = initializareCafenea("Tucano", 12, 20);
    Cafenea cafenea2 = initializareCafenea("Teds", 17, 17.3);
    Cafenea cafenea3 = initializareCafenea("Urban", 65, 33);
    Cafenea sb = initializareCafenea("SB", 25, 43);


    cap = inserareInceput(cafenea, cap);
    cap = inserareInceput(cafenea2, cap);
    cap = inserareInceput(cafenea3, cap);

    afisareCafenele(cap);
    char* numeMinim = numeCafeneaDensitateMinima(cap);
    printf("\nCafenea cu dens minima:%s\n", numeMinim);
    inserareFinal(&cap, sb);
    afisareCafenele(cap);
    stergeLista(&cap);
    afisareCafenele(cap);
    free(cafenea.nume);
    cafenea.nume = NULL;
    free(cafenea2.nume);
    cafenea2.nume = NULL;
    free(cafenea3.nume);
    cafenea3.nume = NULL;
    free(numeMinim);
}