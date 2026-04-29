//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
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
//struct Heap {
//	int lungime;
//	Masina* vector;
//	int nrElementeViz;
//};
//typedef struct Heap Heap;
//
//Masina citireMasinaDinFisier(FILE* file) {
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
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//Heap initializareHeap(int lungime) {
//	Heap h;
//	h.lungime = lungime;
//	h.nrElementeViz = 0;
//	h.vector = malloc(sizeof(Masina) * lungime);
//	return h;
//
//}
//
//void filtreazaHeap(Heap heap, int pozitieNod) {
//	//filtreaza heap-ul pentru nodul a carei pozitie o primeste ca parametru
//	int ps = (2 * pozitieNod) + 1;
//	int pd = (2 * pozitieNod) + 2;
//	int pmax = pozitieNod;
//	if (ps < heap.nrElementeViz && heap.vector[pmax].pret < heap.vector[ps].pret)
//	{
//		pmax = ps;
//	}
//	if (pd < heap.nrElementeViz && heap.vector[pmax].pret < heap.vector[pd].pret)
//	{
//		pmax = pd;
//	}
//	if (pmax != pozitieNod)
//	{
//		Masina aux = heap.vector[pmax];
//		heap.vector[pmax] = heap.vector[pozitieNod];
//		heap.vector[pozitieNod] = aux;
//		if (pmax < (heap.nrElementeViz - 2) / 2)
//		{
//			filtreazaHeap(heap, pmax);
//		}
//	}
//
//}
//
//Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
//	Heap heap = initializareHeap(10);
//	FILE* f = fopen("masini.txt", "r");
//	int i = 0;
//	while (!feof(f)) {
//		Masina m = citireMasinaDinFisier(f);
//		heap.vector[i] = m;
//		i++;
//	}
//	fclose(f);
//	heap.nrElementeViz = i;
//	for (int j = (i - 2) / 2; j >= 0; j--) {
//		filtreazaHeap(heap, j);
//	}
//	return heap;
//}
//
//void afisareHeap(Heap heap) {
//	for (int i = 0; i < heap.nrElementeViz; i++)
//	{
//		afisareMasina(heap.vector[i]);
//	}
//}
//
//void afiseazaHeapAscuns(Heap heap) {
//	for (int i = heap.nrElementeViz; i < heap.lungime; i++)
//	{
//		afisareMasina(heap.vector[i]);
//	}
//}
//
//Masina extrageMasina(Heap* heap) {
//	//extrage si returneaza masina de pe prima pozitie
//	//elementul extras nu il stergem...doar il ascundem
//	Masina m;
//	m.id = -1;
//	if (heap->nrElementeViz != 0)
//	{
//		m = heap->vector[0];
//		heap->vector[0] = heap->vector[heap->nrElementeViz - 1];
//		heap->vector[heap->nrElementeViz - 1] = m;
//		heap->nrElementeViz--;
//		for (int j = (heap->nrElementeViz - 2) / 2; j >= 0; j--) {
//			filtreazaHeap(*heap, j);
//		}
//	}
//	return m;
//}
//int calculeazaInaltimeArbore(Heap heap, int pozitieNod) {
//
//	if (pozitieNod >= heap.nrElementeViz)
//	{
//		return 0;
//	}
//	int inaltimeStanga = calculeazaInaltimeArbore(heap, 2 * pozitieNod + 1);
//	int inaltimeDreapta = calculeazaInaltimeArbore(heap, 2 * pozitieNod + 2);
//	if (inaltimeStanga > inaltimeDreapta)
//	{
//		return 1 + inaltimeStanga;
//	}
//	else 
//	{
//		return 1 + inaltimeDreapta;
//	}
//}
//
//
//
//void dezalocareHeap(Heap* heap) {
//	for (int i = 0; i < heap->lungime; i++)
//	{
//		free(heap->vector[i].model);
//		free(heap->vector[i].numeSofer);
//	}
//	free(heap->vector);
//	heap->vector = NULL;
//	heap->lungime = 0;
//	heap->nrElementeViz = 0;
//}
//
//int main() {
//	Heap heap = citireHeapDeMasiniDinFisier("masini.txt");
//	int inaltime = calculeazaInaltimeArbore;
//	printf("Inaltimea arborelui este: %d\n\n", calculeazaInaltimeArbore(heap, 0));
//	printf("Extrageri: \n");
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	afisareMasina(extrageMasina(&heap));
//	printf("Heap ascuns: \n");
//	afiseazaHeapAscuns(heap);
//	dezalocareHeap(&heap);
//	afisareHeap(heap);
//	return 0;
//}