#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"
#include "file_handling.h"


int main()
{

    char *filename = "test.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("ERROR 100: Unable to open file '%s'", filename);
        exit(1);
    }

    int aVal[MAXLENGTH] = { 0 };
    int bVal[MAXLENGTH] = { 0 };

    int startFromLine = 0;
    int base;
    char opType;

    int result[MAXLENGTH] = { 0 };
    char resultExpression[MAXLENGTH];
    memset(resultExpression, '0', sizeof(resultExpression));

    while (1) {
        opType = get_operation(fp, startFromLine, &base, aVal, bVal);

        if (opType == 'b') {
            convert_bases(base, bVal[0], aVal);
        }

        if (opType == '+') {
            add(base, aVal, bVal, result);
        }

        if (opType == '-') {
            subtract(base, aVal, bVal, result);
        }

        if (opType == '*') {
            multiply(base, aVal, bVal, result);
        }

        if (opType == '/') {
            divide(base, aVal, bVal, result);
        }

        if (opType == '^') {
            exponentiate(base, aVal, bVal, result);
        }

        if (opType == '%') {
            mod(base, aVal, bVal, result);
        }

        break;
    }

    values_to_symbols(result, resultExpression);

    printf("Result: ");
    int i;
    for (i = 0; i < MAXLENGTH; i++) {
        printf("%c", resultExpression[i]);
    }
    return 0;
}