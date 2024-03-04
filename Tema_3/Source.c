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



struct Marfa* citesteMarfa(struct Marfa* m) {

	m->denumire = (char*)malloc(100 * sizeof(char) + 1);

	printf("Introduceti denumirea marfii: ");

	fgets(m->denumire, 100, stdin);

	m->denumire[strcspn(m->denumire, "\n")] = 0;

	printf("Introduceti pretul marfii: ");

	scanf("%f", &m->pret);

	printf("Introduceti cantitatea marfii: ");

	scanf("%d", &m->cantitate);

	printf("Introduceti numarul de review-uri: ");

	scanf("%d", &m->nr_reviews);

	m->reviews = (float*)malloc(m->nr_reviews * sizeof(float));

	for (int i = 0; i < m->nr_reviews; i++) {

		printf("Introduceti review-ul %d: ", i + 1);

		scanf("%f", &m->reviews[i]);

	}

	return m;

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

	printf("---------------------------------\n");

	printf("Denumire marfa: %s\n", m->denumire);

	printf("=================================\n");

	printf("Pret marfa: %.2f\n", m->pret);

	printf("=================================\n");

	printf("Cantitate marfa: %d\n", m->cantitate);

	printf("=================================\n");

	printf("Valoare totala pentru %s: %.2f\n", m->denumire, calculeazaValoareMarfa(m));

	printf("=================================\n");

	printf("Review mediu: %.2f\n", calculeazaReviewMediu(m));

	printf("---------------------------------\n");



}
void afisareVectorMarfa(struct Marfa* m, int size)

{

	printf("\n================= AFISARE VECTOR MARFA ===================\n");

	for (int i = 0; i < size; i++)

	{

		afiseazaMarfa(&m[i]);

	}

}
void afisareVectoriMarfa(struct Marfa** m, int size)

{

	printf("\n================= AFISARE VECTORI MARFA ===================\n");

	for (int i = 0; i < size; i++)

	{

		afiseazaMarfa(m[i]);

	}

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

struct Marfa** concatenareVectoriMarfa(struct Marfa* m1, int size1, struct Marfa* m2, int size2, int* new_size)

{

	*new_size = size1 + size2;

	struct Marfa** new_m = (struct Marfa**)malloc((*new_size) * sizeof(struct Marfa*));

	for (int i = 0; i < size1; i++)

	{

		new_m[i] = (struct Marfa*)malloc(sizeof(struct Marfa));

		new_m[i]->denumire = (char*)malloc((strlen(m1[i].denumire) + 1) * sizeof(char));

		strcpy(new_m[i]->denumire, m1[i].denumire);

		new_m[i]->reviews = (float*)malloc(m1[i].nr_reviews * sizeof(float));

		for (int j = 0; j < m1[i].nr_reviews; j++)

		{

			new_m[i]->reviews[j] = m1[i].reviews[j];

		}

		new_m[i]->pret = m1[i].pret;

		new_m[i]->cantitate = m1[i].cantitate;

		new_m[i]->nr_reviews = m1[i].nr_reviews;

	}

	for (int i = 0; i < size2; i++)

	{

		new_m[i + size1] = (struct Marfa*)malloc(sizeof(struct Marfa));

		new_m[i + size1]->denumire = (char*)malloc((strlen(m2[i].denumire) + 1) * sizeof(char));

		strcpy(new_m[i + size1]->denumire, m2[i].denumire);

		new_m[i + size1]->reviews = (float*)malloc(m2[i].nr_reviews * sizeof(float));

		for (int j = 0; j < m2[i].nr_reviews; j++)

		{

			new_m[i + size1]->reviews[j] = m2[i].reviews[j];

		}

		new_m[i + size1]->pret = m2[i].pret;

		new_m[i + size1]->cantitate = m2[i].cantitate;

		new_m[i + size1]->nr_reviews = m2[i].nr_reviews;

	}

	return new_m;

}
void setPretMarfa(struct Marfa* m, float pretNou) {



	if (pretNou > 0)

		m->pret = pretNou;

	else

		printf("Pretul trebuie sa fie pozitiv!\n");

}
void eliberareMemorie(struct Marfa** m, int size)

{

	for (int i = 0; i < size; i++)

	{

		free((*m)[i].denumire);

		free((*m)[i].reviews);

	}

	free(*m);

	*m = NULL;

}
void eliberareMemorieVector(struct Marfa*** m, int size)

{

	for (int i = 0; i < size; i++)

	{

		free((*m)[i]->denumire);

		free((*m)[i]->reviews);

		free((*m)[i]);

	}

	free(*m);

	*m = NULL;

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

	//struct Marfa m1;
	//citesteMarfa(&m1);
	//afiseazaMarfa(&m1);
	//float pretNou;
	//printf("\n\nIntroduceti noul pret al marfii: ");
	//scanf("%f", &pretNou);
	//setPretMarfa(&m1, pretNou);
	//printf("\n\n\nDupa actualizarea pretului:\n");
	//afiseazaMarfa(&m1);
	//free(m1.denumire);
	//free(m1.reviews);
	//struct Marfa* v;
	//int size;
	//printf("Introduceti numarul de marfuri: ");
	//scanf("%d", &size);
	//v = (struct Marfa*)malloc(size * sizeof(struct Marfa));
	//for (int i = 0; i < size; i++)
	//{
	//	while (getchar() != '\n');
	//	citesteMarfa(&v[i]);
	//}

	//afisareVectorMarfa(v, size);
	//int new_size;
	//struct Marfa* new_m = marfaReviewMediuInInterval(v, size, 3, 4, &new_size);
	//printf("Afisare marfuri cu review-uri in intervalul [3, 4]:\n");
	//afisareVectorMarfa(new_m, new_size);
	//int new_size2;
	//printf("Afisare marfuri cu numarul de review-uri mai mare decat 2:\n");
	//struct Marfa* new_m2 = marfaNrReviewsMaiMare(v, size, 2, &new_size2);
	//afisareVectorMarfa(new_m2, new_size2);
	//eliberareMemorie(&v, size);
	//eliberareMemorie(&new_m, new_size);
	//eliberareMemorie(&new_m2, new_size);
	//struct Marfa* vector1;
	//int size1;
	//printf("Introduceti numarul de marfuri pentru primul vector: ");
	//scanf("%d", &size1);
	//vector1 = (struct Marfa*)malloc(size1 * sizeof(struct Marfa));
	//for (int i = 0; i < size1; i++)
	//{
	//	while (getchar() != '\n');
	//	citesteMarfa(&vector1[i]);
	//}
	//afisareVectorMarfa(vector1, size1);
	//struct Marfa* vector2;

	//int size2;

	//printf("Introduceti numarul de marfuri pentru al doilea vector: ");

	//scanf("%d", &size2);

	//vector2 = (struct Marfa*)malloc(size2 * sizeof(struct Marfa));

	//for (int i = 0; i < size2; i++)

	//{

	//	while (getchar() != '\n');

	//	citesteMarfa(&vector2[i]);

	//}

	//afisareVectorMarfa(vector2, size2);

	//int new_size3;

	//struct Marfa** new_m3 = concatenareVectoriMarfa(vector1, size1, vector2, size2, &new_size3);

	//printf("Afisare vector concatenat:\n");

	//afisareVectoriMarfa(new_m3, new_size3);

	//eliberareMemorieVector(&new_m3, new_size3);

	int size;
	FILE* f = fopen("Marfa.txt", "r");
	if (f)
	{
		struct Marfa* marfa = citesteVectorMarfaFisier(f, &size);
		printf("MARFA DIN VECTOR:\n");
		afisareVectorMarfa(marfa, size);
		FILE* g = fopen("Marfa2.txt", "w");
		if (g)
		{
			scrieVectorMarfaFisier(g, marfa, size);
		}
		else
		{
			printf("Eroare la deschidere fisier de iesire!");
		}
	}
	else
	{
		printf("Eroare la deschidere fisier!");
	}


	return 0;



}

