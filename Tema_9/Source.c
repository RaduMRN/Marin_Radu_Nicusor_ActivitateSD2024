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
void copiazaElev(Elev* destinatie, Elev sursa) {
	destinatie->id = sursa.id;
	destinatie->nrMedii = sursa.nrMedii;
	destinatie->medii = (float*)malloc(sizeof(float) * sursa.nrMedii);
	for (int i = 0; i < sursa.nrMedii; i++) {
		destinatie->medii[i] = sursa.medii[i];
	}
}

void minNod(Nod* head, Nod** minNode)
{
	if (!head) return;
	if (!(*minNode)) { (*minNode) = head; }
	if (head->info.id < (*minNode)->info.id)
	{
		(*minNode) = head;
	}
	minNod(head->right, minNode);
	minNod(head->left, minNode);
}
void eliberareNod(Nod** nod)
{
	free((*nod)->info.medii);
	free((*nod));
	(*nod) = NULL;
}
void stergereNodCautat(Nod** head, int nodDeSters)
{
	if (!(*head)) { return; }
	else if (nodDeSters < (*head)->info.id)
	{
		stergereNodCautat(&((*head)->left), nodDeSters);
	}
	else if (nodDeSters > (*head)->info.id)
	{
		stergereNodCautat(&((*head)->right), nodDeSters);
	}
	else
	{
		//CAZ FRUNZA
		if ((*head)->left == NULL && (*head)->right == NULL)
		{
			eliberareNod(&(*head));
		}
		//CAZ 1 NOD
		else if ((*head)->left && (*head)->right == NULL)
		{
			Nod* aux = (*head);
			(*head) = (*head)->left;
			eliberareNod(&aux);
		}
		else if ((*head)->right && (*head)->left == NULL)
		{
			Nod* aux = (*head);
			(*head) = (*head)->right;
			eliberareNod(&aux);
		}
		//CAZ 2 NODURI
		else
		{
			Nod* aux = NULL;
			minNod((*head)->right, &aux);
			copiazaElev(&(*head)->info, aux->info);
			stergereNodCautat(&((*head)->right), aux->info.id);
		}
	}

}
int inaltime(Nod* nod) {
	if (!nod) return 0;
	int inaltime_s = inaltime(nod->left);
	int inaltime_d = inaltime(nod->right);
	return 1 + (inaltime_s > inaltime_d ? inaltime_s : inaltime_d);
}

Nod* subarboreCuInaltimeMaiMare(Nod* radacina) {
	if (!radacina) return NULL;
	int inaltime_s = inaltime(radacina->left);
	int inaltime_d = inaltime(radacina->right);
	if (inaltime_s == inaltime_d) {
		printf("\nSubarborii sunt egali ca inaltime.\n");
		return NULL;
	}
	return inaltime_s > inaltime_d ? radacina->left : radacina->right;
}
int numarNoduri(Nod* nod) {
	if (!nod) return 0;
	return 1 + numarNoduri(nod->left) + numarNoduri(nod->right);
}
Nod* subarboreCuMaiMulteNoduri(Nod* radacina) {
	if (!radacina) return NULL;
	int numar_s = numarNoduri(radacina->left);
	int numar_d = numarNoduri(radacina->right);
	if (numar_s == numar_d) {
		printf("\nSubarborii au acelasi numar de noduri.\n");
		return NULL;
	}
	return numar_s > numar_d ? radacina->left : radacina->right;
}


void main() {
	Nod* head = citireFisier("Elevi.txt");

	afisareInOrder(head);
	printf("Media generala: %5.2f", calculeazaMedieGenerala(head));
	int nodMin = head->info.id;
	int nodDeSters = 6;
	printf("\n\nDupa stergerea nodului %d:\n", nodDeSters);
	stergereNodCautat(&head, nodDeSters);
	afisareInOrder(head);
	printf("\n\nInaltimea arborelui: %d", inaltime(head));
	Nod* aux = subarboreCuInaltimeMaiMare(head);
	if (aux)
	{
		printf("\n\nSubarborele cu intaltimea mai mare: %d", aux->info.id);
	}
	aux = subarboreCuMaiMulteNoduri(head);
	if (aux)
	{
		printf("\n\nSubarborele cu mai multe noduri: %d\n\n", aux->info.id);
	}
}