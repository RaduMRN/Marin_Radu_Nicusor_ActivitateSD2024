#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Mesaj Mesaj;
struct Mesaj {
    char* text;
    int prioritate;
};

typedef struct Heap Heap;
struct Heap {
    Mesaj* mesaje;
    int dim;
    int dimensiuneTotala;
};

Mesaj init(const char* text, int prioritate) {
    Mesaj m;
    m.text = (char*)malloc(strlen(text) + 1); 
    strcpy(m.text, text);
    m.prioritate = prioritate;

    return m;
}

Heap initHeap(int dimensiune) {
    Heap h;
    h.mesaje = (Mesaj*)malloc(sizeof(Mesaj) * dimensiune);
    h.dimensiuneTotala = dimensiune;
    h.dim = 0;

    return h;
}

void afisareMesaj(Mesaj m) {
    printf("#%d %s\n", m.prioritate, m.text);
}

void afisareHeap(Heap h) {
    for (int i = 0; i < h.dim; i++) {
        afisareMesaj(h.mesaje[i]);
    }
    printf("\n\n\n");
}

void afisareHeapTotal(Heap h) {
    for (int i = 0; i < h.dimensiuneTotala; i++) {
        afisareMesaj(h.mesaje[i]);
    }
    printf("\n\n\n");
}

void filtrareHeap(Heap h, int poz) {
    int leftChildPos = poz * 2 + 1;
    int rightChildPos = poz * 2 + 2;

    int pozMax = poz;

    if (leftChildPos < h.dim && h.mesaje[leftChildPos].prioritate > h.mesaje[pozMax].prioritate) {
        pozMax = leftChildPos;
    }

    if (rightChildPos < h.dim && h.mesaje[rightChildPos].prioritate > h.mesaje[pozMax].prioritate) {
        pozMax = rightChildPos;
    }

    if (pozMax != poz) {
        Mesaj aux = h.mesaje[poz];
        h.mesaje[poz] = h.mesaje[pozMax];
        h.mesaje[pozMax] = aux;

        filtrareHeap(h, pozMax);
    }
}

Mesaj getMesaj(Heap* h) {
    Mesaj aux = { 0 }; 

    if (h->dim > 0) {
        aux = h->mesaje[0];
        h->mesaje[0] = h->mesaje[h->dim - 1];
        h->dim--;

        for (int i = (h->dim / 2) - 1; i >= 0; i--) {
            filtrareHeap(*h, i);
        }
    }

    return aux;
}

void freeHeap(Heap* h) {
    if (h->mesaje != NULL) {
        for (int i = 0; i < h->dim; i++) {
            free(h->mesaje[i].text);
        }

        free(h->mesaje);
        h->mesaje = NULL;
        h->dim = 0;
        h->dimensiuneTotala = 0;
    }
}

int main() {
    Heap h = initHeap(6);
    h.mesaje[0] = init("Salut", 3);
    h.mesaje[1] = init("Salut ce faci", 8);
    h.mesaje[2] = init("Buna", 6);
    h.mesaje[3] = init("Noroc", 2);
    h.mesaje[4] = init("Ce mai zici", 9);
    h.mesaje[5] = init("Esti bine?", 4);

    h.dim = 6;

    afisareHeap(h);

    for (int i = (h.dim / 2) - 1; i >= 0; i--) {
        filtrareHeap(h, i);
    }

    afisareHeap(h);

    Mesaj m = getMesaj(&h);
    afisareMesaj(m);

    m = getMesaj(&h);
    afisareMesaj(m);
    m = getMesaj(&h);
    afisareMesaj(m);
    m = getMesaj(&h);
    afisareMesaj(m);

    printf("\nAfisare totala: \n");
    afisareHeapTotal(h);

    freeHeap(&h);
    return 0;
}
