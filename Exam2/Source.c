#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Aeroport Aeroport;
struct Aeroport
{
	unsigned short int id;
	char* denumire;
	unsigned char nrTerminale;
	float suprafata;
};
Aeroport initializareAeroport(unsigned short int id, const char* denumire, unsigned char nrTerminale, float suprafata)
{
	Aeroport aeroport;
	aeroport.denumire = malloc(sizeof(char) * (1 + strlen(denumire)));
	strcpy(aeroport.denumire, denumire);
	aeroport.id = id;
	aeroport.nrTerminale = nrTerminale;
	aeroport.suprafata = suprafata;
	return aeroport;
}
Aeroport copiereAeroport(Aeroport aeroport)
{
	Aeroport aeroportNou;
	aeroportNou.denumire = malloc(sizeof(char) * (1 + strlen(aeroport.denumire)));
	strcpy(aeroportNou.denumire, aeroport.denumire);
	aeroportNou.id = aeroport.id;
	aeroportNou.nrTerminale = aeroport.nrTerminale;
	aeroportNou.suprafata = aeroport.suprafata;
	return aeroportNou;
}
Aeroport* citireAeroporturi(const char* fisier, int* nrAeroporturi)
{
	(*nrAeroporturi) = 0;
	FILE* f = fopen(fisier, "r");
	if (f)
	{
		Aeroport* aeroporturi=NULL;
		char buffer[400];
		while (fgets(buffer, sizeof(buffer), f))
		{
			char* token;
			Aeroport aeroport;
			token = strtok(buffer, ",");
			aeroport.denumire = malloc(sizeof(char) * (1 + strlen(token)));
			strcpy(aeroport.denumire, token);
			token = strtok(NULL, ",");
			aeroport.id = atoi(token);
			token = strtok(NULL, ",");
			aeroport.nrTerminale = atoi(token);
			token = strtok(NULL, ",");
			aeroport.suprafata = atof(token);
			(*nrAeroporturi) += 1;
			aeroporturi = realloc(aeroporturi, sizeof(Aeroport) * (*nrAeroporturi));
			aeroporturi[(*nrAeroporturi) - 1] = aeroport;
		}
		return aeroporturi;
	}
}
int functieHash(Aeroport aeroport,int nrClustere)
{
	return aeroport.nrTerminale % nrClustere;
}
void afisareAeroporturi(Aeroport* aeroporturi, int nrAeroporturi)
{
	for (int i = 0; i < nrAeroporturi; i++)
	{
		printf("Aeroportul -> %d; Denumire: %s; Nr. Terminale: %d; Suprafata: %5.2f\n", aeroporturi[i].id, aeroporturi[i].denumire, aeroporturi[i].nrTerminale, aeroporturi[i].suprafata);
	}
}
void creareMatrice(Aeroport*** matrice, int** nrAeroporturiPerLinie, Aeroport* aeroporturi, int nrAeroporturi, int nrLinii)
{
	(*matrice) = malloc(sizeof(Aeroport*) * nrLinii);
	(*nrAeroporturiPerLinie) = malloc(sizeof(int) * nrLinii);
	for (int i = 0; i < nrLinii; i++)
	{
		(*matrice)[i] = NULL;
		(*nrAeroporturiPerLinie)[i] = 0;
	}
	for (int i = 0; i < nrAeroporturi; i++)
	{
		int linie = functieHash(aeroporturi[i], nrLinii);
		(*nrAeroporturiPerLinie)[linie] += 1;
		(*matrice)[linie] = realloc((*matrice)[linie], sizeof(Aeroport) * (*nrAeroporturiPerLinie)[linie]);
		(*matrice)[linie][(*nrAeroporturiPerLinie)[linie] - 1] = copiereAeroport(aeroporturi[i]);//deep-copy
	}
}

void afisareMatrice(Aeroport** matrice, int* nrAeroporturiPerLinie, int nrLinii)
{
	for (int i = 0; i < nrLinii; i++)
	{
		printf("Linia -> %d\n", i + 1);
		afisareAeroporturi(matrice[i], nrAeroporturiPerLinie[i]);
	}
}

void sortareDupaNrElemente(Aeroport *** matrice, int** nrAeroporturiPerLinie, int nrLinii)
{
	int i = 0;
	while (i != nrLinii - 1)
	{
		if ((*nrAeroporturiPerLinie)[i] < (*nrAeroporturiPerLinie)[i + 1])
		{
			i += 1;
		}
		else
		{
			Aeroport* aux = (*matrice)[i];
			(*matrice)[i] = (*matrice)[i + 1];
			(*matrice)[i + 1] = aux;
			int nrAux = (*nrAeroporturiPerLinie)[i];
			(*nrAeroporturiPerLinie)[i] = (*nrAeroporturiPerLinie)[i + 1];
			(*nrAeroporturiPerLinie)[i + 1] = nrAux;
			i = 0;
		}
	}
}
void stergereAeroportDupaNume(Aeroport*** matrice, int** nrAeroporturiPerLinie, int* nrLinii, const char* nume)
{
	for (int i = 0; i < (*nrLinii); i++)
	{
		for (int j = 0; j < (*nrAeroporturiPerLinie)[i]; j++)
		{
			if (strcmp(nume, (*matrice)[i][j].denumire) == 0)
			{
				(*nrAeroporturiPerLinie)[i] -= 1;
				Aeroport* aux = malloc(sizeof(Aeroport) * (*nrAeroporturiPerLinie)[i]);
				int indx = 0;
				for (int k = 0; k < (*nrAeroporturiPerLinie)[i] + 1; k++)
				{
					if (k != j)
					{
						aux[indx++] = (*matrice)[i][k];
					}
				}
				free((*matrice)[i]);
				(*matrice)[i] = aux;
			}
		}
	}
}
void dezalocareMemorie(Aeroport*** matrice, int** nrAeroporturiPerLinie, int* nrLinii)
{
	for (int i = 0; i < (*nrLinii); i++)
	{
		for (int j = 0; j < (*nrAeroporturiPerLinie)[i]; j++)
		{
			free((*matrice)[i][j].denumire);
		}
		free((*matrice)[i]);
		(*matrice)[i] = NULL;
	}
	free((*nrAeroporturiPerLinie));
	free((*matrice));
	(*matrice) = NULL;
	(*nrAeroporturiPerLinie) = NULL;
	(*nrLinii) = 0;

}
void main()
{
	int nrAeroporturi;
	Aeroport* aeroporturi = citireAeroporturi("Aeroporturi.txt", &nrAeroporturi);
	afisareAeroporturi(aeroporturi, nrAeroporturi);
	int* nrAeroporturiPerLinie = NULL;
	int nrLinii = 3;
	Aeroport** matrice = NULL;
	creareMatrice(&matrice, &nrAeroporturiPerLinie, aeroporturi, nrAeroporturi, nrLinii);
	printf("\n\n");
	afisareMatrice(matrice, nrAeroporturiPerLinie, nrLinii);
	sortareDupaNrElemente(&matrice, &nrAeroporturiPerLinie, nrLinii);
	printf("\nMatrice sortata dupa nr. de elemente pe linie:\n");
	afisareMatrice(matrice, nrAeroporturiPerLinie, nrLinii);
	printf("\nMatrice dupa stergerea aeroportului U Cluj:\n");
	stergereAeroportDupaNume(&matrice, &nrAeroporturiPerLinie, &nrLinii, "U Cluj");
	afisareMatrice(matrice, nrAeroporturiPerLinie, nrLinii);
	printf("\nMatrice dupa stergerea aeroportului Kogalniceanu:\n");
	stergereAeroportDupaNume(&matrice, &nrAeroporturiPerLinie, &nrLinii, "Kogalniceanu");
	afisareMatrice(matrice, nrAeroporturiPerLinie, nrLinii);
	dezalocareMemorie(&matrice, &nrAeroporturiPerLinie, &nrLinii);
	printf("\nMatrice dupa dezalocare:\n");
	afisareMatrice(matrice, nrAeroporturiPerLinie, nrLinii);
	printf("Matrice: %p", matrice);

}