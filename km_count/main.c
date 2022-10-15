#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include "conversions.h"


int main()
{
    char a[] = "111111111111";
    char b[] = "0F0000000000";

    int size = sizeof(a) / sizeof(a[0]);

    int aVal[MAXLENGTH] = { 0 };
    int bVal[MAXLENGTH] = { 0 };
    int result[MAXLENGTH] = { 0 };
    char resultExpression[MAXLENGTH];
    int i;
    for (i = 0; i < MAXLENGTH; i++) {
        resultExpression[i] = '0';
    }

    symbols_to_values(a, aVal, size);
    symbols_to_values(b, bVal, size);

    /*exponentiate(16, size, aVal, bVal, result);*/

    convert_bases(16, 8, aVal);

    /*for (i = MAXLENGTH; i > 0; i--) {
        printf("%i. %i\n", i - 1, result[i - 1]);
    }*/

    values_to_symbols(aVal, resultExpression);

    printf("Result: ");
    for (i = 0; i < MAXLENGTH; i++) {
        printf("%c", resultExpression[i]);
    }
    return 0;
}