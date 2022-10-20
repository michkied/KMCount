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
    printf("%s\n%i\n\n", opT, opB);

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

char get_operation(FILE *fp, int startFromLine) {
    char buf[MAXLENGTH+1];
    memset(buf, '_', sizeof(buf));
    int lineNum, i;
    for (lineNum=0; fgets(buf, MAXLENGTH + 1, fp) != NULL; lineNum++) {
        if (lineNum < startFromLine) {
            continue;
        }

        if (buf[MAXLENGTH] != '_') {
            printf("ERROR 110: Input line #%i is too long", lineNum + 1);
            exit(1);
        }

        int operationBase;
        char operationType;
        int targetBase = 0;

        if (lineNum == startFromLine) {
            get_header(buf, lineNum, &operationType, &operationBase, &targetBase);
            printf("%i\n%c\n%i\n", operationBase, operationType, targetBase);
        }

        memset(buf, '_', sizeof(buf));
    }
}