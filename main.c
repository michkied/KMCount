#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"
#include "file_handling.h"


int main()
{
    char *filenameIn = "test.txt";
    FILE *fpIn = fopen(filenameIn, "r");

    if (fpIn == NULL) {
        printf("ERROR 100: Unable to open input file: %s", filenameIn);
        exit(1);
    }

    char *filenameOut = "test2.txt";
    FILE *fpOut = fopen(filenameOut, "w");

    if (fpOut == NULL) {
        printf("ERROR 300: Unable to create output file: %s", filenameOut);
        exit(1);
    }

    int aVal[MAXLENGTH] = { 0 };
    int bVal[MAXLENGTH] = { 0 };

    int startFromLine = 0;
    int base;
    char opType;

    int result[MAXLENGTH] = { 0 };
    char resultExpression[MAXLENGTH];
    char buf[MAXLENGTH+3];

    int i;
    while (1) {
        memset(resultExpression, '0', sizeof(resultExpression));
        memset(result, 0, sizeof(result));
        memset(aVal, 0, sizeof(aVal));
        memset(bVal, 0, sizeof(bVal));
        base = 0;

        opType = get_operation(fpIn, fpOut, startFromLine, &base, aVal, bVal);

        if (opType == 'b') {
            convert_bases(base, bVal[0], aVal);
            for (i = 0; i < MAXLENGTH; i++) {
                result[i] = aVal[i];
            }
            startFromLine -= 2;
        }

        else if (opType == '+') {
            add(base, aVal, bVal, result);
        }

        else if (opType == '-') {
            subtract(base, aVal, bVal, result);
        }

        else if (opType == '*') {
            multiply(base, aVal, bVal, result);
        }

        else if (opType == '/') {
            divide(base, aVal, bVal, result);
        }

        else if (opType == '^') {
            exponentiate(base, aVal, bVal, result);
        }

        else if (opType == '%') {
            mod(base, aVal, bVal, result);
        }

        values_to_symbols(result, resultExpression);
        output_result(fpOut, resultExpression);
        startFromLine += 8;

        memset(buf, '_', sizeof(buf));
        for (i = 2; i > 0; i--) {
            if (fgets(buf, MAXLENGTH + 3, fpIn) == NULL) {
                return 0;
            }
        }
    }
    return 10;
}