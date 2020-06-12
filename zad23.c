//
// Created by Bartłomiej Grzesik on 12/06/2020.
//

#include <stdlib.h>

int main(int argc, const char *argv[])
{
    int sum = 0;
    while(argc-- > 1) {
        sum += (int) strtol(argv[argc], NULL, 10);
    }
    return sum;
}