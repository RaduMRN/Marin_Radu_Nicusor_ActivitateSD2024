#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Elev Elev;
struct Elev {
	int id;
	int nrMedii;
	float* medii;
};

typedef struct Nod Nod;
struct Nod {
	Elev info;
	Nod* left;
	Nod* right;
};

void insereazaArbore(Nod** head, Elev elev) {
	if ((*head) != NULL) {
		if ((*head)->info.id > elev.id) {
			insereazaArbore(&((*head)->left), elev);
		}
		else {
			insereazaArbore(&((*head)->right), elev);
		}
	}
	else {
		Nod* nod_adaugat = (Nod*)malloc(sizeof(Nod));
		nod_adaugat->info = elev;
		nod_adaugat->left = NULL;
		nod_adaugat->right = NULL;

		*head = nod_adaugat;
	}
}

Elev citireElev(FILE* f) {
	Elev e;
	fscanf(f, "%d", &e.id);
	fscanf(f, "%d", &e.nrMedii);

	e.medii = (float*)malloc(sizeof(float) * e.nrMedii);

	for (int i = 0; i < e.nrMedii; i++) {
		fscanf(f, "%f", &e.medii[i]);
	}

	return e;
}

Nod* citireFisier(const char* numeFisier) {
	Nod* arbore = NULL;

	if (numeFisier) {
		FILE* f = fopen(numeFisier, "r");

		int nrElevi;
		fscanf(f, "%d", &nrElevi);

		for (int i = 0; i < nrElevi; i++) {
			Elev e = citireElev(f);
			insereazaArbore(&arbore, e);
		}

		fclose(f);
	}

	return arbore;
}

void afisareElev(Elev e) {
	printf("ID: %d -> %d note: ", e.id, e.nrMedii);
	for (int i = 0; i < e.nrMedii; i++) {
		printf("%.2f ", e.medii[i]);
	}

	printf("\n");
}

void afisareInOrder(Nod* arbore) {
	if (arbore != NULL) {
		afisareInOrder(arbore->left);
		afisareElev(arbore->info);
		afisareInOrder(arbore->right);
	}
}

float calculeazaMedieElev(Elev e) {
	if (e.nrMedii > 0) {
		float medie = 0;
		for (int i = 0; i < e.nrMedii; i++) {
			medie += e.medii[i];
		}
		return medie / e.nrMedii;
	}

	return 0;
}

float calculeazaSumaNote(Nod* head, int* nrNote) {
	if (head != NULL) {
		float suma = 0;
		// r
		for (int i = 0; i < head->info.nrMedii; i++) {
			suma += head->info.medii[i];
		}
		(*nrNote) += head->info.nrMedii;

		//stanga
		float sumaStanga = calculeazaSumaNote(head->left, nrNote);

		//dreapta
		float sumaDreapta = calculeazaSumaNote(head->right, nrNote);

		return suma + sumaStanga + sumaDreapta;
	}

	return 0;
}

float calculeazaMedieGenerala(Nod* arbore) {
	int nrNote = 0;
	float suma = calculeazaSumaNote(arbore, &nrNote);

	if (nrNote)
		return suma / nrNote;

	return 0;
}

void main() {
	Nod* head = citireFisier("Elevi.txt");

	afisareInOrder(head);
	printf("Media generala: %5.2f", calculeazaMedieGenerala(head));
}