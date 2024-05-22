#include <stdio.h>
#include <stdbool.h>

/*
 Zaimplementuj ciało funkcji isPrime która zwróci true jeśli podany int §num§ jest liczba pierwszą.
 Zwróć false w przeciwnym wypadku.
 */

bool isPrime(int num) {
    int n = 200; // liczy do jakiej liczby będzie maksymalnie sprawdzać.
    int x = 0; // licznik potrzebny do dzielenia który maksymalnie osiągnie wartość n.
    int c = 0; // licznik który sprawdza przez ile liczb da się podaną liczbę podzielić jeśli jest więcej niż 2 to nie jest liczba Prime.

    for (int i = 1; i <= n; ++i)
    {
        x +=1;
        if(num % x == 0){
            c +=1;
            printf("dodano 1 do c, aktualnie c wynosi: %d.\n",c);
            if (c>2){
                return false;
            }
        }
    }
    return true;
}

void selfTest(void) {
    printf("Self-checking code:\n");
    printf("Test 1: %s\n", isPrime(2) ? "POPRAWNY" : "NIEPRAWIDŁOWY");
    printf("Test 2: %s\n", isPrime(11) ? "POPRAWNY" : "NIEPRAWIDŁOWY");
    printf("Test 3: %s\n", isPrime(99) ?  "NIEPRAWIDŁOWY" : "POPRAWNY");
    printf("Test 4: %s\n", isPrime(97) ? "POPRAWNY" : "NIEPRAWIDŁOWY");
}

int main(void) {
    int num;
    printf("Podaj liczbe: ");
    scanf("%d", &num);

    if (isPrime(num)) {
        printf("%d jest liczba pierwsza.\n", num);
    } else {
        printf("%d nie jest liczba pierwsza.\n", num);
    }

    // Run the self-checking code
    selfTest();

    return 0;
}