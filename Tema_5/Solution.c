#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


struct Marfa {
	char* nume;
	int cantitate;
	float pret;
};
struct Node {
	struct Marfa* marfa;
	struct Node* next;
};

//declaratie de tip prototip pentru a putea apela functia inainte de a o defini
//deoarece C este un limbaj procedural si nu suporta forward declaration
//mai exact, nu suporta apelarea unei functii inainte de a o defini
struct Marfa* creareMarfa(const char* nume, int cantitate, float pret);
struct Node* creareNod(struct Marfa* marfa);
struct Node* inserareNod(struct Node* lista, struct Marfa* marfa);

struct Node* inserareNod(struct Node* lista, struct Marfa* marfa)
{
	struct Node* nod = creareNod(marfa);
	nod->next = lista;
	return nod;
}
struct Marfa* creareMarfa(const char* nume, int cantitate, float pret) {
	struct Marfa* marfa = (struct Marfa*)malloc(sizeof(struct Marfa));
	marfa->nume = (char*)malloc(strlen(nume) + 1);
	strcpy(marfa->nume, nume);
	marfa->cantitate = cantitate;
	marfa->pret = pret;
	return marfa;
}
struct Node* creareNod(struct Marfa* marfa) {
	struct Node* nod = (struct Node*)malloc(sizeof(struct Node));
	//un nod este format dintr-un pointer catre o marfa si un pointer catre urmatorul nod
	nod->marfa = marfa;
	nod->next = NULL;
	return nod;
}
struct Node* stergereNodPozitie(struct Node* lista, int pozitie) {
	int index = 1;
	struct Node* temp = NULL;
	if (pozitie == 1) {
		temp = lista;
		lista = lista->next;
	}
	else
	{
		struct Node* temp2 = lista;
		while (index < pozitie - 1) {
			temp2 = temp2->next;
			index++;
		}
		if (temp2->next != NULL) {
			//verificam daca nodul de sters nu este ultimul, adica exista un nod de sters
			struct Node* temp = temp2->next;
			//temp este nodul de sters
			temp2->next = temp->next;
		}
	}
	if (temp != NULL) {
		free(temp->marfa->nume);
		free(temp->marfa);
		free(temp);
	}
	return lista;
}
void inserareNodPozitieLista(struct Node** lista, struct Marfa* marfa, int pozitie) {
	struct Node* nod = creareNod(marfa);
	if (pozitie == 1) {
		nod->next = (*lista);
		(*lista) = nod;
	}
	else
	{
		struct Node* temp = (*lista);
		int index = 1;
		while (index < pozitie - 1) {
			temp = temp->next;
			index++;
		}
		nod->next = temp->next;
		temp->next = nod;
	}
}

void inserareNodSiSortare(struct Node** lista, struct Marfa* marfa) {
	struct Node* nod = creareNod(marfa);
	if ((*lista) == NULL) {
		(*lista) = nod;
	}
	else
	{
		//folosim temp pentru a parcurge lista
		struct Node* temp = (*lista);
		struct Node* temp2 = NULL;
		//folosim temp2 pentru a retine nodul anterior lui temp
		while (temp != NULL && temp->marfa->pret < marfa->pret) {
			temp2 = temp;
			temp = temp->next;
		}
		if (temp2 == NULL) {
			nod->next = (*lista);
			(*lista) = nod;
		}
		else
		{
			temp2->next = nod;
			nod->next = temp;
		}
	}
}

void sortareLista(struct Node* lista)
{
	//folosim doi pointeri pentru a parcurge lista si a compara elementele
	for (struct Node* i = lista; i != NULL; i = i->next)
	{
		for (struct Node* j = i->next; j != NULL; j = j->next)
		{
			if (i->marfa->pret > j->marfa->pret)
			{
				//interschimbam doar pointerii catre marfa
				//nu interschimbam nodurile in sine, adresele nodurilor raman aceleasi
				struct Marfa* temp = i->marfa;
				i->marfa = j->marfa;
				j->marfa = temp;
			}
		}
	}
}

struct Node* creareVectorNoduriConditie(struct Node* lista, float pret, int* size) {
	struct Marfa* vector = NULL;
	(*size) = 0;
	struct Node* temp = lista;
	int index = 0;
	while (temp != NULL) {
		if (temp->marfa->pret > pret) {
			vector = (struct Marfa*)realloc(vector, (index + 1) * sizeof(struct Marfa));
			vector[index].nume = (char*)malloc(strlen(temp->marfa->nume) + 1);
			strcpy(vector[index].nume, temp->marfa->nume);
			vector[index].cantitate = temp->marfa->cantitate;
			vector[index].pret = temp->marfa->pret;
			index++;
		}
		temp = temp->next;
	}
	(*size) = index;
	return vector;
}

struct Node* citireFisier(const char* numeFisier) {
	struct Node* lista = NULL;
	FILE* file = fopen(numeFisier, "r");
	if (file != NULL) {
		char buffer[100];
		while (fgets(buffer, 100, file)) {
			char* token = strtok(buffer, ",");
			const char* nume = token;
			token = strtok(NULL, ",");
			int cantitate = atoi(token);
			token = strtok(NULL, ",");
			float pret = atof(token);
			struct Marfa* marfa = creareMarfa(nume, cantitate, pret);
			lista = inserareNod(lista, marfa);
		}
		fclose(file);
	}
	return lista;
}

void afisareLista(struct Node* lista) {
	while (lista)
	{
		printf("Nume: %s, Cantitate: %d, Pret: %.2f; Adresa Nod Curent: %p -> Adresa Nod Urmator: %p\n", lista->marfa->nume, lista->marfa->cantitate, lista->marfa->pret, lista, lista->next);
		lista = lista->next;

	}
}

void dezalocareLista(struct Node* lista) {
	while (lista != NULL) {
		struct Node* temp = lista;
		lista = lista->next;
		free(temp->marfa->nume);
		free(temp->marfa);
		free(temp);
	}

}

void main()
{
	struct Node* lista = NULL;
	lista = citireFisier("marfa.txt");
	afisareLista(lista);
	struct Marfa* marfa = creareMarfa("Lapte", 100, 3.5);
	lista = inserareNod(lista, marfa);
	printf("\n Dupa inserare \n");
	afisareLista(lista);
	struct Marfa* marfa2 = creareMarfa("Paine", 200, 2.5);
	inserareNodPozitieLista(&lista, marfa2, 2);
	printf("\n Dupa inserare pozitie 2 \n");
	afisareLista(lista);
	struct Marfa* marfa3 = creareMarfa("Gogosi", 120, 4.9);
	inserareNodSiSortare(&lista, marfa3);
	printf("\n Inserare sortata \n");
	afisareLista(lista);
	sortareLista(lista);
	printf("\n Dupa sortare \n");
	afisareLista(lista);
	lista = stergereNodPozitie(lista, 2);
	printf("\n Dupa stergere \n");
	afisareLista(lista);
	printf("\n Vector: \n");
	int size = 0;
	struct Marfa* vector = creareVectorNoduriConditie(lista, 2.5, &size);
	for (int i = 0; i < size; i++) {
		printf("Nume: %s, Cantitate: %d, Pret: %.2f; Adresa: %p\n", vector[i].nume, vector[i].cantitate, vector[i].pret, vector[i]);
		free(vector[i].nume);
	}
	free(vector);
	dezalocareLista(lista);

}