#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "file_handling.h"

char mathOperations[NUMBER_OF_OPERATIONS] = "+-*/^%";

int is_digit(char character) {
    char digits[10] = "0123456789";
    int i;
    for (i = 0; i < 10; i++)
        if (digits[i] == character) return 1;
    return 0;
}


void get_header(char* buf, int lineNum, char* operationType, int* operationBase, int* targetBase) {
    int i = 0;
    int opB;
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
    sscanf(buf, "%s%i", opT, &opB);

    if (opB > MAX_BASE || opB <= 1) {
        printf("\nERROR 121: Invalid operation base - %i (line #%i)\n", opB, lineNum+1);
        exit(1);
    }
    *operationBase = opB;

    for (i = 0; is_digit(opT[i]); i++) {
        *targetBase *= 10;
        *targetBase += opT[i] - '0';
        *operationType = 'b';
    }
    if (*operationType == 'b') {
        if (*targetBase > MAX_BASE || *targetBase <= 1) {
            printf("\nERROR 123: Invalid target base - %i (line #%i)\n", *targetBase, lineNum+1);
            exit(1);
        }
        return;
    }

    if (buf[1] != ' ') {
        printf("\nERROR 122: Invalid operation type (line #%i)\n", lineNum+1);
        exit(1);
    }

    for (i = 0; i < NUMBER_OF_OPERATIONS; i++) {
        if (buf[0] == mathOperations[i]) {
            *operationType = mathOperations[i];
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
    memset(buf, '_', sizeof(buf));

    for (lineNum=0; fgets(buf, MAX_LENGTH + 3, fpIn) != NULL; lineNum++) {
        fprintf(fpOut, "%s", buf);

        if (finish) return operationType;

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

        i2 = MAX_LENGTH - 1;
        if (lineNum == 4) {
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

    printf("\nERROR 111: Input format invalid (line #%i)\n", lineNum+startFromLine + 1);
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