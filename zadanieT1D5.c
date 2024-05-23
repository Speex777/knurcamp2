#include <stdio.h>
#include <stdlib.h>

/*
 T1D5 - Pamiętaj bo pamięć to rzecz święta xD (pzdr bonusrpk)
 Zarządzanie pamięcią - utrwalenie
 22.05.2025


 Postępuj zgodnie z instrukcjami w komentarzach, i dopisz brakujący kod.
 Zwróć uwagę na użycie funkcji calloc i free.
 Zastanów się, dlaczego używamy calloc zamiast malloc.
 */

int main(void) {
    // Zadanie 1: Poproś użytkownika o podanie liczby elementów
    int n;
    printf("Podaj liczbe elementow: ");
    scanf("%d",&n);

    // Zadanie 2: Przydziel pamięć dynamicznie dla 'n' elementów używając calloc
    int* ptr;
    ptr = (int*)calloc(n, sizeof(int));

    // Zadanie 3: Sprawdź, czy pamięć została pomyślnie przydzielona
    if(ptr != NULL){
        printf("Poprawnie zalokowano pamięć.(%d)\n\n",n);
    }

    // Zadanie 4: Wprowadź elementy do przydzielonej pamięci
    int i,x;
    for (i = 0; i <n; ++i )
    {
        printf("Podaj element numer %d: ",i+1);
        scanf("%d",&x);
        ptr[i] = x;
    }
    // Zadanie 5: Wyświetl te elementy
    printf("\nElementy tablicy to: ");
    for (i =0;i <n;++i)
    {
        if(i == n-1)
        {
            printf("%d.\n",ptr[i]);
        }
        else
        {
            printf("%d,",ptr[i]);
        }

    }
    // Zadanie 6: Zwolnij przydzieloną pamięć

    free(ptr);
    printf("Zwolniono pamięć.");
    // +18 nie czytaj tego co jest niżej to sprawdzanie pamięci haha
    /*printf("\nrozmiar elelemtu ptr[1] to: %d, a rozmiar ptr to: %d",sizeof (ptr[1],sizeof (ptr)));
    if(ptr == NULL){
        printf("\npusto tutaj jets");
    }
    else if(ptr != NULL){
        printf("\nxxx pokazuje 5 bo pewnie to są jakieś pozostałości mi nieznane po zwolnieniu pamięci hmmm... %d",ptr[1]);
    }*/


    return 0;
}