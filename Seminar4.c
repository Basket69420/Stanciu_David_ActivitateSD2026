#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
	Masina info;
	struct Nod* next;
};
typedef struct Nod Nod;
Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;//dc avem nevoie de aux cu steluta?
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);//aici dc trebuie steluta?
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Nod* cap) {
	
	while (cap)
	{
		afisareMasina(cap->info);
		cap = cap->next;
	}
	
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* new=malloc(sizeof(Nod));
	new->info = masinaNoua;
	new->next = NULL;
	if (!(*cap))
	{
		*cap = new;
	}

	else
	{
		Nod* p=*cap;

		while (p->next)
		{
			p = p->next;

		}
		p->next = new;
	}


}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	//adauga la inceputul listei o noua masina pe care o primim ca parametru
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = *cap;
	*cap = nou;
}

void* citireListaMasiniDinFisier(const char* numeFisier) {

	FILE* f = fopen(numeFisier, "r");
	Nod* cap = NULL;

	while (!feof(f))
	{
		adaugaMasinaInLista(&cap, citireMasinaDinFisier(f));

	}
	fclose;
	return cap;
}

void dezalocareListaMasini(Nod** cap) {
	while (*cap)
	{
		free((*cap)->info.model);
		free((*cap)->info.numeSofer);
		Nod* aux = *cap;
		aux = (*cap)->next;
		free(*cap);
		*cap=aux;
	}
}

float calculeazaPretMediu(Nod* cap) {

	float aux=0, cont=0;
	while (cap)
	{
		aux += cap->info.pret;
		cont++;
		cap = cap->next;
	}
	if (cont == 0)
	{
		return(0);
	}
	else
		return aux / cont;
	
}
void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
	while ((*cap) != NULL && (*cap)->info.serie == serieCautata) {
		Nod* aux = *cap;
		*cap = (*cap)->next;
		free(aux);
	}

	Nod* precedent = *cap;
	Nod* actual = (*cap)->next;
	while (actual != NULL) {
		if (actual->info.serie == serieCautata) {
			precedent->next = actual->next;
			free(actual);
			actual = precedent->next;
		}
		else {
			precedent = actual;
			actual = actual->next;
		}
	}
}


float calculeazaPretulMasinilorUnuiSofer(Nod* cap, const char* numeSofer) {
	float aux=0;
	while (cap)
	{

		if (strcmp(numeSofer ,cap->info.numeSofer)==0)
			aux += cap->info.pret;
		cap = cap->next;
	}
	return aux;
}

int main() {
	Masina m;
	m.id = 10;
	m.model = malloc(strlen("Opel") + 1);
	strcpy(m.model, "Opel");
	m.nrUsi = 4;
	m.numeSofer = malloc(strlen("matei") + 1);
	strcpy(m.numeSofer, "matei");
	m.pret = 1000;
	m.serie = "B";
	Nod* cap = citireListaMasiniDinFisier("masini.txt");

	afisareListaMasini(cap);
	if (calculeazaPretMediu(cap) == 0)
		printf("\n nu exista masini");
	else
	printf("\n pretul mediu al masinilor este:%f\n", calculeazaPretMediu(cap));
	printf("Ionescu are networth ul de :%f\n\n\n", calculeazaPretulMasinilorUnuiSofer(cap, "Gigel"));
	adaugaMasinaInLista(&cap, m);

	stergeMasiniDinSeria(&cap, "A");
	afisareListaMasini(cap);


	dezalocareListaMasini(&cap);
	afisareListaMasini(cap);

	if (calculeazaPretMediu(cap) == 0)
		printf("\n nu exista masini");
	else
		printf("\n %f", calculeazaPretMediu(cap));
	

	

	return 0;
}