#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

int main()
{
    char a[] = "12BC";
    char b[] = "78FD";

    int size = sizeof(a) / sizeof(a[0]);


    int *aVal = malloc(size);
    int *bVal = malloc(size);

    symbols_to_values(a, aVal, size);
    symbols_to_values(b, bVal, size);

    int answer = add(16, size, aVal, bVal);
    printf("Answer: %i", answer);
    
    return 0;
}