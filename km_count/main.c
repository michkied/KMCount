#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include "conversions.h"


int main()
{
    char a[] = "123453563513";
    char b[] = "967886454567";

    int size = sizeof(a) / sizeof(a[0]);

    int aVal[MAXLENGTH];
    int bVal[MAXLENGTH];
    int result[MAXLENGTH];
    char resultExpression[MAXLENGTH];
    int i;
    for (i = 0; i < MAXLENGTH; i++) {
        result[i] = 0;
        resultExpression[i] = '0';
    }

    symbols_to_values(a, aVal, size);
    symbols_to_values(b, bVal, size);

    add(10, size, aVal, bVal, result);

    for (i = MAXLENGTH; i > 0; i--) {
        printf("%i. %i\n", i - 1, result[i - 1]);
    }

    values_to_symbols(result, resultExpression);

    for (i = 0; i < MAXLENGTH; i++) {
        printf("%c", resultExpression[i]);
    }
    return 0;
}