#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



typedef struct Cladire Cladire;
struct Cladire {
	char* locatie;
	int an_constructie;
	int id;
};
typedef struct Nod Nod;
struct Nod {
	Cladire cladire;
	Nod* next;
};
Cladire creareCladire(const char* locatie, int an, int id)
{
	Cladire cladire;
	cladire.locatie = (char*)malloc(sizeof(char) * (strlen(locatie) + 1));
	strcpy(cladire.locatie, locatie);
	cladire.id = id;
	cladire.an_constructie = an;
	return cladire;
}
Nod* creareNod(Cladire cladire)
{
	Nod* nod=(Nod*)malloc(sizeof(Nod));
	nod->cladire = creareCladire(cladire.locatie, cladire.an_constructie, cladire.id);
	nod->next = NULL;
	return nod;
}
int functieHash(int an_constructie, int sizeHT)
{
	return an_constructie % sizeHT;
}
struct Nod* inserareLista(struct Nod* nod, Cladire cladire)
{
	Nod* nodnou = creareNod(cladire);
	nodnou->next = nod;
	return nodnou;
}
void inserareHT(Nod** ht, Cladire cladire, int size)
{
	int poz = functieHash(cladire.an_constructie, size);
	ht[poz] = inserareLista(ht[poz], cladire);
}

void afisareHT(Nod** ht, int size)
{
	for (int i = 0; i < size; ++i) {
		printf("Pozitia %d:\n", i+1);
		Nod* nod = ht[i];
		while (nod != NULL) {
			printf("  Locatie: %s, An constructie: %d, ID: %d\n", nod->cladire.locatie, nod->cladire.an_constructie, nod->cladire.id);
			nod = nod->next;
		}
		printf("\n");
	}
}
void afisareVectorCladiri(Cladire* cladiri, int size) {
	printf("Cladirile din vector:\n");
	printf("----------------------\n");
	for (int i = 0; i < size; ++i) {
		printf("Locatie: %s, An constructie: %d, ID: %d\n", cladiri[i].locatie, cladiri[i].an_constructie, cladiri[i].id);
	}
}

void afisareCladiriCluster(Nod** ht, int size, int an_constructie)
{
	int poz = functieHash(an_constructie, size);
	printf("Cladirile construite in anul %d:\n", an_constructie);
	printf("---------------------------------\n");

	Nod* nod = ht[poz];
	while (nod != NULL) {
		if (nod->cladire.an_constructie == an_constructie) {
			printf("Locatie: %s, An constructie: %d, ID: %d\n", nod->cladire.locatie, nod->cladire.an_constructie, nod->cladire.id);
		}
		nod = nod->next;
	}
}
void stergereCladire(Nod** ht, int size, int id, int an_constructie)
{
	int poz = functieHash(an_constructie, size);
	Nod* prev = NULL;
	Nod* current = ht[poz];
	while (current != NULL) {
		if (current->cladire.id == id && current->cladire.an_constructie == an_constructie) {
			if (prev == NULL) {
				ht[poz] = current->next;
			}
			else {
				prev->next = current->next;
			}
			free(current->cladire.locatie);
			free(current);
			printf("Cladirea cu ID-ul %d si anul de constructie %d a fost stearsa cu succes.\n", id, an_constructie);
			return;
		}
		prev = current;
		current = current->next;
	}
}

//Dacă dorim să implementăm o funcție care șterge o clădire doar pe baza ID-ului,
//atunci trebuie să parcurgem întregul hashtable și toate listele asociate pentru a căuta clădirea cu ID-ul specificat. 
//În acest caz, nu vom folosi funcția de dispersie pentru a localiza clusterul potențial.

void stergereCladireDupaID(Nod** ht, int size, int id)
{
	for (int i = 0; i < size; ++i) {
		Nod* prev = NULL;
		Nod* current = ht[i];
		while (current != NULL) {
			if (current->cladire.id == id) {
				if (prev == NULL) {
					ht[i] = current->next;
				}
				else {
					prev->next = current->next;
				}
				free(current->cladire.locatie);
				free(current);
				printf("Cladirea cu ID-ul %d a fost stearsa cu succes.\n", id);
				return;
			}
			prev = current;
			current = current->next;
		}
	}
	printf("Cladirea cu ID-ul %d nu a fost gasita.\n", id);
}
Cladire* vectorCladiriDupaAn(Nod** ht, int size, int an_constructie, int* numar_cladiri) {
	*numar_cladiri = 0;
	Cladire* vector_cladiri = NULL;
	for (int i = 0; i < size; ++i) {
		Nod* nod = ht[i];
		while (nod != NULL) {
			if (nod->cladire.an_constructie == an_constructie) {
				Cladire* temp = (Cladire*)realloc(vector_cladiri, sizeof(Cladire) * (*numar_cladiri + 1));
				vector_cladiri = temp;
				vector_cladiri[*numar_cladiri].locatie = (char*)malloc(strlen(nod->cladire.locatie) + 1);
				strcpy(vector_cladiri[*numar_cladiri].locatie, nod->cladire.locatie);
				vector_cladiri[*numar_cladiri].an_constructie = nod->cladire.an_constructie;
				vector_cladiri[*numar_cladiri].id = nod->cladire.id;
				(*numar_cladiri)++;
			}
			nod = nod->next;
		}
	}

	return vector_cladiri;
}
void modificareAnConstructie(Nod** ht, int size, int id, int old_an, int new_an) {
	int poz_vechi = functieHash(old_an, size);

	Nod* nod = ht[poz_vechi];
	while (nod != NULL) {
		if (nod->cladire.id == id) {
			Cladire cladireNoua = creareCladire(nod->cladire.locatie, nod->cladire.an_constructie, nod->cladire.id);
			cladireNoua.an_constructie = new_an;
			inserareHT(ht,cladireNoua, size);
			stergereCladire(ht, size, id, old_an);
			printf("Anul de constructie pentru cladirea cu ID-ul %d a fost actualizat cu succes la %d.\n", id, new_an);
			return;
		}
		nod = nod->next;
	}
	printf("Cladirea cu ID-ul %d si anul de constructie %d nu a fost gasita.\n", id, old_an);
}
void eliberareHT(Nod** ht, int size) {
	for (int i = 0; i < size; ++i) {
		Nod* current = ht[i];
		while (current != NULL) {
			Nod* next = current->next;
			free(current->cladire.locatie);
			free(current);
			current = next;
		}
	}
	free(ht);
}
void eliberareVector(Cladire* cladiri, int size) {
	for (int i = 0; i < size; ++i) {
		free(cladiri[i].locatie);
	}
	free(cladiri);
}


int main()
{
	const int sizeHT = 4; 
	Nod** ht = (Nod**)malloc(sizeof(Nod*) * sizeHT);
	for (int i = 0; i < sizeHT; ++i) {
		ht[i] = NULL; 
	}
	Cladire cladiri[5];
	cladiri[0] = creareCladire("Bucuresti, Sector 6, Intrarea Nuferilor", 2005, 1);
	cladiri[1] = creareCladire("Cluj-Napoca, Strada Avram Iancu", 1998, 2);
	cladiri[2] = creareCladire("Timisoara, Bulevardul Republicii", 2012, 3);
	cladiri[3] = creareCladire("Iasi, Piata Unirii", 2007, 4);
	cladiri[4] = creareCladire("Constanta, Strada Tomis", 1993, 5);
	for (int i = 0; i < 5; ++i) {
		inserareHT(ht, cladiri[i], sizeHT);
	}
	afisareHT(ht, sizeHT);
	afisareCladiriCluster(ht, sizeHT, 2012);
	int nr;
	Cladire* v_cladiri = vectorCladiriDupaAn(ht, sizeHT, 1998, &nr);
	afisareVectorCladiri(v_cladiri, nr);
	modificareAnConstructie(ht, sizeHT, 3, 2012, 2022);
	afisareHT(ht, sizeHT);


	eliberareHT(ht, sizeHT);
	eliberareVector(v_cladiri, nr);
	return 0;
}