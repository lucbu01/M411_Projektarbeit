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

/*
	Autor: Ghezzi Lars, Bucher Luca
	Datum: 14.12.2018
	Erstellt eine Liste von definierter Anzahl Elementen.
*/
struPerson* createList(int anzahl) {
    srand((unsigned) time(NULL));
    struPerson* pLast = NULL;
    struPerson* pStart = NULL;
    for (int i = 0; i < anzahl; i++) {
        struPerson* pNew = (struPerson*)malloc(sizeof(struPerson));

        // Zufaellige initialisierung der Werte vorname, nachname, Jahrgang
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

/*
	Autor: Ghezzi Lars, Bucher Luca
	Datum: 14.12.2018
	Loescht die Liste und gibt den Speicherplatz frei.
*/
void deleteList(struPerson* pStart) {
	struPerson* pNext = NULL;

	for (struPerson* pElement = pStart; pElement != NULL; pElement = pNext) {
		pNext = pElement->pNext;
		free(pElement);
	}
}

/*
	Autor: Ghezzi Lars, Bucher Luca
	Datum: 14.12.2018
	Loescht Elemente aus einer Liste und gibt den Speicherplatz frei.
*/
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


/*
	Autor: Ghezzi Lars, Bucher Luca
	Datum: 14.12.2018
	Gibt alle Elemente der Liste aus
*/
void output(struPerson* pStart) {
    for (struPerson* pTemp = pStart; pTemp != NULL; pTemp = pTemp->pNext) {
        printf("Element: %s %s %i\n", pTemp->nachname, pTemp->vorname, pTemp->jahrgang);
    }
}

/*
	Autor: Ghezzi Lars	
	Datum: 22.12.2018	
	Tauscht die Positionen Zweier Elemente.
*/
struPerson* changePosition(struPerson* pStart, struPerson* pElement, struPerson* pElementToChange, struPerson* pElementLast, struPerson* pElementToChangeLast) {
	struPerson* pElementNext = pElement->pNext;
	struPerson* pElementToChangeNext = pElementToChange->pNext;

	if (pElement == pStart) {
		pStart = pElementToChange;
	}

	// wenn es das erste ist, gibt es keines zuvor
	if (pElementLast != NULL) {
		pElementLast->pNext = pElementToChange;
	}

	// schaut ob die Elemente hintereinander sind
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

/* Problem: manchmal entsteht ein loop!
	Autor: Ghezzi Lars
	Datum: 22.12.2018
	Sortiert die Liste nach dem BubbleSort Prinzip.
*/
struPerson* sortListWithBubbleSort(struPerson* pStart) {
	// 0 oder weniger == false
	int doneChanges = 0;
	struPerson* pElementLast = NULL;
	do {
		doneChanges = 0;
		for (struPerson* pElement = pStart; pElement->pNext != NULL; pElement = pElement->pNext) {
			struPerson* pElementToCompare = pElement->pNext;

			if (strcmp(pElement->nachname, pElementToCompare->nachname) > 0) {
				//wechselt Element
				pStart = changePosition(pStart, pElement, pElementToCompare, pElementLast, pElement);
				//anderenfalles würde eins übersprungen werden, da in der For-schleife vorwärts gegangen wird
				pElement = pElementToCompare;
				doneChanges++;
			}
			else if (strcmp(pElement->nachname, pElementToCompare->nachname) == 0) {
				if (strcmp(pElement->vorname, pElementToCompare->vorname) > 0) {
					//wechselt Element
					pStart = changePosition(pStart, pElement, pElementToCompare, pElementLast, pElement);
					//anderenfalles würde eins übersprungen werden, da in der For-schleife vorwärts gegangen wird
					pElement = pElementToCompare;
					doneChanges++;
				}
			}
			pElementLast = pElement;
		}
	} while (doneChanges > 0); // Wenn es keine Aenderungen mehr gibt, ist die Liste sortiert
	return pStart;
}

/*
	Autor: Ghezzi Lars
	Datum: 22.12.2018
	Sortiert die Liste nach dem SelectSort Prinzip.
*/
struPerson* sortListWithSelectSort(struPerson* pStart) {
	struPerson* pElementLast = NULL;
	struPerson* pElementToCompareLast = NULL;
	for (struPerson* pElement = pStart; pElement->pNext != NULL; pElement = pElement->pNext) {
		pElementToCompareLast = pElement;
		for (struPerson* pElementToCompare = pElement->pNext; pElementToCompare != NULL; pElementToCompare = pElementToCompare->pNext) {

			if (strcmp(pElement->nachname, pElementToCompare->nachname) > 0) {
				//wechselt Element
				pStart = changePosition(pStart, pElement, pElementToCompare, pElementLast, pElementToCompareLast);
				struPerson* pTemp = pElement;
				pElement = pElementToCompare;
				pElementToCompare = pTemp;
			}
			else if (strcmp(pElement->nachname, pElementToCompare->nachname) == 0) {
				if (strcmp(pElement->vorname, pElementToCompare->vorname) > 0) {
					//wechselt Element
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

/*
	Autor: Bucher Luca
	Datum: 28.12.2018
	Textbasiertes Menu mit den Listenfunktionen.
*/
void main() {
	printf("Willkommen. . .\nWie viele Elemente soll Ihre Liste haben: ");
	int anzahl = 0;
	scanf_s("%i", &anzahl);
	getchar();

    struPerson *pStart = createList(anzahl);

	char input[100];
	int wiederholen = 1;
	while (wiederholen != 0) {
		output(pStart);
		printf("\nWaehlen Sie eine Option:\n\n");
		printf("bubbleSort - Wendet den BubbleSort an der Liste an.\n");
		printf("selectSort - Wendet den SelectSort an der Liste an.\n");
		printf("deleteElement - Loescht ein gewuenschtes Element aus der Liste.\n");
		printf("exit - Loescht die Liste und schliesst das Programm.\n\n>");
		gets_s(input);

		if (strcmp(input, "bubbleSort") == 0) {
			sortListWithBubbleSort(pStart);
		}
		else if (strcmp(input, "selectSort") == 0) {
			sortListWithSelectSort(pStart);
		}
		else if (strcmp(input, "deleteElement") == 0) {
			printf("Vorname: ");
			char vorname[40];
			gets_s(vorname);
			printf("Nachname: ");
			char nachname[40];
			gets_s(nachname);
			pStart = deleteElement(pStart, vorname, nachname);
		}
		else if (strcmp(input, "exit") == 0) {
			deleteList(pStart);
			wiederholen = 0;
		}
		else {
			printf("\nDie Anweisung wurde nicht gefunden.\n\n");
		}

	}

    system("pause");
}