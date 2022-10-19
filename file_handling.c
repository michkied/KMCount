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

int get_target_base(char* buf, int lineNum) {
    int i2 = 0;
    int targetBase = buf[i2] - '0';
    i2++;

    while (buf[i2] != ' ') {
        targetBase *= 10;
        targetBase += buf[i2] - '0';
        i2++;
    }

    if (targetBase > MAXBASE || targetBase <= 1) {
        printf("ERROR 123: Invalid target base (line #%i)", lineNum+1);
        exit(1);
    }

    return targetBase;
}

int get_operation_base(char* buf, int lineNum, int separatorPosition) {
    int i = separatorPosition+1;
    int operationBase = buf[i] - '0';
    i++;

    while (buf[i] != '\n') {
        if (!is_digit(buf[i])) {
            printf("ERROR 121: Invalid operation base (line #%i)", lineNum+1);
            exit(1);
        }

        operationBase *= 10;
        operationBase += buf[i] - '0';
        i++;
    }

    if (operationBase > MAXBASE || operationBase <= 1) {
        printf("ERROR 121: Invalid operation base (line #%i)", lineNum+1);
        exit(1);
    }

    return operationBase;
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

    int separatorPosition = i;
    *operationBase = get_operation_base(buf, lineNum, separatorPosition);

    if (is_digit(buf[0])) {
        *targetBase = get_target_base(buf, lineNum);
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
        int targetBase;

        if (lineNum == startFromLine) {
            get_header(buf, lineNum, &operationType, &operationBase, &targetBase);
            printf("%i\n%c\n%i\n", operationBase, operationType, targetBase);
        }

        memset(buf, '_', sizeof(buf));
    }
}