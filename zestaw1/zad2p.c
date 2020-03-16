#include <stdio.h>
#include <math.h>
/*

2. Kartka z kalendarza

Wersja podstawowa

Dane wejściowe: numer miesiąca (zestaw1 - 12), numer dnia tygodnia (od 0 - niedziela do 6 - sobota)
 w pierwszym dniu tego miesiąca, np. dla listopada będą to liczby 11 i 4.
Program powinien wyprowadzić na ekran tabelkę, np. dla listopada 2018:
 */


int ndays(int month)
{
    switch (month) {
        case 1: return 31;
        case 2: return 29;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return -1;
    }
}

int main(int argc, const char *argv[])
{
    int month, offset;
    printf("Podaj nr miesiąca: ");
    scanf("%d", &month);
    printf("Podaj nr dnia: ");
    scanf("%d", &offset);
    offset--;

    printf("\nMiesiac %d\n", month);
    printf("|Ni |Po |Wt |Sr |Cz |Pt |So |");


    printf("\nMiesiac. %d\n", month);
    printf("|Ni |Po |Wt |Sr |Cz |Pt |So |");

    int a = 1;
    int days = ndays(month);

    while (a <= ceil(days / 7.0) * 7) {
        if ((a - 1) % 7 == 0) {
            printf("\n|");
        }

        if (a <= offset || a - offset > days) {
            printf("   |");
        } else {
            char *pad = a - offset > 9 ? "" : " ";
            printf(" %s%d|", pad, a - offset);
        }

        a++;
    }

}