#include <stdio.h>

/*
 T1D6
 BOMBELKOWE SORTOWANIE NA WSKAZNIKACH HEHE
 Powodzenia bombelku, napisz ciało funkcji sortujPrzezWskazniki.
 Aby spełniała swoje zadanie i posortowała liczby rosnąco.
 */

void sortujPrzezWskazniki(int *tab, int rozmiar) {
    // miejsce na rozwiązanie
    int i;
    int j;
    int t;
    for (i = 0; i < rozmiar; i++)
    {
        for (j = i + 1;j < rozmiar; j++)
        {
            if (*(tab + j) < *(tab + i))
            {
                t = *(tab + i);
                *(tab + i) = *(tab + j);
                *(tab + j) = t;
                printf("\niteracja i = %d, j = %d :   ",i,j);
                for (int i = 0; i < rozmiar; i++) {
                    if (i == rozmiar - 1) {
                        printf("%d... ", tab[i]);
                    } else {
                        printf("%d, ", tab[i]);
                    }
                }
                if(i == rozmiar-2)
                {
                    printf("\n\nKoniec iteracji i wynosi rozmiar-1 (%d). \n",rozmiar-2);
                }

            }
        }
    }
}


int main() {
    int liczby[] = {34, 67, 23, 28, 98, 15};
    int rozmiar = sizeof(liczby) / sizeof(liczby[0]);

    printf("Tablica przed sortowaniem: \n");
    for (int i = 0; i < rozmiar; i++) {
        printf("%d ", liczby[i]);
    }
    printf("\n");

    sortujPrzezWskazniki(liczby, rozmiar);

    printf("Tablica po sortowaniu: \n");
    for (int i = 0; i < rozmiar; i++) {
        printf("%d ", liczby[i]);
    }
    printf("\n");

    return 0;
}