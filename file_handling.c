#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "file_handling.h"

char mathOperations[NUMBER_OF_OPERATIONS] = "+-*/^%";

int is_digit(char character) {
    char digits[10] = "0123456789";
    int i;
    for (i = 0; i < 10; i++) {
        if (digits[i] == character) {
            return 1;
        }
    }
    return 0;
}


void get_header(char* buf, int lineNum, char* operationType, int* operationBase, int* targetBase) {
    int i = 0;
    while (buf[i] != '\n' && buf[i] != EOF) {
        if (buf[i] == ' ') {
            if (buf[i+1] == '\n' || buf[i+1] == EOF) {
                i++;
            }
            break;
        }
        i++;
    }
    if (buf[i] == '\n' || buf[i] == EOF) {
        printf("ERROR 120: Invalid header format (line #%i)", lineNum+1);
        exit(1);
    }

    int opB;
    char opT[MAXLENGTH];
    memset(opT, '_', sizeof(opT));
    sscanf(buf, "%s%i", opT, &opB);

    if (opB > MAXBASE || opB <= 1) {
        printf("ERROR 121: Invalid operation base (line #%i)", lineNum+1);
        exit(1);
    }
    *operationBase = opB;

    for (i = 0; is_digit(opT[i]); i++) {
        *targetBase *= 10;
        *targetBase += opT[i] - '0';
    }
    if (*targetBase) {
        if (*targetBase > MAXBASE || *targetBase <= 1) {
            printf("ERROR 123: Invalid target base (line #%i)", lineNum+1);
            exit(1);
        }
        *operationType = 'b';
        return;
    }

    if (buf[1] != ' ') {
        printf("ERROR 122: Invalid operation type (line #%i)", lineNum+1);
        exit(1);
    }

    for (i = 0; i < NUMBER_OF_OPERATIONS; i++) {
        if (buf[0] == mathOperations[i]) {
            *operationType = mathOperations[i];
            return;
        }
    }

    printf("ERROR 122: Invalid operation type (line #%i)", lineNum+1);
    exit(1);
}


char get_operation(FILE *fp, int startFromLine, int *operationBase, int *aVal, int *bVal) {
    int lineNum, i, value;
    int i2 = MAXLENGTH-1;
    char operationType;
    char buf[MAXLENGTH+3];
    memset(buf, '_', sizeof(buf));

    for (lineNum=0; fgets(buf, MAXLENGTH + 3, fp) != NULL; lineNum++) {
        if (lineNum < startFromLine) {
            continue;
        }

        if (buf[MAXLENGTH+2] != '_') {
            printf("ERROR 110: Input line #%i is too long", lineNum+startFromLine + 1);
            exit(1);
        }

        if (lineNum == startFromLine) {
            get_header(buf, lineNum+startFromLine, &operationType, operationBase, &bVal[0]);
            continue;
        }

        if (lineNum == startFromLine+2) {
            for (i = MAXLENGTH; i >= 0; i--) {
                value = symbol_to_value(buf[i], *operationBase, lineNum+startFromLine);
                if (value == -1) {
                    continue;
                }
                aVal[i2] = value;
                i2--;
            }
        }

        if (operationType == 'b') {
            return operationType;
        }

        i2 = MAXLENGTH-1;
        if (lineNum == startFromLine+4) {
            for (i = MAXLENGTH; i >= 0; i--) {
                value = symbol_to_value(buf[i], *operationBase, lineNum+startFromLine);
                if (value == -1) {
                    continue;
                }
                bVal[i2] = value;
                i2--;
            }
            return operationType;
        }

        memset(buf, '_', sizeof(buf));
    }
    return operationType;
}