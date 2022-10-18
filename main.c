#include <stdio.h>
#include "operations.h"
#include "conversions.h"


int main()
{
    char a[] = "99999";
    char b[] = "9";

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

    multiply(10, aVal, bVal, result);

    values_to_symbols(result, resultExpression);

    printf("Result: ");
    for (i = 0; i < MAXLENGTH; i++) {
        printf("%c", resultExpression[i]);
    }
    return 0;
}