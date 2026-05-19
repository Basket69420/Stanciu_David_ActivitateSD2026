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

struct Nod
{
	struct Nod* left;
	struct Nod* right;
	Masina info;
};

typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
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


void adaugaMasinaInArbore(Nod** root, Masina masinaNoua) 
{
	Nod* new = malloc(sizeof(Nod));
	new->left = NULL;
	new->right = NULL;
	new->info = masinaNoua;
	if (*root == NULL)
	{
		(*root) = new;
		return;
	}
	if (masinaNoua.id < (*root)->info.id)
	{
		adaugaMasinaInArbore(&(*root)->left, masinaNoua);
	}
	else
	{

		adaugaMasinaInArbore(&(*root)->right, masinaNoua);
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) 
{
	FILE* f = fopen(numeFisier, "r");
	if (f)
	{
		Nod* root = NULL;
		while (!feof(f))
		{
			
			adaugaMasinaInArbore(&root, citireMasinaDinFisier(f));
		}
		fclose(f);
		return root;
	}
	
}

void afisareMasiniDinArbore(Nod* root) 
{
	if (root == NULL)
	{
		return;
	}
	else
	{
		afisareMasiniDinArbore(root->left);
		afisareMasina(root->info);
		afisareMasiniDinArbore(root->right);

	}

}
void afisarePostordine(Nod* root)
{
	if (root)
	{
		afisarePostordine(root->left);
		afisareMasiniDinArbore(root->right);
		afisareMasina(root->info);
	}
}

void dezalocareArboreDeMasini(Nod** root) 
{
	if (*root)
	{
		dezalocareArboreDeMasini(&((*root)->left));
		dezalocareArboreDeMasini(&((*root)->right));


		free((*root)->info.model);
		free((*root)->info.numeSofer);
		free(*root);

		*root = NULL;

	}
}

Masina getMasinaByID(Nod* root, int id) 
{
	Masina m;
	m.id = -1;

	if (root)
	{
		if (root->info.id == id)
		{
			m = root->info;

			m.model = malloc(strlen(root->info.model) + 1);
			strcpy_s(m.model, strlen(root->info.model) + 1, root->info.model);
			m.numeSofer = malloc(strlen(root->info.numeSofer) + 1);
			strcpy_s(m.numeSofer, strlen(root->info.numeSofer) + 1, root->info.numeSofer);
			return m;
		}
		else
		{
			if (root->info.id <= id)
			{
				m = getMasinaByID(root->right, id);
			}
			else
			{
				m = getMasinaByID(root->left, id);
			}
		}
	}
	else
		m.id = -1;
		
	return m;
}

int determinaNumarNoduri(Nod*root) 
{
	if (root)
	{
		int nrNoduriSt = determinaNumarNoduri(root->left);
		int nrNoduriDr = determinaNumarNoduri(root->right);
		return 1 + nrNoduriDr + nrNoduriSt;
	}
	else
	{
		return 0;
	}
}

int calculeazaInaltimeArbore(Nod* root) {
	if (root == NULL)
	{
		return -1;
	}
	else
	{
		return 1+ max(calculeazaInaltimeArbore(root->left),calculeazaInaltimeArbore(root->right));
	}
	return 0;
}

float calculeazaPretTotal(Nod* root)
{
	if (root == NULL) return 0;
	else
	{
		float stanga = calculeazaPretTotal(root->left);
		float dreapta = calculeazaPretTotal(root->right);
		return root->info.pret + stanga + dreapta;

	}
	return 0;
}
float calculeazaPretulMasinilorUnuiSofer(Nod* root, const char* numeSofer)
{
	if (root == NULL) return 0;
	else
	{
		float stanga = calculeazaPretulMasinilorUnuiSofer(root->left, numeSofer);
		float dreapta = calculeazaPretulMasinilorUnuiSofer(root->right, numeSofer);

		if (strcmp(root->info.numeSofer, numeSofer) == 0)
		{
			return root->info.pret + stanga + dreapta;
		}
		else
		{
			return stanga + dreapta;
		}
	}
	return 0;
}

int main()
{
	Nod* root = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareMasiniDinArbore(root);
	afisareMasina(getMasinaByID(root, 5));
	printf("Numarul totoatl de noduri este:%d \n", determinaNumarNoduri(root));

	printf("Inaltimea este:%d ", calculeazaInaltimeArbore(root));
	printf("\nPret masini sofer cautat: %.2f\n", calculeazaPretulMasinilorUnuiSofer(root, "Ionescu"));

	dezalocareArboreDeMasini(&root);
	return 0;
}