#include <stdio.h>
#include <stdlib.h>


/*int main(int argc, char** argv) //zadanie 1
{
    printf("lalala\n");

    return 0;
}*/

/*int main(int argc, char** argv) // zadanie 2
{
    int first_gint;
    char znak[2];
    int second_gint;
    int wynik;

    printf("podaj liczbę całkowitą: ");
    scanf("%d", &first_gint);

    printf("podaj znak * / + - : ");
    scanf("%s", znak);

    printf("Podaj 2 liczbę całkowitą: ");
    scanf("%d", &second_gint);

    if (znak[0] == '*')
    {
        wynik = first_gint * second_gint;
        printf("wynik to: %d\n",wynik);
    }

    else if (znak[0] == '/')
    {
        if(second_gint == 0) {
            printf("Nie można dzielić przez zero.");
        }
        else {
            wynik = first_gint / second_gint;
            printf("wynik to: %d\n",wynik);
        }
    }

    else if (znak[0] == '+')
    {
        wynik = first_gint + second_gint;
        printf("wynik to: %d\n",wynik);
    }
    else if (znak[0] == '-')
    {
        wynik = first_gint - second_gint;
        printf("wynik to: %d\n",wynik);
    }

    //printf("twoja liczba to: %d, twoj znak to: %s, druga liczba to: %d", first_gint,&znak, second_gint);
    return 0;

}*/

/*int main(int argc, char** argv) // zadanie 3
{
    int n;
    int first = 0; int second = 1;

    int next_stage = first + second;

    printf("Wypisuje liczby z ciągu Fibonacciego do określonej liczby.\nPodaj do jakiej liczby ma być ciąg Fibonacciego: ");
    scanf("%d", &n);

    printf("Ciag Fibonacciego: %d, %d, ",first,second);
    printf("%d, ", next_stage);

    while (next_stage <= n) {
        first = second;
        second = next_stage;
        next_stage = first + second;
        if (next_stage <= n && next_stage + first > n)
        {
            printf("%d.\n",next_stage);
        }
        else if(next_stage <=n){
            printf("%d, ", next_stage);
        }
    }
    return 0;
}*/

int main(int argc, char** argv) // zadanie 4
{
    char THE_FINALS [1024]; //statycznie przyczielona pamięc
    char first_text[500];
    char second_text[500];
    const char* text;

    printf("Podaj pierwszy tekst: ");
    scanf("%s",first_text);
    //printf("%s\n",first_text);

    printf("Podaj drugi tekst: ");
    scanf("%s",second_text);
    //printf("%s\n",&second_text);

    sprintf(THE_FINALS, "%s%s", first_text,second_text);

    printf("Tekst do zapisania to: %s\n", THE_FINALS);
    text = THE_FINALS;
    //printf(text,"\n");

    FILE* uchwyt = fopen("dupa.txt", "w");
    if (uchwyt == NULL)
    {
        printf("Błąd otwarcia pliku!\n");
        return 1;
    }
    fprintf(uchwyt,"%s\n",text);
    fclose(uchwyt);
    printf("Dodano tekst do pliku dupa! Yeeey!");

    return 0;
}
