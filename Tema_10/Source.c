#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Cartier Cartier;
struct Cartier {
    int id;
    char* nume;
    float suprafata;
};
typedef struct Nod Nod;
struct Nod {
    int BF;
    Cartier info;
    Nod* left;
    Nod* right;
};
typedef struct Lista Lista;
struct Lista {
    Cartier info;
    struct Lista* next;
};
typedef struct ListaDubla ListaDubla;
typedef struct NodD {
    Cartier info;
    struct NodD* prev;
    struct NodD* next;
} NodD;

typedef struct ListaDubla {
    NodD* first;
    NodD* last;
} ListaDubla;

void adaugaInLista(Lista** cap, Cartier info) {
    Lista* nou = malloc(sizeof(Lista));
    nou->info = info;
    nou->next = *cap;
    *cap = nou;
}
void adaugaInListaDubla(ListaDubla* ld, Cartier info) {
    NodD* nou = malloc(sizeof(NodD));
    nou->info = info;
    nou->next = NULL;
    nou->prev = NULL;
    if (ld->first == NULL) {
        ld->first = nou;
        ld->last = nou;
    }
    else {
        nou->next = ld->first;
        ld->first->prev = nou;
        ld->first = nou;
    }
}
void afisareCartier(Cartier cartier) {
    printf("ID: %d -> Cartierul: %s are suprafata %5.2f\n", cartier.id, cartier.nume, cartier.suprafata);
}
Nod* reechilibrare(Nod* radacina);
Nod* creareNod(Cartier cartier) {
    Nod* nodNou = malloc(sizeof(Nod));
    nodNou->info.id = cartier.id;
    nodNou->info.suprafata = cartier.suprafata;
    nodNou->info.nume = malloc(sizeof(char) * (1 + strlen(cartier.nume)));
    strcpy(nodNou->info.nume, cartier.nume);
    nodNou->left = NULL;
    nodNou->right = NULL;
    return nodNou;
}
void inserareInArbore(Nod** radacina, Cartier cartier) {
    if ((*radacina)) {
        if (cartier.id < (*radacina)->info.id) {
            inserareInArbore(&((*radacina)->left), cartier);
            *radacina = reechilibrare(*radacina);
        }
        if (cartier.id > (*radacina)->info.id) {
            inserareInArbore(&((*radacina)->right), cartier);
            *radacina = reechilibrare(*radacina);
        }
    }
    else {
        (*radacina) = creareNod(cartier);
    }
    *radacina = reechilibrare(*radacina);
}
Nod* citireFisier(const char* nume) {
    FILE* f = fopen(nume, "r");
    if (f) {
        Nod* radacina = NULL;
        char* token;
        char buffer[100];
        fgets(buffer, 100, f);
        int size = atoi(buffer);
        for (int i = 0; i < size; i++) {
            Cartier cartier;
            fgets(buffer, 100, f);
            cartier.id = atoi(buffer);
            fgets(buffer, 100, f);
            cartier.suprafata = atof(buffer);
            fgets(buffer, 100, f);
            token = strtok(buffer, "\n"); //Eliminam newline-ul adaugat de functia fgets;
            cartier.nume = malloc(sizeof(char) * (1 + strlen(token)));
            strcpy(cartier.nume, token);
            inserareInArbore(&radacina, cartier);
            free(cartier.nume);
        }
        return radacina;
    }
    else {
        printf("\nEroare la deschiderea fisierului!\n");
        return NULL;
    }
}
void inOrder(Nod* radacina) {
    if (radacina) {
        inOrder(radacina->left);
        printf("ID: %d -> %s: %5.2f; BF: %d\n", radacina->info.id, radacina->info.nume, radacina->info.suprafata, radacina->BF);
        inOrder(radacina->right);
    }
}
void preOrder(Nod* radacina) {
    if (radacina) {
        printf("ID: %d -> %s: %5.2f; BF: %d\n", radacina->info.id, radacina->info.nume, radacina->info.suprafata, radacina->BF);
        preOrder(radacina->left);
        preOrder(radacina->right);
    }
}
void postOrder(Nod* radacina) {
    if (radacina) {
        postOrder(radacina->left);
        postOrder(radacina->right);
        printf("ID: %d -> %s: %5.2f; BF: %d\n", radacina->info.id, radacina->info.nume, radacina->info.suprafata, radacina->BF);
    }
}
int inaltimeArbore(Nod* radacina) {
    if (!radacina) return 0;
    int inaltimeS = 1 + inaltimeArbore(radacina->left);
    int inaltimeD = 1 + inaltimeArbore(radacina->right);
    return inaltimeD >= inaltimeS ? inaltimeD : inaltimeS;
}
void calculBF(Nod* radacina) {
    if (radacina) {
        radacina->BF = inaltimeArbore(radacina->left) - inaltimeArbore(radacina->right);
        calculBF(radacina->left);
        calculBF(radacina->right);
    }
}
Nod* rotatieDreapta(Nod* radacina) {
    Nod* aux = radacina->left;
    radacina->left = aux->right;
    aux->right = radacina;
    radacina = aux;
    return radacina;
}
Nod* rotatieStanga(Nod* radacina) {
    Nod* aux = radacina->right;
    radacina->right = aux->left;
    aux->left = radacina;
    radacina = aux;
    return radacina;
}
Nod* rotatie_dreapta_stanga(Nod* radacina) {
    Nod* aux1 = radacina->right;
    Nod* aux2 = aux1->left;
    aux1->left = aux2->right;
    aux2->right = aux1;
    radacina->right = aux2->left;
    aux2->left = radacina;
    radacina = aux2;
    return radacina;
}
Nod* rotatie_stanga_dreapta(Nod* radacina) {
    Nod* aux1 = radacina->left;
    Nod* aux2 = aux1->right;
    aux1->right = aux2->left;
    aux2->left = aux1;
    radacina->left = aux2->right;
    aux2->right = radacina;
    radacina = aux2;
    return radacina;
}
Nod* reechilibrare(Nod* radacina) {
    calculBF(radacina);
    if (radacina->BF >= 2 && radacina->left->BF >= 1) {
        radacina = rotatieDreapta(radacina);
        calculBF(radacina);
    }
    else if (radacina->BF <= -2 && radacina->right->BF <= -1) {
        radacina = rotatieStanga(radacina);
        calculBF(radacina);
    }
    else if (radacina->BF >= 2 && radacina->left->BF <= -1) {
        radacina = rotatie_stanga_dreapta(radacina);
        calculBF(radacina);
    }
    else if (radacina->BF <= -2 && radacina->right->BF >= 1) {
        radacina = rotatie_dreapta_stanga(radacina);
        calculBF(radacina);
    }
    return radacina;
}
Nod* cautareNod(Nod* radacina, int id) {
    if (!radacina || radacina->info.id == id) {
        return radacina;
    }
    else if (id < radacina->info.id) {
        return cautareNod(radacina->left, id);
    }
    else {
        return cautareNod(radacina->right, id);
    }
}
void inOrderVector(Nod* radacina, Cartier v[], int* index) {
    if (radacina) {
        inOrderVector(radacina->left, v, index);
        v[(*index)++] = radacina->info;
        inOrderVector(radacina->right, v, index);
    }
}
void preOrderVector(Nod* radacina, Cartier v[], int* index) {
    if (radacina) {
        v[(*index)++] = radacina->info;
        preOrderVector(radacina->left, v, index);
        preOrderVector(radacina->right, v, index);
    }
}
void postOrderVector(Nod* radacina, Cartier v[], int* index) {
    if (radacina) {
        postOrderVector(radacina->left, v, index);
        postOrderVector(radacina->right, v, index);
        v[(*index)++] = radacina->info;
    }
}
void preOrderList(Nod* radacina, Lista** lista) {
    if (radacina) {
        adaugaInLista(lista, radacina->info);
        preOrderList(radacina->left, lista);
        preOrderList(radacina->right, lista);
    }
}
void inOrderList(Nod* radacina, Lista** lista) {
    if (radacina) {
        inOrderList(radacina->left, lista);
        adaugaInLista(lista, radacina->info);
        inOrderList(radacina->right, lista);
    }
}
void postOrderList(Nod* radacina, Lista** lista) {
    if (radacina) {
        postOrderList(radacina->left, lista);
        postOrderList(radacina->right, lista);
        adaugaInLista(lista, radacina->info);
    }
}
void preOrderListDubla(Nod* radacina, ListaDubla** lista) {
    if (radacina) {
        adaugaInListaDubla(lista, radacina->info);
        preOrderListDubla(radacina->left, lista);
        preOrderListDubla(radacina->right, lista);
    }
}
void inOrderListDubla(Nod* radacina, ListaDubla** lista) {
    if (radacina) {
        inOrderListDubla(radacina->left, lista);
        adaugaInListaDubla(lista, radacina->info);
        inOrderListDubla(radacina->right, lista);
    }
}
void postOrderListDubla(Nod* radacina, ListaDubla** lista) {
    if (radacina) {
        postOrderListDubla(radacina->left, lista);
        postOrderListDubla(radacina->right, lista);
        adaugaInListaDubla(lista, radacina->info);
    }
}
void afisareListaSimpla(Lista* cap) {
    while (cap) {
        printf("ID: %d -> %s: %5.2f; Nod: %p --> Next: %p\n", cap->info.id, cap->info.nume, cap->info.suprafata, cap, cap->next);
        cap = cap->next;
    }
}
void afisareListaDubla(ListaDubla ld) {
    NodD* aux = ld.first;
    printf("Navigare de la inceput la sfarsit:\n");
    while (aux) {
        printf("ID: %d -> %s: %5.2f; Prev: %p --> Nod: %p --> Next: %p\n", aux->info.id, aux->info.nume, aux->info.suprafata, aux->prev, aux, aux->next);
        aux = aux->next;
    }
    printf("Navigare de la sfarsit la inceput:\n");
    aux = ld.last;
    while (aux) {
        printf("ID: %d -> %s: %5.2f; Prev: %p --> Nod: %p --> Next: %p\n", aux->info.id, aux->info.nume, aux->info.suprafata, aux->prev, aux, aux->next);
        aux = aux->prev;
    }
}
void main() {
    Nod* radacina = citireFisier("Cartiere.txt");
    calculBF(radacina);
    printf("\nParcurgere in-ordine:\n");
    inOrder(radacina);
    printf("\nParcurgere pre-ordine:\n");
    preOrder(radacina);
    printf("\nParcurgere post-ordine:\n");
    postOrder(radacina);
    printf("\nInaltimea arborelui: %d\n", inaltimeArbore(radacina));
    printf("\nCautarea cartierului cu ID-ul: 14:\n");
    afisareCartier(cautareNod(radacina, 14)->info);
    ListaDubla ld;
    ld.first = NULL;
    ld.last = NULL;
    Lista* l = NULL;
    preOrderList(radacina, &l);
    preOrderListDubla(radacina, &ld);
    printf("\nLista simpla:\n");
    afisareListaSimpla(l);
    printf("\nLista dubla:\n");
    afisareListaDubla(ld);
}
