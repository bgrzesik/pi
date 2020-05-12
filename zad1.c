#include <stdio.h>

/*
Zadanie zestaw1.
Proszę samodzielnie napisać program, który metodą bąbelkową sortuje elementy tablicy n elementowej.
 */
void bubble_sort(int *arr, int n)
{
    for (int i = 1; i < n; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    int arr[] = { 1, 3, 2, 5, 6, -1, 0, 10 };
    size_t n = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d, ", arr[i]);
    }
    printf("\n");

    return 0;
}
