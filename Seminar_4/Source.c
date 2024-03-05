#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h> 

struct Aeroport {
    int id;
    char* nume;
    int nrTerminale;
};

struct Aeroport* adaugareAeroport(struct Aeroport* aeroporturi, struct Aeroport aeroport, int* dimensiune) {
    struct Aeroport* copie = (struct Aeroport*)realloc(aeroporturi, sizeof(struct Aeroport) * ((*dimensiune) + 1));
    copie[*dimensiune].nume = (char*)malloc(strlen(aeroport.nume) + 1);
    strcpy(copie[*dimensiune].nume, aeroport.nume);
    copie[*dimensiune].id = aeroport.id;
    copie[*dimensiune].nrTerminale = aeroport.nrTerminale;

    (*dimensiune)++;

    return copie;
}

struct Aeroport* citireFisier(const char* numeFisier, int* nrAeroporturi) {
    struct Aeroport* aeroporturi = NULL;
    *nrAeroporturi = 0;

    FILE* f = fopen(numeFisier, "r");
    if (!f) {
        printf("Eroare deschidere fisier!\n");
        return NULL; 
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), f)) {
        struct Aeroport aeroport;
        char* token = strtok(buffer, ",\n");

        aeroport.id = atoi(token);

        token = strtok(NULL, ",\n");
        aeroport.nume = (char*)malloc(strlen(token) + 1);
        strcpy(aeroport.nume, token);

        token = strtok(NULL, ",\n");
        aeroport.nrTerminale = atoi(token);

        aeroporturi = adaugareAeroport(aeroporturi, aeroport, nrAeroporturi);

        free(aeroport.nume);
    }

    fclose(f);
    return aeroporturi;
}

void afisareAeroport(const struct Aeroport aeroport) {
    printf("ID: %d, Nume: %s, Nr. Terminale: %d\n", aeroport.id, aeroport.nume, aeroport.nrTerminale);
}

void afisareVectorAeroporturi(const struct Aeroport* aeroporturi, int dimensiune) {
    printf("Afisare vector:\n");
    for (int i = 0; i < dimensiune; i++) {
        afisareAeroport(aeroporturi[i]);
    }
}

void dezalocareVector(struct Aeroport** aeroporturi, int dimensiune) {
    for (int i = 0; i < dimensiune; i++) {
        free((*aeroporturi)[i].nume);
    }
    free(*aeroporturi);
    *aeroporturi = NULL;
}

int main() {
    int dimensiune = 0;
    struct Aeroport* aeroporturi = citireFisier("aeroporturi.txt", &dimensiune);

    if (aeroporturi != NULL) {
        afisareVectorAeroporturi(aeroporturi, dimensiune);
        dezalocareVector(&aeroporturi, dimensiune);
    }

    return 0; 
}
