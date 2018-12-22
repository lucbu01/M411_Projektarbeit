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

// Gibt alle Elemente der Liste aus
void output(struPerson* pStart) {
    for (struPerson* pTemp = pStart; pTemp != NULL; pTemp = pTemp->pNext) {
        printf("Element: %s %s %i\n", pTemp->nachname, pTemp->vorname, pTemp->jahrgang);
    }
}

/*
Author: Ghezzi Lars	
Datum: 22.12.2018	
Tauscht die Positionen Zweier Elemente.
*/
struPerson* changePosition(struPerson* pStart, struPerson* pElement, struPerson* pElementToChange, struPerson* pElementLast, struPerson* pElementToChangeLast) {
	struPerson* pElementNext = pElement->pNext;
	struPerson* pElementToChangeNext = pElementToChange->pNext;

	if (pElement == pStart) {
		pStart = pElementToChange;
	}

	//wenn es das erste ist, gibt es keines zuvor
	if (pElementLast != NULL) {
		pElementLast->pNext = pElementToChange;
	}

	//schaut ob die Elemente hintereinander sind
	if (pElement->pNext == pElementToChange) {
		pElementToChange->pNext = pElement;
		pElement->pNext = pElementToChangeNext;
	}
	else {
		pElementToChange->pNext = pElementNext;
		pElementToChangeLast->pNext = pElement;
		pElement->pNext = pElementToChangeNext;
	}

	return pStart;
}

/*
Author: Ghezzi Lars
Datum: 22.12.2018
Sortiert die Liste nach dem BubbleSort Prinzip.
*/
struPerson* sortListWithBubbleSort(struPerson* pStart) {
	//0 or less == false
	int doneChanges = 0;
	struPerson* pElementLast = NULL;
	do {
		doneChanges = 0;
		for (struPerson* pElement = pStart; pElement->pNext != NULL; pElement = pElement->pNext) {
			struPerson* pElementToCompare = pElement->pNext;
			//compare if change must be
			if (strcmp(pElement->nachname, pElementToCompare->nachname) > 0) {
				//change Element
				pStart = changePosition(pStart, pElement, pElementToCompare, pElementLast, pElement);
				//otherweis one would be jumped
				pElement = pElementToCompare;
				doneChanges++;
			}
			else if (strcmp(pElement->nachname, pElementToCompare->nachname) == 0) {
				if (strcmp(pElement->vorname, pElementToCompare->vorname) > 0) {
					//change Element
					pStart = changePosition(pStart, pElement, pElementToCompare, pElementLast, pElement);
					//otherweis one would be jumped
					pElement = pElementToCompare;
					doneChanges++;
				}
			}
			pElementLast = pElement;
		}
	} while (doneChanges > 0); //if there are 0 changes the list is sorted
	return pStart;
}

/*
Author: Ghezzi Lars
Datum: 22.12.2018
Sortiert die Liste nach dem SelectSort Prinzip.
*/
struPerson* sortListWithSelectSort(struPerson* pStart) {
	struPerson* pElementLast = NULL;
	struPerson* pElementToCompareLast = NULL;
	for (struPerson* pElement = pStart; pElement->pNext != NULL; pElement = pElement->pNext) {
		pElementToCompareLast = pElement;
		for (struPerson* pElementToCompare = pElement->pNext; pElementToCompare != NULL; pElementToCompare = pElementToCompare->pNext) {

			//compare if change must be
			if (strcmp(pElement->nachname, pElementToCompare->nachname) > 0) {
				//change Element
				pStart = changePosition(pStart, pElement, pElementToCompare, pElementLast, pElementToCompareLast);
				struPerson* pTemp = pElement;
				pElement = pElementToCompare;
				pElementToCompare = pTemp;
			}
			else if (strcmp(pElement->nachname, pElementToCompare->nachname) == 0) {
				if (strcmp(pElement->vorname, pElementToCompare->vorname) > 0) {
					//change Element
					pStart = changePosition(pStart, pElement, pElementToCompare, pElementLast, pElementToCompareLast);
					struPerson* pTemp = pElement;
					pElement = pElementToCompare;
					pElementToCompare = pTemp;
				}
			}
			pElementToCompareLast = pElementToCompare;
		}
		pElementLast = pElement;
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
	pStart = sortListWithBubbleSort(pStart);

    output(pStart);
	deleteList(pStart);
    system("pause");
}