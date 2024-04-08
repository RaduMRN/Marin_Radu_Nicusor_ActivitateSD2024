#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int id;        
    char nume[100]; 
    int gradUrgenta; 
} Pacient;

typedef struct {
    Pacient* pacienti; // Vectori de pacienti
    int size;    
    int capacity;
} MaxHeap;


MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* h = (MaxHeap*)malloc(sizeof(MaxHeap));
    h->size = 0;
    h->capacity = capacity;
    h->pacienti = (Pacient*)malloc(sizeof(Pacient) * capacity);
    return h;
}


void siftUp(MaxHeap* h, int idx) {
    int parentIdx;
    Pacient temp;
    if (idx > 0) {
        parentIdx = (idx - 1) / 2;
        if (h->pacienti[parentIdx].gradUrgenta < h->pacienti[idx].gradUrgenta) {
            temp = h->pacienti[parentIdx];
            h->pacienti[parentIdx] = h->pacienti[idx];
            h->pacienti[idx] = temp;
            siftUp(h, parentIdx);
        }
    }
}

void maxHeapify(MaxHeap* h, int idx) {
    int left, right, largest;
    Pacient temp;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
    largest = idx;

    if (left < h->size && h->pacienti[left].gradUrgenta > h->pacienti[largest].gradUrgenta) {
        largest = left;
    }
    if (right < h->size && h->pacienti[right].gradUrgenta > h->pacienti[largest].gradUrgenta) {
        largest = right;
    }

    if (largest != idx) {
        temp = h->pacienti[idx];
        h->pacienti[idx] = h->pacienti[largest];
        h->pacienti[largest] = temp;
        maxHeapify(h, largest);
    }
}


void insert(MaxHeap* h, Pacient pacient) {
    if (h->size < h->capacity) {
        h->pacienti[h->size] = pacient;
        siftUp(h, h->size);
        h->size++;
    }
    else {
        printf("Unitatea de Primiri Urgente este plina!\n");
    }
}

Pacient extractMax(MaxHeap* h) {
    if (h->size > 0) {
        Pacient max = h->pacienti[0];
        h->pacienti[0] = h->pacienti[h->size - 1];
        h->size--;
        maxHeapify(h, 0);
        return max;
    }
    else {
        printf("Unitatea de Primiri Urgente este goala!\n");
        return;
    }
}

void printMaxHeap(MaxHeap* h) {
    for (int i = 0; i < h->size; i++) {
        printf("Pacient ID: %d, Nume: %s, Grad Urgenta: %d\n", h->pacienti[i].id, h->pacienti[i].nume, h->pacienti[i].gradUrgenta);
    }
}

int main() {
    int capacity = 10;
    MaxHeap* myHeap = createMaxHeap(capacity);
    insert(myHeap, (Pacient) { 1, "Ion Ionescu", 3 }); 
    insert(myHeap, (Pacient) { 2, "Maria Popescu", 5 });
    insert(myHeap, (Pacient) { 3, "Alexandru Marin", 2 }); 
    insert(myHeap, (Pacient) { 4, "Elena Munteanu", 4 }); 
    insert(myHeap, (Pacient) { 5, "George Dumitru", 5 }); 
    insert(myHeap, (Pacient) { 6, "Laura Stoica", 1 }); 
    insert(myHeap, (Pacient) { 7, "Bogdan Vlad", 4 });
    insert(myHeap, (Pacient) { 8, "Cristina Enache", 3 }); 
    insert(myHeap, (Pacient) { 9, "Daniel Teodorescu", 5 }); 
    insert(myHeap, (Pacient) { 10, "Ioana Grigorescu", 2 }); 


    printMaxHeap(myHeap);
    printf("\n========= PACIENTI PRIORITIZATI IN FUNCTIE DE GRADUL DE URGENTA ========= \n");
    while (myHeap->size > 0) {
        Pacient maxPacient = extractMax(myHeap);
        printf("Pacient tratat: ID: %d, Nume: %s, Grad Urgenta: %d\n", maxPacient.id, maxPacient.nume, maxPacient.gradUrgenta);
    }


    free(myHeap->pacienti);
    free(myHeap);

    return 0;

    return 0;
}
