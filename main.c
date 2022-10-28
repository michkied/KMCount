#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"
#include "file_handling.h"


int main(int argc, char *argv[])
{
    char* filenameIn;
    char* suffix;
    char filenameOut[13];
    char correct_suffix[] = "_out.txt";
    int i, pos;
    FILE *fpIn, *fpOut;

    int aVal[MAXLENGTH] = { 0 };
    int bVal[MAXLENGTH] = { 0 };
    int result[MAXLENGTH] = { 0 };

    int startFromLine = 0;
    int base;
    char opType;

    char resultExpression[MAXLENGTH];
    char buf[MAXLENGTH+3];

    if (argc < 2) {
        printf("ERROR 100: Missing argument - input file");
        exit(1);
    }

    filenameIn = argv[1];
    suffix = strrchr(filenameIn, '_');
    if (strcmp(suffix, "_in.txt") != 0 || strlen(filenameIn) != 12) {
        printf("ERROR 101: Incorrect input file name format");
        exit(1);
    }

    fpIn = fopen(filenameIn, "r");
    if (fpIn == NULL) {
        printf("ERROR 102: Unable to open input file - %s", filenameIn);
        exit(1);
    }

    pos = (int)(suffix - filenameIn);
    for (i = 0; i < pos; i++) {
        filenameOut[i] = filenameIn[i];
    }
    while (i < 13) {
        filenameOut[i] = correct_suffix[i - 5];
        i++;
    }

    fpOut = fopen(filenameOut, "w");
    if (fpOut == NULL) {
        printf("ERROR 103: Unable to create output file - %s", filenameOut);
        exit(1);
    }

    while (1) {
        memset(resultExpression, '0', sizeof(resultExpression));
        memset(result, 0, sizeof(result));
        memset(aVal, 0, sizeof(aVal));
        memset(bVal, 0, sizeof(bVal));

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
                printf("\nSuccess!\n");
                return 0;
            }
        }
    }
}