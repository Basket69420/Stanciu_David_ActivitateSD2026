//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//typedef struct Nod Nod;
//struct Nod {
//	Masina info;
//	Nod* next;
//};
//
//struct HashTable {
//	int dim;
//	Nod** vector; 
//};
//typedef struct HashTable HashTable;
//
//Masina citireMasinaDinFisier(FILE* file) 
//{
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//void afisareMasina(Masina masina)
//{
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasini(Nod* lista) 
//{
//	if (lista) 
//	{
//		while (lista->next)
//		{
//			afisareMasina(lista->info);
//			lista = lista->next;
//		}
//		afisareMasina(lista->info);
//	}
//}
//
//void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) 
//{
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = NULL;
//	Nod* temp = *lista;
//	if (*lista) 
//	{
//		while (temp->next) 
//		{
//			temp = temp->next;
//		}
//		temp->next = nodNou;
//	}
//	else {
//		*lista = nodNou;
//	}
//}
//
//
//HashTable initializareHashTable(int dimensiune) 
//{
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.vector = malloc(dimensiune * sizeof(Nod*));
//	for (int i = 0; i < dimensiune; i++) 
//	{
//		ht.vector[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(int id, int dimensiune)
//{
//	return id * 7 % dimensiune;
//}
//
//void inserareMasinaInTabela(HashTable hash, Masina masina) {
//	int hashCode = calculeazaHash(masina.id, hash.dim);
//	if (!hash.vector[hashCode])
//	{
//		adaugaMasinaInLista(&hash.vector[hashCode], masina);
//	}
//	else 
//	{
//		adaugaMasinaInLista(&hash.vector[hashCode], masina);
//	}
//}
//
//HashTable citireMasiniDinFisier(const char* numeFisier) {
//	FILE* file = fopen(numeFisier, "r");
//	HashTable hash = initializareHashTable(5);
//	if (file) {
//		while (!feof(file)) {
//			Masina masinaCitita = citireMasinaDinFisier(file);
//			inserareMasinaInTabela(hash, masinaCitita);
//		}
//	}
//	fclose(file);
//	return hash;
//}
//
//void afisareTabelaDeMasini(HashTable ht) {
//	for (int i = 0; i < ht.dim; i++) {
//		printf("Clusterul %d: \n", i + 1);
//		afisareListaMasini(ht.vector[i]);
//		printf("-----------------------------------------------\n");
//	}
//}
//
//void dezalocareTabelaDeMasini(HashTable* ht) 
//{
//	if (ht != NULL && ht->vector != NULL)
//	{
//		for (int i = 0; i < ht->dim; i++) 
//		{
//			Nod* temp = ht->vector[i];
//			while (temp != NULL) 
//			{
//				Nod* deSters = temp;
//				temp = temp->next;
//				free(deSters->info.model);
//				free(deSters->info.numeSofer);
//				free(deSters);
//			}
//		}
//		free(ht->vector);
//		ht->vector = NULL;
//		ht->dim = 0;
//	}
//}
//
//float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere)
//{
//
//	*nrClustere = 0;
//	for (int i = 0; i < ht.dim; i++) 
//	{
//		if (ht.vector[i] != NULL)
//		{
//			(*nrClustere)++;
//		}
//	}
//
//	if (*nrClustere == 0) 
//	{
//		return NULL;
//	}
//
//	float* preturiMedii = (float*)malloc(sizeof(float) * (*nrClustere));
//	int indexVector = 0;
//
//	for (int i = 0; i < ht.dim; i++) 
//	{
//		if (ht.vector[i] != NULL)
//		{
//			float sumaPreturi = 0;
//			int numarMasini = 0;
//			Nod* temp = ht.vector[i];
//
//			while (temp != NULL)
//			{
//				sumaPreturi += temp->info.pret;
//				numarMasini++;
//				temp = temp->next;
//			}
//
//			preturiMedii[indexVector] = sumaPreturi / numarMasini;
//			indexVector++;
//		}
//	}
//
//	return preturiMedii;
//}
//
//Masina getMasinaDupaId(HashTable ht, int id) {
//	Masina m;
//	m.id = -1;
//	int hashCode = calculeazaHash(id, ht.dim);
//	Nod* cautare = ht.vector[hashCode];
//	while (cautare) {
//		if (cautare->info.id == id) {
//			m = cautare->info;
//			m.numeSofer = (char*)malloc(sizeof(char) * (strlen(cautare->info.numeSofer) + 1));
//			strcpy(m.numeSofer, cautare->info.numeSofer);
//			m.model = (char*)malloc(sizeof(char) * (strlen(cautare->info.model) + 1));
//			strcpy(m.model, cautare->info.model);
//			return m;
//		}
//		cautare = cautare->next;
//	}
//	return m;
//}
//
//int main() {
//	HashTable hash = citireMasiniDinFisier("masini.txt");
//	afisareTabelaDeMasini(hash);
//	afisareMasina(getMasinaDupaId(hash, 5));
//	int nrClustereOcupate = 0;
//	float* preturi = calculeazaPreturiMediiPerClustere(hash, &nrClustereOcupate);
//	if (preturi != NULL)
//	{
//		printf("Preturi medii pentru %d clustere ocupate:\n", nrClustereOcupate);
//		for (int i = 0; i < nrClustereOcupate; i++) 
//		{
//			printf("- Clusterul ocupat %d: %.2f\n", i + 1, preturi[i]);
//		}
//		free(preturi);
//		printf("\n");
//	}
//	dezalocareTabelaDeMasini(&hash);
//	afisareTabelaDeMasini(hash);
//
//
//	return 0;
//}