//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//    int id;
//    int nrUsi;
//    float pret;
//    char* model;
//    char* numeSofer;
//    char serie; // Corectat: schimbat in char simplu
//};
//typedef struct StructuraMasina Masina;
//
//typedef struct Nod Nod;
//struct Nod {
//    Masina masina;
//    Nod* next;
//};
//
//Masina citireMasinaDinFisier(FILE* file) {
//    char buffer[100];
//    char sep[3] = ",\n";
//    char* aux;
//    Masina m1;
//
//    m1.id = -1; // Setam un id default pentru a marca erorile/finalul fisierului
//    if (fgets(buffer, 100, file) == NULL) return m1;
//
//    aux = strtok(buffer, sep);
//    if (!aux) return m1;
//    m1.id = atoi(aux);
//    m1.nrUsi = atoi(strtok(NULL, sep));
//    m1.pret = atof(strtok(NULL, sep));
//
//    aux = strtok(NULL, sep);
//    m1.model = malloc(strlen(aux) + 1);
//    strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//    aux = strtok(NULL, sep);
//    m1.numeSofer = malloc(strlen(aux) + 1);
//    strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//    aux = strtok(NULL, sep);
//    // Corectat: am evitat dereferentierea in caz ca strtok returneaza NULL
//    m1.serie = aux ? aux[0] : '-';
//    return m1;
//}
//
//void afisareMasina(Masina masina) {
//    if (masina.id == -1) return; // Nu afisa daca masina e invalida
//    printf("Id: %d\n", masina.id);
//    printf("Nr. usi : %d\n", masina.nrUsi);
//    printf("Pret: %.2f\n", masina.pret);
//    printf("Model: %s\n", masina.model);
//    printf("Nume sofer: %s\n", masina.numeSofer);
//    printf("Serie: %c\n\n", masina.serie);
//}
//
////STACK
////Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
////putem reprezenta o stiva prin LSI, LDI sau vector
//void pushStack(Nod** stiva, Masina masina) {
//    Nod* temp = (Nod*)malloc(sizeof(Nod));
//    temp->masina = masina;
//    temp->next = (*stiva);
//    (*stiva) = temp;
//}
//
//Masina popStack(Nod** stiva) {
//    if ((*stiva) == NULL) {
//        Masina rezultat;
//        rezultat.id = -1;
//        return rezultat;
//    }
//    Masina rezultat = (*stiva)->masina;
//    Nod* temp = (*stiva)->next;
//    free(*stiva);
//    *stiva = temp;
//    return rezultat;
//
//}
//
//char isEmptyStack(Nod* stiva) {
//    return stiva == NULL;
//}
//
//// Corectat: Tipul returnat este Nod*, nu void*
//Nod* citireStackMasiniDinFisier(const char* numeFisier) {
//    FILE* file = fopen(numeFisier, "r");
//    if (!file) {
//        return NULL;
//    }
//    Nod* stiva = NULL;
//    // Corectat: Am eliminat feof pentru a nu dubla ultima citire
//    while (1) {
//        Masina masina = citireMasinaDinFisier(file);
//        if (masina.id == -1) break;
//        pushStack(&stiva, masina);
//    }
//    fclose(file);
//    return stiva;
//}
//
//void dezalocareStivaDeMasini(/*stiva*/) {
//    //sunt dezalocate toate masinile si stiva de elemente
//}
//
//int size(/*stiva*/) {
//    //returneaza numarul de elemente din stiva
//    return 0; // Adaugat doar pentru a permite compilarea
//}
//
//// Corectat: Lipseste cuvantul cheie "struct" in alias
//typedef struct NodDublu NodDublu;
//struct NodDublu {
//    Masina info;
//    NodDublu* next;
//    NodDublu* prev;
//};
//
//// Corectat: Lipseste cuvantul cheie "struct" in alias
//typedef struct ListaDubla ListaDubla;
//struct ListaDubla {
//    NodDublu* first;
//    NodDublu* last;
//};
////QUEUE
////Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
////putem reprezenta o coada prin LSI, LDI sau vector
//void enqueue(ListaDubla* coada, Masina masina) {
//    NodDublu* NodNou = (NodDublu*)malloc(sizeof(NodDublu));
//    NodNou->info = masina;
//    NodNou->next = NULL;
//    NodNou->prev = coada->last;
//    if (coada->last) {
//        coada->last->next = NodNou;
//    }
//    else {
//        coada->first = NodNou;
//    }
//    coada->last = NodNou;
//}
//
//Masina dequeue(ListaDubla* coada) {
//    Masina rezultat;
//    rezultat.id = -1;
//    if (coada->first) {
//        rezultat = coada->first->info;
//        NodDublu* temp = coada->first;
//        coada->first = temp->next;
//
//        // Corectat: trebuie sa facem update si la ultimul nod cand coada se goleste
//        if (coada->first == NULL) {
//            coada->last = NULL;
//        }
//        else {
//            coada->first->prev = NULL;
//        }
//
//        free(temp);
//    }
//    return rezultat;
//}
//
//ListaDubla citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//    ListaDubla coada;
//    coada.first = coada.last = NULL;
//    FILE* f = fopen(numeFisier, "r");
//    if (f) {
//        // Corectat: Am eliminat feof pentru a nu dubla ultima citire
//        while (1) {
//            Masina masina = citireMasinaDinFisier(f);
//            if (masina.id == -1) break;
//            enqueue(&coada, masina);
//        }
//        fclose(f);
//    }
//    return coada;
//}
//
//void dezalocareCoadaDeMasini(/*coada*/) {
//    //sunt dezalocate toate masinile si coada de elemente
//}
//
//
////metode de procesare
//Masina getMasinaByID(Nod** stiva, int id) {
//    Masina rezultat;
//    rezultat.id = -1; // Setam initial pe -1 ca sa nu returnam date "gunoi"
//
//    if ((*stiva) == NULL) {
//        return rezultat;
//    }
//    Nod* stivaNoua = NULL;
//    while ((*stiva)) {
//        Masina masinaNoua = popStack(stiva);
//        if (masinaNoua.id == id) {
//            rezultat = masinaNoua;
//            // Atentie: am scos `break` ca sa lase iteratia sa continue,
//            // altfel restul masinilor raman blocate in stiva veche
//        }
//        // Indiferent daca o gasim sau nu, o salvam in stiva noua ca sa nu o pierdem
//        pushStack(&stivaNoua, masinaNoua);
//    }
//    while (stivaNoua) {
//        pushStack(stiva, popStack(&stivaNoua));
//    }
//    return rezultat;
//}
//
//float calculeazaPretTotal(/*stiva sau coada de masini*/);
//
//int main() {
//    Nod* stiva = citireStackMasiniDinFisier("masini.txt");
//    afisareMasina(popStack(&stiva));
//    afisareMasina(popStack(&stiva));
//
//    afisareMasina(getMasinaByID(&stiva, 4));
//
//    printf("COADA---------------------------------------\n");
//    ListaDubla coada = citireCoadaDeMasiniDinFisier("masini.txt");
//    afisareMasina(dequeue(&coada));
//    afisareMasina(dequeue(&coada));
//    return 0;
//}