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
        printf("\nCRITICAL ERROR 101: Incorrect input file name format\n");
        exit(1);
    }
    if (pathLen != FILENAME_LEN) {
        fnameIn = strrchr(fnamePath, '/');
        if (fnameIn == NULL)
            fnameIn = strrchr(fnamePath, '\\');

        if (fnameIn == NULL || strlen(fnameIn) != FILENAME_LEN + 1) {
            printf("\nCRITICAL ERROR 101: Incorrect input file name format\n");
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
        printf("\nCRITICAL ERROR 102: Unable to open input file - %s\n", fnamePath);
        exit(1);
    }
    *fpOut = fopen(fnameOut, "w");
    if (fpOut == NULL) {
        printf("\nCRITICAL ERROR 103: Unable to create output file - %s\n", fnameOut);
        exit(1);
    }
}


int get_header(FILE* fpIn, FILE* fpOut, char* buf, char* operationType, int* operationBase, int* targetBase) {
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
        printf("\nCRITICAL ERROR 120: Invalid header format\n");
        exit(1);
    }

    memset(opT, '_', sizeof(opT));
    sscanf(buf, "%s%i", opT, &base);

    *operationType = *opT;
    for (i = 0; is_digit(opT[i]); i++) {
        base2 *= 10;
        base2 += opT[i] - '0';
        *operationType = 'b';
    }
    if (*operationType == 'b') {
        *targetBase = base;
        *operationBase = base2;
        if (*targetBase > MAX_BASE || *targetBase <= 1) {
            skip_lines(fpIn, fpOut, 3);
            fprintf(fpOut,"ERROR 123: Invalid target base - %i\n", *targetBase);
            return 1;
        }
        if (*operationBase > MAX_BASE || *operationBase <= 1) {
            skip_lines(fpIn, fpOut, 3);
            fprintf(fpOut,"ERROR 121: Invalid operation base - %i\n\n", *operationBase);
            return 1;
        }
        return 0;
    }

    if (base > MAX_BASE || base <= 1) {
        skip_lines(fpIn, fpOut, 5);
        fprintf(fpOut,"ERROR 121: Invalid operation base - %i\n\n", base);
        return 1;
    }
    *operationBase = base;

    if (buf[1] != ' ') {
        skip_lines(fpIn, fpOut, 5);
        fprintf(fpOut, "ERROR 122: Invalid operation type\n\n");
        return 1;
    }

    for (i = 0; i < strlen(OPERATORS); i++) {
        if (buf[0] == OPERATORS[i]) {
            *operationType = OPERATORS[i];
            return 0;
        }
    }

    skip_lines(fpIn, fpOut, 5);
    fprintf(fpOut, "ERROR 122: Invalid operation type\n\n");
    return 1;
}


char get_operation(FILE *fpIn, FILE *fpOut, int *operationBase, int *aVal, int *bVal, int errNum, int opNum) {
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
        if (lineNum > 4) break;
        if (buf[0] != '\n') hasData = 1; else continue;

        if (buf[MAX_LENGTH + 2] != '_') {
            skip_lines(fpIn, fpOut, 6-lineNum);
            fprintf(fpOut, "ERROR 110: Input line too long (max %i characters)\n\n", MAX_LENGTH);
            return 'E';
        }

        if (lineNum == 0) {
             if (get_header(fpIn, fpOut, buf, &operationType, operationBase, &bVal[0])) {
                 return 'E';
             };
            continue;
        }

        if (lineNum == 2) {
            for (i = MAX_LENGTH; i >= 0; i--) {
                value = symbol_to_value(buf[i], *operationBase);
                if (value == -1) continue;
                if (value == -2) {
                    skip_lines(fpIn, fpOut, (operationType=='b')?3-lineNum:5-lineNum);
                    fprintf(fpOut, "ERROR 130: Character %c is not valid in base %i\n\n", buf[i], *operationBase);
                    return 'E';
                }
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
                value = symbol_to_value(buf[i], *operationBase);
                if (value == -1) continue;
                if (value == -2) {
                    skip_lines(fpIn, fpOut, (operationType=='b')?3-lineNum:5-lineNum);
                    fprintf(fpOut, "ERROR 130: Character %c is not valid in base %i\n\n", buf[i], *operationBase);
                    return 'E';
                }
                bVal[i2] = value;
                i2--;
            }
            finish = 1;
            continue;
        }

        memset(buf, '_', sizeof(buf));
    }

    if (!hasData) {
        if (errNum)
            printf("\nFinished with %i non-critical error(s)\n", errNum);
        else
            printf("\nFinished with no errors\n");
        exit(0);
    }
    printf("\nCRITICAL ERROR 111: Input format invalid (operation #%i)\n", opNum);
    exit(1);
}


void output_result(FILE *fpOut, char* resultExpression) {
    int i = 0;
    while (resultExpression[i] == '0')
        i++;

    if (i == MAX_LENGTH)
        fprintf(fpOut, "0");

    else
        for (;i < MAX_LENGTH; i++)
            fprintf(fpOut, "%c", resultExpression[i]);

    fprintf(fpOut, "\n\n");
}

void skip_lines(FILE* fpIn, FILE* fpOut, int numOfLines) {
    char buf[MAX_LENGTH+3];
    for (;numOfLines > 0; numOfLines--) {
        fgets(buf, MAX_LENGTH + 3, fpIn);
        fprintf(fpOut, "%s", buf);
    }
}
