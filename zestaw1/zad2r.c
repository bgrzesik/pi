#include <stdio.h>
#include <limits.h>
#include <math.h>

/*

2. Kartka z kalendarza

Wersja podstawowa

Dane wejściowe: numer miesiąca (zestaw1 - 12), numer dnia tygodnia (od 0 - niedziela do 6 - sobota)
 w pierwszym dniu tego miesiąca, np. dla listopada będą to liczby 11 i 4.
Program powinien wyprowadzić na ekran tabelkę, np. dla listopada 2018:

Wersje rozszerzone

dane wejściowe: numer miesiąca drukowanego, numer miesiąca aktualnego i numery dnia dzisiejszego (miesiąca i tygodnia),
numer miesiąca pisany cyframi rzymskimi,
na ekranie (za numerem miesiąca) program pisze nazwa miesiąca (ew. korzysta z alfabetu polskiego),
dane wejściowe: numer miesiąca, (dane o dzisiejszym dniu - z biblioteki time.h),
program wyprowadza na ekran 12 tabelek (dla kolejnych miesięcy jednego roku),
program tworzy tabelkę w postaci transponowanej, tj.:
 */


int ndays(int month)
{
    switch (month) {
        case 1: return 31;
        case 2: return 28;
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

const char *month_name(int month)
{
    switch (month) {
        case 1: return "Styczeń";
        case 2: return "Luty";
        case 3: return "Marzec";
        case 4: return "Kwiecień";
        case 5: return "Maj";
        case 6: return "Czerwiec";
        case 7: return "Lipiec";
        case 8: return "Sierpień";
        case 9: return "Wrzesień";
        case 10: return "Październik";
        case 11: return "Listopad";
        case 12: return "Grudzień";
        default: return "Błąd";
    }
}

// nie najlepszy algorytm wczytywania liczb rzymskich
int read_roman(void)
{
    int c;
    int val = 0;
    int last = INT_MAX;

    do {
        int n = 0;

        c = getchar();

        switch (c) {
            case 'i':
            case 'I':n = 1;
                break;

            case 'v':
            case 'V':n = 5;
                break;

            case 'x':
            case 'X':n = 10;
                break;

            default:n = -1;
                break;
        }

        if (n == -1) {
            continue;
        }

        if (n > last) {
            val -= 2 * last;
            val += n;
        } else {
            val += n;
        }
        last = n;

    } while (c != '\n');

    return val;
}

const char *to_roman(int month) {
    switch (month) {
        case 1: return "I";
        case 2: return "II";
        case 3: return "III";
        case 4: return "IV";
        case 5: return "V";
        case 6: return "VI";
        case 7: return "VII";
        case 8: return "VIII";
        case 9: return "IX";
        case 10: return "X";
        case 11: return "XI";
        case 12: return "XII";
        default: return NULL;
    }
}

void print_card(int month, int offset)
{
    printf("\n%s. %s\n", to_roman(month), month_name(month));
    printf("|Ni |Po |Wt |Sr |Cz |Pt |So |");

    int a = 1;
    int days = ndays(month);

    while (a <= ceil((days + offset) / 7.0) * 7) {
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

int main(int argc, const char *argv[])
{
    int month, offset;
    printf("Podaj nr miesiąca w systemie rzymskim: ");
    month = read_roman();
    printf("Podaj nr dnia: ");
    scanf("%d", &offset);

    offset--;


    int day_year = 1;
    while (month != 1) {
        month -= 1;
        day_year += ndays(month);
    }

    offset = (7 + (day_year % 7) - offset) % 7;


    while (month <= 12) {
        print_card(month, offset);
        offset = (ndays(month) + offset) % 7;
        month += 1;
    }

}