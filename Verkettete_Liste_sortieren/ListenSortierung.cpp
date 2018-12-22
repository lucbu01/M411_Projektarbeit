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

/*
 *	Prinzip: SelectSort
 *	Author: Ghezzi Lars
 *	Datum: 22.12.2018

 *	Problem: Pointer an schluss setzen geht nicht!!!

 *	Sortiert die Liste nach dem SelectSort Prinzip.
*/
struPerson* sortListWithSelectSort(struPerson* pStart) {
	struPerson* pLastElementToCompare = NULL;

	for (struPerson* pElement = pStart; pElement->pNext != NULL; pElement = pElement->pNext) {
		pLastElementToCompare = pElement;
		struPerson* pElementToCompare = pElement->pNext;
		do {
			//boolean 0 = false, 1 true
			short isGreater = 0;

			//compare if change must be
			if (strcmp(pElement->nachname, pElementToCompare->nachname) > 0) {
				isGreater = 1;
			}
			else if (strcmp(pElement->nachname, pElementToCompare->nachname) == 0) {
				if (strcmp(pElement->vorname, pElementToCompare->vorname) > 0) {
					isGreater = 1;
				}
			}

			//change elements
			struPerson* pTemp = pElement;
			if (isGreater > 0) {
				struPerson* pTempElementToCompareNext = pElementToCompare->pNext;

				//umhänken
				//checkt ob der Pointer am anfang ist
				if (pStart == pElement) {
					pStart = pElementToCompare;
				}
				//prüft ob die Elemente hintereinander sind
				if (pTemp->pNext == pElementToCompare) {
					pElementToCompare->pNext = pElement;
					pElement->pNext = pTempElementToCompareNext;
					pElement = pElementToCompare;
					pElementToCompare = pTemp;
					pLastElementToCompare = pElement;
				}
				else {
					pElementToCompare->pNext = pTemp->pNext;
					pElement->pNext = pTempElementToCompareNext;
					pElementToCompare->pNext->pNext = pElement;
					pElement = pElementToCompare;
					pElementToCompare = pTemp;
				}
			}
			else {
				//setzte die Pointer der letzten Elemente, für die nächste Überprüfung
				pLastElementToCompare = pLastElementToCompare;
			}

			if (pElementToCompare->pNext == NULL) {
			}
			else {
				pElementToCompare = pElementToCompare->pNext;
			}
			//output(pStart);
			//printf("\n");
		} while (pElementToCompare->pNext != NULL);
	}
	return pStart;
}

void main() {
    struPerson *pStart = create(5);

	//test deleteElement
	strcpy_s(pStart->vorname, "L");
	strcpy_s(pStart->nachname, "A");
	strcpy_s(pStart->pNext->vorname, "D");
	strcpy_s(pStart->pNext->nachname, "Z");
	strcpy_s(pStart->pNext->pNext->pNext->vorname, "C");
	strcpy_s(pStart->pNext->pNext->pNext->nachname, "Z");
	output(pStart);
    printf("\n");
	//pStart = deleteElement(pStart, "L", "A");
	//pStart = deleteElement(pStart, "C", "Z");
	pStart = sortListWithSelectSort(pStart);

    output(pStart);
	deleteList(pStart);
    system("pause");
}