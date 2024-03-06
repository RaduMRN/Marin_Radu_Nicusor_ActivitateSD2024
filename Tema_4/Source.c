#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Marfa {
	char* denumire;
	float pret;
	int cantitate;
	float* reviews;
	int nr_reviews;
};

struct Marfa citesteMarfa() {
	struct Marfa m;
	char buffer[100];
	printf("Introduceti denumirea marfii: ");
	fgets(buffer, 100, stdin);
	m.denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(m.denumire, buffer);
	printf("Introduceti pretul marfii: ");
	fgets(buffer, 100, stdin);
	m.pret = (float)atof(buffer);
	printf("Introduceti cantitatea marfii: ");
	fgets(buffer, 100, stdin);
	m.cantitate = (int)atoi(buffer);
	printf("Introduceti numarul de review-uri: ");
	fgets(buffer, 100, stdin);
	m.nr_reviews = (int)atoi(buffer);
	m.reviews = (float*)malloc(sizeof(float) * m.nr_reviews);
	for (int i = 0; i < m.nr_reviews; i++) {
		printf("Introduceti review-ul %d: ", i + 1);
		fgets(buffer, 100, stdin);
		m.reviews[i] = (float)atof(buffer);
	}
	return m;

}
void citesteMarfaV2(struct Marfa* m) {
	char buffer[100];
	printf("Introduceti denumirea marfii: ");
	fgets(buffer, 100, stdin);
	m->denumire = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(m->denumire, buffer);
	printf("Introduceti pretul marfii: ");
	fgets(buffer, 100, stdin);
	m->pret = (float)atof(buffer);
	printf("Introduceti cantitatea marfii: ");
	fgets(buffer, 100, stdin);
	m->cantitate = (int)atoi(buffer);
	printf("Introduceti numarul de review-uri: ");
	fgets(buffer, 100, stdin);
	m->nr_reviews = (int)atoi(buffer);
	m->reviews = (float*)malloc(sizeof(float) * m->nr_reviews);
	for (int i = 0; i < m->nr_reviews; i++) {
		printf("Introduceti review-ul %d: ", i + 1);
		fgets(buffer, 100, stdin);
		m->reviews[i] = (float)atof(buffer);

	}

}

float calculeazaValoareMarfa(struct Marfa* m) {
	return m->pret * m->cantitate;
}
float calculeazaReviewMediu(struct Marfa* m) {
	float s = 0;
	for (int i = 0; i < m->nr_reviews; i++) {
		s += m->reviews[i];
	}
	return s / m->nr_reviews;
}

void afiseazaMarfa(struct Marfa* m) {
	printf("Denumire: %s, Pret: %.2f, Cantitate: %d, Valoare Totala: %.2f, Review Mediu: %.2f\n",
		m->denumire,
		m->pret,
		m->cantitate,
		calculeazaValoareMarfa(m),
		calculeazaReviewMediu(m));
}
void afisareVectorMarfa(struct Marfa* m, int size)
{
	printf("\n================= AFISARE VECTOR MARFA ===================\n");
	for (int i = 0; i < size; i++)
	{
		afiseazaMarfa(&m[i]);
	}
}

struct Marfa copiazaMarfa(struct Marfa* m) {

	struct Marfa copie;

	copie.denumire = (char*)malloc((strlen(m->denumire) + 1) * sizeof(char));

	strcpy(copie.denumire, m->denumire);

	copie.pret = m->pret;

	copie.cantitate = m->cantitate;

	copie.nr_reviews = m->nr_reviews;

	copie.reviews = (float*)malloc(m->nr_reviews * sizeof(float));

	for (int i = 0; i < m->nr_reviews; i++) {

		copie.reviews[i] = m->reviews[i];

	}

	return copie;

}
void adaugaMarfaInVector(struct Marfa** m, int size, struct Marfa* marfaNoua, int* new_size)
{
	(*new_size) = size + 1;
	struct Marfa* new_m = (struct Marfa*)malloc((*new_size) * sizeof(struct Marfa));
	for (int i = 0; i < size; i++)
	{
		new_m[i] = (*m)[i];
	}
	//deep copy
	new_m[size] = copiazaMarfa(marfaNoua);
	(*m) = new_m;
}


struct Marfa* marfaReviewMediuInInterval(struct Marfa* m, int size, float pragi, float prags, int* new_size)
{
	*new_size = 0;
	for (int i = 0; i < size; i++) {
		if (calculeazaReviewMediu(&m[i]) >= pragi && calculeazaReviewMediu(&m[i]) <= prags)
		{
			(*new_size)++;
		}

	}
	struct Marfa* new_m = (struct Marfa*)malloc((*new_size) * sizeof(struct Marfa));
	int index = 0;
	for (int i = 0; i < size; i++)
	{
		if (calculeazaReviewMediu(&m[i]) >= pragi && calculeazaReviewMediu(&m[i]) <= prags)
		{
			//deep copy
			new_m[index] = m[i];
			new_m[index].denumire = (char*)malloc((strlen(m[i].denumire) + 1) * sizeof(char));
			strcpy(new_m[index].denumire, m[i].denumire);
			new_m[index].reviews = (float*)malloc(m[i].nr_reviews * sizeof(float));
			for (int j = 0; j < m[i].nr_reviews; j++)
			{
				new_m[index].reviews[j] = m[i].reviews[j];
			}
			index++;
		}
	}
	return new_m;

}
struct Marfa* marfaNrReviewsMaiMare(struct Marfa* m, int size, int nr, int* new_size)

{

	*new_size = 0;

	for (int i = 0; i < size; i++) {

		if (m[i].nr_reviews > nr)

		{

			(*new_size)++;

		}

	}

	struct Marfa* new_m = (struct Marfa*)malloc((*new_size) * sizeof(struct Marfa));

	int index = 0;

	for (int i = 0; i < size; i++)

	{

		if (m[i].nr_reviews > nr)

		{

			new_m[index] = m[i];

			new_m[index].denumire = (char*)malloc((strlen(m[i].denumire) + 1) * sizeof(char));

			strcpy(new_m[index].denumire, m[i].denumire);

			new_m[index].reviews = (float*)malloc(m[i].nr_reviews * sizeof(float));

			for (int j = 0; j < m[i].nr_reviews; j++)

			{

				new_m[index].reviews[j] = m[i].reviews[j];

			}

			index++;

		}

	}

	return new_m;

}

//concatenare vectori deep copy
struct Marfa* concatenareVectoriMarfaDeep(struct Marfa* m1, int size1, struct Marfa* m2, int size2, int* new_size)
{
	*new_size = size1 + size2;
	struct Marfa* new_m = (struct Marfa*)malloc((*new_size) * sizeof(struct Marfa));
	int index = 0;
	for (int i = 0; i < size1; i++)
	{
		new_m[index] = m1[i];
		new_m[index].denumire = (char*)malloc((strlen(m1[i].denumire) + 1) * sizeof(char));
		strcpy(new_m[index].denumire, m1[i].denumire);
		new_m[index].reviews = (float*)malloc(m1[i].nr_reviews * sizeof(float));
		for (int j = 0; j < m1[i].nr_reviews; j++)
		{
			new_m[index].reviews[j] = m1[i].reviews[j];
		}
		index++;
	}
	for (int i = 0; i < size2; i++)
	{
		new_m[index] = m2[i];
		new_m[index].denumire = (char*)malloc((strlen(m2[i].denumire) + 1) * sizeof(char));
		strcpy(new_m[index].denumire, m2[i].denumire);
		new_m[index].reviews = (float*)malloc(m2[i].nr_reviews * sizeof(float));
		for (int j = 0; j < m2[i].nr_reviews; j++)
		{
			new_m[index].reviews[j] = m2[i].reviews[j];
		}
		index++;
	}
	return new_m;
}
//concatenare vectori shallow copy
struct Marfa* concatenareVectoriMarfaShallow(struct Marfa* m1, int size1, struct Marfa* m2, int size2, int* new_size)
{
	*new_size = size1 + size2;
	struct Marfa* new_m = (struct Marfa*)malloc((*new_size) * sizeof(struct Marfa));
	int index = 0;
	for (int i = 0; i < size1; i++)
	{
		new_m[index] = m1[i];
		index++;
	}
	for (int i = 0; i < size2; i++)
	{
		new_m[index] = m2[i];
		index++;
	}
	return new_m;
}
void setPretMarfa(struct Marfa* m, float pretNou) {



	if (pretNou > 0)

		m->pret = pretNou;

	else

		printf("Pretul trebuie sa fie pozitiv!\n");

}

float* preturiOrdonate(struct Marfa* m, int dimensiune)
{
	float* preturi = (float*)malloc(sizeof(float) * dimensiune);
	for (int i = 0; i < dimensiune; i++)
	{
		preturi[i] = m[i].pret;
	}
	int index = 0;
	while (index < dimensiune - 1)
	{
		if (preturi[index] > preturi[index + 1])
		{
			float aux = preturi[index];
			preturi[index] = preturi[index + 1];
			preturi[index + 1] = aux;
			index = 0;
		}
	}
	return preturi;
}
float pretMaxim(struct Marfa* m, int dimensiune)
{
	float pretMaxim = m[0].pret;
	for (int i = 1; i < dimensiune; i++)
	{
		if (pretMaxim < m[i].pret)
		{
			pretMaxim = m[i].pret;
		}
	}
	return pretMaxim;
}
float pretMinim(struct Marfa* m, int dimensiune)
{
	float pretMinim = m[0].pret;
	for (int i = 1; i < dimensiune; i++)
	{
		if (pretMinim > m[i].pret)
		{
			pretMinim = m[i].pret;
		}
	}
	return pretMinim;
}
struct Marfa** marfaInIntervalePreturi(struct Marfa* m, int dimensiune, float pretMin, float pretMax, int nrIntervale, int** nrMarfaInterval)
{
	(*nrMarfaInterval) = (int*)malloc(sizeof(int) * nrIntervale);
	struct Marfa** matrice = (struct Marfa**)malloc(sizeof(struct Marfa*) * nrIntervale);
	for (int i = 0; i < nrIntervale; i++)
	{
		matrice[i] = NULL;
		(*nrMarfaInterval)[i] = 0;
	}
	float interval = (pretMax - pretMin) / nrIntervale;
	for (int i = 0; i < nrIntervale; i++)
	{
		float pragI = pretMin + i * interval;
		float pragS = pretMin + (i + 1) * interval;
		for (int j = 0; j < dimensiune; j++)
		{
			if (m[j].pret <= pragS && m[j].pret >= pragI)
			{

				if (matrice[i] == NULL)
				{
					matrice[i] = malloc(sizeof(struct Marfa) * 1);
					//DEEP COPY
					matrice[i][0] = copiazaMarfa(&m[j]);
				}
				struct Marfa* aux = malloc(sizeof(struct Marfa) * ((*nrMarfaInterval)[i] + 1));
				for (int k = 0; k < (*nrMarfaInterval)[i]; k++)
				{

					aux[k] = matrice[i][k];
				}
				free(matrice[i]);
				aux[(*nrMarfaInterval)[i]] = copiazaMarfa(&m[j]);
				matrice[i] = aux;
				(*nrMarfaInterval)[i] += 1;
			}
		}
	}
	return matrice;


}

//am folosit aceasta functie pentru a respecta intervalele dupa care am sortat matricea
float* intervalePreturi(float pretMin, float pretMax, int nrIntervale)
{
	float* intervale = (float*)malloc(sizeof(float) * (nrIntervale + 1));
	float interval = (pretMax - pretMin) / nrIntervale;
	for (int i = 0; i < nrIntervale + 1; i++)
	{
		intervale[i] = pretMin + i * interval;
	}
	return intervale;
}
void sortareMatriceDupaNrElementeLinie(struct Marfa*** m, int nrIntervale, int** nrMarfaIntervale, int** mapareIntervale)
{
	//acest vector de mapare va retine ordinea initiala a intervalelor
	for (int i = 0; i < nrIntervale; i++)
	{
		(*mapareIntervale)[i] = i;
	}
	//sortare matrice dupa numarul de elemente de pe linie respectand sttind ca vectorul de preturi este ordonat crescator si cu un element in plus
	for (int i = 0; i < nrIntervale - 1; i++)
	{
		for (int j = i + 1; j < nrIntervale; j++)
		{
			if ((*nrMarfaIntervale)[i] > (*nrMarfaIntervale)[j])
			{
				int aux = (*nrMarfaIntervale)[i];
				(*nrMarfaIntervale)[i] = (*nrMarfaIntervale)[j];
				(*nrMarfaIntervale)[j] = aux;
				struct Marfa* aux2 = (*m)[i];
				(*m)[i] = (*m)[j];
				(*m)[j] = aux2;
				//avand in vedere ca am schimbat linia i cu linia j in matrice trebuie sa schimb si 
				// pragul inferior dar si superior al intervalelor de preturi astfel folosim vectorul de mapare
				int aux3 = (*mapareIntervale)[i];
				(*mapareIntervale)[i] = (*mapareIntervale)[j];
				(*mapareIntervale)[j] = aux3;


			}
		}
	}

}
void afisareMarfaIntervalDupaSortare(struct Marfa** m, int* nrMarfaInterval, int nrIntervale, float* intervalePreturi, int* mapareIntervale)
{
	//cu ajutorul vectorului de mapare afisam matricea de marfuri in ordinea initiala a intervalelor respectand sortarea dupa numarul de elemente de pe linie
	for (int i = 0; i < nrIntervale; i++)
	{
		printf("Intervalul de preturi %.2f - %.2f contine %d marfuri\n", intervalePreturi[mapareIntervale[i]], intervalePreturi[mapareIntervale[i] + 1], nrMarfaInterval[i]);
		for (int j = 0; j < nrMarfaInterval[i]; j++)
		{
			afiseazaMarfa(&m[i][j]);
		}
	}
}
void afisareMarfaInterval(struct Marfa** m, int* nrMarfaInterval, int nrIntervale, float* intervalePreturi)
{
	for (int i = 0; i < nrIntervale; i++)
	{
		printf("Intervalul de preturi %.2f - %.2f contine %d marfuri\n", intervalePreturi[i], intervalePreturi[i + 1], nrMarfaInterval[i]);
		for (int j = 0; j < nrMarfaInterval[i]; j++)
		{
			afiseazaMarfa(&m[i][j]);
		}
	}
}

void eliberareMemorieMarfaInterval(struct Marfa*** m, int** nrMarfaInterval, int* nrIntervale, float** intervalePreturi)
{
	for (int i = 0; i < (*nrIntervale); i++)
	{
		for (int j = 0; j < (*nrMarfaInterval)[i]; j++)
		{
			free((*m)[i][j].denumire);
			free((*m)[i][j].reviews);
		}
		free((*m)[i]);
	}
	free(*m);
	free(*nrMarfaInterval);
	free(*intervalePreturi);
	(*m) = NULL;
	(*nrMarfaInterval) = NULL;
	(*intervalePreturi) = NULL;
	(*nrIntervale) = 0;
}
void eliberareMemorie(struct Marfa** m, int* size)
{
	for (int i = 0; i < (*size); i++)
	{
		free((*m)[i].denumire);
		free((*m)[i].reviews);
	}
	free(*m);
	(*m) = NULL;
	(*size) = 0;
}


struct Marfa citesteMarfaFisier(FILE* f)
{
	struct Marfa m;
	char buffer[100];
	fgets(buffer, 100, f);
	char* aux;
	aux = strtok(buffer, "\n");
	m.denumire = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy(m.denumire, aux);
	fgets(buffer, 100, f);
	m.pret = (float)atof(buffer);
	fgets(buffer, 100, f);
	m.cantitate = (int)atoi(buffer);
	fgets(buffer, 100, f);
	m.nr_reviews = (int)atoi(buffer);
	m.reviews = (float*)malloc(sizeof(float) * m.nr_reviews);
	for (int i = 0; i < m.nr_reviews; i++)
	{
		fgets(buffer, 100, f);
		m.reviews[i] = (float)atof(buffer);
	}
	return m;

}
struct Marfa* citesteVectorMarfaFisier(FILE* f, int* size)
{
	struct Marfa* m = NULL;
	(*size) = 0;
	char buffer[100];
	fgets(buffer, 100, f);
	(*size) = (int)atoi(buffer);
	if ((*size) > 0)
	{
		m = (struct Marfa*)malloc(sizeof(struct Marfa) * (*size));
		for (int i = 0; i < (*size); i++)
		{
			m[i] = citesteMarfaFisier(f);
		}
	}
	return m;

}
void scrieMarfaFisier(FILE* f, struct Marfa* m)
{
	fprintf(f, "%s\n", m->denumire);
	fprintf(f, "%.2f\n", m->pret);
	fprintf(f, "%d\n", m->cantitate);
	fprintf(f, "%d\n", m->nr_reviews);
	for (int i = 0; i < m->nr_reviews; i++)
	{
		fprintf(f, "%.2f\n", m->reviews[i]);
	}
}
void scrieVectorMarfaFisier(FILE* f, struct Marfa* m, int size)
{
	fprintf(f, "%d\n", size);
	for (int i = 0; i < size; i++)
	{
		scrieMarfaFisier(f, &m[i]);
	}
}


int main() {
	//struct Marfa m1 = citesteMarfa();
	//afiseazaMarfa(&m1);
	//struct Marfa m2;
	//citesteMarfaV2(&m2);
	//afiseazaMarfa(&m2);
	//struct Marfa* vector;
	//int size = 0;
	//adaugaMarfaInVector(&vector, 0, &m1, &size);
	//adaugaMarfaInVector(&vector, size, &m2, &size);
	//int size2 = 0;
	////folosim aceleasi structuri m1 si m2 dar facem deep copy, practic copiem continutul structurii in alta zona de memorie, 
	//// vectorul [vector2] are aceleasi elemente ca vectorul [vector] dar in alta zona de memorie in conditiile in care toate elementele din [vector] 
	////se incadreaza in intervalul [pragi, prags]
	//struct Marfa* vector2 = marfaReviewMediuInInterval(vector, size, 3, 4, &size2);
	//int sizeConcatenat = 0;
	////[vector] si [vector2] sunt vectori de structuri de tip Marfa si contin aceleasi elemente(m1 si m2) dar in alta zona de memorie
	////la randul lui [vectorConcatenat] este un vector de structuri de tip Marfa si contine toate elementele din [vector] si [vector2] dar in alta zona de memorie
	//struct Marfa* vectorConcatenat=concatenareVectoriMarfaDeep(vector, size, vector2, size2, &sizeConcatenat);
	//afisareVectorMarfa(vectorConcatenat, sizeConcatenat);
	//eliberareMemorie(&vector, &size);
	//eliberareMemorie(&vector2, &size2);
	//eliberareMemorie(&vectorConcatenat, &sizeConcatenat);
	FILE* f = fopen("Marfa.txt", "r");
	if (f)
	{
		int size = 0;
		struct Marfa* marfuri = citesteVectorMarfaFisier(f, &size);
		float pretMax = pretMaxim(marfuri, size);
		float pretMin = pretMinim(marfuri, size);
		int* nrMarfaInterval;
		int nrIntervale = 3;
		struct Marfa** matrice = marfaInIntervalePreturi(marfuri, size, pretMin, pretMax, nrIntervale, &nrMarfaInterval);
		float* intervale = intervalePreturi(pretMin, pretMax, nrIntervale);
		afisareMarfaInterval(matrice, nrMarfaInterval, nrIntervale, intervale);
		int* mapareIntervale = (int*)malloc(sizeof(int) * nrIntervale);
		sortareMatriceDupaNrElementeLinie(&matrice, nrIntervale, &nrMarfaInterval, &mapareIntervale);
		printf("\n================= MATRICE DUPA SORTARE ===================\n");
		afisareMarfaIntervalDupaSortare(matrice, nrMarfaInterval, nrIntervale, intervale, mapareIntervale);
		eliberareMemorieMarfaInterval(&matrice, &nrMarfaInterval, &nrIntervale, &intervale);
		free(mapareIntervale);
	}

	fclose(f);


}

