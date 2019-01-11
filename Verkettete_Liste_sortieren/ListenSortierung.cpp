#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct Person {
    char vorname[40];
    char nachname[40];
    int jahrgang;
    struct Person* pNext;
	struct Person* pBefore;
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
		pNew->pBefore = pLast;
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
	struPerson* pBefore = NULL;

	for (struPerson* pElement = pStart; pElement != NULL; pElement = pNext) {
		pNext = pElement->pNext;
		pBefore = pElement->pBefore;

		if (strcmp(pElement->vorname, pVorname) == 0 && strcmp(pElement->nachname, pNachname) == 0) {
			free(pElement);
			if (pBefore == NULL) {
				pStart = pNext;
			}
			else {
				pBefore->pNext = pNext;
			}
			if (pNext != NULL) {
				pNext->pBefore = pBefore;
			}
		}
	}
	return pStart;
}

/*
	Autor: Bucher Luca
	Datum: 10.01.2019
	Gibt die gewuenschte Anzahl Elemente der Liste aus (0 fuer alle Elemente)
*/
void output(struPerson* pStart, int anzahl) {
    anzahl = anzahl == 0 ? INT_MAX : anzahl;
    for (struPerson* pTemp = pStart; anzahl > 0 && pTemp != NULL; pTemp = pTemp->pNext) {
            printf("Nachname: %s\tVorname: %s\tJahrgang: %i\n", pTemp->nachname, pTemp->vorname, pTemp->jahrgang);
            anzahl--;
    }
}

/*
    Autor: Bucher Luca
    Datum: 11.01.2019
    Gibt die gewuenschte Anzahl Elemente der Liste rueckaerts aus (0 fuer alle Elemente)
*/
void outputr(struPerson* pStart, int anzahl) {
    anzahl = anzahl == 0 ? INT_MAX : anzahl;
    struPerson* pTemp = pStart;
    while (pTemp->pNext != NULL) {
        pTemp = pTemp->pNext;
    }
    while (anzahl > 0 && pTemp != NULL) {
        printf("Nachname: %s\tVorname: %s\tJahrgang: %i\n", pTemp->nachname, pTemp->vorname, pTemp->jahrgang);
        pTemp = pTemp->pBefore;
        anzahl--;
    }
}

/*
	Autor: Bucher Luca
	Datum: 03.01.2018
	Tauscht die Positionen Zweier Elemente.
*/
struPerson* changePosition(struPerson* pStart, struPerson* pElement, struPerson* pElementToChange) {
	struPerson* pElementBefore = pElement->pBefore;
	struPerson* pElementNext = pElement->pNext;
	struPerson* pElementToChangeBefore = pElementToChange->pBefore;
	struPerson* pElementToChangeNext = pElementToChange->pNext;

	if (pElement == pStart) {
		pStart = pElementToChange;
	}

	// wenn es das erste ist, gibt es keines zuvor
	if (pElementBefore != NULL) {
		pElementBefore->pNext = pElementToChange;
	}

	int elementToChangeAfterElement = 0;
	int elementAfterElementToChange = 0;
	int elementsNotAfterEachOther = 0;

	// schaut ob die Elemente hintereinander sind
	if (pElement->pNext == pElementToChange) {
		pElementToChange->pNext = pElement;
		pElement->pBefore = pElementToChange;
		elementToChangeAfterElement = 1;
	}
	else if (pElementToChange->pNext == pElement) {
		pElement->pNext = pElementToChange;
		pElementToChange->pBefore = pElement;
		elementAfterElementToChange = 1;
	}
	else {
		elementsNotAfterEachOther = 1;
	}

	// Wenn ElementToChange direkt nach Element kommt oder die beiden nicht hintereinander sind.
	if (elementToChangeAfterElement > 0 || elementsNotAfterEachOther > 0) {
		pElementToChange->pBefore = pElementBefore;

		pElement->pNext = pElementToChangeNext;

		if (pElementToChangeNext != NULL) pElementToChangeNext->pBefore = pElement;

		if (pElementBefore != NULL) pElementBefore->pNext = pElementToChange;
	}

	// Wenn Element direkt nach ElementToChange kommt oder die beiden nicht hintereinander sind.
	if (elementAfterElementToChange > 0 || elementsNotAfterEachOther > 0) {
		pElement->pBefore = pElementToChangeBefore;

		pElementToChange->pNext = pElementNext;

		if (pElementNext != NULL) pElementNext->pBefore = pElementToChange;

		if (pElementToChangeBefore != NULL) pElementToChangeBefore->pNext = pElement;
	}

	return pStart;
}

/*
	Autor: Ghezzi Lars, Bucher Luca
	Datum: 22.12.2018
	Sortiert die Liste nach dem BubbleSort Prinzip.
*/
struPerson* sortListWithBubbleSort(struPerson* pStart) {
	// 0 oder weniger == false
	int doneChanges = 0;
	struPerson* pElementLast = NULL;
	do {
		doneChanges = 0;
		for (struPerson* pElement = pStart; pElement !=NULL && pElement->pNext != NULL; pElement = pElement->pNext) {
			struPerson* pElementToCompare = pElement->pNext;

            int change = 0; // boolean
			if (strcmp(pElement->nachname, pElementToCompare->nachname) > 0) {
                change = 1;
			}
			else if (strcmp(pElement->nachname, pElementToCompare->nachname) == 0) {
				if (strcmp(pElement->vorname, pElementToCompare->vorname) > 0) {
                    change = 1;
				}
                else if (strcmp(pElement->vorname, pElementToCompare->vorname) == 0) {
                    if (pElement->jahrgang > pElementToCompare->jahrgang) {
                        change = 1;
                    }
                }
			}

            if (change == 1) {
                // wechselt Element
                pStart = changePosition(pStart, pElement, pElementToCompare);
                // anderenfalles würde eins übersprungen werden, da in der For-schleife vorwärts gegangen wird
                pElement = pElementToCompare;
                doneChanges++;
            }

			pElementLast = pElement;
		}
	} while (doneChanges > 0); // Wenn es keine Aenderungen mehr gibt, ist die Liste sortiert
	return pStart;
}

/*
	Autor: Ghezzi Lars, Bucher Luca
	Datum: 22.12.2018
	Sortiert die Liste nach dem SelectSort Prinzip.
*/
struPerson* sortListWithSelectSort(struPerson* pStart) {
	for (struPerson* pElement = pStart; pElement != NULL && pElement->pNext != NULL; pElement = pElement->pNext) {
		for (struPerson* pElementToCompare = pElement->pNext; pElementToCompare != NULL; pElementToCompare = pElementToCompare->pNext) {

            int change = 0; // boolean
			if (strcmp(pElement->nachname, pElementToCompare->nachname) > 0) {
                change = 1;
			}
			else if (strcmp(pElement->nachname, pElementToCompare->nachname) == 0) {
				if (strcmp(pElement->vorname, pElementToCompare->vorname) > 0) {
                    change = 1;
                }
                else if (strcmp(pElement->vorname, pElementToCompare->vorname) == 0){
                    if (pElement->jahrgang > pElementToCompare->jahrgang) {
                        change = 1;
                    }
                }
			}

            if (change == 1) {
                //wechselt Element
                pStart = changePosition(pStart, pElement, pElementToCompare);
                struPerson* pTemp = pElement;
                pElement = pElementToCompare;
                pElementToCompare = pTemp;
            }
		}
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
		printf("\nWaehlen Sie eine Option:\n\n");
        printf("output - Liste ausgeben\n");
        printf("outputr - Liste rueckwaerts ausgeben\n");
		printf("bubbleSort - Wendet den BubbleSort an der Liste an.\n");
		printf("selectSort - Wendet den SelectSort an der Liste an.\n");
		printf("deleteElement - Loescht ein gewuenschtes Element aus der Liste.\n");
        printf("deleteList - Loescht die Liste.\n");
		printf("exit - Loescht die Liste und schliesst das Programm.\n\n>");
		gets_s(input);

        if (strcmp(input, "output") == 0) {
            printf("Anzahl Elemente [0 fuer alle Elemente]: ");
            int anzahl = 0;
            scanf_s("%i", &anzahl);
            getchar();
            output(pStart, anzahl);
        } else if (strcmp(input, "outputr") == 0) {
            printf("Anzahl Elemente [0 fuer alle Elemente]: ");
            int anzahl = 0;
            scanf_s("%i", &anzahl);
            getchar();
            outputr(pStart, anzahl);
        }
		else if (strcmp(input, "bubbleSort") == 0) {
			pStart = sortListWithBubbleSort(pStart);
		}
		else if (strcmp(input, "selectSort") == 0) {
			pStart = sortListWithSelectSort(pStart);
		}
		else if (strcmp(input, "deleteElement") == 0) {
			printf("Nachname: ");
			char nachname[40];
			gets_s(nachname);
			printf("Vorname: ");
			char vorname[40];
			gets_s(vorname);
			pStart = deleteElement(pStart, vorname, nachname);
        }
        else if (strcmp(input, "deleteList") == 0) {
            deleteList(pStart);
            wiederholen = 0;
            printf("Die Liste Wurde geloescht.\n\n");
            main();
        }
		else if (strcmp(input, "exit") == 0) {
			deleteList(pStart);
			wiederholen = 0;
            system("pause");
		}
		else {
			printf("\nDie Anweisung wurde nicht gefunden.\n\n");
		}

	}

}