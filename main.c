#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"
#include "file_handling.h"


int main()
{

    char *filename = "test.txt";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("ERROR 100: Unable to open file '%s'", filename);
        exit(1);
    }

    char a[MAXLENGTH];
    char b[MAXLENGTH];
    memset(a, '0', sizeof(a));
    memset(b, '0', sizeof(b));

    int startFromLine = 0;

    while (1) {
        char operationType = get_operation(fp, startFromLine);


        memset(a, '0', sizeof(a));
        memset(b, '0', sizeof(b));
        break;
    }

    int aSize = sizeof(a) / sizeof(a[0]);
    int bSize = sizeof(b) / sizeof(b[0]);

    int aVal[MAXLENGTH] = { 0 };
    int bVal[MAXLENGTH] = { 0 };
    int result[MAXLENGTH] = { 0 };
    char resultExpression[MAXLENGTH];
    int i;
    for (i = 0; i < MAXLENGTH; i++) {
        resultExpression[i] = '0';
    }

    symbols_to_values(a, aVal, aSize);
    symbols_to_values(b, bVal, bSize);

//    multiply(10, aVal, bVal, result);


    values_to_symbols(result, resultExpression);

    printf("Result: ");
    for (i = 0; i < MAXLENGTH; i++) {
        printf("%c", resultExpression[i]);
    }
    return 0;
}