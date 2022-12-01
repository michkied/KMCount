#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"
#include "file_handling.h"

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
    FILE *fpIn, *fpOut;
    int aVal[MAX_LENGTH] = { 0 };
    int bVal[MAX_LENGTH] = { 0 };
    int result[MAX_LENGTH] = { 0 };
    char resultExpression[MAX_LENGTH];
    char buf[MAX_LENGTH + 3];
    int lineNum = 0, base, i;
    char opType;

    if (argc < 2) {
        printf("\nERROR 100: Missing argument - input file\n");
        exit(1);
    }

    get_io_files(argv[1], &fpIn, &fpOut);

    do {
        memset(resultExpression, '0', sizeof(resultExpression));
        memset(result, 0, sizeof(result));
        memset(aVal, 0, sizeof(aVal));
        memset(bVal, 0, sizeof(bVal));

        opType = get_operation(fpIn, fpOut, lineNum, &base, aVal, bVal);

        switch (opType) {
            case 'b':
                convert_bases(base, bVal[0], aVal);
                for (i = 0; i < MAX_LENGTH; i++)
                    result[i] = aVal[i];
                lineNum -= 2;

            case '+':
                add(base, aVal, bVal, result);

            case '-':
                subtract(base, aVal, bVal, result);

            case '*' :
                multiply(base, aVal, bVal, result);

            case '/' :
                divide(base, aVal, bVal, result);

            case '^' :
                exponentiate(base, aVal, bVal, result);

            case '%' :
                mod(base, aVal, bVal, result);
        }

        values_to_symbols(result, resultExpression);
        output_result(fpOut, resultExpression);
        lineNum += 8;
        memset(buf, '_', sizeof(buf));

    } while (!is_done(buf, fpIn));

    printf("\nSuccess!\n");
    return 0;
}