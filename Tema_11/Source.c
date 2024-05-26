#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Animal {
    char* denumire;
    int greutate;
    char categorie;
} Animal;

Animal creareAnimal(const char* denumire, int greutate, char categorie) {
    Animal animal;
    animal.denumire = malloc(sizeof(char) * (1 + strlen(denumire)));
    strcpy(animal.denumire, denumire);
    animal.greutate = greutate;
    animal.categorie = categorie;
    return animal;
}

void afisareAnimal(Animal animal) {
    printf("Animalul: %s -> Greutate: %d -> Categorie: %c\n", animal.denumire, animal.greutate, animal.categorie);
}

void eliberareAnimal(Animal* animal) {
    free(animal->denumire);
}


typedef struct Nod {
    Animal info;
    struct Nod* next;
} Nod;

Nod* initializareNod(Animal animal) {
    Nod* nod = malloc(sizeof(Nod));
    nod->info = animal;
    nod->next = NULL;
    return nod;
}

void eliberareNod(Nod** nod) {
    eliberareAnimal(&(*nod)->info);
    free(*nod);
    *nod = NULL;
}

void Push(Nod** stiva, Animal animal) {
    Nod* nodNou = initializareNod(animal);
    nodNou->next = (*stiva);
    (*stiva) = nodNou;
}

Animal Pop(Nod** stiva) {
    if ((*stiva)) {
        Animal animal = (*stiva)->info;
        Nod* aux = (*stiva);
        (*stiva) = (*stiva)->next;
        free(aux);
        return animal;
    }
    else {
        printf("Nu mai avem noduri in Stiva!\n");
        return creareAnimal("N/A", -1, '-');
    }
}

void afisareStiva(Nod** stiva) {
    Nod* aux = NULL;
    while (*stiva != NULL) {
        Animal animal = Pop(stiva);
        afisareAnimal(animal);
        Push(&aux, animal);
    }
    while (aux) {
        Push(stiva, Pop(&aux));
    }
}

int calculeazaKgTotal(Nod** stiva) {
    Nod* aux = NULL;
    int suma = 0;
    while ((*stiva)) {
        Animal animal = Pop(stiva);
        Push(&aux, animal);
        suma += animal.greutate;
    }
    while (aux) {
        Push(stiva, Pop(&aux));
    }
    return suma;
}

// coada pe lista simpla
typedef struct CoadaS {
    Nod* fata;
    Nod* spate;
} CoadaS;

CoadaS* creareCoadaS() {
    CoadaS* coada = (CoadaS*)malloc(sizeof(CoadaS));
    coada->fata = coada->spate = NULL;
    return coada;
}

int esteGoalaCoadaS(CoadaS* coada) {
    return coada->fata == NULL;
}

void EnqueueS(CoadaS* coada, Animal animal) {
    Nod* nodNou = initializareNod(animal);
    if (coada->spate == NULL) {
        coada->fata = coada->spate = nodNou;
    }
    else {
        coada->spate->next = nodNou;
        coada->spate = nodNou;
    }
}

Animal DequeueS(CoadaS* coada) {
    if (esteGoalaCoadaS(coada)) {
        printf("Coada este goala!\n");
        return creareAnimal("N/A", -1, '-');
    }
    Nod* aux = coada->fata;
    Animal animal = aux->info;
    coada->fata = coada->fata->next;
    if (coada->fata == NULL) {
        coada->spate = NULL;
    }
    free(aux);
    return animal;
}

void afisareCoadaS(CoadaS* coada) {
    Nod* current = coada->fata;
    while (current != NULL) {
        afisareAnimal(current->info);
        current = current->next;
    }
}

int calculeazaKgTotalCoadaS(CoadaS* coada) {
    int suma = 0;
    Nod* current = coada->fata;
    while (current != NULL) {
        suma += current->info.greutate;
        current = current->next;
    }
    return suma;
}

void eliberareCoadaS(CoadaS* coada) {
    while (!esteGoalaCoadaS(coada)) {
        Animal animal = DequeueS(coada);
        eliberareAnimal(&animal);
    }
    free(coada);
}

typedef struct NodD {
    Animal info;
    struct NodD* next;
    struct NodD* prev;
} NodD;

NodD* initializareNodD(Animal animal) {
    NodD* nod = (NodD*)malloc(sizeof(NodD));
    nod->info = animal;
    nod->next = NULL;
    nod->prev = NULL;
    return nod;
}

void eliberareNodD(NodD** nod) {
    eliberareAnimal(&(*nod)->info);
    free(*nod);
    *nod = NULL;
}

void PushD(NodD** stiva, Animal animal) {
    NodD* nodNou = initializareNodD(animal);
    if (*stiva != NULL) {
        (*stiva)->prev = nodNou;
    }
    nodNou->next = *stiva;
    *stiva = nodNou;
}

Animal PopD(NodD** stiva) {
    if (*stiva == NULL) {
        printf("Stiva este goala!\n");
        return creareAnimal("N/A", -1, '-');
    }
    Animal animal = (*stiva)->info;
    NodD* aux = *stiva;
    *stiva = (*stiva)->next;
    if (*stiva != NULL) {
        (*stiva)->prev = NULL;
    }
    free(aux);
    return animal;
}

void afisareStivaD(NodD** stiva) {
    NodD* aux = NULL;
    while (*stiva != NULL) {
        Animal animal = PopD(stiva);
        afisareAnimal(animal);
        PushD(&aux, animal);
    }
    while (aux != NULL) {
        PushD(stiva, PopD(&aux));
    }
}

int calculeazaKgTotalD(NodD** stiva) {
    NodD* aux = NULL;
    int suma = 0;
    while (*stiva != NULL) {
        Animal animal = PopD(stiva);
        PushD(&aux, animal);
        suma += animal.greutate;
    }
    while (aux != NULL) {
        PushD(stiva, PopD(&aux));
    }
    return suma;
}

//  coada pe lista dublu 
typedef struct CoadaD {
    NodD* fata;
    NodD* spate;
} CoadaD;

CoadaD* creareCoadaD() {
    CoadaD* coada = (CoadaD*)malloc(sizeof(CoadaD));
    coada->fata = coada->spate = NULL;
    return coada;
}

int esteGoalaCoadaD(CoadaD* coada) {
    return coada->fata == NULL;
}

void EnqueueD(CoadaD* coada, Animal animal) {
    NodD* nodNou = initializareNodD(animal);
    if (coada->spate == NULL) {
        coada->fata = coada->spate = nodNou;
    }
    else {
        coada->spate->next = nodNou;
        nodNou->prev = coada->spate;
        coada->spate = nodNou;
    }
}

Animal DequeueD(CoadaD* coada) {
    if (esteGoalaCoadaD(coada)) {
        printf("Coada este goala!\n");
        return creareAnimal("N/A", -1, '-');
    }
    NodD* aux = coada->fata;
    Animal animal = aux->info;
    coada->fata = coada->fata->next;
    if (coada->fata != NULL) {
        coada->fata->prev = NULL;
    }
    else {
        coada->spate = NULL;
    }
    free(aux);
    return animal;
}

void afisareCoadaD(CoadaD* coada) {
    NodD* current = coada->fata;
    while (current != NULL) {
        afisareAnimal(current->info);
        current = current->next;
    }
}

int calculeazaKgTotalCoadaD(CoadaD* coada) {
    int suma = 0;
    NodD* current = coada->fata;
    while (current != NULL) {
        suma += current->info.greutate;
        current = current->next;
    }
    return suma;
}

void eliberareCoadaD(CoadaD* coada) {
    while (!esteGoalaCoadaD(coada)) {
        Animal animal = DequeueD(coada);
        eliberareAnimal(&animal);
    }
    free(coada);
}

// stiva pe vector
typedef struct Stiva {
    Animal* animale;
    int top;
    int capacitate;
} Stiva;

Stiva* creareStiva(int capacitate) {
    Stiva* stiva = (Stiva*)malloc(sizeof(Stiva));
    stiva->capacitate = capacitate;
    stiva->top = -1;
    stiva->animale = (Animal*)malloc(capacitate * sizeof(Animal));
    return stiva;
}

int estePlina(Stiva* stiva) {
    return stiva->top == stiva->capacitate - 1;
}

int esteGoala(Stiva* stiva) {
    return stiva->top == -1;
}

void PushS(Stiva* stiva, Animal animal) {
    if (estePlina(stiva)) {
        printf("Stiva este plina!\n");
        return;
    }
    stiva->animale[++(stiva->top)] = animal;
}

Animal PopS(Stiva* stiva) {
    if (esteGoala(stiva)) {
        printf("Stiva este goala!\n");
        return creareAnimal("N/A", -1, '-');
    }
    return stiva->animale[(stiva->top)--];
}

void afisareStivaVector(Stiva* stiva) {
    if (esteGoala(stiva)) {
        printf("Stiva este goala!\n");
        return;
    }
    for (int i = stiva->top; i >= 0; i--) {
        afisareAnimal(stiva->animale[i]);
    }
}

int calculeazaKgTotalVector(Stiva* stiva) {
    int suma = 0;
    for (int i = 0; i <= stiva->top; i++) {
        suma += stiva->animale[i].greutate;
    }
    return suma;
}

void eliberareStiva(Stiva* stiva) {
    for (int i = 0; i <= stiva->top; i++) {
        eliberareAnimal(&stiva->animale[i]);
    }
    free(stiva->animale);
    free(stiva);
}

void main() {
    Animal a1 = creareAnimal("Girafa", 245, 'A');
    Animal a2 = creareAnimal("Leu", 198, 'C');
    Animal a3 = creareAnimal("Urs", 439, 'D');
    Animal a4 = creareAnimal("Leopard", 312, 'C');

    printf("Stiva pe lista simpla:\n");
    Nod* stiva = NULL;
    Push(&stiva, a1);
    Push(&stiva, a2);
    Push(&stiva, a3);
    Push(&stiva, a4);
    afisareStiva(&stiva);
    printf("Greutatea totala a animalelor: %d\n\n", calculeazaKgTotal(&stiva));

    printf("Stiva pe vector:\n");
    Stiva* stivaVector = creareStiva(10);
    PushS(stivaVector, a1);
    PushS(stivaVector, a2);
    PushS(stivaVector, a3);
    PushS(stivaVector, a4);
    afisareStivaVector(stivaVector);
    printf("Greutatea totala a animalelor: %d\n\n", calculeazaKgTotalVector(stivaVector));
    //eliberareStiva(stivaVector);

    printf("Stiva pe lista dublu inlantuita:\n");
    NodD* stivaD = NULL;
    PushD(&stivaD, a1);
    PushD(&stivaD, a2);
    PushD(&stivaD, a3);
    PushD(&stivaD, a4);
    afisareStivaD(&stivaD);
    printf("Greutatea totala a animalelor: %d\n\n", calculeazaKgTotalD(&stivaD));

    printf("Coada pe lista simpla:\n");
    CoadaS* coadaS = creareCoadaS();
    EnqueueS(coadaS, a1);
    EnqueueS(coadaS, a2);
    EnqueueS(coadaS, a3);
    EnqueueS(coadaS, a4);
    afisareCoadaS(coadaS);
    printf("Greutatea totala a animalelor: %d\n\n", calculeazaKgTotalCoadaS(coadaS));
    //eliberareCoadaS(coadaS);

    printf("Coada pe lista dublu inlantuita:\n");
    CoadaD* coadaD = creareCoadaD();
    EnqueueD(coadaD, a1);
    EnqueueD(coadaD, a2);
    EnqueueD(coadaD, a3);
    EnqueueD(coadaD, a4);
    afisareCoadaD(coadaD);
    printf("Greutatea totala a animalelor: %d\n\n", calculeazaKgTotalCoadaD(coadaD));
    eliberareCoadaD(coadaD);
}
