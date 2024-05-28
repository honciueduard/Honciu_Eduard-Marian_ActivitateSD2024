#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Cinema Cinema;
typedef struct Nod Nod;

struct Cinema {
	int id;
	int nrFilme;
	char** listaFilme;
};

struct Nod {
	Cinema info;
	Nod* st;
	Nod* dr;
};

void inserareInArbore(Nod** radacina, Cinema c) {
	if (*radacina) {
		if ((*radacina)->info.id > c.id) {
			inserareInArbore(&((*radacina)->st), c);
		}
		else {
			inserareInArbore(&((*radacina)->dr), c);
		}

	}
	else {
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL;
		nod->st = NULL;
		nod->info = c;
		(*radacina) = nod;
	}
}

Cinema citireCinemaFisier(FILE* f) {
	Cinema c;
	fscanf(f, "%d", &(c.id));
	fscanf(f, "%d", &(c.nrFilme));
	if (c.nrFilme > 0) {
		c.listaFilme = (char**)malloc(c.nrFilme * sizeof(char*));
		for (int i = 0; i < c.nrFilme; i++) {
			char buffer[100];
			fscanf(f, "%s", buffer);
			c.listaFilme[i] = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(c.listaFilme[i], buffer);
		}
	}
	else {
		c.listaFilme = NULL;
	}
	return c;
}

Nod* citireArboreFisier(const char* numeFisier) {
	Nod* radacina = NULL;
	if (numeFisier != NULL && strlen(numeFisier) != 0) {
		FILE* f = fopen(numeFisier, "r");
		if (f != NULL) {
			int dim = 0;
			fscanf(f, "%d", &dim);
			for (int i = 0; i < dim; i++) {
				Cinema cinema;
				cinema = citireCinemaFisier(f);
				inserareInArbore(&radacina, cinema);
			}
		}
	}
	return radacina;
}

void afisareCinema(Cinema c) {
	printf("Cinematograful cu id-ul %d are in derulare %d filme:", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++) {
		printf("%s, ", c.listaFilme[i]);
	}
	printf("\n");
}

void afisareArborePreordine(Nod* rad) {
	if (rad) {
		afisareCinema(rad->info);
		afisareArborePreordine(rad->st);
		afisareArborePreordine(rad->dr);
	}
}

void afisareArboreInordine(Nod* rad) {
	if (rad) {
		afisareArboreInordine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

int calculNrFilmeRedate(Nod* rad) {
	if (rad) {
		int suma = rad->info.nrFilme;
		suma += calculNrFilmeRedate(rad->st);
		suma += calculNrFilmeRedate(rad->dr);
		return suma;
	}
	return 0;
}
void main() {
	Nod* arbore = NULL;
	arbore = citireArboreFisier("cinema.txt");
	afisareArboreInordine(arbore);

	printf("\n\nNumar filme: %d", calculNrFilmeRedate(arbore));

}