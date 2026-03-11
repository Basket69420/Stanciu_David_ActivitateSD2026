//#include<stdio.h>
//#include<malloc.h>
//
//struct Telefon {
//	int id;
//	int RAM;
//	char* producator;
//	float pret;
//	char serie;
//};
//struct Telefon initializare(int id, int RAM, char* producator, float pret, char serie) {
//	struct Telefon t;
//	t.id = id;
//	t.RAM = RAM;
//	t.producator = (char*)malloc((strlen(producator) + 1) * sizeof(char));
//	strcpy(t.producator, producator);
//	t.pret = pret;
//	t.serie = serie;
//	return t;
//}
//
//struct Telefon copyTelefon(struct Telefon t) {
//	struct Telefon telefon = initializare(t.id, t.RAM, t.producator, t.pret, t.serie);
//	return telefon;
//}
//
//void afisare(struct Telefon t) {
//	printf("Id: %d\nRAM: %d\nPRoducator: %s\nPret: %.2f\nSerie: %c\n\n", t.id, t.RAM, t.producator, t.pret, t.serie);
//}
//
//void afisareVector(struct Telefon* vector, int nrElemente) {
//	for (int i = 0; i < nrElemente; i++) {
//		afisare(vector[i]);
//	}
//}
//
//struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
//	if (nrElementeCopiate > nrElemente) {
//		nrElementeCopiate = nrElemente;
//	}
//	struct Telefon* vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
//	for (int i = 0; i < nrElementeCopiate; i++)
//		vectorNou[i] = copyTelefon(vector[i]);
//
//	return vectorNou;
//
//}
//
//void dezalocare(struct Telefon** vector, int* nrElemente) {
//	for (int i = 0; i < *nrElemente; i++) {
//		free((*vector)[i].producator);
//		(*vector)[i].producator = NULL;
//	}
//	free(*vector);
//	*vector = NULL;
//	*nrElemente = 0;
//
//}
//
//void copiazaTelefoaneScumpe(struct Telefon* vector, char nrElemente, float pretMinim, struct Telefon** vectorNou, int* dimensiune) {
//	*dimensiune = 0;
//	for (int i = 0; i < nrElemente; i++) {
//		if (vector[i].pret >= pretMinim) {
//			(*dimensiune)++;
//		}
//	}
//	*vectorNou = malloc(*dimensiune * sizeof(struct Telefon));
//	int k = 0;
//	for (int i = 0; i < nrElemente; i++) {
//		if (vector[i].pret >= pretMinim)
//			(*vectorNou)[k++] = copyTelefon(vector[i]);
//	}
//}
//
//struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
//	//trebuie cautat elementul care indeplineste o conditie
//	//dupa atributul de tip char*. Acesta este returnat.
//	struct Telefon s;
//	s.id = 1;
//
//	return s;
//}
//
//
//
//int main() {
//	struct Telefon t;
//	t = initializare(1, 4, "Samsung", 1500.50, 'A');
//	//afisare(t);
//	int nrTelefoane = 3;
//	struct Telefon* telefoane = (struct Telefon*)malloc(nrTelefoane * sizeof(struct Telefon));
//	telefoane[0] = initializare(2, 6, "Apple", 3000.00, 'B');
//	telefoane[1] = initializare(3, 8, "Huawei", 2000.00, 'C');
//	telefoane[2] = t;
//	afisareVector(telefoane, nrTelefoane);
//	int nrTelefoaneCopiate = 2;
//	struct Telefon* telefoaneCopiate = copiazaPrimeleNElemente(telefoane, nrTelefoane, nrTelefoaneCopiate);
//	//printf("Vector telefoane copiate: \n");
//	//afisareVector(telefoaneCopiate, nrTelefoaneCopiate);
//	//dezalocare(&telefoaneCopiate, &nrTelefoaneCopiate);
//	//printf("Vectorul dupa dezalocare");
//	//afisareVector(telefoaneCopiate, nrTelefoaneCopiate);
//	struct Telefon* vectorNou;
//	int dimensiune;
//	copiazaTelefoaneScumpe(telefoane, nrTelefoane, 2000, &vectorNou, &dimensiune);
//	printf("Telefoane scumpe:\n");
//	afisareVector(vectorNou, dimensiune);
//	return 0;
//}