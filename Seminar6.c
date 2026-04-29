#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina
{
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	char serie;
};
typedef struct StructuraMasina Masina;

typedef struct Nod Nod;
struct Nod
{
	Masina masina;
	Nod* next;
};

typedef struct NodDublu NodDublu;
struct NodDublu
{
	Masina info;
	NodDublu* next;
	NodDublu* prev;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla
{
	NodDublu* first;
	NodDublu* last;
};

Masina citireMasinaDinFisier(FILE* file)
{
	char buffer[100];
	char sep[3] = ",\n";
	char* aux;
	Masina m1;

	m1.id = -1;
	if (fgets(buffer, 100, file) == NULL)
	{
		return m1;
	}

	aux = strtok(buffer, sep);
	if (!aux)
	{
		return m1;
	}
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));

	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.serie = aux ? aux[0] : '-';
	return m1;
}

void afisareMasina(Masina masina)
{
	if (masina.id == -1)
	{
		return;
	}
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

void pushStack(Nod** stiva, Masina masina)
{
	Nod* temp = (Nod*)malloc(sizeof(Nod));
	temp->masina = masina;
	temp->next = (*stiva);
	(*stiva) = temp;
}

Masina popStack(Nod** stiva)
{
	if ((*stiva) == NULL)
	{
		Masina rezultat;
		rezultat.id = -1;
		return rezultat;
	}
	Masina rezultat = (*stiva)->masina;
	Nod* temp = (*stiva)->next;
	free(*stiva);
	*stiva = temp;
	return rezultat;
}

char isEmptyStack(Nod* stiva)
{
	return stiva == NULL;
}

Nod* citireStackMasiniDinFisier(const char* numeFisier)
{
	FILE* file = fopen(numeFisier, "r");
	if (!file)
	{
		return NULL;
	}
	Nod* stiva = NULL;
	while (1)
	{
		Masina masina = citireMasinaDinFisier(file);
		if (masina.id == -1)
		{
			break;
		}
		pushStack(&stiva, masina);
	}
	fclose(file);
	return stiva;
}

void dezalocareStivaDeMasini(Nod** stiva)
{
	while (!isEmptyStack(*stiva))
	{
		Masina m = popStack(stiva);
		free(m.model);
		free(m.numeSofer);
	}
}

int size(Nod* stiva)
{
	int count = 0;
	Nod* temp = stiva;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	return count;
}

float calculeazaPretTotalStiva(Nod** stiva)
{
	float pretTotal = 0;
	Nod* stivaAux = NULL;

	while (!isEmptyStack(*stiva))
	{
		Masina m = popStack(stiva);
		pretTotal += m.pret;
		pushStack(&stivaAux, m);
	}

	while (!isEmptyStack(stivaAux))
	{
		pushStack(stiva, popStack(&stivaAux));
	}

	return pretTotal;
}

void enqueue(ListaDubla* coada, Masina masina)
{
	NodDublu* NodNou = (NodDublu*)malloc(sizeof(NodDublu));
	NodNou->info = masina;
	NodNou->next = NULL;
	NodNou->prev = coada->last;
	if (coada->last)
	{
		coada->last->next = NodNou;
	}
	else
	{
		coada->first = NodNou;
	}
	coada->last = NodNou;
}

Masina dequeue(ListaDubla* coada)
{
	Masina rezultat;
	rezultat.id = -1;
	if (coada->first)
	{
		rezultat = coada->first->info;
		NodDublu* temp = coada->first;
		coada->first = temp->next;

		if (coada->first == NULL)
		{
			coada->last = NULL;
		}
		else
		{
			coada->first->prev = NULL;
		}

		free(temp);
	}
	return rezultat;
}

ListaDubla citireCoadaDeMasiniDinFisier(const char* numeFisier)
{
	ListaDubla coada;
	coada.first = coada.last = NULL;
	FILE* f = fopen(numeFisier, "r");
	if (f)
	{
		while (1)
		{
			Masina masina = citireMasinaDinFisier(f);
			if (masina.id == -1)
			{
				break;
			}
			enqueue(&coada, masina);
		}
		fclose(f);
	}
	return coada;
}

void dezalocareCoadaDeMasini(ListaDubla* coada)
{
	while (coada->first != NULL)
	{
		Masina m = dequeue(coada);
		free(m.model);
		free(m.numeSofer);
	}
}

float calculeazaPretTotalCoada(ListaDubla coada)
{
	float pretTotal = 0;
	NodDublu* temp = coada.first;
	while (temp)
	{
		pretTotal += temp->info.pret;
		temp = temp->next;
	}
	return pretTotal;
}

Masina getMasinaByID(Nod** stiva, int id)
{
	Masina rezultat;
	rezultat.id = -1;

	if ((*stiva) == NULL)
	{
		return rezultat;
	}
	Nod* stivaNoua = NULL;
	while ((*stiva))
	{
		Masina masinaNoua = popStack(stiva);
		if (masinaNoua.id == id)
		{
			rezultat = masinaNoua;
		}
		pushStack(&stivaNoua, masinaNoua);
	}
	while (stivaNoua)
	{
		pushStack(stiva, popStack(&stivaNoua));
	}
	return rezultat;
}

int main()
{
	printf("STIVA---------------------------------------\n");
	Nod* stiva = citireStackMasiniDinFisier("masini.txt");

	afisareMasina(popStack(&stiva));
	afisareMasina(popStack(&stiva));

	printf("Cautare masina ID 4 in stiva:\n");
	afisareMasina(getMasinaByID(&stiva, 4));

	printf("Dimensiune stiva ramasa: %d\n", size(stiva));
	printf("Pret total masini in stiva: %.2f\n\n", calculeazaPretTotalStiva(&stiva));

	printf("COADA---------------------------------------\n");
	ListaDubla coada = citireCoadaDeMasiniDinFisier("masini.txt");

	afisareMasina(dequeue(&coada));
	afisareMasina(dequeue(&coada));

	printf("Pret total masini ramase in coada: %.2f\n\n", calculeazaPretTotalCoada(coada));

	dezalocareStivaDeMasini(&stiva);
	dezalocareCoadaDeMasini(&coada);

	return 0;
}