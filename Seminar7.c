//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
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
//	Nod** vector; //vector de liste
//};
//typedef struct HashTable HashTable;
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
//void afisareListaMasini(Nod* lista) {
//	if (lista) {
//		while (lista->next) {
//			afisareMasina(lista->info);
//			lista = lista->next;
//		}
//		afisareMasina(lista->info);
//	}
//}
//
//void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
//	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
//	nodNou->info = masinaNoua;
//	nodNou->next = NULL;
//	Nod* temp = *lista;
//	if (*lista) {
//		while (temp->next) {
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
//HashTable initializareHashTable(int dimensiune) {
//	HashTable ht;
//	ht.dim = dimensiune;
//	ht.vector = malloc(dimensiune * sizeof(Nod*));
//	for (int i = 0; i < dimensiune; i++) {
//		ht.vector[i] = NULL;
//	}
//	return ht;
//}
//
//int calculeazaHash(int id, int dimensiune) {
//	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii
//	return id * 7 % dimensiune;
//}
//
//void inserareMasinaInTabela(HashTable hash, Masina masina) {
//	//este folosit mecanismul CHAINING
//	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
//	int hashCode = calculeazaHash(masina.id, hash.dim);
//	if (!hash.vector[hashCode]) {//verificam daca nu avem coliziune
//		adaugaMasinaInLista(&hash.vector[hashCode], masina);
//	}
//	else {//avem coliziune
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
//	//sunt afisate toate masinile cu evidentierea clusterelor realizate
//	for (int i = 0; i < ht.dim; i++) {
//		printf("Clusterul %d: \n", i + 1);
//		afisareListaMasini(ht.vector[i]);
//		printf("-----------------------------------------------\n");
//	}
//}
//
//void dezalocareTabelaDeMasini(HashTable* ht) {
//	//sunt dezalocate toate masinile din tabela de dispersie
//}
//
//float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
//	//calculeaza pretul mediu al masinilor din fiecare cluster.
//	//trebuie sa returnam un vector cu valorile medii per cluster.
//	//lungimea vectorului este data de numarul de clustere care contin masini
//	return NULL;
//}
//
//Masina getMasinaDupaId(HashTable ht, int id) {
//	Masina m;
//	m.id = -1;
//	//cauta masina dupa valoarea atributului cheie folosit in calcularea hash-ului
//	//trebuie sa modificam numele functiei 
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
//
//
//	return 0;
//}