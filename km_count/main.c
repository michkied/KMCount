#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

int main()
{
    char a[] = "F2E3F1";
    char b[] = "F478FA";

    int size = sizeof(a) / sizeof(a[0]);

    int *aVal = malloc(size);
    int *bVal = malloc(size);
    int *result[MAXLENGTH];

    symbols_to_values(a, aVal, size);
    symbols_to_values(b, bVal, size);

    add(16, size, aVal, bVal, result);
    
    return 0;
}