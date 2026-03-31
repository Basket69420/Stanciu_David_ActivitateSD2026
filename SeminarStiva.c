
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
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

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector
typedef struct Nod Nod;
struct Nod {
	Masina masina;
	Nod* next;
};
typedef struct Nod Nod;

void pushStack(Nod** cap, Masina masina) {

	Nod* first = (Nod*)malloc(sizeof(Nod));
	first->masina = masina;
	first->next = (*cap);
	(*cap) = first;


}

Masina popStack(Nod** cap) {

	if ((*cap) == NULL)
	{
		Masina rezultat;
		rezultat.id = -1;
		return rezultat;
	}
	Masina rezultat = (*cap)->masina;
	Masina rezultat = (*cap)->masina;
	Nod* temp = (*cap)->next;
	free(*cap);
	*cap = temp;
	return rezultat;
}

int isEmptyStack(Nod* cap) {

	return cap == NULL;

}

void* citireStackMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul

	FILE* file = fopen(numeFisier, "r");
	if (!file)
	{
		return NULL;
	}
	Nod* cap = (Nod*)malloc(sizeof(Nod));
	while (!feof(file))
	{
		Masina masina = citireMasinaDinFisier(file);
		pushStack(&cap, masina);

	}
}

void dezalocareStivaDeMasini(/*stiva*/) {
	//sunt dezalocate toate masinile si stiva de elemente
}

int size(/*stiva*/) {
	//returneaza numarul de elemente din stiva
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
void enqueue(/*coada*/ Masina masina) {
	//adauga o masina in coada
}

Masina dequeue(/*coada*/) {
	//extrage o masina din coada
}

void* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareCoadaDeMasini(/*coada*/) {
	//sunt dezalocate toate masinile si coada de elemente
}


//metode de procesare
Masina getMasinaByID(Nod** stiva,int id)
{
	Masina rezultat;
	if ((*stiva) == NULL)
	{
		Masina rezultat;
		rezultat.d = -1;
		return rezultat;
	}
	Nod* stivaNoua = NULL;
	while ((*stiva)) {


		Masina masinaNoua = popStack(stiva);
		if (masinaNoua.id == id) {
			rezultat = masinaNoua;
		}
		else
		{
			pushStack(stivaNoua, masinaNoua);
		}
		pushStack(stivaNoua, masinaNoua);
	}
	while (stivaNoua)
	{
		pushStack(stiva, popStack(stivaNoua));
	}
}



float calculeazaPretTotal(/*stiva sau coada de masini*/);

int main() {

	Nod* stiva = citireStackMasiniDinFisier("masini.txt");
	afisareMasina(popStack(&stiva));
	afisareMasina(popStack(&stiva));

	afisareMasina(getMasinaByID(stiva))

	return 0;
}
