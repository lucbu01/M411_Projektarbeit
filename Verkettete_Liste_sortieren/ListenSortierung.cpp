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
    srand((unsigned) time(NULL));
    struPerson* pLast = NULL;
    struPerson* pStart = NULL;
    for (int i = 0; i < anzahl; i++) {
        struPerson* pNew = (struPerson*)malloc(sizeof(struPerson));

        //Zufaellige initialisierung der Werte vorname, nachname, Jahrgang
        pNew->vorname[0] = rand() % 26 + 65;
        pNew->vorname[1] = '\0';
        pNew->nachname[0] = rand() % 26 + 65;
        pNew->nachname[1] = '\0';
        pNew->jahrgang = rand() % 119 + 1900;

        pNew->pNext = NULL;
		if (pStart == NULL) pStart = pNew;
        if (pLast != NULL) pLast->pNext = pNew;
        pLast = pNew;
    }
    return pStart;
}

// Loescht die Liste und gibt den Speicherplatz frei
void deleteList(struPerson* pStart) {
	struPerson* pNext = NULL;

	for (struPerson* pElement = pStart; pElement != NULL; pElement = pNext) {
		pNext = pElement->pNext;
		free(pElement);
	}
}

// Loescht Elemente aus einer Liste und gibt den Speicherplatz frei
struPerson* deleteElement(struPerson* pStart, const char* pVorname, const char* pNachname) {
	struPerson* pNext = NULL;
	struPerson* pLast = NULL;

	for (struPerson* pElement = pStart; pElement != NULL; pElement = pNext) {
		pNext = pElement->pNext;
		if (strcmp(pElement->vorname, pVorname) == 0 && strcmp(pElement->nachname, pNachname) == 0) {
			free(pElement);
			if (pLast == NULL) {
				pStart = pNext;
			}
			else {
				pLast->pNext = pNext;
			}
		} else {
			pLast = pElement;
		}
	}
	return pStart;
}

// Sortiert die Liste nach Nachname und Vorname
struPerson* sortList(struPerson* pStart) {
	//bezieht sich auf pElement, A ist kleiner als D
	bool isGreater = false;
	bool sorted = false;
	struPerson* pLastElement = NULL;
	struPerson* pTemp = NULL;
	while(!sorted) {
		sorted = true;
		for (struPerson* pElement = pStart; pElement != NULL; pElement = pElement->pNext) {
			if (strcmp(pElement->nachname, pElement->pNext->nachname) > 0) {
				isGreater = true;
			}
			else if (strcmp(pElement->nachname, pElement->pNext->nachname) == 0) {
				if (strcmp(pElement->vorname, pElement->pNext->vorname) > 0) {
					isGreater = true;
				}
			}

			if (isGreater) {
				sorted = false;
				pTemp = pElement->pNext;
				if (pElement == pStart) {
					pStart = pElement;
				}
				else {
					pLastElement->pNext = pElement->pNext;
				}

				pElement->pNext = pElement->pNext->pNext;
				pElement->pNext->pNext = pElement;
				isGreater = false;
			}
			pLastElement = pElement;
		}
	}
	return pStart;
}

// Gibt alle Elemente der Liste aus
void output(struPerson* pStart) {
    for (struPerson* pTemp = pStart; pTemp != NULL; pTemp = pTemp->pNext) {
        printf("Element: %s %s %i\n", pTemp->nachname, pTemp->vorname, pTemp->jahrgang);
    }
}

void main() {
    struPerson *pStart = create(5);

	//test deleteElement
	strcpy_s(pStart->vorname, "L");
	strcpy_s(pStart->nachname, "A");
	strcpy_s(pStart->pNext->vorname, "C");
	strcpy_s(pStart->pNext->nachname, "Z");
	strcpy_s(pStart->pNext->pNext->pNext->vorname, "C");
	strcpy_s(pStart->pNext->pNext->pNext->nachname, "Z");
	output(pStart);
    printf("\n");
	//pStart = deleteElement(pStart, "L", "A");
	//pStart = deleteElement(pStart, "C", "Z");
	pStart = sortList(pStart);

    output(pStart);
	deleteList(pStart);
    system("pause");
}