#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include "conversions.h"


int main()
{
    char a[] = "12FB";
    char b[] = "7EBB";

    int aSize = sizeof(a) / sizeof(a[0]);
    int bSize = sizeof(b) / sizeof(b[0]);

    int aVal[MAXLENGTH] = { 0 };
    int bVal[MAXLENGTH] = { 0 };
    int result[MAXLENGTH] = { 0 };
    char resultExpression[MAXLENGTH];
    int i;
    for (i = 0; i < MAXLENGTH; i++) {
        resultExpression[i] = '0';
    }

    symbols_to_values(a, aVal, aSize);
    symbols_to_values(b, bVal, bSize);

    multiply(16, aVal, bVal, result);

    /*for (i = MAXLENGTH; i > 0; i--) {
        printf("%i. %i\n", i - 1, result[i - 1]);
    }*/

    values_to_symbols(result, resultExpression);

    printf("Result: ");
    for (i = 0; i < MAXLENGTH; i++) {
        printf("%c", resultExpression[i]);
    }
    return 0;
}