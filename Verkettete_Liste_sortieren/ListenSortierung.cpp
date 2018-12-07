#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Person {
    char vorname[40];
    char nachname[40];
    int jahrgang;
    struct Person* pNext;
} struPerson;

// Erstellt eine Liste von definierter Anzahl Elementen
struPerson* create(int anzahl) {
    srand(time(NULL));
    struPerson* pLast = NULL;
    struPerson* pStart = NULL;
    for (int i = 0; i < anzahl; i++) {
        struPerson* pNew = (struPerson*)malloc(sizeof(struPerson));

        //Zufällige initialisierung der Werte vorname, nachname, Jahrgang

        pNew->pNext = NULL;
        if (pStart == NULL) pStart = pNew;
        if (pLast != NULL) pLast->pNext = pNew;
        pLast = pNew;
    }
    return pStart;
}

// Gibt alle Elemente der Liste aus
void output(struPerson* pStart) {
    for (struPerson* pTemp = pStart; pTemp != NULL; pTemp = pTemp->pNext) {
        printf("Element: %s %s\n", pTemp->vorname, pTemp->nachname);
    }
}

void main() {
    struPerson *pStart = create(5);
    output(pStart);
    system("pause");
}