#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Galerie Galerie;
typedef struct Nod Nod;
typedef struct HashTable HashTable;
struct Galerie {
	int cod;
	char* nume;
	float pretIntrare;
};

struct Nod {
	Galerie info;
	Nod* next;
};

struct HashTable {
	Nod** vector;
	int dim;
};

HashTable initializareHashTable(int dimensiune) {
	HashTable hash;
	hash.dim = dimensiune;
	hash.vector = (Nod**)malloc(sizeof(Nod*) * dimensiune);
	for (int i = 0; i < dimensiune; i++) {
		hash.vector[i] = NULL;
	}
	return hash;
}

Galerie initGalerie(int cod, const char* nume, float pret) {
	Galerie g;
	g.cod = cod;
	g.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(g.nume, nume);
	g.pretIntrare = pret;
	return g;
}

int calculHash(int cod, const char* nume, int dimensiune)
{
	if (dimensiune > 0)
	{
		int rez = cod * strlen(nume);
		return rez % dimensiune;
	}
	return -1;
}

void inserareLaFinal(Nod** cap, Galerie galerie) {
	Nod* temp = (Nod*)malloc(sizeof(Nod));
	temp->info = galerie;
	temp->next = NULL;
	if (*cap)
	{
		Nod* aux = (*cap);
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = temp;
	}
	else
	{
		(*cap) = temp;
	}
}

void inserareGalerieInTabela(HashTable hash, Galerie galerie)
{
	if (hash.dim > 0)
	{
		int pozitie = calculHash(galerie.cod, galerie.nume, hash.dim);
		if (hash.vector[pozitie] != NULL)
		{
			//coliziune
			inserareLaFinal(&(hash.vector[pozitie]),galerie);

		}
		else
		{
			//nu am coliziune
			inserareLaFinal(&(hash.vector[pozitie]), galerie);
		}
	}
}
void afisareGalerie(Galerie g)
{
	printf("%d. Intrarea la galeria %s costa %.2f\n", g.cod, g.nume, g.pretIntrare);
}
void afisareListaGalerii(Nod* cap)
{
	while (cap)
	{

		afisareGalerie(cap->info);
		cap = cap->next;
	}

}


void afisareTabela(HashTable tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vector[i] != NULL)
		{
			printf("Clusterul: %d\n", (i + 1));
			afisareListaGalerii(tabela.vector[i]);
		}
	}
}

Galerie cautaGalerieDupaCheie(int cod, const char* nume, HashTable tabela)
{
	int pozitie = calculHash(cod, nume, tabela.dim);
	if (pozitie >= 0 && pozitie < tabela.dim)
	{
		Nod* p = tabela.vector[pozitie];
		while (p && p->info.cod != cod && strcmp(p->info.nume, nume) != 0)
		{
			p = p->next;
			
		}
		if (p)
		{
			return p->info;//SHALLOW COPY
		}
		else
		{
			return initGalerie(-1, "N/A", 0);
		}
	}
	else
	{
		return initGalerie(-1, "N/A", 0);
	}

}

void main() {

	Galerie g1=initGalerie(1,"Orizont",10);
	Galerie g2 = initGalerie(2, "Cercul armatei", 6);
	Galerie g3 = initGalerie(3, "Louvre", 30);
	Galerie g4 = initGalerie(4, "Antipa", 20);
	Galerie g5 = initGalerie(5, "Istorie", 15);
	Galerie g6 = initGalerie(6, "Geologie", 17);
	HashTable tabela = initializareHashTable(5);

	inserareGalerieInTabela(tabela, g1);
	inserareGalerieInTabela(tabela, g2);
	inserareGalerieInTabela(tabela, g3);
	inserareGalerieInTabela(tabela, g4);
	inserareGalerieInTabela(tabela, g5);
	inserareGalerieInTabela(tabela, g6);

	afisareTabela(tabela);

	Galerie g = cautaGalerieDupaCheie(1, "Orizont", tabela);
	printf("\nCautare: \n");
	afisareGalerie(g);
}



