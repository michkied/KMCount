#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"
#include "file_handling.h"


int main(int argc, char *argv[]) {
    char *filenameIn;
    char filenameOut[] = "km_XX_out.txt";
    int i;
    FILE *fpIn, *fpOut;
    int aVal[MAX_LENGTH] = { 0 };
    int bVal[MAX_LENGTH] = { 0 };
    int result[MAX_LENGTH] = { 0 };
    int lineNum = 0;
    int base;
    char opType;
    char resultExpression[MAX_LENGTH];
    char buf[MAX_LENGTH + 3];

    if (argc < 2) {
        printf("\nERROR 100: Missing argument - input file\n");
        exit(1);
    }

    filenameIn = argv[1];
    if (strlen(filenameIn) != 12) {
        printf("\nERROR 101: Incorrect input file name format\n");
        exit(1);
    }

    fpIn = fopen(filenameIn, "r");
    if (fpIn == NULL) {
        printf("\nERROR 102: Unable to open input file - %s\n", filenameIn);
        exit(1);
    }

    filenameOut[3] = filenameIn[3];
    filenameOut[4] = filenameIn[4];

    fpOut = fopen(filenameOut, "w");
    if (fpOut == NULL) {
        printf("\nERROR 103: Unable to create output file - %s\n", filenameOut);
        exit(1);
    }

    while (1) {
        memset(resultExpression, '0', sizeof(resultExpression));
        memset(result, 0, sizeof(result));
        memset(aVal, 0, sizeof(aVal));
        memset(bVal, 0, sizeof(bVal));

        opType = get_operation(fpIn, fpOut, lineNum, &base, aVal, bVal);

        if (opType == 'b') {
            convert_bases(base, bVal[0], aVal);
            for (i = 0; i < MAX_LENGTH; i++)
                result[i] = aVal[i];
            lineNum -= 2;
        }

        else if (opType == '+')
            add(base, aVal, bVal, result);

        else if (opType == '-')
            subtract(base, aVal, bVal, result);

        else if (opType == '*')
            multiply(base, aVal, bVal, result);

        else if (opType == '/')
            divide(base, aVal, bVal, result);

        else if (opType == '^')
            exponentiate(base, aVal, bVal, result);

        else if (opType == '%')
            mod(base, aVal, bVal, result);

        values_to_symbols(result, resultExpression);
        output_result(fpOut, resultExpression);
        lineNum += 8;

        memset(buf, '_', sizeof(buf));
        for (i = 2; i > 0; i--) {
            if (fgets(buf, MAX_LENGTH + 3, fpIn) == NULL) {
                printf("\nSuccess!\n");
                return 0;
            }
        }
    }
}