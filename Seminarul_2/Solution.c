#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
//vectorul este o structura de date omogena, care ocupa o zona de memorie contigua

struct Calculator
{
	char* serie;
	float pret;
	int nrPorturi;
};

struct Calculator initializare(const char* serie, float pret, int nrPorturi)
{
	struct Calculator c;
	c.serie = (char*)malloc(sizeof(char) * (strlen(serie) + 1));
	strcpy(c.serie, serie);
	c.nrPorturi = nrPorturi;
	c.pret = pret;
	return c;
}

void afisareCalculator(struct Calculator c)
{
	printf("Calculatorul cu seria %s costa %5.2f si are %d porturi\n", c.serie, c.pret, c.nrPorturi);
}

void afisareVectorCalculatoare(struct Calculator* vector, int nrCalculatoare)
{
	if (nrCalculatoare > 0 && vector != NULL)
	{
		for (int i = 0; i < nrCalculatoare; i++)
		{
			afisareCalculator(vector[i]);
		}
	}


}

struct Calculator* copiazaNCalculatoare(struct Calculator* calculatoare, int nrCalculatoare, int nrCalculatoareCopiate)
{
	struct Calculator* copiate = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoareCopiate);
	for (int i = 0; i < nrCalculatoareCopiate; i++)
	{
		copiate[i] = calculatoare[i];
		copiate[i].serie = (char*)malloc(sizeof(char) * (1 + strlen(calculatoare[i].serie)));
		strcpy(copiate[i].serie, calculatoare[i].serie);
	}
	return copiate;
}

struct Calculator* copiazaCalculatoareCuMultePorturi(struct Calculator* calculatoare, int nrCalculatoare, int pragNrPorturi, int* nrCalculatoarePorturi)
{
	*nrCalculatoarePorturi = 0;
	for (int i = 0; i < nrCalculatoare; i++)
	{
		if (calculatoare[i].nrPorturi > pragNrPorturi)
		{
			(*nrCalculatoarePorturi)++;
		}
	}

	struct Calculator* v = (struct Calculator*)malloc(sizeof(struct Calculator) * (*nrCalculatoarePorturi));
	int k = 0;
	for (int i = 0; i < nrCalculatoare; i++)
	{
		if (calculatoare[i].nrPorturi > pragNrPorturi)
		{
			v[k++] = initializare(calculatoare[i].serie, calculatoare[i].pret, calculatoare[i].nrPorturi);
		}
	}
	return v;
}
struct Calculator** PretDat(struct Calculator* calculatoare, int nrCalculatoare, float valoareaPret, int* nrCalculatoarePret) {
	struct Calculator** potrivirecalculator = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoare);
	if (potrivirecalculator == NULL) {
		*nrCalculatoarePret = 0;
		return NULL;
	}

	int count = 0;
	for (int i = 0; i < nrCalculatoare; i++) {
		if (calculatoare[i].pret == valoareaPret) {
			potrivirecalculator[count++] = &calculatoare[i];
		}
	}

	*nrCalculatoarePret = count;
	return potrivirecalculator;
}

void dezalocare(struct Calculator** vector, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free((*vector)[i].serie);
	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}

void main()
{
	int nrCalculatoare = 5;
	struct Calculator* calculatoare = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoare);
	for (int i = 0; i < nrCalculatoare; i++)
	{
		calculatoare[i] = initializare("1234567890", i * 20 + 10, i + 1);
	}
	afisareVectorCalculatoare(calculatoare, nrCalculatoare);

	printf("\n\n----------------------------------\n\n");

	int nrCalculatoareCopiate = 3;

	struct Calculator* calculatoareCopiate = copiazaNCalculatoare(calculatoare, nrCalculatoare, nrCalculatoareCopiate);

	afisareVectorCalculatoare(calculatoareCopiate, nrCalculatoareCopiate);

	printf("\n\n----------------------------------\n\n");

	int nrCalculatoarePorturi = 0;
	struct Calculator* calculatoarePorturi = copiazaCalculatoareCuMultePorturi(calculatoare, nrCalculatoare, 3, &nrCalculatoarePorturi);

	afisareVectorCalculatoare(calculatoarePorturi, nrCalculatoarePorturi);
	printf("\n\n-");
	float pretDatlaCalculatoare = 50.00;
	int nrCalculatoarePret = 0;
	struct Calculator** calculatorulcupretulrespectiv = PretDat(calculatoare, nrCalculatoare, pretDatlaCalculatoare, &nrCalculatoarePret);
	if (calculatorulcupretulrespectiv != NULL) {
		printf("\nCalculatoare cu pretul %5.2f:\n", pretDatlaCalculatoare);
		for (int i = 0; i < nrCalculatoarePret; i++) {
			afisareCalculator(*calculatorulcupretulrespectiv[i]);
		}
		free(calculatorulcupretulrespectiv);
	}
	else {
		printf("\nNu s-au gasit calculatoare cu pretul %5.2f\n", pretDatlaCalculatoare);
	}

	printf("\n\n");

	dezalocare(&calculatoare, &nrCalculatoare);
}