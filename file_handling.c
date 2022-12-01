#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "file_handling.h"

#define FILENAME_LEN 12
#define OPERATORS "+-*/^%"


int is_digit(char character) {
    char digits[10] = "0123456789";
    int i;
    for (i = 0; i < 10; i++)
        if (digits[i] == character) return 1;
    return 0;
}


void get_io_files(char* fnamePath, FILE** fpIn, FILE** fpOut) {
    unsigned int pathLen = strlen(fnamePath);
    char* fnameIn;
    char fnameOut[] = "XX_XX_out.txt";
    int i = 0;

    if (pathLen < FILENAME_LEN) {
        printf("\nERROR 101: Incorrect input file name format\n");
        exit(1);
    }
    if (pathLen != FILENAME_LEN) {
        fnameIn = strrchr(fnamePath, '/');
        if (fnameIn == NULL)
            fnameIn = strrchr(fnamePath, '\\');

        if (fnameIn == NULL || strlen(fnameIn) != FILENAME_LEN + 1) {
            printf("\nERROR 101: Incorrect input file name format\n");
            exit(1);
        }
        i++;
    }
    else {
        fnameIn = fnamePath;
    }
    fnameOut[0] = fnameIn[i];
    fnameOut[1] = fnameIn[i+1];
    fnameOut[3] = fnameIn[i+3];
    fnameOut[4] = fnameIn[i+4];

    *fpIn = fopen(fnamePath, "r");
    if (fpIn == NULL) {
        printf("\nERROR 102: Unable to open input file - %s\n", fnamePath);
        exit(1);
    }
    *fpOut = fopen(fnameOut, "w");
    if (fpOut == NULL) {
        printf("\nERROR 103: Unable to create output file - %s\n", fnameOut);
        exit(1);
    }
}


void get_header(char* buf, int lineNum, char* operationType, int* operationBase, int* targetBase) {
    int i = 0;
    int base, base2 = 0;
    char opT[MAX_LENGTH];

    while (buf[i] != '\n' && buf[i] != EOF) {
        if (buf[i] == ' ') {
            if (buf[i+1] == '\n' || buf[i+1] == EOF)
                i++;
            break;
        }
        i++;
    }
    if (buf[i] == '\n' || buf[i] == EOF) {
        printf("\nERROR 120: Invalid header format (line #%i)\n", lineNum+1);
        exit(1);
    }

    memset(opT, '_', sizeof(opT));
    sscanf(buf, "%s%i", opT, &base);

    if (base > MAX_BASE || base <= 1) {
        printf("\nERROR 121: Invalid operation base - %i (line #%i)\n", base, lineNum+1);
        exit(1);
    }

    for (i = 0; is_digit(opT[i]); i++) {
        base2 *= 10;
        base2 += opT[i] - '0';
        *operationType = 'b';
    }
    if (*operationType == 'b') {
        *targetBase = base;
        *operationBase = base2;
        if (*targetBase > MAX_BASE || *targetBase <= 1) {
            printf("\nERROR 123: Invalid target base - %i (line #%i)\n", *targetBase, lineNum+1);
            exit(1);
        }
        return;
    }
    *operationBase = base;

    if (buf[1] != ' ') {
        printf("\nERROR 122: Invalid operation type (line #%i)\n", lineNum+1);
        exit(1);
    }

    for (i = 0; i < NUMBER_OF_OPERATIONS; i++) {
        if (buf[0] == OPERATORS[i]) {
            *operationType = OPERATORS[i];
            return;
        }
    }

    printf("\nERROR 122: Invalid operation type (line #%i)\n", lineNum+1);
    exit(1);
}


char get_operation(FILE *fpIn, FILE *fpOut, int startFromLine, int *operationBase, int *aVal, int *bVal) {
    int lineNum, i, value;
    int i2 = MAX_LENGTH - 1;
    char operationType;
    int finish = 0;
    char buf[MAX_LENGTH + 3];
    int hasData = 0;
    memset(buf, '_', sizeof(buf));

    for (lineNum=0; fgets(buf, MAX_LENGTH + 3, fpIn) != NULL; lineNum++) {
        fprintf(fpOut, "%s", buf);

        if (finish) return operationType;
        if (buf[0] != '\n') hasData = 1; else continue;
        if (lineNum > 4) break;

        if (buf[MAX_LENGTH + 2] != '_') {
            printf("\nERROR 110: Input line #%i is too long\n", lineNum+startFromLine + 1);
            exit(1);
        }

        if (lineNum == 0) {
            get_header(buf, lineNum+startFromLine, &operationType, operationBase, &bVal[0]);
            continue;
        }

        if (lineNum == 2) {
            for (i = MAX_LENGTH; i >= 0; i--) {
                value = symbol_to_value(buf[i], *operationBase, lineNum+startFromLine);
                if (value == -1) continue;
                aVal[i2] = value;
                i2--;
            }
            if (operationType == 'b') {
                finish = 1;
                continue;
            }
        }

        if (lineNum == 4) {
            i2 = MAX_LENGTH - 1;
            for (i = MAX_LENGTH; i >= 0; i--) {
                value = symbol_to_value(buf[i], *operationBase, lineNum+startFromLine);
                if (value == -1) continue;
                bVal[i2] = value;
                i2--;
            }
            finish = 1;
            continue;
        }

        memset(buf, '_', sizeof(buf));
    }

    if (!hasData) {
        printf("\nSuccess!\n");
        exit(0);
    }

    printf("\nERROR 111: Input format invalid\n");
    exit(1);
}


void output_result(FILE *fpOut, char* resultExpression) {
    int i = 0;
    while (resultExpression[i] == '0')
        i++;

    if (i == MAX_LENGTH)
        fprintf(fpOut, "0");

    else
        for (i; i < MAX_LENGTH; i++)
            fprintf(fpOut, "%c", resultExpression[i]);

    fprintf(fpOut, "\n\n");
}