#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"
#include "file_handling.h"
#define FILENAME_LEN 12

int is_done(char*, FILE*);

int is_done(char* buf, FILE* fpIn) {
    int i;
    for (i = 2; i > 0; i--) {
        if (fgets(buf, MAX_LENGTH + 3, fpIn) == NULL) {
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    char *filenamePath, *filenameIn;
    char filenameOut[] = "XX_XX_out.txt";
    unsigned int pathLen;
    int i = 0;
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

    filenamePath = argv[1];
    pathLen = (unsigned int) strlen(filenamePath);
    if (pathLen < FILENAME_LEN) {
        printf("\nERROR 101: Incorrect input file name format\n");
        exit(1);
    }
    if (pathLen != FILENAME_LEN) {
        filenameIn = strrchr(filenamePath, '/');
        if (filenameIn == NULL)
            filenameIn = strrchr(filenamePath, '\\');

        if (filenameIn == NULL || strlen(filenameIn) != FILENAME_LEN+1) {
            printf("\nERROR 101: Incorrect input file name format\n");
            exit(1);
        }
        i++;
    }
    else {
        filenameIn = filenamePath;
    }
    filenameOut[0] = filenameIn[i];
    filenameOut[1] = filenameIn[i+1];
    filenameOut[3] = filenameIn[i+3];
    filenameOut[4] = filenameIn[i+4];

    fpIn = fopen(filenamePath, "r");
    if (fpIn == NULL) {
        printf("\nERROR 102: Unable to open input file - %s\n", filenamePath);
        exit(1);
    }
    fpOut = fopen(filenameOut, "w");
    if (fpOut == NULL) {
        printf("\nERROR 103: Unable to create output file - %s\n", filenameOut);
        exit(1);
    }

    do {
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
    } while (!is_done(buf, fpIn));

    printf("\nSuccess!\n");
    return 0;
}