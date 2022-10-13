#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

int main()
{
    char a[] = "6432453";
    char b[] = "5345237";

    int size = sizeof(a) / sizeof(a[0]);

    int aVal[MAXLENGTH];
    int bVal[MAXLENGTH];
    int result[MAXLENGTH];
    int i;
    for (i = 0; i < MAXLENGTH; i++) {
        result[i] = 0;
    }

    symbols_to_values(a, aVal, size);
    symbols_to_values(b, bVal, size);

    add(8, size, aVal, bVal, result);

    for (i = MAXLENGTH; i > 0; i--) {
        printf("%i. %i\n", i - 1, result[i - 1]);
    }

    char resultExpression[MAXLENGTH];
    values_to_symbols(result, resultExpression);

    for (i = 0; i > MAXLENGTH; i++) {
        printf("%i. %c\n", i, resultExpression[i]);
    }
    
    return 0;
}