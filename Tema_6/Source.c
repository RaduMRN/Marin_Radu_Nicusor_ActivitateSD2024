#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Nod Nod;
typedef struct Marfa Marfa;
struct Marfa {
	char* denumire;
	float pret;
	int cantitate;
};
struct Nod {
	Marfa info;
	Nod* next;
	Nod* prev;
};
struct NodS {
	Marfa info;
	struct NodS* pNext;

};

Nod* creareNod(Marfa* m);
Marfa creareMarfa(const char* denumire, float pret, int cantitate);
void inserareInceput(Nod** cap, Marfa* m);
void citireFisier(const char* numeFisier, Nod** cap);
int numarNoduri(Nod* cap);
void stergereNodPozitie(Nod** cap, int pozitie, int nrNoduri);
void inserareSortareCriteriu(Nod** cap, Marfa* marfa);
void afisare(Nod* cap);
void eliberareNod(Nod** nod);


Marfa creareMarfa(const char* denumire, float pret, int cantitate)
{
	Marfa m;
	m.denumire = (char*)malloc((strlen(denumire) + 1) * sizeof(char));
	strcpy(m.denumire, denumire);
	m.pret = pret;
	m.cantitate = cantitate;
	return m;
}
Nod* creareNod(Marfa* m)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = creareMarfa(m->denumire, m->pret, m->cantitate);
	nou->next = NULL;
	nou->prev = NULL;
	return nou;
}
void inserareInceput(Nod** cap, Marfa* m) {
	Nod* nou = creareNod(m);
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		nou->next = *cap;
		(*cap)->prev = nou;
		*cap = nou;
	}
}
void citireFisier(const char* numeFisier, Nod** cap) {
	FILE* f = fopen(numeFisier, "r");
	if (f) {
		char buffer[100];
		char* token, sep[] = ",";
		while (fgets(buffer, 100, f)) {
			Marfa m;
			token = strtok(buffer, sep);
			m.denumire = (char*)malloc((strlen(token) + 1) * sizeof(char));
			strcpy(m.denumire, token);
			token = strtok(NULL, sep);
			m.pret = atof(token);
			token = strtok(NULL, sep);
			m.cantitate = atoi(token);
			inserareInceput(cap, &m);
		}
		fclose(f);
	}
	else {
		printf("Fisierul nu a putut fi deschis");
	}
}
void eliberareNod(Nod** nod) {

	free((*nod)->info.denumire);
	free((*nod));
	(*nod) = NULL;

}
int numarNoduri(Nod* cap) {
	int nr = 0;
	Nod* temp = cap;
	while (temp) {
		nr++;
		temp = temp->next;
	}
	return nr;
}
void stergereNodPozitie(Nod** cap, int pozitie, int nrNoduri) {
	if (pozitie < 0 || pozitie >= nrNoduri || *cap == NULL) {
		return;
	}

	Nod* temp = *cap;
	if (pozitie == 0 && nrNoduri == 1) {
		*cap = NULL;
		eliberareNod(&temp);
		return;
	}
	if (pozitie == 0) {
		*cap = temp->next;
		(*cap)->prev = NULL;
	}
	else {
		for (int i = 0; i < pozitie; i++) {
			temp = temp->next;
		}
		temp->prev->next = temp->next;
		if (temp->next != NULL) {
			temp->next->prev = temp->prev;
		}
	}
	eliberareNod(&temp);
}
void inserareSortareCriteriu(Nod** cap, Marfa* marfa)
{
	Nod* nou = creareNod(marfa);
	if (*cap == NULL) {
		*cap = nou;
	}
	else {
		Nod* temp = *cap;
		if (temp->info.pret > marfa->pret) {
			nou->next = temp;
			temp->prev = nou;
			*cap = nou;
		}
		else {
			while (temp->next != NULL && temp->next->info.pret < marfa->pret) {
				temp = temp->next;
			}
			nou->next = temp->next;
			nou->prev = temp;
			if (temp->next != NULL) {
				temp->next->prev = nou;
			}
			temp->next = nou;
		}
	}
}
void afisare(Nod* cap) {
	Nod* temp = cap;
	while (temp) {
		printf("Denumire: %s, Pret: %5.2f, Cantitate: %d, Adresa prev: %p -> Adresa: %p -> Adresa next: %p\n", temp->info.denumire, temp->info.pret, temp->info.cantitate, temp->prev, temp, temp->next);
		temp = temp->next;
	}
}
void afisareDescrescatoare(Nod* cap) {
	Nod* temp = cap;
	while (temp->next) {
		temp = temp->next;
	}
	while (temp) {
		printf("Denumire: %s, Pret: %5.2f, Cantitate: %d, Adresa prev: %p -> Adresa: %p -> Adresa next: %p\n", temp->info.denumire, temp->info.pret, temp->info.cantitate, temp->prev, temp, temp->next);
		temp = temp->prev;
	}
}
void eliberareLista(Nod** cap) {
	Nod* temp = *cap;
	while (temp) {
		Nod* temp2 = temp;
		temp = temp->next;
		eliberareNod(&temp2);
	}
	*cap = NULL;
}

//Implementati o functie care salveaza intr - o lista simplu inlantuita toate obiectele care indeplinesc o conditie stabilita de voi.
//Realizati deep copy, astfel incat elementele din listasimplu inlantuita sa fie diferite de cele din lista dublu inlantuita.
//Observati diferenta dintre utilizarea de lista inlantuita si vector(task - ul precedent);

//Inserarea intr-o lista simplu inlantuita comparativ cu un vector este mai eficienta deoarece nu trebuie sa realocam memorie pentru a insera un element nou.
struct NodS* inserareListaSimpluInlantuita(struct NodS* cap, struct Nod* capDublu, int cantitate) {
	struct Nod* temp = capDublu;
	while (temp) {
		if (temp->info.cantitate > cantitate) {
			struct NodS* nou = (struct NodS*)malloc(sizeof(struct NodS));
			nou->info = creareMarfa(temp->info.denumire, temp->info.pret, temp->info.cantitate);
			nou->pNext = NULL;
			if (cap == NULL) {
				cap = nou;
			}
			else {
				struct NodS* temp2 = cap;
				while (temp2->pNext) {
					temp2 = temp2->pNext;
				}
				temp2->pNext = nou;
			}
		}
		temp = temp->next;
	}
	return cap;
}
void afisareSimpluInlantuita(struct Nod* cap)
{
	while (cap)
	{
		printf("Denumire: %s, Pret: %5.2f, Cantitate: %d, Adresa: %p -> Adresa next: %p\n", cap->info.denumire, cap->info.pret, cap->info.cantitate, cap, cap->next);
		cap = cap->next;
	}
}
void eliberareListaSimpla(struct NodS** cap) {
	while(*cap)
	{
		struct NodS* temp = *cap;
		*cap = (*cap)->pNext;
		eliberareNod(&temp);
	}
}
//CIRCULARA

void transformareCirculara(Nod** cap) {
	Nod* temp = *cap;
	if (*cap != NULL) {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = *cap;
		(*cap)->prev = temp;
	}
}
int numarNoduriListaCirculara(Nod* cap) {
	int nr = 0;
	Nod* temp = cap;

	if (cap != NULL) {
		do {
			nr++;
			temp = temp->next;
		} while (temp != cap);
	}

	return nr;
}
void interschimbareInformatiiPozitii(Nod** cap, int pozitie1, int pozitie2) {
	if (pozitie1 < 0 || pozitie2 < 0 || pozitie1 == pozitie2 || *cap == NULL) {
		return;
	}
	Nod* temp1 = *cap;
	Nod* temp2 = *cap;
	for (int i = 0; i < pozitie1; i++) {
		temp1 = temp1->next;
	}
	for (int i = 0; i < pozitie2; i++) {
		temp2 = temp2->next;
	}
	Marfa aux = temp1->info;
	temp1->info = temp2->info;
	temp2->info = aux;
}
void afisareCirculara(Nod* cap) {
	Nod* temp = cap;
	if (cap != NULL) {
		do {
			printf("Denumire: %s, Pret: %5.2f, Cantitate: %d, Adresa prev: %p -> Adresa: %p -> Adresa next: %p\n", temp->info.denumire, temp->info.pret, temp->info.cantitate, temp->prev,temp, temp->next);
			temp = temp->next;
		} while (temp != cap);
	}
}
void eliberareListaCirculara(Nod** cap) {
	Nod* temp = *cap;
	if (*cap != NULL) {
		do {
			Nod* temp2 = temp;
			temp = temp->next;
			eliberareNod(&temp2);
		} while (temp != *cap);
	}
	*cap = NULL;
}


void main() {
	Nod* cap = NULL;
	citireFisier("Marfa.txt", &cap);
	afisare(cap);
	printf("\n");
	//Marfa m = creareMarfa("Lapte", 2.5, 100);
	//inserareSortareCriteriu(&cap, &m);
	//afisare(cap);
	//printf("\n\n");
	//stergereNodPozitie(&cap, 0, numarNoduri(cap));
	//afisare(cap);
	//printf("\n\n");
	//afisareDescrescatoare(cap);
	//printf("\n\n");
	//transformareCirculara(&cap);
	//afisareCirculara(cap);
	//printf("\n\n");
	//printf("Numar noduri lista circulara: %d\n", numarNoduriListaCirculara(cap));
	//eliberareListaCirculara(&cap);
	interschimbareInformatiiPozitii(&cap, 1, 3);
	afisare(cap);
	printf("\n Lista simplu inlantuita \n");
	struct NodS* nod = NULL;
	nod = inserareListaSimpluInlantuita(nod, cap, 5);
	afisareSimpluInlantuita(nod);
	eliberareLista(&cap);
	eliberareListaSimpla(&nod);


}